#ifndef CCU_REGS_H__
#define CCU_REGS_H__

#include "hps_address_map.h"

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t caiuidr;   // offset: 0x0000
    volatile uint32_t caiufuidr; // offset: 0x0004
    volatile uint32_t __pad_0x8_0x3c[14];
    volatile uint32_t caiutcr; // offset: 0x0040
    volatile uint32_t caiutar; // offset: 0x0044
    volatile uint32_t __pad_0x48_0xfc[46];
    volatile uint32_t caiuuedr;  // offset: 0x0100
    volatile uint32_t caiuueir;  // offset: 0x0104
    volatile uint32_t caiuuesr;  // offset: 0x0108
    volatile uint32_t caiuuelr0; // offset: 0x010c
    volatile uint32_t caiuuelr1; // offset: 0x0110
    volatile uint32_t caiuuesar; // offset: 0x0114
    volatile uint32_t __pad_0x118_0x17c[26];
    volatile uint32_t caiucrtr; // offset: 0x0180
    volatile uint32_t __pad_0x184_0x18c[3];
    volatile uint32_t caiutocr; // offset: 0x0190
    volatile uint32_t __pad_0x194_0x1fc[27];
    volatile uint32_t caiuqoscr; // offset: 0x0200
    volatile uint32_t caiuqossr; // offset: 0x0204
    volatile uint32_t __pad_0x208_0x37c[94];
    volatile uint32_t nrsbar; // offset: 0x0380
    volatile uint32_t nrsbhr; // offset: 0x0384
    volatile uint32_t nrsblr; // offset: 0x0388
    volatile uint32_t __pad_0x38c;
    volatile uint32_t caiubrar;  // offset: 0x0390
    volatile uint32_t caiubrblr; // offset: 0x0394
    volatile uint32_t caiubrbhr; // offset: 0x0398
    volatile uint32_t __pad_0x39c_0x3bc[9];
    volatile uint32_t caiuamigr; // offset: 0x03c0
    volatile uint32_t caiumifsr; // offset: 0x03c4
    volatile uint32_t __pad_0x3c8_0x3fc[14];
    volatile uint32_t caiugprar0;  // offset: 0x0400
    volatile uint32_t caiugprblr0; // offset: 0x0404
    volatile uint32_t caiugprbhr0; // offset: 0x0408
    volatile uint32_t __pad_0x40c;
    volatile uint32_t caiugprar1;  // offset: 0x0410
    volatile uint32_t caiugprblr1; // offset: 0x0414
    volatile uint32_t caiugprbhr1; // offset: 0x0418
    volatile uint32_t __pad_0x41c;
    volatile uint32_t caiugprar2;  // offset: 0x0420
    volatile uint32_t caiugprblr2; // offset: 0x0424
    volatile uint32_t caiugprbhr2; // offset: 0x0428
    volatile uint32_t __pad_0x42c;
    volatile uint32_t caiugprar3;  // offset: 0x0430
    volatile uint32_t caiugprblr3; // offset: 0x0434
    volatile uint32_t caiugprbhr3; // offset: 0x0438
    volatile uint32_t __pad_0x43c;
    volatile uint32_t caiugprar4;  // offset: 0x0440
    volatile uint32_t caiugprblr4; // offset: 0x0444
    volatile uint32_t caiugprbhr4; // offset: 0x0448
    volatile uint32_t __pad_0x44c;
    volatile uint32_t caiugprar5;  // offset: 0x0450
    volatile uint32_t caiugprblr5; // offset: 0x0454
    volatile uint32_t caiugprbhr5; // offset: 0x0458
    volatile uint32_t __pad_0x45c;
    volatile uint32_t caiugprar6;  // offset: 0x0460
    volatile uint32_t caiugprblr6; // offset: 0x0464
    volatile uint32_t caiugprbhr6; // offset: 0x0468
    volatile uint32_t __pad_0x46c;
    volatile uint32_t caiugprar7;  // offset: 0x0470
    volatile uint32_t caiugprblr7; // offset: 0x0474
    volatile uint32_t caiugprbhr7; // offset: 0x0478
    volatile uint32_t __pad_0x47c;
    volatile uint32_t caiugprar8;  // offset: 0x0480
    volatile uint32_t caiugprblr8; // offset: 0x0484
    volatile uint32_t caiugprbhr8; // offset: 0x0488
    volatile uint32_t __pad_0x48c;
    volatile uint32_t caiugprar9;  // offset: 0x0490
    volatile uint32_t caiugprblr9; // offset: 0x0494
    volatile uint32_t caiugprbhr9; // offset: 0x0498
    volatile uint32_t __pad_0x49c;
    volatile uint32_t caiugprar10;  // offset: 0x04a0
    volatile uint32_t caiugprblr10; // offset: 0x04a4
    volatile uint32_t caiugprbhr10; // offset: 0x04a8
    volatile uint32_t __pad_0x4ac;
    volatile uint32_t caiugprar11;  // offset: 0x04b0
    volatile uint32_t caiugprblr11; // offset: 0x04b4
    volatile uint32_t caiugprbhr11; // offset: 0x04b8
    volatile uint32_t __pad_0x4bc_0x8fc[273];
    volatile uint32_t caiucctrlr;  // offset: 0x0900
    volatile uint32_t caiutctrlr0; // offset: 0x0904
    volatile uint32_t caiutbalr0;  // offset: 0x0908
    volatile uint32_t caiutbahr0;  // offset: 0x090c
    volatile uint32_t caiutopcr00; // offset: 0x0910
    volatile uint32_t caiutopcr10; // offset: 0x0914
    volatile uint32_t caiutubr0;   // offset: 0x0918
    volatile uint32_t caiutubmr0;  // offset: 0x091c
    volatile uint32_t __pad_0x920_0xafc[120];
    volatile uint32_t caiucntcr0; // offset: 0x0b00
    volatile uint32_t caiucntvr0; // offset: 0x0b04
    volatile uint32_t caiucntsr0; // offset: 0x0b08
    volatile uint32_t __pad_0xb0c;
    volatile uint32_t caiucntcr1; // offset: 0x0b10
    volatile uint32_t caiucntvr1; // offset: 0x0b14
    volatile uint32_t caiucntsr1; // offset: 0x0b18
    volatile uint32_t __pad_0xb1c;
    volatile uint32_t caiucntcr2; // offset: 0x0b20
    volatile uint32_t caiucntvr2; // offset: 0x0b24
    volatile uint32_t caiucntsr2; // offset: 0x0b28
    volatile uint32_t __pad_0xb2c;
    volatile uint32_t caiucntcr3; // offset: 0x0b30
    volatile uint32_t caiucntvr3; // offset: 0x0b34
    volatile uint32_t caiucntsr3; // offset: 0x0b38
    volatile uint32_t __pad_0xb3c_0xfec[301];
    volatile uint32_t caiunrsar; // offset: 0x0ff0
    volatile uint32_t caiuuevir; // offset: 0x0ff4
    volatile uint32_t __pad_0xff8;
    volatile uint32_t caiuinfor; // offset: 0x0ffc
} ccu_caiu_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t xaiuidr;   // offset: 0x0000
    volatile uint32_t xaiufuidr; // offset: 0x0004
    volatile uint32_t __pad_0x8_0x3c[14];
    volatile uint32_t xaiutcr; // offset: 0x0040
    volatile uint32_t xaiutar; // offset: 0x0044
    volatile uint32_t __pad_0x48_0xfc[46];
    volatile uint32_t xaiuuedr;  // offset: 0x0100
    volatile uint32_t xaiuueir;  // offset: 0x0104
    volatile uint32_t xaiuuesr;  // offset: 0x0108
    volatile uint32_t xaiuuelr0; // offset: 0x010c
    volatile uint32_t xaiuuelr1; // offset: 0x0110
    volatile uint32_t xaiuuesar; // offset: 0x0114
    volatile uint32_t __pad_0x118_0x13c[10];
    volatile uint32_t xaiucecr;  // offset: 0x0140
    volatile uint32_t xaiucesr;  // offset: 0x0144
    volatile uint32_t xaiucelr0; // offset: 0x0148
    volatile uint32_t xaiucelr1; // offset: 0x014c
    volatile uint32_t xaiucesar; // offset: 0x0150
    volatile uint32_t __pad_0x154_0x178[10];
    volatile uint32_t xaiucrtr; // offset: 0x017c
    volatile uint32_t __pad_0x180_0x18c[4];
    volatile uint32_t xaiutocr; // offset: 0x0190
    volatile uint32_t __pad_0x194_0x1fc[27];
    volatile uint32_t xaiuqoscr; // offset: 0x0200
    volatile uint32_t xaiuqossr; // offset: 0x0204
    volatile uint32_t __pad_0x208_0x37c[94];
    volatile uint32_t xaiunrsbar; // offset: 0x0380
    volatile uint32_t xaiunrsbhr; // offset: 0x0384
    volatile uint32_t xaiunrsblr; // offset: 0x0388
    volatile uint32_t __pad_0x38c_0x39c[5];
    volatile uint32_t xaiubrar;  // offset: 0x03a0
    volatile uint32_t xaiubrblr; // offset: 0x03a4
    volatile uint32_t xaiubrbhr; // offset: 0x03a8
    volatile uint32_t __pad_0x3ac_0x3bc[5];
    volatile uint32_t xaiuamigr; // offset: 0x03c0
    volatile uint32_t xaiumifsr; // offset: 0x03c4
    volatile uint32_t __pad_0x3c8_0x3fc[14];
    volatile uint32_t xaiugprar0;  // offset: 0x0400
    volatile uint32_t xaiugprblr0; // offset: 0x0404
    volatile uint32_t xaiugprbhr0; // offset: 0x0408
    volatile uint32_t __pad_0x40c;
    volatile uint32_t xaiugprar1;  // offset: 0x0410
    volatile uint32_t xaiugprblr1; // offset: 0x0414
    volatile uint32_t xaiugprbhr1; // offset: 0x0418
    volatile uint32_t __pad_0x41c;
    volatile uint32_t xaiugprar2;  // offset: 0x0420
    volatile uint32_t xaiugprblr2; // offset: 0x0424
    volatile uint32_t xaiugprbhr2; // offset: 0x0428
    volatile uint32_t __pad_0x42c;
    volatile uint32_t xaiugprar3;  // offset: 0x0430
    volatile uint32_t xaiugprblr3; // offset: 0x0434
    volatile uint32_t xaiugprbhr3; // offset: 0x0438
    volatile uint32_t __pad_0x43c;
    volatile uint32_t xaiugprar4;  // offset: 0x0440
    volatile uint32_t xaiugprblr4; // offset: 0x0444
    volatile uint32_t xaiugprbhr4; // offset: 0x0448
    volatile uint32_t __pad_0x44c;
    volatile uint32_t xaiugprar5;  // offset: 0x0450
    volatile uint32_t xaiugprblr5; // offset: 0x0454
    volatile uint32_t xaiugprbhr5; // offset: 0x0458
    volatile uint32_t __pad_0x45c;
    volatile uint32_t xaiugprar6;  // offset: 0x0460
    volatile uint32_t xaiugprblr6; // offset: 0x0464
    volatile uint32_t xaiugprbhr6; // offset: 0x0468
    volatile uint32_t __pad_0x46c;
    volatile uint32_t xaiugprar7;  // offset: 0x0470
    volatile uint32_t xaiugprblr7; // offset: 0x0474
    volatile uint32_t xaiugprbhr7; // offset: 0x0478
    volatile uint32_t __pad_0x47c;
    volatile uint32_t xaiugprar8;  // offset: 0x0480
    volatile uint32_t xaiugprblr8; // offset: 0x0484
    volatile uint32_t xaiugprbhr8; // offset: 0x0488
    volatile uint32_t __pad_0x48c;
    volatile uint32_t xaiugprar9;  // offset: 0x0490
    volatile uint32_t xaiugprblr9; // offset: 0x0494
    volatile uint32_t xaiugprbhr9; // offset: 0x0498
    volatile uint32_t __pad_0x49c;
    volatile uint32_t xaiugprar10;  // offset: 0x04a0
    volatile uint32_t xaiugprblr10; // offset: 0x04a4
    volatile uint32_t xaiugprbhr10; // offset: 0x04a8
    volatile uint32_t __pad_0x4ac;
    volatile uint32_t xaiugprar11;  // offset: 0x04b0
    volatile uint32_t xaiugprblr11; // offset: 0x04b4
    volatile uint32_t xaiugprbhr11; // offset: 0x04b8
    volatile uint32_t __pad_0x4bc_0x804[211];
    volatile uint32_t xaiutbalr0;  // offset: 0x0808
    volatile uint32_t xaiutbahr0;  // offset: 0x080c
    volatile uint32_t xaiutopcr00; // offset: 0x0810
    volatile uint32_t xaiutopcr10; // offset: 0x0814
    volatile uint32_t xaiutubr0;   // offset: 0x0818
    volatile uint32_t xaiutubmr0;  // offset: 0x081c
    volatile uint32_t __pad_0x820_0x8fc[56];
    volatile uint32_t xaiucctrlr;  // offset: 0x0900
    volatile uint32_t xaiutctrlr0; // offset: 0x0904
    volatile uint32_t __pad_0x908_0x9fc[62];
    volatile uint32_t xaiuedr0; // offset: 0x0a00
    volatile uint32_t xaiuedr1; // offset: 0x0a04
    volatile uint32_t xaiuedr2; // offset: 0x0a08
    volatile uint32_t xaiuedr3; // offset: 0x0a0c
    volatile uint32_t xaiuedr4; // offset: 0x0a10
    volatile uint32_t xaiuedr5; // offset: 0x0a14
    volatile uint32_t xaiuedr6; // offset: 0x0a18
    volatile uint32_t xaiuedr7; // offset: 0x0a1c
    volatile uint32_t __pad_0xa20_0xafc[56];
    volatile uint32_t xaiucntcr0; // offset: 0x0b00
    volatile uint32_t xaiucntvr0; // offset: 0x0b04
    volatile uint32_t xaiucntsr0; // offset: 0x0b08
    volatile uint32_t __pad_0xb0c;
    volatile uint32_t xaiucntcr1; // offset: 0x0b10
    volatile uint32_t xaiucntvr1; // offset: 0x0b14
    volatile uint32_t xaiucntsr1; // offset: 0x0b18
    volatile uint32_t __pad_0xb1c;
    volatile uint32_t xaiucntcr2; // offset: 0x0b20
    volatile uint32_t xaiucntvr2; // offset: 0x0b24
    volatile uint32_t xaiucntsr2; // offset: 0x0b28
    volatile uint32_t __pad_0xb2c;
    volatile uint32_t xaiucntcr3; // offset: 0x0b30
    volatile uint32_t xaiucntvr3; // offset: 0x0b34
    volatile uint32_t xaiucntsr3; // offset: 0x0b38
    volatile uint32_t __pad_0xb3c_0xfec[301];
    volatile uint32_t xaiunrsar;  // offset: 0x0ff0
    volatile uint32_t xaiuengidr; // offset: 0x0ff4
    volatile uint32_t __pad_0xff8;
    volatile uint32_t xaiuinfor; // offset: 0x0ffc
} ccu_ncaiu_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t dceuidr;   // offset: 0x000
    volatile uint32_t dceufuidr; // offset: 0x004
    volatile uint32_t __pad_0x8_0x3c[14];
    volatile uint32_t dceutcr; // offset: 0x040
    volatile uint32_t dceutar; // offset: 0x044
    uint32_t __pad_0x48_0x4c[2];
    volatile uint32_t dceuser0; // offset: 0x050
    volatile uint32_t __pad_0x54_0xfc[43];
    volatile uint32_t dceucecr;  // offset: 0x100
    volatile uint32_t dceucesr;  // offset: 0x104
    volatile uint32_t dceucelr0; // offset: 0x108
    volatile uint32_t dceucelr1; // offset: 0x10c
    volatile uint32_t dceucesar; // offset: 0x110
    volatile uint32_t __pad_0x114_0x13c[11];
    volatile uint32_t dceuuedr;  // offset: 0x140
    volatile uint32_t dceuueir;  // offset: 0x144
    volatile uint32_t dceuuesr;  // offset: 0x148
    volatile uint32_t dceuuelr0; // offset: 0x14c
    volatile uint32_t dceuuelr1; // offset: 0x150
    volatile uint32_t dceuuesar; // offset: 0x154
    volatile uint32_t __pad_0x158_0x18c[14];
    volatile uint32_t dceutocr; // offset: 0x190
    volatile uint32_t __pad_0x194_0x1fc[27];
    volatile uint32_t dceuqoscr0; // offset: 0x200
    volatile uint32_t __pad_0x204_0x23c[15];
    volatile uint32_t dceusfmcr; // offset: 0x240
    volatile uint32_t dceusfmar; // offset: 0x244
    volatile uint32_t __pad_0x248_0x39c[86];
    volatile uint32_t dceubrar;  // offset: 0x3a0
    volatile uint32_t dceubrblr; // offset: 0x3a4
    volatile uint32_t dceubrbhr; // offset: 0x3a8
    volatile uint32_t __pad_0x3ac_0x3bc[5];
    volatile uint32_t dceuamigr; // offset: 0x3c0
    volatile uint32_t dceumifsr; // offset: 0x3c4
    volatile uint32_t __pad_0x3c8_0x3fc[14];
    volatile uint32_t dceugprar0;  // offset: 0x400
    volatile uint32_t dceugprblr0; // offset: 0x404
    volatile uint32_t dceugprbhr0; // offset: 0x408
    volatile uint32_t __pad_0x40c;
    volatile uint32_t dceugprar1;  // offset: 0x410
    volatile uint32_t dceugprblr1; // offset: 0x414
    volatile uint32_t dceugprbhr1; // offset: 0x418
    volatile uint32_t __pad_0x41c;
    volatile uint32_t dceugprar2;  // offset: 0x420
    volatile uint32_t dceugprblr2; // offset: 0x424
    volatile uint32_t dceugprbhr2; // offset: 0x428
    volatile uint32_t __pad_0x42c;
    volatile uint32_t dceugprar3;  // offset: 0x430
    volatile uint32_t dceugprblr3; // offset: 0x434
    volatile uint32_t dceugprbhr3; // offset: 0x438
    volatile uint32_t __pad_0x43c;
    volatile uint32_t dceugprar4;  // offset: 0x440
    volatile uint32_t dceugprblr4; // offset: 0x444
    volatile uint32_t dceugprbhr4; // offset: 0x448
    volatile uint32_t __pad_0x44c;
    volatile uint32_t dceugprar5;  // offset: 0x450
    volatile uint32_t dceugprblr5; // offset: 0x454
    volatile uint32_t dceugprbhr5; // offset: 0x458
    volatile uint32_t __pad_0x45c;
    volatile uint32_t dceugprar6;  // offset: 0x460
    volatile uint32_t dceugprblr6; // offset: 0x464
    volatile uint32_t dceugprbhr6; // offset: 0x468
    volatile uint32_t __pad_0x46c;
    volatile uint32_t dceugprar7;  // offset: 0x470
    volatile uint32_t dceugprblr7; // offset: 0x474
    volatile uint32_t dceugprbhr7; // offset: 0x478
    volatile uint32_t __pad_0x47c;
    volatile uint32_t dceugprar8;  // offset: 0x480
    volatile uint32_t dceugprblr8; // offset: 0x484
    volatile uint32_t dceugprbhr8; // offset: 0x488
    volatile uint32_t __pad_0x48c;
    volatile uint32_t dceugprar9;  // offset: 0x490
    volatile uint32_t dceugprblr9; // offset: 0x494
    volatile uint32_t dceugprbhr9; // offset: 0x498
    volatile uint32_t __pad_0x49c;
    volatile uint32_t dceugprar10;  // offset: 0x4a0
    volatile uint32_t dceugprblr10; // offset: 0x4a4
    volatile uint32_t dceugprbhr10; // offset: 0x4a8
    volatile uint32_t __pad_0x4ac;
    volatile uint32_t dceugprar11;  // offset: 0x4b0
    volatile uint32_t dceugprblr11; // offset: 0x4b4
    volatile uint32_t dceugprbhr11; // offset: 0x4b8
    volatile uint32_t __pad_0x4bc_0xbfc[337];
    volatile uint32_t dceuedr0; // offset: 0xa00
    volatile uint32_t __pad_0xa04_0xaff[63];
    volatile uint32_t dcecntcr0; // offset: 0xb00
    volatile uint32_t dcecntvr0; // offset: 0xb04
    volatile uint32_t dcecntsr0; // offset: 0xb08
    volatile uint32_t __pad_0xb0c;
    volatile uint32_t dcecntcr1; // offset: 0xb10
    volatile uint32_t dcecntvr1; // offset: 0xb14
    volatile uint32_t dcecntsr1; // offset: 0xb18
    volatile uint32_t __pad_0xb1c;
    volatile uint32_t dcecntcr2; // offset: 0xb20
    volatile uint32_t dcecntvr2; // offset: 0xb24
    volatile uint32_t dcecntsr2; // offset: 0xb28
    volatile uint32_t __pad_0xb2c;
    volatile uint32_t dcecntcr3; // offset: 0xb30
    volatile uint32_t dcecntvr3; // offset: 0xb34
    volatile uint32_t dcecntsr3; // offset: 0xb38
    volatile uint32_t __pad_0xb3c_0xbfc[49];
    volatile uint32_t dceuccr0; // offset: 0xc00
    volatile uint32_t dceuccr1; // offset: 0xc04
    volatile uint32_t __pad_0xc08_0xc7c[30];
    volatile uint32_t dcemcntcr; // offset: 0xc80
    volatile uint32_t __pad_0xc84_0xfec[219];
    volatile uint32_t dceusbsir;  // offset: 0xff0
    volatile uint32_t dceuengidr; // offset: 0xff4
    volatile uint32_t __pad_0xff8;
    volatile uint32_t dceuinfor; // offset: 0xffc
} ccu_dce_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t dmiuidr;   // offset: 0x000
    volatile uint32_t dmiufuidr; // offset: 0x004
    volatile uint32_t __pad_0x8_0x40[15];
    volatile uint32_t dmiutar; // offset: 0x044
    volatile uint32_t __pad_0x48_0xfc[46];
    volatile uint32_t dmiuuedr;  // offset: 0x100
    volatile uint32_t dmiuueir;  // offset: 0x104
    volatile uint32_t dmiuuesr;  // offset: 0x108
    volatile uint32_t dmiuuelr0; // offset: 0x10c
    volatile uint32_t dmiuuelr1; // offset: 0x110
    volatile uint32_t dmiuuesar; // offset: 0x114
    volatile uint32_t __pad_0x118_0x13c[10];
    volatile uint32_t dmiucecr;  // offset: 0x140
    volatile uint32_t dmiucesr;  // offset: 0x144
    volatile uint32_t dmiucelr0; // offset: 0x148
    volatile uint32_t dmiucelr1; // offset: 0x14c
    volatile uint32_t dmiucesar; // offset: 0x150
    volatile uint32_t __pad_0x154_0x18f[15];
    volatile uint32_t dmiutocr; // offset: 0x190
    volatile uint32_t __pad_0x194_0x1fc[27];
    volatile uint32_t dmiuqoscr0; // offset: 0x200
    volatile uint32_t __pad_0x204_0x2fc[63];
    volatile uint32_t dmiusmctcr; // offset: 0x300
    volatile uint32_t dmiusmctar; // offset: 0x304
    volatile uint32_t dmiusmcapr; // offset: 0x308
    volatile uint32_t dmiusmcisr; // offset: 0x30c
    volatile uint32_t __pad_0x310_0x3fc[12];
    volatile uint32_t dmiusmcmcr;  // offset: 0x340
    volatile uint32_t dmiusmcmar;  // offset: 0x344
    volatile uint32_t dmiusmcmlr0; // offset: 0x348
    volatile uint32_t dmiusmcmlr1; // offset: 0x34c
    volatile uint32_t dmiusmcmdr;  // offset: 0x350
    volatile uint32_t __pad_0x354_0x7fc[299];
    volatile uint32_t dmicctrlr; // offset: 0x800
    volatile uint32_t __pad_0x804_0xafc[191];
    volatile uint32_t dmicntcr0; // offset: 0xb00
    volatile uint32_t dmicntvr0; // offset: 0xb04
    volatile uint32_t dmicntsr0; // offset: 0xb08
    volatile uint32_t __pad_0xb0c;
    volatile uint32_t dmicntcr1; // offset: 0xb10
    volatile uint32_t dmicntvr1; // offset: 0xb14
    volatile uint32_t dmicntsr1; // offset: 0xb18
    volatile uint32_t __pad_0xb1c;
    volatile uint32_t dmicntcr2; // offset: 0xb20
    volatile uint32_t dmicntvr2; // offset: 0xb24
    volatile uint32_t dmicntsr2; // offset: 0xb28
    volatile uint32_t __pad_0xb2c;
    volatile uint32_t dmicntcr3; // offset: 0xb30
    volatile uint32_t dmicntvr3; // offset: 0xb34
    volatile uint32_t dmicntsr3; // offset: 0xb38
    volatile uint32_t __pad_0xb3c_0xbfc[49];
    volatile uint32_t dmibcntfr0; // offset: 0xC00
    volatile uint32_t dmibcntmr0; // offset: 0xc04
    volatile uint32_t dmibcntfr1; // offset: 0xc08
    volatile uint32_t dmibcntmr1; // offset: 0xc0c
    volatile uint32_t dmibcntfr2; // offset: 0xc10
    volatile uint32_t dmibcntmr2; // offset: 0xc14
    volatile uint32_t dmibcntfr3; // offset: 0xc18
    volatile uint32_t dmibcntmr3; // offset: 0xc1c
    volatile uint32_t __pad_0xc20_0xc7c[24];
    volatile uint32_t dmilcntcr; // offset: 0xc80
    volatile uint32_t dmimcntcr; // offset: 0xc84
    volatile uint32_t __pad_0xc88_0xfdc[214];
    volatile uint32_t mrdsbsir; // offset: 0xfe0
    volatile uint32_t __pad_0xfe4_0xfec[3];
    volatile uint32_t cmdsbsir;   // offset: 0xff0
    volatile uint32_t dmiuevidr;  // offset: 0xff4
    volatile uint32_t dmiusmcifr; // offset: 0xff8
    volatile uint32_t dmiuinfor;  // offset: 0xffc
} ccu_dmi_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t diiuidr;   // offset: 0x000
    volatile uint32_t diiufuidr; // offset: 0x004
    volatile uint32_t __pad_0x8_0x3f[14];
    volatile uint32_t diiutar; // offset: 0x040
    volatile uint32_t __pad_0x44_0x114[53];
    volatile uint32_t diiuuedr;  // offset: 0x118
    volatile uint32_t diiuueir;  // offset: 0x11c
    volatile uint32_t diiuuesr;  // offset: 0x120
    volatile uint32_t diiuuelr0; // offset: 0x124
    volatile uint32_t diiuuelr1; // offset: 0x128
    volatile uint32_t diiuuesar; // offset: 0x12c
    volatile uint32_t __pad_0x130_0x8fc[500];
    volatile uint32_t diicctrlr; // offset: 0x900
    volatile uint32_t __pad_0x904_0xafc[127];
    volatile uint32_t diicntcr0; // offset: 0xb00
    volatile uint32_t diicntvr0; // offset: 0xb04
    volatile uint32_t diicntsr0; // offset: 0xb08
    volatile uint32_t __pad_0xb0c;
    volatile uint32_t diicntcr1; // offset: 0xb10
    volatile uint32_t diicntvr1; // offset: 0xb14
    volatile uint32_t diicntsr1; // offset: 0xb18
    volatile uint32_t __pad_0xb1c;
    volatile uint32_t diicntcr2; // offset: 0xb20
    volatile uint32_t diicntvr2; // offset: 0xb24
    volatile uint32_t diicntsr2; // offset: 0xb28
    volatile uint32_t __pad_0xb2c;
    volatile uint32_t diicntcr3; // offset: 0xb30
    volatile uint32_t diicntvr3; // offset: 0xb34
    volatile uint32_t diicntsr3; // offset: 0xb38
    volatile uint32_t __pad_0xb3c_bfc[49];
    volatile uint32_t diibcntfr0; // offset: 0xc00
    volatile uint32_t diibcntmr0; // offset: 0xc04
    volatile uint32_t diibcntfr1; // offset: 0xc08
    volatile uint32_t diibcntmr1; // offset: 0xc0c
    volatile uint32_t diibcntfr2; // offset: 0xc10
    volatile uint32_t diibcntmr2; // offset: 0xc14
    volatile uint32_t diibcntfr3; // offset: 0xc18
    volatile uint32_t diibcntmr3; // offset: 0xc1c
    volatile uint32_t __pad_0xc20_0xc7c[24];
    volatile uint32_t diilcntcr; // offset: 0xc80
    volatile uint32_t diimcntcr; // offset: 0xc84
    volatile uint32_t __pad_0xc88_0xfec0[218];
    volatile uint32_t diiusbsir; // offset: 0xff0
    volatile uint32_t diiuuevir; // offset: 0xff4
    volatile uint32_t __pad_0xff8;
    volatile uint32_t diiuinfor; // offset: 0xffc
} ccu_dii_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t dveuidr;   // offset: 0x000
    volatile uint32_t dveufuidr; // offset: 0x004
    volatile uint32_t __pad_0x8_0x40[15];
    volatile uint32_t dveutar; // offset: 0x044
    volatile uint32_t __pad_0x48_0xfc[46];
    volatile uint32_t dvececr; // offset: 0x100
    volatile uint32_t __pad_0x104;
    volatile uint32_t dvecesr;  // offset: 0x108
    volatile uint32_t dvecelr0; // offset: 0x10c
    volatile uint32_t dvecelr1; // offset: 0x110
    volatile uint32_t dvecesar; // offset: 0x114
    volatile uint32_t __pad_0x118_0x13c[10];
    volatile uint32_t dveuuedr;  // offset: 0x140
    volatile uint32_t dveuueir;  // offset: 0x144
    volatile uint32_t dveuuesr;  // offset: 0x148
    volatile uint32_t dveuuelr0; // offset: 0x14c
    volatile uint32_t dveuuelr1; // offset: 0x150
    volatile uint32_t dveuesar;  // offset: 0x154
    volatile uint32_t __pad_0x158_0x17c[10];
    volatile uint32_t dveucrtr; // offset: 0x180
    volatile uint32_t __pad_0x184_0x3fc[159];
    volatile uint32_t dveuser0; // offset: 0x400
    volatile uint32_t __pad_0x404_0x8ff[319];
    volatile uint32_t dvetascr;  // offset: 0x900
    volatile uint32_t dvetadhr;  // offset: 0x904
    volatile uint32_t dvetadtsr; // offset: 0x908
    volatile uint32_t __pad_0x90c;
    volatile uint32_t dvetad0r;  // offset: 0x910
    volatile uint32_t dvetad1r;  // offset: 0x914
    volatile uint32_t dvetad2r;  // offset: 0x918
    volatile uint32_t dvetad3r;  // offset: 0x91c
    volatile uint32_t dvetad4r;  // offset: 0x920
    volatile uint32_t dvetad5r;  // offset: 0x924
    volatile uint32_t dvetad6r;  // offset: 0x928
    volatile uint32_t dvetad7r;  // offset: 0x92c
    volatile uint32_t dvetad8r;  // offset: 0x930
    volatile uint32_t dvetad9r;  // offset: 0x934
    volatile uint32_t dvetad10r; // offset: 0x938
    volatile uint32_t dvetad11r; // offset: 0x93c
    volatile uint32_t dvetad12r; // offset: 0x940
    volatile uint32_t dvetad13r; // offset: 0x944
    volatile uint32_t dvetad14r; // offset: 0x948
    volatile uint32_t dvetad15r; // offset: 0x94c
    volatile uint32_t __pad_0x950_0xafc[108];
    volatile uint32_t dvecntcr0; // offset: 0xb00
    volatile uint32_t dvecntvr0; // offset: 0xb04
    volatile uint32_t dvecntsr0; // offset: 0xb08
    volatile uint32_t __pad_0xb0c;
    volatile uint32_t dvecntcr1; // offset: 0xb10
    volatile uint32_t dvecntvr1; // offset: 0xb14
    volatile uint32_t dvecntsr1; // offset: 0xb18
    volatile uint32_t __pad_0xb1c;
    volatile uint32_t dvecntcr2; // offset: 0xb20
    volatile uint32_t dvecntvr2; // offset: 0xb24
    volatile uint32_t dvecntsr2; // offset: 0xb28
    volatile uint32_t __pad_0xb2c;
    volatile uint32_t dvecntcr3; // offset: 0xb30
    volatile uint32_t dvecntvr3; // offset: 0xb34
    volatile uint32_t dvecntsr3; // offset: 0xb38
    volatile uint32_t __pad_0xb3c_0xc7c[81];
    volatile uint32_t dvemcntcr; // offset: 0xc80
    volatile uint32_t __pad_0xc84_0xfec[219];
    volatile uint32_t dveuengdbr; // offset: 0xff0
    volatile uint32_t dveuengidr; // offset: 0xff4
    volatile uint32_t __pad_0xff8;
    volatile uint32_t dveuinfor; // offset: 0xffc
} ccu_dve_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {
    volatile uint32_t grbucssfidr0;          // offset: 0xf00
    volatile uint32_t __pad_0xf04_0xfec[59]; // padding
    volatile uint32_t grbunrrir;             // offset: 0xff0
    volatile uint32_t grbuengidr;            // offset: 0xff4
    volatile uint32_t grbunrrucr;            // offset: 0xff8
    volatile uint32_t grbunsidr;             // offset: 0xffc
} ccu_sys_global_register_blk_regs_t;

typedef struct __attribute__((packed)) __attribute__((aligned(4))) {

    volatile ccu_caiu_regs_t dsu;       // offset 0x0
    volatile ccu_ncaiu_regs_t ncaiu[4]; // offset 0x1000: fpga2soc, 0x2000: gic_m, 0x3000: tcu, 0x4000: ccu_iom
    volatile ccu_dce_regs_t dce[2];     // offset 0x5000: dce0, 0x6000: dce1
    volatile ccu_dmi_regs_t dmi[2];     // offset 0x7000: dmi0, 0x8000: dmi1
    volatile ccu_dii_regs_t
        dii[5]; // offset 0x9000: ccu_ios, 0xa000: ccu_mpfe_csr, 0xb000: gic_csr, 0xc000: ocram, 0xd000: sys_dii
    volatile ccu_dve_regs_t dve; // offset 0xe000
    volatile uint32_t __pad_0xf000_0xffffc[246720];
    volatile ccu_sys_global_register_blk_regs_t sys_global_register_blk; // offset 0xfff00
} ccu_regs_t;

#endif // CCU_REGS_H__