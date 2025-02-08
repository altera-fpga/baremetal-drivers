#ifndef NOC_FIREWALL_REGS_H__
#define NOC_FIREWALL_REGS_H__

/*
 * NOC_FIREWALL Documentation Overview:
 *   -- Register Map
 *       -- noc_fw_l4_per__ocp_slv__10d21000
 *   -- High-Level Architecture Specification
 *       -- "SM HPS Interconnect HAS 1.1.pdf"
 */

// Base Memory address for NOC_FIREWALL access
#define NOC_FIREWALL_BASE (0x10D21000)
#define NOC_FIREWALL_L4_PER_OFST (0x0)
#define NOC_FIREWALL_L4_SYS_OFST (0x100)
#define NOC_FIREWALL_HPS2FPGA_OFST (0x200)
#define NOC_FIREWALL_LWHPS2FPGA_OFST (0x300)
#define NOC_FIREWALL_TCU_OFST (0x400)

/*
 * structure yielding access to NOC firewall L4_PER parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t nand_register; /* Offset 0x0 */
    volatile uint32_t _pad_0[2];     /* *UNDEFINED* */
    volatile uint32_t usb0_register; /* Offset 0xc */
    volatile uint32_t usb1_register; /* Offset 0x10 */
    volatile uint32_t _pad_1[2];     /* *UNDEFINED* */
    volatile uint32_t spi_master0;   /* Offset 0x1c */
    volatile uint32_t spi_master1;   /* Offset 0x20 */
    volatile uint32_t spi_slave0;    /* Offset 0x24 */
    volatile uint32_t spi_slave1;    /* Offset 0x28 */
    volatile uint32_t emac0;         /* Offset 0x2c */
    volatile uint32_t emac1;         /* Offset 0x30 */
    volatile uint32_t emac2;         /* Offset 0x34 */
    volatile uint32_t _pad_2[2];     /* *UNDEFINED* */
    volatile uint32_t sdmmc;         /* Offset 0x40 */
    volatile uint32_t gpio0;         /* Offset 0x44 */
    volatile uint32_t gpio1;         /* Offset 0x48 */
    volatile uint32_t _pad_3;        /* *UNDEFINED* */
    volatile uint32_t i2c0;          /* Offset 0x50 */
    volatile uint32_t i2c1;          /* Offset 0x54 */
    volatile uint32_t i2c2;          /* Offset 0x58 */
    volatile uint32_t i2c3;          /* Offset 0x5c */
    volatile uint32_t i2c4;          /* Offset 0x60 */
    volatile uint32_t sp_timer0;     /* Offset 0x64 */
    volatile uint32_t sp_timer1;     /* Offset 0x68 */
    volatile uint32_t uart0;         /* Offset 0x6c */
    volatile uint32_t uart1;         /* Offset 0x70 */
    volatile uint32_t i3c0;          /* Offset 0x74 */
    volatile uint32_t i3c1;          /* Offset 0x78 */
    volatile uint32_t dma0;          /* Offset 0x7c */
    volatile uint32_t dma1;          /* Offset 0x80 */
    volatile uint32_t combo_phy;     /* Offset 0x84 */
    volatile uint32_t nand_sdma;     /* Offset 0x88 */
    volatile uint32_t _pad_4[29];    /* *UNDEFINED* */
} noc_firewall_l4_per_regs_words_t;

/*
 * structure yielding access to NOC firewall L4_SYS parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t _pad_0[2];      /* *UNDEFINED* */
    volatile uint32_t dma_ecc;        /* Offset 0x8 */
    volatile uint32_t emac0rx_ecc;    /* Offset 0xc */
    volatile uint32_t emac0tx_ecc;    /* Offset 0x10 */
    volatile uint32_t emac1rx_ecc;    /* Offset 0x14 */
    volatile uint32_t emac1tx_ecc;    /* Offset 0x18 */
    volatile uint32_t emac2rx_ecc;    /* Offset 0x1c */
    volatile uint32_t emac2tx_ecc;    /* Offset 0x20 */
    volatile uint32_t _pad_1[2];      /* *UNDEFINED* */
    volatile uint32_t nand_ecc;       /* Offset 0x2c */
    volatile uint32_t nand_read_ecc;  /* Offset 0x30 */
    volatile uint32_t nand_write_ecc; /* Offset 0x34 */
    volatile uint32_t ocram_ecc;      /* Offset 0x38 */
    volatile uint32_t _pad_2;         /* *UNDEFINED* */
    volatile uint32_t sdmmc_ecc;      /* Offset 0x40 */
    volatile uint32_t usb0_ecc;       /* Offset 0x44 */
    volatile uint32_t usb1_cacheecc;  /* Offset 0x48 */
    volatile uint32_t clock_manager;  /* Offset 0x4c */
    volatile uint32_t _pad_3;         /* *UNDEFINED* */
    volatile uint32_t io_manager;     /* Offset 0x54 */
    volatile uint32_t reset_manager;  /* Offset 0x58 */
    volatile uint32_t system_manager; /* Offset 0x5c */
    volatile uint32_t osc0_timer;     /* Offset 0x60 */
    volatile uint32_t osc1_timer;     /* Offset 0x64 */
    volatile uint32_t watchdog0;      /* Offset 0x68 */
    volatile uint32_t watchdog1;      /* Offset 0x6c */
    volatile uint32_t watchdog2;      /* Offset 0x70 */
    volatile uint32_t watchdog3;      /* Offset 0x74 */
    volatile uint32_t dap;            /* Offset 0x78 */
    volatile uint32_t watchdog4;      /* Offset 0x7c */
    volatile uint32_t power_manager;  /* Offset 0x80 */
    volatile uint32_t usb1_rxecc;     /* Offset 0x84 */
    volatile uint32_t usb1_txecc;     /* Offset 0x88 */
    volatile uint32_t _pad_4;         /* *UNDEFINED* */
    volatile uint32_t l4_noc_probes;  /* Offset 0x90 */
    volatile uint32_t l4_noc_qos;     /* Offset 0x94 */
    volatile uint32_t _pad_5[26];     /* *UNDEFINED* */
} noc_firewall_l4_sys_regs_words_t;

/*
 * structure yielding access to NOC firewall HPS2FPGA parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t soc2fpga;   /* Offset 0x0 */
    volatile uint32_t _pad_0[63]; /* *UNDEFINED* */
} noc_firewall_hps2fpga_regs_words_t;

/*
 * structure yielding access to NOC firewall LWHPS2FPGA parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t lwsoc2fpga; /* Offset 0x0 */
    volatile uint32_t _pad_0[63]; /* *UNDEFINED* */
} noc_firewall_lwhps2fpga_regs_words_t;

/*
 * structure yielding access to NOC firewall TCU parameters words
 */
typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t tcu;        /* Offset 0x0 */
    volatile uint32_t _pad_0[63]; /* *UNDEFINED* */
} noc_firewall_tcu_regs_words_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    noc_firewall_l4_per_regs_words_t noc_firewall_l4_per_regs_words_s;
    noc_firewall_l4_sys_regs_words_t noc_firewall_l4_sys_regs_words_s;
    noc_firewall_hps2fpga_regs_words_t noc_firewall_hps2fpga_regs_words_s;
    noc_firewall_lwhps2fpga_regs_words_t noc_firewall_lwhps2fpga_regs_words_s;
    noc_firewall_tcu_regs_words_t noc_firewall_tcu_regs_words_s;
} noc_firewall_regs_t;

#endif // NOC_FIREWALL_REGS_H__