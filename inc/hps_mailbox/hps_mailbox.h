#ifndef HPS_MAILBOX_H__
#define HPS_MAILBOX_H__

#include <stddef.h>
#include <stdint.h>

// IOCTL commands for getting and setting HPS mailbox registers
enum {
    // Commands to read data from HPS mailbox
    IOCTL_MBOX_CMD_GET_STATUS = 0,
    IOCTL_MBOX_CMD_GET_RBUF_VAL,
    IOCTL_MBOX_CMD_GET_CBUF_VAL,
    IOCTL_MBOX_CMD_GET_HPS_DBELL,
    IOCTL_MBOX_CMD_GET_SDM_DBELL,
    IOCTL_MBOX_CMD_GET_CIN_OFST,
    IOCTL_MBOX_CMD_GET_ROUT_OFST,
    IOCTL_MBOX_CMD_GET_RIN_OFST,
    IOCTL_MBOX_CMD_GET_COUT_OFST,
    IOCTL_MBOX_CMD_GET_INT_FLAG,
    IOCTL_MBOX_CMD_GET_URG,

    // Commands to Write to elements of HPS mailbox
    IOCTL_MBOX_CMD_SET_RBUF_VAL,
    IOCTL_MBOX_CMD_SET_CBUF_VAL,
    IOCTL_MBOX_CMD_SET_CIN_VAL,
    IOCTL_MBOX_CMD_SET_ROUT_VAL,
    IOCTL_MBOX_CMD_SET_COUT_VAL,
    IOCTL_MBOX_CMD_SET_RIN_VAL,
    IOCTL_MBOX_CMD_SET_COE_FLAG,
    IOCTL_MBOX_CMD_SET_RIE_FLAG,
    IOCTL_MBOX_CMD_SET_UAE_FLAG,
    IOCTL_MBOX_CMD_SET_DBELL_TOSDM,
    IOCTL_MBOX_CMD_SET_DBELL_TOHPS,

    // RESET HPS MAILBOX
    IOCTL_MBOX_CMD_RESET_HPS_MBOX,

    // Easy Increment Methods
    IOCTL_MBOX_CMD_INC_CIN_ADDR,
    IOCTL_MBOX_CMD_INC_COUT_ADDR,
    IOCTL_MBOX_CMD_INC_RIN_ADDR,
    IOCTL_MBOX_CMD_INC_ROUT_ADDR,

    // HPS MAILBOX IOCTL END
    IOCTL_MBOX_END
};
// Method foot print

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      hps_mbox_recv
 * description:
 *      return 0
 */
size_t hps_mbox_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags);

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      hps_mbox_read
 * description:
 *      return 0
 */
size_t hps_mbox_read(int32_t fd, uintptr_t buf, size_t size);

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      hps_mbox_send
 * description:
 *      return 0
 */
size_t hps_mbox_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags);

/*
 * Common Driver Methods "Spec Requirement"
 * name:
 *      hps_mbox_write
 * description:
 *      return 0
 */
size_t hps_mbox_write(int32_t fd, const uintptr_t buf, size_t size);

/* name: hps_mbox_open
 * description: attempt to open the device noted by device name
 * parameters(s): path "string name of device"
 *                flags "currently unused"
 */
int32_t hps_mbox_open(const char *path, int32_t flags);

/* name: hps_mbox_close
 * description: close the fd via the base address of the device
 * parameters(s): base_add "address of the hps mailbox device open"
 */
int32_t hps_mbox_close(int32_t base_add);

/* name: hps_mbox_ioctl
 * description: process the input output control command
 * parameters(s): base_add "address of the hps mailbox device open"
 *                operation "specific ioctl command for hps mailbox"
 *                user_data "address of the data or buffer to be filled with data"
 *                length "expected length of the register to be read or written to
 */
int32_t hps_mbox_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length);

#endif // HPS_MAILBOX_H__
