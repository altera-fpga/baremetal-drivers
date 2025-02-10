#ifndef DEVICE_H__
#define DEVICE_H__

#include <stdbool.h>
#include <stdint.h>

#include "hps_address_map.h"

typedef struct {
    const char *name;
    int32_t fd;
    bool acquired;
} device_descriptor_t;

bool claim_device(device_descriptor_t *device);

#endif // DEVICE_H__