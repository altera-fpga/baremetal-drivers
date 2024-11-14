This driver supports a Synopsis DesignWare 16550 UART IP.

The UART driver implemented here operates in FIFO mode using polling. Other modes can be configured via ioctl register modifications.

Internally, the UART driver has no memory buffers. The read and write operations are blocking.

