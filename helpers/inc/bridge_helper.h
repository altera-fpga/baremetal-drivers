#ifndef BRIDGE_HELPER_H__
#define BRIDGE_HELPER_H__

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int32_t bridge_enable(int32_t fd, int32_t timer_handle, int32_t sysmgr_handle);
int32_t bridge_disable(int32_t fd, int32_t timer_handle, int32_t sysmgr_handle);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // BRIDGE_HELPER_H__