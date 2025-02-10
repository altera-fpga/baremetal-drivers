#include "watchdog.h"
#include "watchdog_internal.h"
#include "watchdog_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

class WdtUtest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Lets validate that the elements of the Core Structure are in place via verification of the ending offset and 2 random
// offsets within the core structure
TEST_F(WdtUtest, ElementVerification) {
    // CORE Element Unit Test Start
    int32_t result = static_cast<int32_t>(offsetof(watchdog_regs_words_t, wdt_cr));
    EXPECT_EQ(result, static_cast<int32_t>(0));

    // verify counter register
    result = static_cast<int32_t>(offsetof(watchdog_regs_words_t, wdt_crr));
    EXPECT_EQ(result, static_cast<int32_t>(0x0c));

    // verify eoi
    result = static_cast<int32_t>(offsetof(watchdog_regs_words_t, wdt_eoi));
    EXPECT_EQ(result, static_cast<int32_t>(0x14));

    // verify comp version
    result = static_cast<int32_t>(offsetof(watchdog_regs_words_t, wdt_comp_version));
    EXPECT_EQ(result, static_cast<int32_t>(0xf8));

    // Verify comp type
    result = static_cast<int32_t>(offsetof(watchdog_regs_words_t, wdt_comp_type));
    EXPECT_EQ(result, static_cast<int32_t>(0xfc));
}
