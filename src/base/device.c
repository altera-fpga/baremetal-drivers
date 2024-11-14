#include "device.h"
#include <stddef.h>

bool claim_device(device_descriptor_t *device) {
    bool return_value = false;
    if (device == nullptr) {
        return_value = false;
    } else if (device->acquired) {
        return_value = false;
    } else {
        device->acquired = true;
        return_value = true;
    }
    return return_value;
}