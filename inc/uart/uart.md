# Universal Asynchronous Receive Transmit

This driver provides access to a 16550 compliant UART. The read/recv API receives from the IP's FIFO buffer and write/send push data into the IP's fifo buffer.

Configuration of the UART is done through the associated IOCTLs:

### IOCTL_UART_BAUD_RATE_DIVSIOR_GET & IOCTL_UART_BAUD_RATE_DIVISOR_SET
Gets or sets as appropriate the baud rate divisor to set the baud rate.

### IOCTL_UART_INTERRUPT_ENABLE_GET & IOCTL_UART_INTERRUPT_ENABLE_SET
Gets or sets as appropriate the interrupt enable for the UART

### IOCTL_UART_INTERRUPT_STATUS_GET
Gets the current interrupt status

### IOCTL_UART_LINE_CONTROL_GET & IOCTL_UART_LINE_CONTROL_SET
Gets or sets as appropriate the UART line control value.

### IOCTL_UART_MODEM_CONTROL_GET & IOCTL_UART_MODEM_CONTROL_SET
Gets or sets as appropriate the UART modem control value

### IOCTL_UART_LINE_STATUS_GET
Gets the current line status

### IOCTL_UART_MODEM_STATUS_GET
Gets the current modem status

### IOCTL_UART_SCRATCH_GET & IOCTL_UART_SCRATCH_SET
Gets or sets the UART IP's scratch register

### IOCTL_UART_SHADOW_RECEIVE_BUFFER_GET
Gets the UART shadow receive buffer

### IOCTL_UART_FIFO_ACCESS_GET & IOCTL_UART_FIFO_ACCESS_SET
Gets or sets the UART FIFO access value

### IOCTL_UART_XMIT_FIFO_READ & IOCTL_UART_RECV_FIFO_WRITE
Gets the register values related to the transmit FIFO being read or the receive FIFO being written to. This provides information about the internal state of the IP.

### IOCTL_UART_STATUS_GET
Gets the current IP status

### IOCTL_UART_XMIT_FIFO_LEVEL_GET & IOCTL_UART_RECV_FIFO_LEVEL_GET
Gets the current fill level fo the transmit FIFO or receive FIFO, respectively.

### IOCTL_UART_SW_RESET_SET
Conducts a software reset of the UART IP

### IOCTL_UART_SHADOW_RTS_GET & IOCTL_UART_SHADOW_RTS_SET
Gets and sets as appropriate the shadow Ready to Send register

### IOCTL_UART_SHADOW_BREAK_CTRL_GET & IOCTL_UART_SHADOW_BREAK_CTRL_SET
Gets and sets as appropriate the shadow break register

### IOCTL_UART_SHADOW_DMA_MODE_GET & IOCTL_UART_SHADOW_DMA_MODE_SET
Gets and sets as appropriate the shadow DMA mode register

### IOCTL_UART_SHADOW_FIFO_ENABLE_GET & IOCTL_UART_SHADOW_FIFO_ENABLE_SET
Gets and sets as appropriate the shadow FIFO enable register

### IOCTL_UART_SHADOW_RECV_TRIGGER_GET & IOCTL_UART_SHADOW_RECV_TRIGGER_SET
Gets and sets as appropriate the shadow receive trigger register

### IOCTL_UART_SHADOW_TX_EMPTY_TRIGGER_GET & IOCTL_UART_SHADOW_TX_EMPTY_TRIGGER_SET
Gets and sets as appropriate the shadow TX empty trigger register

### IOCTL_UART_HALT_TX_GET & IOCTL_UART_HALT_TX_SET
Gets and sets as appropriate the Halt register

### IOCTL_UART_DMA_SW_ACK_SET
Sets the DMA software acknowledge

### IOCTL_UART_COMPONENT_PARAMETER_GET
Gets the component paramter register. This is decided at HW design time.

### IOCTL_UART_COMPONENT_VERSION_GET
Gets the component version register. This is decided at HW design time.

### IOCTL_UART_COMPONENT_TYPE_GET
Gets the component type register. This is decided at HW design time.
