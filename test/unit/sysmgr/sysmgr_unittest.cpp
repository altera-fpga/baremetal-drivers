#include "sysmgr.h"
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
