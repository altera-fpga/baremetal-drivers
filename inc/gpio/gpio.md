# GPIO

The general purpose IO driver allows control of GPIO pins. The read/recv, write/send, and error APIs are unused and will return default values if called.

Provides control of GPIO pins via the following IOCTLs:

### IOCTL_GPIO_SET_DIRECTION & IOCTL_GPIO_GET_DIRECTION
Sets and gets, as appropriate, the direction registers.

### IOCTL_GPIO_SET_VALUE & IOCTL_GPIO_GET_VALUE
Sets and gets, as appropriate, the value of the GPIO pin.

### IOCTL_GPIO_SET_INTERRUPT_TYPE & IOCTL_GPIO_GET_INTERRUPT_TYPE
Sets and gets, as appropriate, the interrupt type for the GPIO pin.

### IOCTL_GPIO_SET_INTERRUPT_MASK & IOCTL_GPIO_GET_INTERRUPT_MASK
Sets and gets, as appropriate, the interrupt mask for the GPIO pin bank.

### IOCTL_GPIO_SET_INTERRUPT_ENABLE & IOCTL_GPIO_GET_INTERRUPT_ENABLE
Sets and gets, as appropriate, the interrupt enable bits for the GPIO pin bank.

### IOCTL_GPIO_SET_INTERRUPT_POLARITY & IOCTL_GPIO_GET_INTERRUPT_POLARITY
Sets and gets, as appropriate, the interrupt polarity for the bank.

### IOCTL_GPIO_GET_INTERRUPT_STATUS & IOCTL_GPIO_GET_INTERRUPT_STATUS_RAW
Gets the interrupt status and raw interrupt status, as appropriate, for the bank. The interrupt status accounts for the mask setting. The raw status does not account for the mask.

### IOCTL_GPIO_SET_DEBOUNCE & IOCTL_GPIO_GET_DEBOUNCE
Sets and gets, as appropriate, the pin debounce setting.

### IOCTL_GPIO_GET_SYNC & IOCTL_GPIO_SET_SYNC
Sets and gets, as appropriate, the sync settings for each pin in the bank.

### IOCTL_GPIO_GET_ID
Returns the ID register value for the GPIO IP. This is hardware defined.

### IOCTL_GPIO_GET_VERSION
Returns the version register value for the GPIO IP. This is hardware defined.

### IOCTL_GPIO_GET_CONFIG
Returns the config regsister value for the GPIO IP. This is hardware defined.