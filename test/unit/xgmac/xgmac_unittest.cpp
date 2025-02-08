#include "xgmac.h"
#include "xgmac_internal.h"
#include "xgmac_regs.h"
#include "gtest/gtest.h"

#include <stddef.h>

class XgmacTest : public ::testing::Test {
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
TEST_F(XgmacTest, ElementVerification) {
    // CORE Element Unit Test Start
    int32_t result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_core.mac_ver));
    EXPECT_EQ(result, static_cast<int32_t>(0x110));

    // Verify fpe_tx_int of core structure
    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_core.mmc_fpe_tx_int));
    EXPECT_EQ(result, static_cast<int32_t>(0xA00));

    // Verify transmit single collision packet of core structure
    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_core.tx_sgl_col_gpkt));
    EXPECT_EQ(result, static_cast<int32_t>(0xA40));

    // Verify the ending of the core structure
    result = (int32_t)(offsetof(xgmac_t, xgmac_core.mac_log_msg_intv));
    EXPECT_EQ(result, static_cast<int32_t>(0xDD0));
    // CORE Element Unit Test End

    // MTL Element Unit Tests Start
    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_mtl.xgmac_mtl_base.mtl_op_mode));
    EXPECT_EQ(result, static_cast<int32_t>(0x1000));

    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_mtl.xgmac_mtl_base.mtl_fpe_adv));
    EXPECT_EQ(result, static_cast<int32_t>(0x1094));

    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_txqN_op_mode));
    EXPECT_EQ(result, static_cast<int32_t>(0x1100));

    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_tcN_ets_ctrl));
    EXPECT_EQ(result, static_cast<int32_t>(0x1110));

    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_qN_int_sts));
    EXPECT_EQ(result, static_cast<int32_t>(0x1474));

    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_mtl.xgmac_mtl_tcq_7g.mtl_q7_int_sts));
    EXPECT_EQ(result, static_cast<int32_t>(0x14F4));
    // MTL Element Unit Tests End

    // DMA Element Unit Tests Start
    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_dma.dma_base.DMA_Mode));
    EXPECT_EQ(result, static_cast<int32_t>(0x3000));

    result = static_cast<int32_t>(offsetof(xgmac_t, xgmac_dma.dma_ch[7].DMA_CH_Rx_Desc_Write_Ring_Offset));
    EXPECT_EQ(result, static_cast<int32_t>(0x34FC));
    // DMA Element Unit Tests End
}
