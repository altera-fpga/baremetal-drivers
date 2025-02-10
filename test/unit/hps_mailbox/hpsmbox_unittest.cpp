#include "hps_mailbox.h"
#include "hps_mailbox_internal.h"
#include "hps_mailbox_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

class hpsmbox : public ::testing::Test {
  protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Verify opening a valid device
TEST_F(hpsmbox, OpenCloseMbox_success) {

    // Create const for mailbox
    const char mbox_dev[] = "/dev/hps_mailbox";
    // open mailbox
    int32_t base_add = hps_mbox_open(mbox_dev, 0);
    EXPECT_EQ(base_add, static_cast<int32_t>(HPS_MAILBOX_BASE));

    base_add = hps_mbox_close(base_add);
    EXPECT_EQ(base_add, static_cast<int32_t>(0));
}

// Verify opening an invalid device
TEST_F(hpsmbox, OpenMbox_failure) {

    // Create const for mailbox
    const char mbox_dev[] = "/dev/hps_mailbox2";

    // open mailbox
    int32_t base_add = hps_mbox_open(mbox_dev, 0);
    EXPECT_EQ(base_add, static_cast<int32_t>(-1));
}

// Verify closing an invalid device
TEST_F(hpsmbox, CloseMbox_failure) {
    // Close mailbox
    int32_t base_add = hps_mbox_close(0x800000);
    EXPECT_EQ(base_add, static_cast<int32_t>(-1));
}

// Verify IOCTL invalid Length
TEST_F(hpsmbox, IOCTL_bad_length) {
    // User data element
    uint32_t udata = 0;

    // Create const for mailbox
    const char mbox_dev[] = "/dev/hps_mailbox";

    // Close mailbox
    int32_t base_add = hps_mbox_open(mbox_dev, 0);
    EXPECT_EQ(base_add, static_cast<int32_t>(HPS_MAILBOX_BASE));

    // validate IOCTL with wrong length
    EXPECT_EQ(hps_mbox_ioctl(base_add, IOCTL_MBOX_CMD_GET_STATUS, reinterpret_cast<uintptr_t>(&udata), 2),
              static_cast<int32_t>(-1));

    base_add = hps_mbox_close(base_add);
    EXPECT_EQ(base_add, static_cast<int32_t>(0));
}

// Verify IOCTL invalid command
TEST_F(hpsmbox, IOCTL_bad_cmd) {
    // User data element
    uint32_t udata = 0;

    // Create const for mailbox
    const char mbox_dev[] = "/dev/hps_mailbox";

    // Close mailbox
    int32_t base_add = hps_mbox_open(mbox_dev, 0);
    EXPECT_EQ(base_add, static_cast<int32_t>(HPS_MAILBOX_BASE));

    // Validate IOCTL with invalid operation
    EXPECT_EQ(hps_mbox_ioctl(base_add, static_cast<uintptr_t>(0xFFFFFFFF), reinterpret_cast<uintptr_t>(&udata),
                             sizeof(uint32_t)),
              static_cast<int32_t>(-2));

    base_add = hps_mbox_close(base_add);
    EXPECT_EQ(base_add, static_cast<int32_t>(0));
}

// Lets validate that the elements of the Core Structure are in place via verification of the ending offset and 2 random
// offsets within the core structure
TEST_F(hpsmbox, ElementVerification) {
    // CORE Element Unit Test Start
    int32_t result = static_cast<int32_t>(offsetof(hps_mailbox_regs_words_t, hps_mbox_cin));
    EXPECT_EQ(result, static_cast<int32_t>(0));

    // verify command buffer
    result = static_cast<int32_t>(offsetof(hps_mailbox_regs_words_t, hps_mbox_cmd_buf[0]));
    EXPECT_EQ(result, static_cast<int32_t>(0x40));

    // verify response buffer
    result = static_cast<int32_t>(offsetof(hps_mailbox_regs_words_t, hps_mbox_rsp_buf[0]));
    EXPECT_EQ(result, static_cast<int32_t>(0xC0));

    // verify hps to sdm doorbell
    result = static_cast<int32_t>(offsetof(hps_mailbox_regs_words_t, hps_mbox_dbell_tosdm));
    EXPECT_EQ(result, static_cast<int32_t>(0x400));

    // Verify sdm to hps doorbell
    result = static_cast<int32_t>(offsetof(hps_mailbox_regs_words_t, hps_mbox_dbell_tohps));
    EXPECT_EQ(result, static_cast<int32_t>(0x480));
}
