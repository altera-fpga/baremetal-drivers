/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_mbox_client.c
 *
 * SDM Mailbox source implementation for the SoCFPGA bare-metal software stack.
 */

/*
 * This driver implements the APIs required to access the SDM mailbox.
 * The sip_svc subsystem provides a set of APIs to interact with the
 * Secure Monitor Call (SMC) interface in the Arm Trusted Firmware (ATF).
 * This set of  APIs allow the application to send commands to the ATF
 * which in turn performs a variety of mailbox commands such as reading hardware
 * monitor values, cryptographic operations etc.
 *
 * The below diagram shows how this driver interacts with the ATF and the hardware
 *
 *                          +---------------------------------------------+
 *                          |                 FreeRTOS                    |
 *                          | +----------------------------------------+  |
 *                          | |  Client Application (RSU, FCS, SEU)    |  |
 *                          | +-------------------^--------------------+  |
 *                          |                     |                       |
 *                          |                     v                       |
 *                          |            +------------------+             |
 *                          |            |     sip_svc      |             |
 *                          |            |  +------------+  |             |
 *                          |            |  | Mailbox    |  |             |
 *                          |            |  |  Client    |  |             |
 *                          |            |  +------------+  |             |
 *                          |            |         |        |             |
 *                          |            |         v        |             |
 *                          |            |  +------------+  |             |
 *                          |            |  | Mailbox    |  |             |
 *                          |            |  |  Service   |  |             |
 *                          |            |  +------------+  |             |
 *                          |            +------------------+             |
 *                          +---------------------^-----------------------+
 *                                                |
 *                                                |
 * +----------------------------------------------v------------------------------------+
 * |                                            EL3                                    |
 * | +-----------------------+  +-----------------------+  +-------------------------+ |
 * | | Poll Mailbox Response |  | Get Response Trans ID |  | Mailbox Cmd Function ID | |
 * | +-----------------------+  +-----------------------+  +-------------------------+ |
 * |               |                                                    |              |
 * |               +-------------------------+---------------------------              |
 * |                                         v                                         |
 * |                            +---------------------------+                          |
 * |                            |     SDM Mailbox           |                          |
 * |                            |  +---------------------+  |                          |
 * |                            |  | Poll Mailbox Resp   |  |                          |
 * |                            |  +---------------------+  |                          |
 * |                            |  | Send Mailbox Cmd    |  |                          |
 * |                            |  +---------------------+  |                          |
 * |                            +---------------------------+                          |
 * +--------------------------------^---------------------------|----------------------+
 *                                  |                           |
 *                                  |                           |
 *                           +------|---------------------------v---------+
 *                           |                Hardware                    |
 *                           |                  SDM                       |
 *                           |  +----------------+  +-------------------+ |
 *                           |  | Response FIFO  |  |  Command FIFO     | |
 *                           |  +----------------+  +-------------------+ |
 *                           +--------------------------------------------+
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "socfpga_sip_handler.h"
#include "socfpga_mbox_client.h"
#include "socfpga_interrupt.h"
#include "cache.h"
#include "mmio.h"

#define MAX_CLIENT_INSTANCES       16U
#define MAX_JOB_ID                 16U
#define JOB_POOL_FULL              0xFFFFU
#define SIP_SMC_GET_RESP           0x420000C8U
#define SIP_SMC_GET_TRANS_ID       0x420000C9U
/*
 * V1 sync mailbox SiP (INTEL_SIP_SMC_MBOX_SEND_CMD). Used by mbox_send_command()
 * so generic SDM opcodes bypass ATF's V3 GEN_MBOX default-deny allowlist.
 * Dedicated SiP services (for example FCS) still go through sip_svc_send().
 */
#define SIP_SMC_MBOX_SEND_CMD      0xC200003CU
#define SIP_SMC_STATUS_OK          0
#define SIP_SMC_STATUS_ERROR       4

#define FORMAT_TRANS_ID(cid, jid) \
    ((((uint64_t)(cid) & 0xFU) << 4) | (((uint64_t)(jid) & 0xFU)))
#define GET_CLIENT_ID(trans_id)    ((trans_id) & 0xF0U) >> 4
#define GET_JOB_ID(trans_id)       ((trans_id) & 0xFU)
#define ATF_CLIENT_ID       1U
#define MBOX_TASK_CLOSED    0U
#define MBOX_TASK_OPEN      1U
#define MBOX_TASK_BUSY      2U

#define OSAL_STATUS_FAIL    0
#define OSAL_STATUS_OK      1

/* =========================
 * Baremetal primitives
 * ========================= */
typedef struct {
    int locked;
} baremetal_mutex_t;

typedef struct {
    int count;
} baremetal_semaphore_t;

/* =========================
 * Static semaphore pool
 * ========================= */
#define MAX_SEMAPHORES 8

static baremetal_semaphore_t sem_pool[MAX_SEMAPHORES];
static int sem_index;

/* =========================
 * Mutex stubs
 * ========================= */
baremetal_mutex_t osal_mutex_create(void *unused)
{
    (void)unused;
    baremetal_mutex_t m;
    m.locked = 0;
    return m;
}

int osal_mutex_unlock(baremetal_mutex_t m)
{
    (void)m;
    return OSAL_STATUS_OK;
}

int osal_mutex_delete(baremetal_mutex_t m)
{
    (void)m;
    return OSAL_STATUS_OK;
}

/* =========================
 * Semaphore stubs
 * ========================= */
baremetal_semaphore_t *osal_semaphore_create(void *unused)
{
    (void)unused;

    if (sem_index >= MAX_SEMAPHORES)
        return NULL;

    sem_pool[sem_index].count = 0;
    return &sem_pool[sem_index++];
}

int osal_semaphore_post(baremetal_semaphore_t *sem)
{
    if (!sem)
        return OSAL_STATUS_FAIL;

    sem->count = 1;
    return OSAL_STATUS_OK;
}

int osal_semaphore_delete(baremetal_semaphore_t *sem)
{
    (void)sem;
    return OSAL_STATUS_OK;
}

typedef struct {
    baremetal_mutex_t       client_mutex;
    baremetal_semaphore_t *client_free;

} mbox_client_descriptor_t;





typedef struct
{
    uint64_t *resp_data;
    uint64_t resp_len;
} job_id_resp_map;
struct sdm_client_descriptor
{
    uint16_t job_pool;
    uint8_t job_head;
    uint8_t client_status;
    mbox_call_back_t call_back;
	uint8_t client_mutex;
	uint8_t client_free;
    job_id_resp_map job_resp[MAX_JOB_ID];
};
struct sdm_mbox_descriptor
{
    uint8_t client_list_mutex;
    uint8_t call_complete_sem;
    uint8_t task_state;
};

static struct sdm_mbox_descriptor static_mbox_desc;
static struct sdm_mbox_descriptor *mbox_descriptor = NULL;
static struct sdm_client_descriptor client_descriptors[MAX_CLIENT_INSTANCES];

/* Process-wide shared client for single-threaded bare-metal examples/drivers. */
static sdm_client_handle g_shared_client = NULL;

void mbox_poll_resp_task(void *param);

void mbox_irq_handler(void *param);

static uint8_t assign_job_id(sdm_client_handle mbox_handle)
{
    uint8_t i = 0;
    if ((mbox_handle == NULL) || (mbox_handle->job_pool == (JOB_POOL_FULL)))
    {
        printf("ERROR: Maximum allowed jobs running");
        return 0xFFU;
    }

	i = mbox_handle->job_head;
	/*Find free job_id*/
	while (((mbox_handle->job_pool) & (((uint16_t)0x1U << i))) != 0U)
	{
		i++;
		i %= MAX_JOB_ID;
	}
	mbox_handle->job_pool |= ((uint16_t)1U << i);
	mbox_handle->job_head = (i + 1U) % MAX_JOB_ID;
	if (0)
	{
		printf("ERROR: Failed to unlock mutex\n");
		return 0xFFU;
	}

    return i;
}

static int8_t free_job_id(uint8_t client_id, uint8_t job_id)
{
    sdm_client_handle mbox_handle = &client_descriptors[client_id];
    if ((mbox_handle == NULL) || (mbox_handle->job_pool == 0U))
    {
        return -EIO;
    }

	mbox_handle->job_pool ^= ((uint16_t)1U << job_id);
	if (false)
	{
		printf("ERROR: Failed to unlock mutex\n");
		return -EIO;
	}

    return 0;
}

void mbox_poll_resp_task(void *param)
{
    (void)param;

    sdm_client_handle mbox_handle;
    uint64_t bitmask[SMC_CALL_REG_COUNT], smc_args[SMC_CALL_REG_COUNT];
    uint8_t trans_id, i, j;
    uint8_t client_id, job_id;
    int ret;
    cache_force_write_back(smc_args, sizeof(smc_args));
    cache_force_invalidate(smc_args, sizeof(smc_args));
    for ( ;;)
    {

		if (mbox_descriptor->task_state == MBOX_TASK_CLOSED)
		{
			break;
		}
		/* response is available to poll */
		(void)memset(bitmask, 0, sizeof(bitmask));
		(void)memset(smc_args, 0, sizeof(smc_args));
		ret = smc_call(SIP_SMC_GET_TRANS_ID, bitmask);
		if (ret == 0)
		{
			printf("INFO: Transaction ID bitmasks:\r\n"
					"bitmask[0]: %lx\r\n"
					"bitmask[1]: %lx\r\n"
					"bitmask[2]: %lx\r\n"
					"bitmask[3]: %lx", bitmask[0], bitmask[1], bitmask[2],
					bitmask[3]);
			/* Finding the transaction id corresponding to the response */
			for (i = 0U; i < 4U; i++)
			{
				/*
				 * Transaction Id is obtained as follows from the bit mask
				 *
				 * trans_id = (i * 64) + j;
				 * Where i is the bitmask which contains the response
				 * j is the bit in the bitmask which is high
				 */
				j = 0U;
				while (bitmask[i] != 0UL)
				{
					trans_id = (i * 64U);
					/* 64 bits to process */
					while (j < 64U)
					{
						if (((bitmask[i] >> j) & 1UL) == 1UL)
						{
							break;
						}
						j++;
					}
					trans_id += j;
					/* Setting the bit as 0 to show its been processed */
					bitmask[i] = bitmask[i] & ~((uint64_t)1 << j);
					client_id = GET_CLIENT_ID(trans_id);
					if (client_id == ATF_CLIENT_ID)
					{
						/* Ignoring any transactions belonging to ATF */
						continue;
					}
					mbox_handle = &client_descriptors[client_id];
					job_id = GET_JOB_ID(trans_id);
					smc_args[0] = trans_id;
					printf("INFO: Polling response, transaction ID: %x", trans_id);

					ret = smc_call(SIP_SMC_GET_RESP, smc_args);
					if (ret != 0)
					{
						(void)memset(smc_args, 0, sizeof(smc_args));
						printf("ERROR: Failed to poll response\n");
						continue;
					}
					if ((mbox_handle->job_resp[job_id].resp_data != NULL) &&
							(mbox_handle->job_resp[job_id].resp_len != 0UL))
					{
						(void)memcpy(
								mbox_handle->job_resp[job_id].resp_data,
								smc_args,
								mbox_handle->job_resp[job_id].resp_len);
					}
					if (free_job_id(client_id, job_id) != 0)
					{
						printf("ERROR: Failed to free job id\n");
						continue;
					}
					if (client_descriptors[client_id].call_back != NULL)
					{
						client_descriptors[client_id].call_back(smc_args);
					}
					//        false)
					if (false)
					{
						printf("ERROR: Failed to post semaphore\n");
					}
				}
			}
		}
        mbox_descriptor->task_state = MBOX_TASK_OPEN;
    }
}

sdm_client_handle mbox_open_client(void)
{
    uint8_t i;
    sdm_client_handle obtained = NULL;

	for (i = 2U; i < MAX_CLIENT_INSTANCES; i++)
	{
		if (client_descriptors[i].client_status == 0U)
		{
			client_descriptors[i].client_status = 1;
			obtained = &client_descriptors[i];
			printf("MBOX client #%u opened, handle=%p\n", i, (void *)obtained);
			//        false)
			if (false)
			{
				printf("ERROR: Failed to post semaphore\n");
				return NULL;
			}
			break;
		}
	}
	if (false)
	{
		printf("ERROR: Failed to unlock mutex\n");
		return NULL;
	}

    return obtained;
}

int32_t mbox_close_client(sdm_client_handle mbox_handle)
{
    if ((mbox_handle == NULL) || (mbox_handle->client_status == 0U))
    {
        return -EINVAL;
    }
    /*
     * Baremetal has no OSAL completion waiter, so async jobs can remain
     * marked in job_pool after sip_svc_send(). Drop them so the client
     * can be released and mbox_deinit() is not blocked.
     */
    mbox_handle->job_pool = 0;
    mbox_handle->job_head = 0;
    mbox_handle->client_status = 0;
	if (false)
	{
		printf("ERROR: Failed to delete semaphore\n");
		return -EIO;
	}
	(void)memset(mbox_handle->job_resp, 0,
			sizeof(mbox_handle->job_resp));
	if (false)
	{
		printf("ERROR: Failed to unlock mutex\n");
		return -EIO;
	}

	if (false)
	{
		printf("ERROR: Failed to unlock mutex\n");
		return -EIO;
	}
	if (false)
	{
		printf("ERROR: Failed to delete mutex\n");
		return -EIO;
	}

    return 0;
}

sdm_client_handle mbox_client_acquire(void)
{
    if (g_shared_client != NULL)
    {
        return g_shared_client;
    }

    if (mbox_init() != 0)
    {
        printf("ERROR: Failed to initialise mailbox for shared client\n");
        return NULL;
    }

    g_shared_client = mbox_open_client();
    if (g_shared_client == NULL)
    {
        printf("ERROR: Failed to open shared MBOX client\n");
    }

    return g_shared_client;
}

void mbox_client_release(void)
{
    /*
     * Keep the shared client open so the next example/driver can reuse it.
     * Closing here reintroduces the open/close lifetime issues this API avoids.
     */
}

int32_t mbox_send_command(sdm_client_handle mbox_handle, uint32_t command,
        uint32_t *command_args, uint32_t arg_size,
        uint32_t *resp, uint32_t resp_size,
        uint64_t *smc_resp, uint32_t smc_resp_len)
{
    uint64_t smc_args[SMC_CALL_REG_COUNT] = { 0 };
    int sip_status;
    uint32_t arg_words = 0U;
    uint32_t resp_words = 0U;

    if (mbox_handle == NULL)
    {
        return -EINVAL;
    }

    if (((arg_size % 4U) != 0U) || ((resp_size % 4U) != 0U))
    {
        /* Mailbox arguments should be multiples of 4 bytes */
        printf("ERROR: Invalid size. Not multiple of 4 bytes\n");
        return -EINVAL;
    }

    if ((command_args != NULL) && (arg_size != 0U))
    {
        arg_words = arg_size / 4U;
        cache_force_write_back(command_args, arg_size);
    }
    if ((resp != NULL) && (resp_size != 0U))
    {
        resp_words = resp_size / 4U;
        cache_force_invalidate(resp, resp_size);
    }

    /*
     * V1 ABI (smc_call register_val[] -> X1..X6):
     *   [0] opcode, [1] cmd buf, [2] cmd words, [3] urgent,
     *   [4] resp buf, [5] resp words
     * Returns: X0=SiP status, X1=SDM err, X2=resp words written.
     */
    smc_args[0] = command;
    smc_args[1] = (uint64_t)(uintptr_t)command_args;
    smc_args[2] = arg_words;
    smc_args[3] = 0U;
    smc_args[4] = (uint64_t)(uintptr_t)resp;
    smc_args[5] = resp_words;

    sip_status = smc_call(SIP_SMC_MBOX_SEND_CMD, smc_args);
    if (sip_status != SIP_SMC_STATUS_OK)
    {
        if ((sip_status == SIP_SMC_STATUS_ERROR) && (smc_args[0] != 0UL))
        {
            printf("ERROR: SDM mbox cmd 0x%x rejected (err=0x%lx)\n",
                   command, (unsigned long)smc_args[0]);
        }
        else
        {
            printf("ERROR: SiP MBOX_SEND_CMD rejected (status=%d)\n",
                   sip_status);
        }
        return -EIO;
    }

    if (smc_args[0] != 0UL)
    {
        printf("ERROR: SDM mbox cmd 0x%x failed (err=0x%lx)\n",
               command, (unsigned long)smc_args[0]);
        return -EIO;
    }

    if ((resp != NULL) && (resp_size != 0U))
    {
        cache_force_invalidate(resp, resp_size);
    }

    if ((smc_resp != NULL) && (smc_resp_len != 0U))
    {
        smc_resp[0] = smc_args[0];
        if (smc_resp_len > 1U)
        {
            smc_resp[1] = smc_args[1];
        }
    }

    return 0;
}

int32_t sip_svc_send(sdm_client_handle mbox_handle, uint64_t smc_func_id,
        uint64_t *mbox_args, uint32_t arg_len, uint64_t *resp_data,
        uint32_t resp_len)
{
    uint64_t smc_values[SMC_CALL_REG_COUNT] =
    {
        0
    };
    uint8_t client_id = 0xFFU, job_id, i;
    int ret = 0;

    if ((mbox_handle == NULL) || (mbox_handle->client_status == 0U) ||
            ((mbox_args != NULL) && (arg_len == 0U)) ||
            ((mbox_args == NULL) && (arg_len != 0U)))
    {
        return -EIO;
    }
    else
    {
        /* Since ATF uses client ID 1 we start from 2 */
        for (i = 2; i < MAX_CLIENT_INSTANCES; i++)
        {
            if (memcmp((const void *)mbox_handle, (const
                    void *)&client_descriptors[i],
                    sizeof(client_descriptors[i])) == 0)
            {
                client_id = i;
                break;
            }
        }
        if (client_id == 0xFFU)
        {
            printf("ERROR: Failed to find client\n");
            return -EIO;
        }
    }
    if (mbox_handle->call_back == NULL)
    {
        printf("INFO: No callback registered\n");
    }

	job_id = assign_job_id(mbox_handle);
	if (job_id >= MAX_JOB_ID)
	{
		printf("ERROR: Failed to assign job id\n");
		return -EIO;
	}
	mbox_handle->job_resp[job_id].resp_data = resp_data;
	mbox_handle->job_resp[job_id].resp_len = resp_len;

	smc_values[0] = FORMAT_TRANS_ID(client_id, job_id);
	if (mbox_args != NULL)
	{
		(void)memcpy(&smc_values[1], mbox_args, arg_len);
	}

	ret = smc_call(smc_func_id, smc_values);

	if ((resp_data == NULL) || (resp_len == 0U) || (ret != 0))
	{
		/* No response so immediately release semaphore and free the job id */
		if (free_job_id(client_id, job_id) != 0)
		{
			printf("ERROR: Failed to free job id\n");
			return -EIO;
		}
		if(false)
		{
			printf("ERROR: Failed to post semaphore\n");
			return -EIO;
		}
		if (ret != 0)
		{
			ret = -ret;
		}
	}
	if(false)
	{
		printf("ERROR: Failed to unlock mutex\n");
		return -EIO;
	}

    return ret;
}

int32_t mbox_set_callback(sdm_client_handle mbox_handle,
        mbox_call_back_t callback)
{
    if (mbox_handle == NULL)
    {
        return -EIO;
    }
    else
    {
        /*callback can also be NULL*/
        mbox_handle->call_back = callback;

        if(false)
        {
            printf("ERROR: Failed to unlock mutex\n");
            return -EIO;
        }
    }
    return 0;
}
int mbox_init(void)
{
    if (mbox_descriptor == NULL)
    {
        mbox_descriptor = &static_mbox_desc;
        memset(mbox_descriptor, 0, sizeof(struct sdm_mbox_descriptor));
        mbox_descriptor->task_state = MBOX_TASK_OPEN;
    }
    else
    {
        printf("INFO: Mailbox already initialised\n");
    }
    return 0;
}

int mbox_deinit(void)
{
    unsigned int i;
    if (mbox_descriptor == NULL)
    {
        printf("ERROR: Mailbox not initialised\n");
        return -EIO;
    }
    if (mbox_descriptor->task_state == MBOX_TASK_CLOSED)
    {
        printf("ERROR: Task not initialised\n");
        return -EIO;
    }
    if (mbox_descriptor->task_state == MBOX_TASK_BUSY)
    {
        printf("ERROR: Task is performing some function, cannot close\n");
        return -EIO;
    }
    for (i = 2U; i < MAX_CLIENT_INSTANCES; i++)
    {
        /* Check if any clients are opened */
        if (client_descriptors[i].client_status == 1U)
        {
            printf("ERROR: Clients #%u is still open, aborting mbox_deinit\n", i);
            return -EIO;
        }
    }

    /* Signal completion */
    mbox_descriptor->task_state = MBOX_TASK_CLOSED;
    if(false)
    {
        printf("ERROR: Failed to post semaphore\n");
        return -EIO;
    }
    if (false)
    {
        printf("ERROR: Failed to delete mutex\n");
        return -EIO;
    }
    if(false)
    {
        printf("ERROR: Failed to delete semaphore\n");
        return -EIO;
    }

    (void)memset(mbox_descriptor, 0, sizeof(struct sdm_mbox_descriptor));
    mbox_descriptor = NULL;

    return 0;
}

/*
 * mbox_poll_once - single-iteration response drain.
 *
 * Calls SIP_SMC_GET_TRANS_ID once to drain the S2C MCSR ring and obtain
 * the bitmap of newly-ready (client_id, job_id) pairs.  For every set bit
 * calls SIP_SMC_GET_RESP to consume the response (which triggers the ATF
 * sip_smc_ret_nbytes_cb callback that writes the SDM payload into the
 * DDR buffer registered during send).
 *
 * Returns the number of responses successfully processed (0 = none ready yet).
 */
int mbox_poll_once(void)
{
    uint64_t bitmask[SMC_CALL_REG_COUNT];
    uint64_t smc_args[SMC_CALL_REG_COUNT];
    uint8_t trans_id, i, j;
    uint8_t client_id, job_id;
    int ret;
    int n_processed = 0;

    memset(bitmask, 0, sizeof(bitmask));

    /* SIP_SMC_GET_TRANS_ID: drains S2C ring, returns XOR-bitmap of newly-ready trans_ids */
    ret = smc_call(SIP_SMC_GET_TRANS_ID, bitmask);
    if (ret != 0) {
        return 0;   /* no new responses */
    }

    for (i = 0U; i < 4U; i++) {
        j = 0U;
        while (bitmask[i] != 0UL) {
            while (j < 64U) {
                if (((bitmask[i] >> j) & 1UL) == 1UL) {
                    break;
                }
                j++;
            }

            trans_id = (uint8_t)((i * 64U) + j);
            bitmask[i] &= ~((uint64_t)1U << j);

            client_id = (uint8_t)GET_CLIENT_ID(trans_id);
            if (client_id == ATF_CLIENT_ID) {
                continue;   /* ATF-internal transaction  skip */
            }

            job_id = (uint8_t)GET_JOB_ID(trans_id);
            sdm_client_handle mbox_handle = &client_descriptors[client_id];

            /* SIP_SMC_GET_RESP: consume response; ATF callback writes payload to DDR */
            memset(smc_args, 0, sizeof(smc_args));
            smc_args[0] = trans_id;     /* x1 = (client_id<<4)|job_id */
            ret = smc_call(SIP_SMC_GET_RESP, smc_args);
            if (ret != 0) {
                continue;
            }

            /* Copy ATF SMC return values (status/err_code/nbytes) if requested */
            if ((mbox_handle->job_resp[job_id].resp_data != NULL) &&
                    (mbox_handle->job_resp[job_id].resp_len != 0UL)) {
                (void)memcpy(mbox_handle->job_resp[job_id].resp_data,
                             smc_args,
                             mbox_handle->job_resp[job_id].resp_len);
            }

            (void)free_job_id(client_id, job_id);

            if (client_descriptors[client_id].call_back != NULL) {
                client_descriptors[client_id].call_back(smc_args);
            }

            n_processed++;
        }
    }

    return n_processed;
}

void mbox_irq_handler(void *param)
{
    (void)param;
    /*
     * Disable the interrupt as the interrupt keeps getting triggered
     * while a response is available
     */

    mbox_descriptor->task_state = MBOX_TASK_BUSY;
    if(false)
    {
        printf("ERROR: Failed to post semaphore\n");
    }
}
