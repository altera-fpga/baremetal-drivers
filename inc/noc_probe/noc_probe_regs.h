#ifndef NOC_PROBE_REGS_H
#define NOC_PROBE_REGS_H

#include <stddef.h>
#include <stdint.h>

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;     // offset: 0x0
    volatile uint32_t id_revisionid; // offset: 0x4
    volatile uint32_t atbid;         // offset: 0x8
    volatile uint32_t atben;         // offset: 0xc
} noc_probe_atbendpoint_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;     // offset: 0x0
    volatile uint32_t id_revisionid; // offset: 0x4
    volatile uint32_t faulten;       // offset: 0x8
    volatile uint32_t errvld;        // offset: 0xc
    volatile uint32_t errclr;        // offset: 0x10
    volatile uint32_t errlog0;       // offset: 0x14
    volatile uint32_t errlog1;       // offset: 0x18
    volatile uint32_t __pad_0x1c;
    volatile uint32_t errlog3; // offset: 0x20
    volatile uint32_t errlog4; // offset: 0x24
    volatile uint32_t errlog5; // offset: 0x28
    volatile uint32_t errlog6; // offset: 0x2c
    volatile uint32_t errlog7; // offset: 0x30
    volatile uint32_t __pad_0x34_0x48[6];
    volatile uint32_t stallen; // offset: 0x4c
} noc_probe_errorlogger_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;     // offset: 0x0
    volatile uint32_t id_revisionid; // offset: 0x4
    volatile uint32_t asyncperiod;   // offset: 0x8
    volatile uint32_t stpv2en;       // offset: 0xc
} noc_probe_stpv2converter_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t routeidbase;   // offset: 0x0
    volatile uint32_t routeidmask;   // offset: 0x4
    volatile uint32_t addrbase_low;  // offset: 0x8
    volatile uint32_t addrbase_high; // offset: 0xc
    volatile uint32_t windowsize;    // offset: 0x10
    volatile uint32_t securitybase;  // offset: 0x14
    volatile uint32_t securitymask;  // offset: 0x18
    volatile uint32_t opcode;        // offset: 0x1c
    volatile uint32_t status;        // offset: 0x20
    volatile uint32_t length;        // offset: 0x24
    volatile uint32_t urgency;       // offset: 0x28
    volatile uint32_t __pad_0x0c_0x5c[13];
} noc_probe_probe_filters_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t __pad_0x0;
    volatile uint32_t src;       // offset: 0x204
    volatile uint32_t alarmmode; // offset: 0x208
    volatile uint32_t val;       // offset: 0x20c
} noc_probe_probe_counters_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;     // offset: 0x0
    volatile uint32_t id_revisionid; // offset: 0x4
    volatile uint32_t mainctl;       // offset: 0x8
    volatile uint32_t cfgctl;        // offset: 0xc
    volatile uint32_t __pad_0x10;
    volatile uint32_t filterlut;        // offset: 0x14
    volatile uint32_t tracealarmen;     // offset: 0x18
    volatile uint32_t tracealarmstatus; // offset: 0x1c
    volatile uint32_t tracealarmclr;    // offset: 0x20
    volatile uint32_t statperiod;       // offset: 0x24
    volatile uint32_t statgo;           // offset: 0x28
    volatile uint32_t statalarmmin;     // offset: 0x2c
    volatile uint32_t __pad_0x30;
    volatile uint32_t statalarmmax; // offset: 0x34
    volatile uint32_t __pad_0x38;
    volatile uint32_t statalarmstatus; // offset: 0x3c
    volatile uint32_t statalarmclr;    // offset: 0x40
    volatile uint32_t statalarmen;     // offset: 0x44
    volatile uint32_t __pad_0x48_0x7c[14];
    volatile noc_probe_probe_filters_t filters[2]; // offset: 0x80
    volatile uint32_t __pad_0x140_0x1fc[48];
    volatile noc_probe_probe_counters_t counters[4]; // offset: 0x200
} noc_probe_probe_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;     // offset: 0x0
    volatile uint32_t id_revisionid; // offset: 0x4
    volatile uint32_t en;            // offset: 0x8
    volatile uint32_t mode;          // offset: 0xc
    volatile uint32_t __pad_0x10_0x28[7];
    volatile uint32_t thresholds_0[3]; // offset: 0x2c
    volatile uint32_t __pad_0x38_0x68[13];
    volatile uint32_t overflowstatus;   // offset: 0x6c
    volatile uint32_t overflowreset;    // offset: 0x70
    volatile uint32_t pendingeventmode; // offset: 0x74
    volatile uint32_t prescaler;        // offset: 0x78
} noc_probe_transactionstatprofiler_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;     // offset: 0x0
    volatile uint32_t id_revisionid; // offset: 0x4
    volatile uint32_t priority;      // offset: 0x8
    volatile uint32_t mode;          // offset: 0xc
    volatile uint32_t bandwidth;     // offset: 0x10
    volatile uint32_t saturation;    // offset: 0x14
    volatile uint32_t extcontrol;    // offset: 0x18
} noc_probe_qosgenerator_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t id_coreid;      // offset: 0x0
    volatile uint32_t id_revisionid;  // offset: 0x4
    volatile uint32_t mode;           // offset: 0x8
    volatile uint32_t addrbase_low;   // offset: 0xc
    volatile uint32_t addrbase_high;  // offset: 0x10
    volatile uint32_t addrwindowsize; // offset: 0x14
    volatile uint32_t __pad_0x18_0x1c[2];
    volatile uint32_t opcode;       // offset: 0x20
    volatile uint32_t userbase;     // offset: 0x24
    volatile uint32_t usermask;     // offset: 0x28
    volatile uint32_t securitybase; // offset: 0x2c
    volatile uint32_t securitymask; // offset: 0x30
    volatile uint32_t userbasehigh; // offset: 0x34
    volatile uint32_t usermaskhigh; // offset: 0x38
} noc_probe_transactionstatfilter_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile noc_probe_atbendpoint_t atbendpoint; // offset: 0x0000
    volatile uint32_t __pad_0x10_0x7c[28];
    volatile noc_probe_errorlogger_t errorlogger_0; // offset: 0x0080
    volatile uint32_t __pad_0xd0_0xfc[12];
    volatile noc_probe_stpv2converter_t stpv2converter; // offset: 0x0100
    volatile uint32_t __pad_0x110_0x3fc[188];
    volatile noc_probe_probe_regs_t ccu_probe; // offset: 0x0400
    volatile uint32_t __pad_0x640_0x7fc[112];
    volatile noc_probe_probe_regs_t emac_probe; // offset: 0x0800
    volatile uint32_t __pad_0xa40_0xbfc[112];
    volatile noc_probe_probe_regs_t soc2fpga_probe; // offset: 0x0c00
    volatile uint32_t __pad_0xe40_0xffc[112];
    volatile noc_probe_transactionstatprofiler_regs_t emac_transactionstatprofiler; // offset: 0x1000
    volatile uint32_t __pad_0x107c_0x13fc[225];
    volatile noc_probe_probe_regs_t io_probe; // offset: 0x1400
    volatile uint32_t __pad_0x1640_0x17fc[112];
    volatile noc_probe_transactionstatprofiler_regs_t io_transactionstatprofiler; // offset: 0x1800
    volatile uint32_t __pad_0x187c_0x1ffc[481];
    volatile noc_probe_qosgenerator_regs_t ccu_qosgenerator; // offset: 0x2000
    volatile uint32_t __pad_0x201c_0x207c[25];
    volatile noc_probe_qosgenerator_regs_t dma_qosgenerator; // offset: 0x2080
    volatile uint32_t __pad_0x209c_0x20fc[25];
    volatile noc_probe_qosgenerator_regs_t emac_qosgenerator; // offset: 0x2100
    volatile uint32_t __pad_0x211c_0x217c[25];
    volatile noc_probe_qosgenerator_regs_t io_qosgenerator; // offset: 0x2180
    volatile uint32_t __pad_0x219c_0x21fc[25];
    volatile noc_probe_qosgenerator_regs_t sdm_qosgenerator; // offset: 0x2200
    volatile uint32_t __pad_0x221c_0x23fc[121];
    volatile noc_probe_transactionstatfilter_regs_t emac_transactionstatfilter; // offset: 0x2400
    volatile uint32_t __pad_0x243c_0x247c[17];
    volatile noc_probe_transactionstatfilter_regs_t io_transactionstatfilter; // offset: 0x2480
} noc_probe_regs_t;

#endif // NOC_PROBE_REGS_H
