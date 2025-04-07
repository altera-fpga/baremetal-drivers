#include "sysmgr.h"
#include "sysmgr_regs.h"
#include "gtest/gtest.h"

class SysmgrTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

TEST_F(SysmgrTest, OpenValidDevice) {
    int32_t fd = sysmgr_open("/dev/sysmgr", 0);
    ASSERT_GE(fd, 0);
    sysmgr_close(fd);
}

TEST_F(SysmgrTest, OpenInvalidDevice) {
    int32_t fd = sysmgr_open("/dev/invalid", 0);
    ASSERT_EQ(fd, -1);
}

TEST_F(SysmgrTest, CloseValidFd) {
    int32_t fd = sysmgr_open("/dev/sysmgr", 0);
    ASSERT_GE(fd, 0);
    int32_t result = sysmgr_close(fd);
    ASSERT_EQ(result, 0);
}

TEST_F(SysmgrTest, CloseInvalidFd) {
    int32_t result = sysmgr_close(-1);
    ASSERT_EQ(result, -1);
}

// Lets validate that the elements of the Core Structure are in place via verification of the ending offset and 2 random
// offsets within the core structure
TEST_F(SysmgrTest, ElementVerification) {
    // CORE Element Unit Test Start
    int32_t result = static_cast<int32_t>(offsetof(sysmgr_regs_t, siliconid1));
    EXPECT_EQ(result, static_cast<int32_t>(0));

    result = static_cast<int32_t>(offsetof(sysmgr_regs_t, sdmmc_cmd_queue_setting_reg));
    EXPECT_EQ(result, static_cast<int32_t>(0x138));

    // Verify comp type
    result = static_cast<int32_t>(offsetof(sysmgr_regs_t, sdm_be_araddr_remap));
    EXPECT_EQ(result, static_cast<int32_t>(0x284));
}
