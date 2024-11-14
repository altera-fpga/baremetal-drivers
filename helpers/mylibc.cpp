#include <memory.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <sys/times.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "debug.h"
#include "page_tables.h"
#include "rstmgr.h"
#include "rstmgr_regs.h"
#include "uart.h"

extern unsigned char __heap_start;
static unsigned char *heap = 0x0;

int32_t stdout_uart_fd = 0;

int _fstat(int fildes, struct stat *st);

void _cpu_init_hook() {
    uint64_t current_el = (uint64_t)0;
    asm volatile("mrs %0, CurrentEL" : "=r"(current_el));
    current_el >>= 2; // Shift bits to get EL value. Bits 0 and 1 are RES0
    if (current_el == 3) {
        apply_page_tables_el3();
    } else if (current_el == 2) {
        apply_page_tables_el2();
    } else if (current_el == 1) {
        apply_page_tables_el1();
    } else {
        // This should never happen. The _cpu_init_hook is only called in el3, el2, or el1.
        // So, deadloop
        while (1)
            ;
    }
    _fstat(1, NULL);
}

char *getcwd(char *buf, size_t size __attribute__((unused))) {
    buf[0] = '.';
    buf[1] = 0;
    return buf;
}
int mkdir(const char *path __attribute__((unused)), mode_t mode __attribute__((unused))) { return -1; }

// The my_putchar function deliberately doesn't use the UART driver, but writes directly to the UART
// registers. This allows the debug function in this file to not rely on the correctness of the UART
// driver.
void my_putchar(char c) {
    volatile uint32_t *addr = (volatile uint32_t *)0x10c02000;
    volatile uint32_t *USR = (volatile uint32_t *)0x10C0207C;
    while (((*USR) & 0x2U) == 0U) {
    }
    *addr = (uint32_t)c;
}

void debug(const char *str) {
    return;

    for (int i = 0; str[i] != '\0'; ++i) {
        my_putchar(str[i]);
    }
    my_putchar('\r');
    my_putchar('\n');
}

void *_sbrk(intptr_t incr) {
    debug(__FUNCTION__);
    if (heap == 0) {
        heap = &__heap_start;
    }
    unsigned char *prev_heap = heap;
    heap += incr;
    return prev_heap;
}

void _exit(int rc) {
    debug(__FUNCTION__);
    /* Default stub just causes a divide by 0 exception.  */

#ifdef IN_TESTS
    // Sentinel output for matching by tests
    if (rc == 0) {
        puts("__PASS__");
    } else {
        puts("__FAIL__");
    }
#endif

    /* Convince GCC that this function never returns.  */
    for (;;)
        ;
}

int _close(int fildes) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    return -1;
}
int _fstat(int fildes, struct stat *st) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    if (fildes == 1 && stdout_uart_fd <= 0) { // if this is unopened stdout
        int32_t rstmgr_handle = rstmgr_open("/dev/rstmgr", 0);
        if (rstmgr_handle < 0) {
            return rstmgr_handle;
        }
        hps_rstmgr_regs_t regs_buffer;

        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_READ, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));
        regs_buffer.per1modrst &= ~((uint32_t)0x00030000);
        rstmgr_ioctl(rstmgr_handle, (int32_t)IOCTL_RSTMGR_WRITE, (uintptr_t)(&regs_buffer), sizeof(hps_rstmgr_regs_t));

        rstmgr_close(rstmgr_handle);

        stdout_uart_fd = uart_open("/dev/uart0", 0);
        if (stdout_uart_fd < 0) {
            return stdout_uart_fd;
        }
    }

    return 0;
}

int _gettimeofday(struct timeval *ptimeval, void *ptimezone) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    memset(ptimeval, 0, sizeof(timeval));
    return 0;
}
int env(char *file) {
    debug(__FUNCTION__);
    return 0;
}

int _open(char *file, int flags, int mode) {
    debug(__FUNCTION__);

    return -1;
}

int puts(const char *s) {
    errno = ENOSYS;
    if (stdout_uart_fd > 0) {
        size_t length = (size_t)(strlen(s));
        int count = uart_write((int32_t)(stdout_uart_fd), (uintptr_t)(s), length);

        // CRLF is required for UART purposes
        length = (size_t)(strlen("\r\n"));
        count += uart_write((int32_t)(stdout_uart_fd), (uintptr_t) "\r\n", length);
        return count;
    } else {
        return 0;
    }
}

int putchar(int c) {
    errno = ENOSYS;
    if (stdout_uart_fd > 0) {
        unsigned char s[1] = {(unsigned char)c};
        int count = uart_write((int32_t)(stdout_uart_fd), (uintptr_t)(s), 1);
        if (count > 0) {
            return (int)(s[0]);
        } else {
            return EOF;
        }
    } else {
        return EOF;
    }
}

int _write(int file, char *ptr, int len) {
    // debug(__FUNCTION__);
    errno = ENOSYS;
    if (stdout_uart_fd > 0) {
        return uart_write((int32_t)(stdout_uart_fd), (uintptr_t)(ptr), (size_t)(len));
    } else {
        return 0;
    }
}

int _getpid(void) {
    debug(__FUNCTION__);
    return 1;
}

int _isatty(int file) {
    debug(__FUNCTION__);
    if (file == 1) {
        return 1;
    }
    return 0;
}

int _kill(int pid, int sig) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    return 0;
}

int _read(int file, char *ptr, int len) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    return 0;
}

int _stat(const char *file, struct stat *st) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    return -1;
}

int atexit(void (*)(void)) { return 0; }

void exit(int rc) { _exit(rc); }

clock_t _times(struct tms *buf) {
    debug(__FUNCTION__);
    errno = ENOSYS;
    return -1;
}

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus
