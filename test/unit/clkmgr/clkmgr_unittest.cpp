#include "clkmgr.h"
#include "clkmgr_internal.h"
#include "clkmgr_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

#define MAINPLL_OFFSET 0x00000024
#define PERPLL_OFFSET 0x0000007C
#define CTLGRP_OFFSET 0x000000D0

#define OFFSET_CLKMGR_CTRL 0x00000000
#define OFFSET_CLKMGR_STAT 0x00000004
#define OFFSET_CLKMGR_TESTIOCTRL 0x00000008
#define OFFSET_CLKMGR_INTRGEN 0x0000000C
#define OFFSET_CLKMGR_INTRMSK 0x00000010
#define OFFSET_CLKMGR_INTRCLR 0x00000014
#define OFFSET_CLKMGR_INTRSTS 0x00000018
#define OFFSET_CLKMGR_INTRSTK 0x0000001C
#define OFFSET_CLKMGR_INTRRAW 0x00000020

#define OFFSET_MAINPLL_EN (0x00000024 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_ENS (0x00000028 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_ENR (0x0000002C - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_BYPASS (0x00000030 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_BYPASSS (0x00000034 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_BYPASSR (0x00000038 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_NOCCLK (0x00000040 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_NOCDIV (0x00000044 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_PLLGLOB (0x00000048 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_FDBCK (0x0000004C - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_MEM (0x00000050 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_MEMSTAT (0x00000054 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_VCOCALIB (0x00000058 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_PLLC0 (0x0000005C - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_PLLC1 (0x00000060 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_PLLC2 (0x00000064 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_PLLC3 (0x00000068 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_PLLM (0x0000006C - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_FHOP (0x00000070 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_SSC (0x00000074 - MAINPLL_OFFSET)
#define OFFSET_MAINPLL_LOSTLOCK (0x00000078 - MAINPLL_OFFSET)

#define OFFSET_PERPLL_EN (0x0000007C - PERPLL_OFFSET)
#define OFFSET_PERPLL_ENS (0x00000080 - PERPLL_OFFSET)
#define OFFSET_PERPLL_ENR (0x00000084 - PERPLL_OFFSET)
#define OFFSET_PERPLL_BYPASS (0x00000088 - PERPLL_OFFSET)
#define OFFSET_PERPLL_BYPASSS (0x0000008C - PERPLL_OFFSET)
#define OFFSET_PERPLL_BYPASSR (0x00000090 - PERPLL_OFFSET)
#define OFFSET_PERPLL_EMACCTL (0x00000094 - PERPLL_OFFSET)
#define OFFSET_PERPLL_GPIODIV (0x00000098 - PERPLL_OFFSET)
#define OFFSET_PERPLL_PLLGLOB (0x0000009C - PERPLL_OFFSET)
#define OFFSET_PERPLL_FDBCK (0x000000A0 - PERPLL_OFFSET)
#define OFFSET_PERPLL_MEM (0x000000A4 - PERPLL_OFFSET)
#define OFFSET_PERPLL_MEMSTAT (0x000000A8 - PERPLL_OFFSET)
#define OFFSET_PERPLL_VCOCALIB (0x000000AC - PERPLL_OFFSET)
#define OFFSET_PERPLL_PLLC0 (0x000000B0 - PERPLL_OFFSET)
#define OFFSET_PERPLL_PLLC1 (0x000000B4 - PERPLL_OFFSET)
#define OFFSET_PERPLL_PLLC2 (0x000000B8 - PERPLL_OFFSET)
#define OFFSET_PERPLL_PLLC3 (0x000000BC - PERPLL_OFFSET)
#define OFFSET_PERPLL_PLLM (0x000000C0 - PERPLL_OFFSET)
#define OFFSET_PERPLL_FHOP (0x000000C4 - PERPLL_OFFSET)
#define OFFSET_PERPLL_SSC (0x000000C8 - PERPLL_OFFSET)
#define OFFSET_PERPLL_LOSTLOCK (0x000000CC - PERPLL_OFFSET)

#define OFFSET_CTLGRP_JTAG (0x000000D0 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_EMACACTR (0x000000D4 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_EMACBCTR (0x000000D8 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_EMACPTPCTR (0x000000DC - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_GPIODBCTR (0x000000E0 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_S2FUSER0CTR (0x000000E8 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_S2FUSER1CTR (0x000000EC - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_PSIREFCTR (0x000000F0 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_EXTCNTRST (0x000000F4 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_USB31CTR (0x000000F8 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_DSUCTR (0x000000FC - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_CORE01CTR (0x00000100 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_CORE23CTR (0x00000104 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_CORE2CTR (0x00000108 - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_CORE3CTR (0x0000010C - CTLGRP_OFFSET)
#define OFFSET_CTLGRP_SERIAL_CON_PLL_CTR (0x00000110 - CTLGRP_OFFSET)

class ClkmgrTest : public ::testing::TestWithParam<int> {
  protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Open/Close Valid/Invalid cases
TEST_F(ClkmgrTest, OpenValidDevice) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);
    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, OpenInvalidDevice) {
    int32_t fd = clkmgr_open("/dev/inval", 0);
    ASSERT_EQ(fd, -1);
}

TEST_F(ClkmgrTest, CloseValidFd) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);
    int32_t result = clkmgr_close(fd);
    ASSERT_EQ(result, 0);
}

TEST_F(ClkmgrTest, CloseInvalidFd) {
    int32_t result = clkmgr_close(-1);
    ASSERT_EQ(result, -1);
}

// All Register access

TEST_F(ClkmgrTest, IoctlClkmgrRegsRead) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_REGS_READ;
    hps_clkmgr_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrRegsWrite) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_REGS_WRITE;
    hps_clkmgr_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrMainPllRegsRead) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_MAINPLL_REGS_READ;
    hps_clkmgr_mainpll_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrMainPllRegsWrite) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_MAINPLL_REGS_WRITE;
    hps_clkmgr_mainpll_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrPerPllRegsRead) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_PERPLL_REGS_READ;
    hps_clkmgr_perpll_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrPerPllRegsWrite) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_PERPLL_REGS_WRITE;
    hps_clkmgr_perpll_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrCtlGrpRegsRead) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_CTLGRP_READ;
    hps_clkmgr_ctlgrp_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

TEST_F(ClkmgrTest, IoctlClkmgrCtlGrpRegsWrite) {
    int32_t fd = clkmgr_open("/dev/clkmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_CLKMGR_CTLGRP_WRITE;
    hps_clkmgr_ctlgrp_regs_t value = {0};
    int32_t result = clkmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value));
    EXPECT_EQ(result, 0);

    // Add assertions to check the side effects of each IOCTL

    clkmgr_close(fd);
}

// Verify the offset of each register is correct
TEST_F(ClkmgrTest, OffsetVerification) {

    int32_t result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, ctrl));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_CTRL));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, stat));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_STAT));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, testioctrl));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_TESTIOCTRL));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, intrgen));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_INTRGEN));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, intrmsk));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_INTRMSK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, intrclr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_INTRCLR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, intrsts));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_INTRSTS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, intrstk));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_INTRSTK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_regs_t, intrraw));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CLKMGR_INTRRAW));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, en));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_EN));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, ens));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_ENS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, enr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_ENR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, bypass));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_BYPASS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, bypasss));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_BYPASSS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, bypassr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_BYPASSR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, nocclk));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_NOCCLK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, nocdiv));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_NOCDIV));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, pllglob));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_PLLGLOB));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, fdbck));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_FDBCK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, mem));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_MEM));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, memstat));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_MEMSTAT));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, vcocalib));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_VCOCALIB));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, pllc0));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_PLLC0));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, pllc1));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_PLLC1));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, pllc2));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_PLLC2));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, pllc3));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_PLLC3));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, pllm));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_PLLM));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, fhop));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_FHOP));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, ssc));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_SSC));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_mainpll_regs_t, lostlock));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MAINPLL_LOSTLOCK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, en));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_EN));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, ens));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_ENS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, enr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_ENR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, bypass));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_BYPASS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, bypasss));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_BYPASSS));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, bypassr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_BYPASSR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, emacctl));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_EMACCTL));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, gpiodiv));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_GPIODIV));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, pllglob));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_PLLGLOB));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, fdbck));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_FDBCK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, mem));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_MEM));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, memstat));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_MEMSTAT));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, vcocalib));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_VCOCALIB));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, pllc0));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_PLLC0));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, pllc1));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_PLLC1));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, pllc2));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_PLLC2));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, pllc3));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_PLLC3));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, pllm));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_PLLM));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, fhop));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_FHOP));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, ssc));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_SSC));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_perpll_regs_t, lostlock));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PERPLL_LOSTLOCK));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, jtag));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_JTAG));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, emacactr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_EMACACTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, emacbctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_EMACBCTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, emacptpctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_EMACPTPCTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, gpiodbctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_GPIODBCTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, s2fuser0ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_S2FUSER0CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, s2fuser1ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_S2FUSER1CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, psirefctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_PSIREFCTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, extcntrst));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_EXTCNTRST));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, usb31ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_USB31CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, dsuctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_DSUCTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, core01ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_CORE01CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, core23ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_CORE23CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, core2ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_CORE2CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, core3ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_CORE3CTR));

    result = static_cast<int32_t>(offsetof(hps_clkmgr_ctlgrp_regs_t, serial_con_pll_ctr));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CTLGRP_SERIAL_CON_PLL_CTR));
}