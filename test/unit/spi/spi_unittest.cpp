#include "spi.h"
#include "spi_internal.h"
#include "spi_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

class SpiTest : public ::testing::TestWithParam<int> {
  protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Cleanup code if needed
    }
};

// Verify the offset of each register is correct
TEST_F(SpiTest, OffsetVerification) {

    int32_t result = static_cast<int32_t>(offsetof(spi_regs_t, CTRLR0));
    EXPECT_EQ(result, static_cast<int32_t>(0));

    result = static_cast<int32_t>(offsetof(spi_regs_t, SSI_VERSION_ID));
    EXPECT_EQ(result, static_cast<int32_t>(0x5C));

    result = static_cast<int32_t>(offsetof(spi_regs_t, DR35));
    EXPECT_EQ(result, static_cast<int32_t>(0xEC));

    result = static_cast<int32_t>(offsetof(spi_regs_t, RX_SAMPLE_DLY));
    EXPECT_EQ(result, static_cast<int32_t>(0xF0));

    result = static_cast<int32_t>(offsetof(spi_regs_t, RSVD_2));
    EXPECT_EQ(result, static_cast<int32_t>(0xfC));
}
