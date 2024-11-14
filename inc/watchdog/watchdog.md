# WATCHDOG TIMER

This driver provides access to Watchdog Timer's (WDT). The reset behavior upon watchdog expiry is managed by the SDM. See the register map for more details "https://www.intel.com/content/www/us/en/programmable/hps/agilex5/hps.html#topics/addressblock_Watchdog_timer_summary.html"

## Accessing WDT
### Opening WDT
To gain access to the WDT the user must first successfully open the device via "watchdog_open" passing a valid device file
  Device File Example: "/dev/watchdog#" # equals a value from 0 - 4
#### watchdog_open return options:
##### A.) If access is granted the user will retrieve a valid base address via the open command.
##### B.) If access is denied the watchdog_open will return "-1"

### Closing WDT
To close/remove a users access to a WDT successful closing of previously access must occur. To close a previously opened WDT the user must pass a valid base address to
the "watchdog_close(base address)" method.
#### watchdog_close(base address) return options:
##### A.) The watchdog_close method will return 0 if succcessful
##### B.) The watchdog_close method will return -1 if not successful

## IOCTL Register Access
### IOCTL_WDT_GET_ENABLE & IOCTL_WDT_SET_ENABLE
Read and Set the enable bit of watchdog contro register

### IOCTL_WDT_GET_RMOD & IOCTL_WDT_SET_RMOD
Read or set the watchdog timer's response mode

### IOCTL_WDT_GET_RESET_PULSE & IOCTL_WDT_SET_RESET_PULSE
Read or Set the number of pclock cycles of which system reset will remain asserted

### IOCTL_WDT_GET_TOP & IOCTL_WDT_SET_TOP
Read or Set the time out period for watchdog counter

### IOCTL_WDT_GET_TOP_INIT & IOCTL_WDT_SET_TOP_INIT
Read or Set the initial time out period for watchdog counter

### IOCTL_WDT_GET_CCRV_STATUS
Read the current internal counter value

### IOCTL_WDT_SET_COUNTER_RESTART
Restart the WDT "only 0x76 is valid reset value"

### IOCTL_WDT_GET_INTERRUPT_STATUS
Read the status of the watchdog timer interrupt

### IOCTL_WDT_GET_CLEAR_INTERRUPT
Read to watchdog timer intterupt to clear it

### IOCTL_WDT_GET_COUNT_WIDTH
Read counter width from components parameter register "read only value equals 0x10"

### IOCTL_WDT_GET_DFLT_TOP_INIT
Read Default initial time out period from components parameter register "read only value equals 0x0F"

### IOCTL_WDT_GET_DFLT_TOP
Read Default time out period from components parameter register "read only value equals 0x0F"	

### IOCTL_WDT_GET_DFLT_RST_PULSE_WIDTH
Read default reset pulse width from components parameter register "read only value is 0x4"

### IOCTL_WDT_GET_APB_DATA_WIDTH
Read default APB data width value from components parameter register

### IOCTL_WDT_GET_PAUSE_STATE
Read default watchdog timer pause enable value

### IOCTL_WDT_GET_FIX_TOP_STATE
Read the fixed time out period state "1 = predefined, 0 = userdefined"

### IOCTL_WDT_GET_HDCODE_TOP_STATE
Read if the watchdog has hardcoded timeout period or programmable "1 = hardcoded, 0 = programmable"

### IOCTL_WDT_GET_HDCODE_RST_PULSE_STATE
Read if the watchdog has hardcoded reset pulse width or programmable "1 = hardcoded, 0 = programmable"

### IOCTL_WDT_GET_HDCODE_RSP_MODE_STATE
Read if the watchdog has hardcoded response mode or programmable "1 = hardcoded, 0 = programmable"

### IOCTL_WDT_GET_DUAL_TOP
Read if dual time out period is set or not "1 = enabled, 0 = disabled"

### IOCTL_WDT_GET_DFLT_RSP_MODE
Read if default response mode is enabled or disabled "1 = enabled, 0 = disabled"

### IOCTL_WDT_GET_ALWAYS_ENABLE_STATE
Read if watchdog timer is always enabled or not " 1 = always enabled, 0 = not always enabled"

### IOCTL_WDT_GET_GET_COMP_VERSION
Read watchdog timer component version "value = 0x3130382A"

### IOCTL_WDT_GET_GET_COMP_TYPE
Read watchdog timer component type "value = 0x44570120"
