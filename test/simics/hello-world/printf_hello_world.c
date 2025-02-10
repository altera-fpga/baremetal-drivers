#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "rstmgr.h"
#include "rstmgr_regs.h"
#ifdef FSBL_EXECUTION
#include <fsbl_boot_help.h>
#endif

int main(void) {
    int32_t return_value = -1;
    const char *const message = "This is a test of the printf function that prints a line exeeding %d characters.\n";
#ifdef FSBL_EXECUTION
    fsbl_configuration();
#endif

    printf("Hello, World!\n");
    printf(message, strlen(message));
    return_value = 0;

    return return_value;
}

#ifdef __cplusplus
}
#endif
