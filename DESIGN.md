# About the API Design

The drivers in this repository follow a subset of the POSIX API with a handful of modifications to fulfill MISRA Compliance.

## Implementation Pattern

The outward facing API consists of 8 APIs: open/close, read/recv, write/send, ioctl, and error.

`int32_t driver_open(const char* name, int32_t flags);`
The Open API claims the driver described by name, with optional flags applied. The return value is either a pointer to the base address of the IP block or NULL if the attempt to claim failed.

`int32_t driver_close(int32_t fd);`
The Close API releases a prior claim based on the fd.

`size_t driver_recv(int32_t fd, uintptr_t buf, size_t size, int32_t flags);`
The Recv API receives a stream or block of data up to size, places the data at the location pointed to by buf, and returns the length received.

`size_t driver_read(int32_t fd, uintptr_t buf, size_t size);`
The Read API is strictly idential to the Recv API with no flags set.

`size_t driver_send(int32_t fd, const uintptr_t buf, size_t size, int32_t flags);`
The Send API transmits a stream or block from the location pointed to by buf of data up to size and returns the size transmitted.

`size_t driver_write(int32_t fd, const uintptr_t buf, size_t size);`
The Write API is strictly identical to the Send API with no flags set.

`int32_t driver_ioctl(int32_t fd, int32_t request, uintptr_t arg, size_t length);`
The IOCTL API enables operations that are not stream or block operations. These are sometimes IP configuration options but IOCTL is also used as a catchall for operations generally not conforming to read/write or recv/send. The data pointed to by arg may be a struct or buffer. Length shall match the length of the allocation pointed to by arg. The implementation checks that the length is sufficient to complete the operation.

Every driver IOCTL implementation shall include methods to read and write the underlying register struct(s) directly. This both allows for flexibility in the implementation as well as a means to enable use cases not covered in this repository's implementation.

`int32_t driver_error(int32_t fd);`
The Error API allows for reporting of asynchronous errors (i.e. errors that occur outside the scope of a function call).
