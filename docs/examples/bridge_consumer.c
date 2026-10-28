#include <stddef.h>
#include <stdint.h>
#include "errno.h"
#include "bridge_api.h"

/* Store route metadata only: no bridge enable and no memory access. */
int bridge_route_example(uint64_t fabric_base, uint64_t fabric_size)
{
    bridge_handle_t handle;
    bridge_api_route_t route;
    int32_t rc;
    int32_t close_rc;

    handle = bridge_api_open(BRIDGE_API_HPS2FPGA);
    if (handle == NULL) {
        return -EINVAL;
    }
    route.direction = BRIDGE_API_DIR_HPS_TO_FPGA;
    route.base_addr = fabric_base;
    route.window_size = fabric_size;
    rc = bridge_api_set_route(handle, &route);
    close_rc = bridge_api_close_handle(handle);
    return rc != 0 ? (int)rc : (int)close_rc;
}
