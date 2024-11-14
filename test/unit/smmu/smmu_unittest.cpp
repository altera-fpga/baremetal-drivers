#include "smmu.h"
#include "smmu_internal.h"
#include "smmu_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

class SmmuTest : public ::testing::Test {
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
TEST_F(SmmuTest, ElementVerification) {
    // CORE Element Unit Test Start
    int32_t result = static_cast<int32_t>(offsetof(smmu_regs_t, SMMU_S_CR0));
    EXPECT_EQ(result, static_cast<int32_t>(0x8020));

    result = static_cast<int32_t>(offsetof(smmu_regs_t, TCU_NODE_CTRL61));
    EXPECT_EQ(result, static_cast<int32_t>(0x90F4));

    result = static_cast<int32_t>(offsetof(smmu_regs_t, SMMU_PMCG_CAPR));
    EXPECT_EQ(result, static_cast<int32_t>(0x22D88));
}
