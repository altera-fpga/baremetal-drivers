#include "rstmgr.h"
#include "rstmgr_internal.h"
#include "rstmgr_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

#define OFFSET_STAT 0x00000000
#define OFFSET_MISCSTAT 0x00000008
#define OFFSET_HDSKEN 0x00000010
#define OFFSET_HDSKREQ 0x00000014
#define OFFSET_HDSKACK 0x00000018
#define OFFSET_HDSKSTALL 0x0000001C
#define OFFSET_PER0MODRST 0x00000024
#define OFFSET_PER1MODRST 0x00000028
#define OFFSET_BRGMODRST 0x0000002C
#define OFFSET_DBGMODRST 0x0000003C
#define OFFSET_BRGWARMMASK 0x0000004C
#define OFFSET_TSTSTA 0x0000005C
#define OFFSET_HDSKTIMEOUT 0x00000064
#define OFFSET_DBGHDSKTIMEOUT 0x0000006C
#define OFFSET_DBGRSTCMPLT 0x00000070
#define OFFSET_HPSRSTCMPLT 0x00000080
#define OFFSET_CPUINRESET 0x00000090
#define OFFSET_CPURSTRELEASE 0x00000094
#define OFFSET_CPU0_RESET_BASE_LOW 0x00000098
#define OFFSET_CPU0_RESET_BASE_HIGH 0x0000009C
#define OFFSET_CPU1_RESET_BASE_LOW 0x000000A0
#define OFFSET_CPU1_RESET_BASE_HIGH 0x000000A4
#define OFFSET_CPU2_RESET_BASE_LOW 0x000000A8
#define OFFSET_CPU2_RESET_BASE_HIGH 0x000000AC
#define OFFSET_CPU3_RESET_BASE_LOW 0x000000B0
#define OFFSET_CPU3_RESET_BASE_HIGH 0x000000B4

class RstmgrTest : public ::testing::TestWithParam<int> {
  protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Open/Close Valid/Invalid cases
TEST_F(RstmgrTest, OpenValidDevice) {
    int32_t fd = rstmgr_open("/dev/rstmgr", 0);
    ASSERT_GE(fd, 0);
    rstmgr_close(fd);
}

TEST_F(RstmgrTest, OpenInvalidDevice) {
    int32_t fd = rstmgr_open("/dev/inval", 0);
    ASSERT_EQ(fd, -1);
}

TEST_F(RstmgrTest, CloseValidFd) {
    int32_t fd = rstmgr_open("/dev/rstmgr", 0);
    ASSERT_GE(fd, 0);
    int32_t result = rstmgr_close(fd);
    ASSERT_EQ(result, 0);
}

TEST_F(RstmgrTest, CloseInvalidFd) {
    int32_t result = rstmgr_close(-1);
    ASSERT_EQ(result, -1);
}

// All Register access
TEST_F(RstmgrTest, IoctlAllRegsRead) {
    int32_t fd = rstmgr_open("/dev/rstmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_RSTMGR_READ;
    hps_rstmgr_regs_t value = {0};
    int32_t result = rstmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value), sizeof(hps_rstmgr_regs_t));
    EXPECT_EQ(result, 0);

    result = rstmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value), sizeof(uint32_t));
    EXPECT_NE(result, 0); // Fails as provided data length is too small

    // Add assertions to check the side effects of each IOCTL

    rstmgr_close(fd);
}

TEST_F(RstmgrTest, IoctlAllRegsWrite) {
    int32_t fd = rstmgr_open("/dev/rstmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = IOCTL_RSTMGR_WRITE;
    hps_rstmgr_regs_t value = {0};
    int32_t result = rstmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value), sizeof(hps_rstmgr_regs_t));
    EXPECT_EQ(result, 0);

    result = rstmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value), sizeof(uint32_t));
    EXPECT_NE(result, 0); // Fails as provided data length is too small

    // Add assertions to check the side effects of each IOCTL

    rstmgr_close(fd);
}

// Access each of the IOCTL functions
TEST_P(RstmgrTest, IoctlNotAllRegs) {
    int32_t fd = rstmgr_open("/dev/rstmgr", 0);
    ASSERT_GE(fd, 0);

    int32_t ioctlCode = GetParam();
    uint32_t value = 0;
    int32_t result = rstmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value), sizeof(uint32_t));
    EXPECT_EQ(result, 0);

    result = rstmgr_ioctl(fd, ioctlCode, (uintptr_t)(&value), 0);
    EXPECT_NE(result, 0); // Fails as provided data length is too small

    // Add assertions to check the side effects of each IOCTL

    rstmgr_close(fd);
}

INSTANTIATE_TEST_SUITE_P(
    RstmgrIoctlTests, RstmgrTest,
    ::testing::Values(IOCTL_RSTMGR_GET_STAT, IOCTL_RSTMGR_SET_STAT, IOCTL_RSTMGR_GET_MISCSTAT,
                      IOCTL_RSTMGR_SET_MISCSTAT, IOCTL_RSTMGR_GET_HDSKEN, IOCTL_RSTMGR_SET_HDSKEN,
                      IOCTL_RSTMGR_GET_HDSKREQ, IOCTL_RSTMGR_SET_HDSKREQ, IOCTL_RSTMGR_SET_HDSKACK,
                      IOCTL_RSTMGR_GET_HDSKACK, IOCTL_RSTMGR_SET_HDSKSTALL, IOCTL_RSTMGR_GET_HDSKSTALL,
                      IOCTL_RSTMGR_GET_PER0MODRST, IOCTL_RSTMGR_SET_PER0MODRST, IOCTL_RSTMGR_GET_PER1MODRST,
                      IOCTL_RSTMGR_SET_PER1MODRST, IOCTL_RSTMGR_GET_BRGMODRST, IOCTL_RSTMGR_SET_BRGMODRST,
                      IOCTL_RSTMGR_GET_DBGMODRST, IOCTL_RSTMGR_SET_DBGMODRST, IOCTL_RSTMGR_GET_BRGWARMMASK,
                      IOCTL_RSTMGR_SET_BRGWARMMASK, IOCTL_RSTMGR_GET_TSTSTA, IOCTL_RSTMGR_GET_HDSKTIMEOUT,
                      IOCTL_RSTMGR_SET_HDSKTIMEOUT, IOCTL_RSTMGR_GET_DBGHDSKTIMEOUT, IOCTL_RSTMGR_SET_DBGHDSKTIMEOUT,
                      IOCTL_RSTMGR_GET_DBGRSTCMPLT, IOCTL_RSTMGR_SET_DBGRSTCMPLT, IOCTL_RSTMGR_GET_HPSRSTCMPLT,
                      IOCTL_RSTMGR_SET_HPSRSTCMPLT, IOCTL_RSTMGR_GET_CPUINRESET, IOCTL_RSTMGR_GET_CPURSTRELEASE,
                      IOCTL_RSTMGR_SET_CPURSTRELEASE, IOCTL_RSTMGR_GET_CPU0_RESET_BASE_LOW,
                      IOCTL_RSTMGR_SET_CPU0_RESET_BASE_LOW, IOCTL_RSTMGR_GET_CPU0_RESET_BASE_HIGH,
                      IOCTL_RSTMGR_SET_CPU0_RESET_BASE_HIGH, IOCTL_RSTMGR_GET_CPU1_RESET_BASE_LOW,
                      IOCTL_RSTMGR_SET_CPU1_RESET_BASE_LOW, IOCTL_RSTMGR_GET_CPU1_RESET_BASE_HIGH,
                      IOCTL_RSTMGR_SET_CPU1_RESET_BASE_HIGH, IOCTL_RSTMGR_GET_CPU2_RESET_BASE_LOW,
                      IOCTL_RSTMGR_SET_CPU2_RESET_BASE_LOW, IOCTL_RSTMGR_GET_CPU2_RESET_BASE_HIGH,
                      IOCTL_RSTMGR_SET_CPU2_RESET_BASE_HIGH, IOCTL_RSTMGR_GET_CPU3_RESET_BASE_LOW,
                      IOCTL_RSTMGR_SET_CPU3_RESET_BASE_LOW));

// Verify the offset of each register is correct
TEST_F(RstmgrTest, OffsetVerification) {

    int32_t result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, stat));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_STAT));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, miscstat));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_MISCSTAT));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, hdsken));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_HDSKEN));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, hdskreq));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_HDSKREQ));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, hdskack));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_HDSKACK));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, hdskstall));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_HDSKSTALL));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, per0modrst));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PER0MODRST));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, per1modrst));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_PER1MODRST));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, brgmodrst));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_BRGMODRST));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, dbgmodrst));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_DBGMODRST));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, brgwarmmask));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_BRGWARMMASK));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, tststa));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_TSTSTA));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, hdsktimeout));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_HDSKTIMEOUT));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, dbghdsktimeout));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_DBGHDSKTIMEOUT));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, dbgrstcmplt));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_DBGRSTCMPLT));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, hpsrstcmplt));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_HPSRSTCMPLT));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpuinreset));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPUINRESET));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpurstrelease));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPURSTRELEASE));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu0_reset_base_low));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU0_RESET_BASE_LOW));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu0_reset_base_high));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU0_RESET_BASE_HIGH));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu1_reset_base_low));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU1_RESET_BASE_LOW));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu1_reset_base_high));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU1_RESET_BASE_HIGH));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu2_reset_base_low));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU2_RESET_BASE_LOW));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu2_reset_base_high));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU2_RESET_BASE_HIGH));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu3_reset_base_low));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU3_RESET_BASE_LOW));

    result = static_cast<int32_t>(offsetof(hps_rstmgr_regs_t, cpu3_reset_base_high));
    EXPECT_EQ(result, static_cast<int32_t>(OFFSET_CPU3_RESET_BASE_HIGH));
}
