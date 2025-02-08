#ifndef TIMER_REGS_H
#define TIMER_REGS_H

#include "device.h"
#include <stdint.h>

#include "hps_address_map.h"

typedef struct {
    volatile uint32_t TIMER1LOADCOUNT;     /* ALT_TMR_TIMER1LOADCOUNT */
    volatile uint32_t TIMER1CURRENTVAL;    /* ALT_TMR_TIMER1CURRENTVAL */
    volatile uint32_t TIMER1CONTROLREG;    /* ALT_TMR_TIMER1CONTROLREG */
    volatile uint32_t TIMER1EOI;           /* ALT_TMR_TIMER1EOI */
    volatile uint32_t TIMER1INTSTAT;       /* ALT_TMR_TIMER1INTSTAT */
    volatile uint32_t _pad_0x14_0x9f[35];  /* *UNDEFINED* */
    volatile uint32_t TIMERSINTSTAT;       /* ALT_TMR_TIMERSINTSTAT */
    volatile uint32_t TIMERSEOI;           /* ALT_TMR_TIMERSEOI */
    volatile uint32_t TIMERSRAWINTSTAT;    /* ALT_TMR_TIMERSRAWINTSTAT */
    volatile uint32_t TIMERSCOMPVERSION;   /* ALT_TMR_TIMERSCOMPVERSION */
    volatile uint32_t _pad_0xb0_0x100[20]; /* *UNDEFINED* */
} hps_timer_regs_t;

#endif // TIMER_REGS_H
