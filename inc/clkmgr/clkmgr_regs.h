#ifndef CLKMGR_REGS_H
#define CLKMGR_REGS_H

#include "device.h"
#include <stdint.h>

#include "system.h"

typedef struct {
    volatile uint32_t ctrl;       /* CLKMGR_CTRL */
    volatile uint32_t stat;       /* CLKMGR_STAT */
    volatile uint32_t testioctrl; /* CLKMGR_TESTIOCTRL */
    volatile uint32_t intrgen;    /* CLKMGR_INTRGEN */
    volatile uint32_t intrmsk;    /* CLKMGR_INTRMSK */
    volatile uint32_t intrclr;    /* CLKMGR_INTRCLR */
    volatile uint32_t intrsts;    /* CLKMGR_INTRSTS */
    volatile uint32_t intrstk;    /* CLKMGR_INTRSTK */
    volatile uint32_t intrraw;    /* CLKMGR_INTRRAW */
} hps_clkmgr_regs_t;

typedef struct {
    volatile uint32_t en;             /* CLKMGR_MAINPLL_EN */
    volatile uint32_t ens;            /* CLKMGR_MAINPLL_ENS */
    volatile uint32_t enr;            /* CLKMGR_MAINPLL_ENR */
    volatile uint32_t bypass;         /* CLKMGR_MAINPLL_BYPASS */
    volatile uint32_t bypasss;        /* CLKMGR_MAINPLL_BYPASSS */
    volatile uint32_t bypassr;        /* CLKMGR_MAINPLL_BYPASSR */
    volatile uint32_t _pad_0x18_0x1b; /* *UNDEFINED* */
    volatile uint32_t nocclk;         /* CLKMGR_MAINPLL_NOCCLK */
    volatile uint32_t nocdiv;         /* CLKMGR_MAINPLL_NOCDIV */
    volatile uint32_t pllglob;        /* CLKMGR_MAINPLL_PLLGLOB */
    volatile uint32_t fdbck;          /* CLKMGR_MAINPLL_FDBCK */
    volatile uint32_t mem;            /* CLKMGR_MAINPLL_MEM */
    volatile uint32_t memstat;        /* CLKMGR_MAINPLL_MEMSTAT */
    volatile uint32_t vcocalib;       /* CLKMGR_MAINPLL_VCOCALIB */
    volatile uint32_t pllc0;          /* CLKMGR_MAINPLL_PLLC0 */
    volatile uint32_t pllc1;          /* CLKMGR_MAINPLL_PLLC1 */
    volatile uint32_t pllc2;          /* CLKMGR_MAINPLL_PLLC2 */
    volatile uint32_t pllc3;          /* CLKMGR_MAINPLL_PLLC3 */
    volatile uint32_t pllm;           /* CLKMGR_MAINPLL_PLLM */
    volatile uint32_t fhop;           /* CLKMGR_MAINPLL_FHOP */
    volatile uint32_t ssc;            /* CLKMGR_MAINPLL_SSC */
    volatile uint32_t lostlock;       /* CLKMGR_MAINPLL_LOSTLOCK */
} hps_clkmgr_mainpll_regs_t;

typedef struct {
    volatile uint32_t en;       /* CLKMGR_PERPLL_EN */
    volatile uint32_t ens;      /* CLKMGR_PERPLL_ENS */
    volatile uint32_t enr;      /* CLKMGR_PERPLL_ENR */
    volatile uint32_t bypass;   /* CLKMGR_PERPLL_BYPASS */
    volatile uint32_t bypasss;  /* CLKMGR_PERPLL_BYPASSS */
    volatile uint32_t bypassr;  /* CLKMGR_PERPLL_BYPASSR */
    volatile uint32_t emacctl;  /* CLKMGR_PERPLL_EMACCTL */
    volatile uint32_t gpiodiv;  /* CLKMGR_PERPLL_GPIODIV */
    volatile uint32_t pllglob;  /* CLKMGR_PERPLL_PLLGLOB */
    volatile uint32_t fdbck;    /* CLKMGR_PERPLL_FDBCK */
    volatile uint32_t mem;      /* CLKMGR_PERPLL_MEM */
    volatile uint32_t memstat;  /* CLKMGR_PERPLL_MEMSTAT */
    volatile uint32_t vcocalib; /* CLKMGR_PERPLL_VCOCALIB */
    volatile uint32_t pllc0;    /* CLKMGR_PERPLL_PLLC0 */
    volatile uint32_t pllc1;    /* CLKMGR_PERPLL_PLLC1 */
    volatile uint32_t pllc2;    /* CLKMGR_PERPLL_PLLC2 */
    volatile uint32_t pllc3;    /* CLKMGR_PERPLL_PLLC3 */
    volatile uint32_t pllm;     /* CLKMGR_PERPLL_PLLM */
    volatile uint32_t fhop;     /* CLKMGR_PERPLL_FHOP */
    volatile uint32_t ssc;      /* CLKMGR_PERPLL_SSC */
    volatile uint32_t lostlock; /* CLKMGR_PERPLL_LOSTLOCK */
} hps_clkmgr_perpll_regs_t;

typedef struct {
    volatile uint32_t jtag;               /* CLK_MGR_CTLGRP_JTAG */
    volatile uint32_t emacactr;           /* CLK_MGR_CTLGRP_EMACACTR */
    volatile uint32_t emacbctr;           /* CLK_MGR_CTLGRP_EMACBCTR */
    volatile uint32_t emacptpctr;         /* CLK_MGR_CTLGRP_EMACPTPCTR */
    volatile uint32_t gpiodbctr;          /* CLK_MGR_CTLGRP_GPIODBCTR */
    volatile uint32_t _pad_0x14_0x17;     /* *UNDEFINED* */
    volatile uint32_t s2fuser0ctr;        /* CLK_MGR_CTLGRP_S2FUSER0CTR */
    volatile uint32_t s2fuser1ctr;        /* CLK_MGR_CTLGRP_S2FUSER1CTR */
    volatile uint32_t psirefctr;          /* CLK_MGR_CTLGRP_PSIREFCTR */
    volatile uint32_t extcntrst;          /* CLK_MGR_CTLGRP_EXTCNTRST */
    volatile uint32_t usb31ctr;           /* CLK_MGR_CTLGRP_USB31CTR */
    volatile uint32_t dsuctr;             /* CLK_MGR_CTLGRP_DSUCTR */
    volatile uint32_t core01ctr;          /* CLK_MGR_CTLGRP_CORE01CTR */
    volatile uint32_t core23ctr;          /* CLK_MGR_CTLGRP_CORE23CTR */
    volatile uint32_t core2ctr;           /* CLK_MGR_CTLGRP_CORE2CTR */
    volatile uint32_t core3ctr;           /* CLK_MGR_CTLGRP_CORE3CTR */
    volatile uint32_t serial_con_pll_ctr; /* CLK_MGR_CTLGRP_SERIAL_CON_PLL_CTR */
} hps_clkmgr_ctlgrp_regs_t;

#endif // CLKMGR_REGS_H