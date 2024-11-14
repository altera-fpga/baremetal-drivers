#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint32_t __attribute__((noinline)) end_main_atf(uint32_t i) { return (uint32_t)i + (uint32_t)1U; }

int main(void) {
    uint32_t a, b = 0;
    a = b << 1;
    return (int)end_main_atf(a) >> 2U;
}

#ifdef __cplusplus
}
#endif
