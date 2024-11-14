#include "qspi.h"
#include "device.h"
#include "qspi_internal.h"
#include "qspi_regs.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

device_descriptor_t qspi_devices[] = {{.name = "/dev/qspi0", .fd = QSPI_BASE, .acquired = 0}};

int32_t qspi_open(const char *path, int32_t flags) {
    int32_t return_value = -1;
    if (path != nullptr) {
        for (uint32_t i = 0; i < (sizeof(qspi_devices) / sizeof(device_descriptor_t)); i++) {
            if (strcmp(qspi_devices[i].name, path) == 0) {
                if (claim_device(&qspi_devices[i])) {
                    return_value = qspi_devices[i].fd;
                } else {
                    return_value = -1;
                }
            }
        }
    }
    return return_value;
}
int32_t qspi_close(int32_t fd) {
    int32_t return_value = -1;
    if (fd != -1) {
        for (uint32_t i = 0; i < (sizeof(qspi_devices) / sizeof(device_descriptor_t)); i++) {
            if (qspi_devices[i].fd == fd) {
                qspi_devices[i].acquired = 0;
                return_value = 0;
                break;
            }
        }
    }
    return return_value;
}
size_t qspi_read(int32_t fd, uintptr_t buf, size_t size) { return qspi_recv(fd, buf, size, 0); }
size_t qspi_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    return qspi_recv_internal(fd, buf, size, flags);
}
size_t qspi_write(int32_t fd, uintptr_t buf, size_t size) { return qspi_send(fd, buf, size, 0); }
size_t qspi_send(int32_t fd, uintptr_t buf, size_t size, int32_t flags) {
    return qspi_send_internal(fd, buf, size, flags);
}
int32_t qspi_ioctl(int32_t fd, int32_t operation, uintptr_t arg, size_t length) {
    int32_t return_value = -1;
    if ((fd == -1) || (((void *)(arg)) == nullptr)) {
        return_value = -1;
    } else {
        switch ((qspi_ioctl_t)operation) {
        case IOCTL_QSPI_REGS_READ:
            return_value = qspi_read_regs(fd, arg, length);
            break;
        case IOCTL_QSPI_REGS_WRITE:
            return_value = qspi_write_regs(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_SET:
            return_value = qspi_set_cfg_reg(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_GET:
            return_value = qspi_get_cfg_reg(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_BAUD_RATE_DIV_SET:
            return_value = qspi_set_baud_rate_div(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_BAUD_RATE_DIV_GET:
            return_value = qspi_get_baud_rate_div(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_ENABLE_SET:
            return_value = qspi_set_enable(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_ENABLE_GET:
            return_value = qspi_get_enable(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CLKPOL_SET:
            return_value = qspi_set_clkpol(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CLKPOL_GET:
            return_value = qspi_get_cklpol(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CLKPHASE_SET:
            return_value = qspi_set_clkphase(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CLKPHASE_GET:
            return_value = qspi_get_clkphase(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CS_DECODE_SET:
            return_value = qspi_set_cs_decode(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CS_DECODE_GET:
            return_value = qspi_get_cs_decode(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CS_SET:
            return_value = qspi_set_cs(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_CS_GET:
            return_value = qspi_get_cs(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_WRITE_PROTECT_PIN_SET:
            return_value = qspi_set_write_protect_pin(fd, arg, length);
            break;
        case IOCTL_QSPI_CFG_WRITE_PROTECT_PIN_GET:
            return_value = qspi_get_write_protect_pin(fd, arg, length);
            break;
        case IOCTL_QSPI_READ_PARAMS_SET:
            return_value = qspi_set_read_params(fd, arg, length);
            break;
        case IOCTL_QSPI_READ_PARAMS_GET:
            return_value = qspi_get_read_params(fd, arg, length);
            break;
        case IOCTL_QSPI_WRITE_PARAMS_SET:
            return_value = qspi_set_write_params(fd, arg, length);
            break;
        case IOCTL_QSPI_WRITE_PARAMS_GET:
            return_value = qspi_get_write_params(fd, arg, length);
            break;
        case IOCTL_QSPI_CS_DELAYS_SET:
            return_value = qspi_set_cs_delays(fd, arg, length);
            break;
        case IOCTL_QSPI_CS_DELAYS_GET:
            return_value = qspi_get_cs_delays(fd, arg, length);
            break;
        case IOCTL_QSPI_READ_DATA_CAPTURE_DLY_SET:
            return_value = qspi_set_read_data_capture_dly(fd, arg, length);
            break;
        case IOCTL_QSPI_READ_DATA_CAPTURE_DLY_GET:
            return_value = qspi_get_read_data_capture_dly(fd, arg, length);
            break;
        case IOCTL_QSPI_DEVICE_SIZE_PARAMS_SET:
            return_value = qspi_set_device_size_params(fd, arg, length);
            break;
        case IOCTL_QSPI_DEVICE_SIZE_PARAMS_GET:
            return_value = qspi_get_device_size_params(fd, arg, length);
            break;
        case IOCTL_QSPI_INDIRECT_ADDR_SPAN_SET:
            return_value = qspi_set_indirect_addr_span(fd, arg, length);
            break;
        case IOCTL_QSPI_INDIRECT_ADDR_SPAN_GET:
            return_value = qspi_get_indirect_addr_span(fd, arg, length);
            break;
        case IOCTL_QSPI_INDIRECT_BASE_ADDR_SET:
            return_value = qspi_set_indirect_base_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_INDIRECT_BASE_ADDR_GET:
            return_value = qspi_get_indirect_base_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_DMA_CFG_SET:
            return_value = qspi_set_dma_cfg(fd, arg, length);
            break;
        case IOCTL_QSPI_DMA_CFG_GET:
            return_value = qspi_get_dma_cfg(fd, arg, length);
            break;
        case IOCTL_QSPI_REMAP_ADDR_SET:
            return_value = qspi_set_remap_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_REMAP_ADDR_GET:
            return_value = qspi_get_remap_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_MODE_BITS_SET:
            return_value = qspi_set_mode_bits(fd, arg, length);
            break;
        case IOCTL_QSPI_MODE_BITS_GET:
            return_value = qspi_get_mode_bits(fd, arg, length);
            break;
        case IOCTL_QSPI_SRAM_FILL_LEVEL_GET:
            return_value = qspi_get_sram_fill_lvl(fd, arg, length);
            break;
        case IOCTL_QSPI_TX_THRESHOLD_SET:
            return_value = qspi_set_irq_txthresh(fd, arg, length);
            break;
        case IOCTL_QSPI_TX_THRESHOLD_GET:
            return_value = qspi_get_irq_txthresh(fd, arg, length);
            break;
        case IOCTL_QSPI_RX_THRESHOLD_SET:
            return_value = qspi_set_irq_rxthresh(fd, arg, length);
            break;
        case IOCTL_QSPI_RX_THRESHOLD_GET:
            return_value = qspi_get_irq_rxthresh(fd, arg, length);
            break;
        case IOCTL_QSPI_IRQ_STAT_GET:
            return_value = qspi_get_irqstat(fd, arg, length);
            break;
        case IOCTL_QSPI_IRQ_STAT_SET:
            return_value = qspi_set_irqstat(fd, arg, length);
            break;
        case IOCTL_QSPI_IRQ_MASK_GET:
            return_value = qspi_get_irqmask(fd, arg, length);
            break;
        case IOCTL_QSPI_IRQ_MASK_SET:
            return_value = qspi_set_irqmask(fd, arg, length);
            break;
        case IOCTL_QSPI_WRPROT_SET:
            return_value = qspi_set_wrprot(fd, arg, length);
            break;
        case IOCTL_QSPI_WRPROT_GET:
            return_value = qspi_get_wrprot(fd, arg, length);
            break;
        case IOCTL_QSPI_WRPROT_LOW_SET:
            return_value = qspi_set_wrprot_low(fd, arg, length);
            break;
        case IOCTL_QSPI_WRPROT_LOW_GET:
            return_value = qspi_get_wrprot_low(fd, arg, length);
            break;
        case IOCTL_QSPI_WRPROT_HI_SET:
            return_value = qspi_set_wrprot_high(fd, arg, length);
            break;
        case IOCTL_QSPI_WRPROT_HI_GET:
            return_value = qspi_get_wrprot_high(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_SET:
            return_value = qspi_set_indirect_read(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_GET:
            return_value = qspi_get_indirect_read(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_WATERMARK_SET:
            return_value = qspi_set_indirect_rd_watermark(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_WATERMARK_GET:
            return_value = qspi_get_indirect_rd_watermark(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_START_ADDR_SET:
            return_value = qspi_set_indirect_rd_start_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_START_ADDR_GET:
            return_value = qspi_get_indirect_rd_start_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_COUNT_SET:
            return_value = qspi_set_indirect_rd_count(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_RD_COUNT_GET:
            return_value = qspi_get_indirect_rd_count(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_SET:
            return_value = qspi_set_indirect_write(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_GET:
            return_value = qspi_get_indirect_write(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_WATERMARK_SET:
            return_value = qspi_set_indirect_wr_watermark(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_WATERMARK_GET:
            return_value = qspi_get_indirect_wr_watermark(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_START_ADDR_SET:
            return_value = qspi_set_indirect_wr_start_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_START_ADDR_GET:
            return_value = qspi_get_indirect_wr_start_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_COUNT_SET:
            return_value = qspi_set_indirect_wr_count(fd, arg, length);
            break;
        case IOCTL_QSPI_IND_WR_COUNT_GET:
            return_value = qspi_get_indirect_wr_count(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_SET:
            return_value = qspi_set_flash_cmd(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_GET:
            return_value = qspi_get_flash_cmd(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_ADDR_SET:
            return_value = qspi_set_flash_cmd_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_ADDR_GET:
            return_value = qspi_get_flash_cmd_addr(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_READ_DATA_GET:
            return_value = qspi_get_flash_cmd_rd_data(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_WRITE_DATA_SET:
            return_value = qspi_set_flash_cmd_wr_data(fd, arg, length);
            break;
        case IOCTL_QSPI_FLASH_CMD_WRITE_DATA_GET:
            return_value = qspi_get_flash_cmd_wr_data(fd, arg, length);
            break;
        case IOCTL_QSPI_MODULE_ID_GET:
            return_value = qspi_get_module_id(fd, arg, length);
            break;
        default:
            return_value = -1;
            break;
        }
    }
    return return_value;
};

int32_t qspi_error(int32_t fd) { return 0; }