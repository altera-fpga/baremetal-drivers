#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint32_t __attribute__((noinline)) end_main(uint32_t i) { return (uint32_t)i + (uint32_t)1UL; }

int main(void) {
    uint32_t a, b = 0;
    a = b << 1;
    return (int32_t)end_main(a);
}

#ifdef __cplusplus
}
#endif