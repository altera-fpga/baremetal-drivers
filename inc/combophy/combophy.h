#ifndef COMBOPHY_H__
#define COMBOPHY_H__

#include <stddef.h>
#include <stdint.h>

// IOCTL commands for getting and setting combophy registers
typedef enum {
    IOCTL_COMBOPHY_READ_REGS,
    IOCTL_COMBOPHY_WRITE_REGS,
    IOCTL_COMBOPHY_GET_DQ_TIMING,
    IOCTL_COMBOPHY_SET_DQ_TIMING,
    IOCTL_COMBOPHY_GET_DQS_TIMING,
    IOCTL_COMBOPHY_SET_DQS_TIMING,
    IOCTL_COMBOPHY_GET_GATE_LPBK_CTRL,
    IOCTL_COMBOPHY_SET_GATE_LPBK_CTRL,
    IOCTL_COMBOPHY_GET_DLL_MASTER_CTRL,
    IOCTL_COMBOPHY_SET_DLL_MASTER_CTRL,
    IOCTL_COMBOPHY_GET_DLL_SLAVE_CTRL,
    IOCTL_COMBOPHY_SET_DLL_SLAVE_CTRL,
    IOCTL_COMBOPHY_GET_IE_TIMING,
    IOCTL_COMBOPHY_SET_IE_TIMING,
    IOCTL_COMBOPHY_GET_OBS_REG_0,
    IOCTL_COMBOPHY_GET_DLL_OBS_REG0,
    IOCTL_COMBOPHY_GET_DLL_OBS_REG1,
    IOCTL_COMBOPHY_GET_DLL_OBS_REG2,
    IOCTL_COMBOPHY_GET_STATIC_TOGG,
    IOCTL_COMBOPHY_SET_STATIC_TOGG,
    IOCTL_COMBOPHY_GET_WR_DESKEW,
    IOCTL_COMBOPHY_SET_WR_DESKEW,
    IOCTL_COMBOPHY_GET_WR_RD_DESKEW_CMD,
    IOCTL_COMBOPHY_SET_WR_RD_DESKEW_CMD,
    IOCTL_COMBOPHY_GET_WR_DESKEW_PD_CTRL0,
    IOCTL_COMBOPHY_SET_WR_DESKEW_PD_CTRL0,
    IOCTL_COMBOPHY_GET_WR_DESKEW_PD_CTRL1,
    IOCTL_COMBOPHY_SET_WR_DESKEW_PD_CTRL1,
    IOCTL_COMBOPHY_GET_RD_DESKEW,
    IOCTL_COMBOPHY_SET_RD_DESKEW,
    IOCTL_COMBOPHY_GET_VERSION,
    IOCTL_COMBOPHY_GET_FEATURES,
    IOCTL_COMBOPHY_GET_CTRL,
    IOCTL_COMBOPHY_SET_CTRL,
    IOCTL_COMBOPHY_GET_TSEL,
    IOCTL_COMBOPHY_SET_TSEL,
    IOCTL_COMBOPHY_END,
} combophy_ioctl_t;

int32_t combophy_open(const char *path, int32_t flags);
int32_t combophy_close(int32_t base_add);
size_t combophy_read(int32_t base_add, uintptr_t user_data, size_t length);
size_t combophy_recv(int32_t base_add, uintptr_t user_data, size_t length, int32_t flags);
size_t combophy_write(int32_t base_add, uintptr_t user_data, size_t length);
size_t combophy_send(int32_t base_add, uintptr_t user_data, size_t size, int32_t flags);
int32_t combophy_ioctl(int32_t base_add, int32_t operation, uintptr_t user_data, size_t length);
int32_t combophy_error(int32_t base_add);

#endif // COMBOPHY_H
