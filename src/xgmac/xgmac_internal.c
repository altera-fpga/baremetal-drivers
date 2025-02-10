#include <stddef.h>
#include <stdint.h>

// XGMAC Specific header
#include "xgmac.h"
#include "xgmac_internal.h"
#include "xgmac_regs.h"

/*
This code controls a cadence XGMAC controller for an Altera Agilex5e HPS
*/

/* Initialization Methods */

/* MTL READ METHOD DEFINITION START */
/*
 * Read Operation  Mode
 */
uint32_t xgmac_mtl_get_opmode(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_op_mode;
}

/*
 * Read Interrupt Status
 */
uint32_t xgmac_mtl_get_int_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_interrupt_sts;
}

/*
 * Read RxQ DMAP0
 */
uint32_t xgmac_mtl_get_rxq_dmap0(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_rxq_dma_m0;
}

/*
 * Read RxQ DMAP1
 */
uint32_t xgmac_mtl_get_rxq_dmap1(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_rxq_dma_m1;
}

/*
 * Read TC priority map0
 */
uint32_t xgmac_mtl_get_tc_pmap0(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_prty_m0;
}

/*
 * Read TC priority map1
 */
uint32_t xgmac_mtl_get_tc_pmap1(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_prty_m1;
}

/*
 * Read TBS control
 */
uint32_t xgmac_mtl_get_tbs_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_tbs_ctrl;
}

/*
 * Read TBS Status
 */
uint32_t xgmac_mtl_get_tbs_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_tbs_sts;
}

/*
 * Read EST control
 */
uint32_t xgmac_mtl_get_est_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_ctrl;
}

/*
 * Read EST over head
 */
uint32_t xgmac_mtl_get_est_ohead(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_ovrhd;
}

/*
 * Read EST status
 */
uint32_t xgmac_mtl_get_est_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_sts;
}

/*
 * Read EST scheduling error
 */
uint32_t xgmac_mtl_get_est_scerror(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_sch_err;
}

/*
 * Read EST frame size error
 */
uint32_t xgmac_mtl_get_est_fsz_error(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_frm_szerr;
}

/*
 * Read EST capture frame size & queue number of the first frame size related error
 */
uint32_t xgmac_mtl_get_est_cptr_efsze(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_frm_cptr;
}

/*
 * Read EST interrupt enable bits
 */
uint32_t xgmac_mtl_get_est_intr_en(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_int_en;
}

/*
 * Read gate control lists information
 */
uint32_t xgmac_mtl_get_gcl_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_gcl_ctrl;
}

/*
 * Read gate control lists read and write data
 */
uint32_t xgmac_mtl_get_gcl_data(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_gcl_data;
}

/*
 * Read frame preemption control status
 */
uint32_t xgmac_mtl_get_fpe_csts(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_fpe_ctrl_sts;
}

/*
 * Read frame preemption hold and release advance time
 */
uint32_t xgmac_mtl_get_fpe_adv(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_fpe_adv;
}

/*
 * Read Queue # "N" operation mode
 */
uint32_t xgmac_mtl_get_tcq_tx_opmode(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_txqN_op_mode;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_txqN_op_mode;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_txqN_op_mode;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_txqN_op_mode;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_txqN_op_mode;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_txqN_op_mode;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_txqN_op_mode;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_txq7_op_mode;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" packets aborted for under flow
 */
uint32_t xgmac_mtl_get_tcq_tx_uflow(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_txqN_unflow;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_txqN_unflow;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_txqN_unflow;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_txqN_unflow;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_txqN_unflow;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_txqN_unflow;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_txqN_unflow;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_txq7_unflow;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" debug status
 */
uint32_t xgmac_mtl_get_tcq_tx_dbg(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_txqN_dbg;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_txqN_dbg;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_txqN_dbg;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_txqN_dbg;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_txqN_dbg;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_txqN_dbg;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_txqN_dbg;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_txq7_dbg;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" traffic class transmission configuration algorithm control
 */
uint32_t xgmac_mtl_get_tcq_ets_ctrl(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_tcN_ets_ctrl;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_tcN_ets_ctrl;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_tcN_ets_ctrl;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_tcN_ets_ctrl;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_tcN_ets_ctrl;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_tcN_ets_ctrl;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_tcN_ets_ctrl;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_ets_ctrl;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" traffic class transmission configuration algorithm status
 */
uint32_t xgmac_mtl_get_tcq_ets_sts(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_tcN_ets_sts;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_tcN_ets_sts;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_tcN_ets_sts;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_tcN_ets_sts;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_tcN_ets_sts;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_tcN_ets_sts;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_tcN_ets_sts;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_ets_sts;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N"  quantum weight "average traffic transmitted in traffic class"
 */
uint32_t xgmac_mtl_get_tcq_qwght(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_tcN_qntm_wght;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_tcN_qntm_wght;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_tcN_qntm_wght;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_tcN_qntm_wght;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_tcN_qntm_wght;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_tcN_qntm_wght;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_tcN_qntm_wght;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_qntm_wght;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" receive queue operation mode
 */
uint32_t xgmac_mtl_get_tcq_rx_opmode(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_op_mode;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_op_mode;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_op_mode;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_op_mode;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_op_mode;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_op_mode;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_op_mode;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_op_mode;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" received missed packet overflow count
 */
uint32_t xgmac_mtl_get_tcq_rx_mpocnt(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_msd_pkt_ocnt;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_msd_pkt_ocnt;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" received debug status
 */
uint32_t xgmac_mtl_get_tcq_rx_dbg(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_dbg;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_dbg;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_dbg;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_dbg;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_dbg;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_dbg;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_dbg;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_dbg;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" received control configuration "receive arbitration and passing of received packets
 */
uint32_t xgmac_mtl_get_tcq_rx_ctrl(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_ctrl;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_ctrl;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_ctrl;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_ctrl;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_ctrl;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_ctrl;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_ctrl;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_ctrl;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" receive de-activation and activation threshold for pause/pfc flow control
 */
uint32_t xgmac_mtl_get_tcq_rx_fctrl(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_fctrl;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_fctrl;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_fctrl;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_fctrl;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_fctrl;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_fctrl;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_fctrl;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_fctrl;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" receive interrupt enable bits for traffic class/queue
 */
uint32_t xgmac_mtl_get_tcq_queue_int_en(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_qN_int_en;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_qN_int_en;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_qN_int_en;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_qN_int_en;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_qN_int_en;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_qN_int_en;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_qN_int_en;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_q7_int_en;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue # "N" receive interrupt status bits for traffic class/queue
 */
uint32_t xgmac_mtl_get_tcq_queue_int_sts(int32_t base_address, uint32_t queue_num) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    uint32_t ret_val = 0xffffffffU;
    switch (queue_num) {
    case 0:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_qN_int_sts;
        break;
    case 1:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_qN_int_sts;
        break;
    case 2:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_qN_int_sts;
        break;
    case 3:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_qN_int_sts;
        break;
    case 4:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_qN_int_sts;
        break;
    case 5:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_qN_int_sts;
        break;
    case 6:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_qN_int_sts;
        break;
    case 7:
        ret_val = (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_q7_int_sts;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Read Queue 7 slope credit register
 */
uint32_t xgmac_mtl_get_q7_slope_credit(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_snd_slp_credit;
}

/*
 * Read Queue 7 high credit value
 */
uint32_t xgmac_mtl_get_q7_high_credit(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_hi_credit;
}

/*
 * Read Queue 7 high credit value
 */
uint32_t xgmac_mtl_get_q7_low_credit(int32_t base_address) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_low_credit;
}
/* MTL READ METHOD DEFINITION END */

/* MTL SET METHODS DEFINITION START */
/*
 * Set Operation  Mode
 */
int32_t xgmac_mtl_set_opmode(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_op_mode = wvalue;
    return 0;
}

/*
 * Set RxQ DMAP0
 */
int32_t xgmac_mtl_set_rxq_dmap0(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_rxq_dma_m0 = wvalue;
    return 0;
}

/*
 * Set RxQ DMAP1
 */
int32_t xgmac_mtl_set_rxq_dmap1(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_rxq_dma_m1 = wvalue;
    return 0;
}

/*
 * Set TC priority map0
 */
int32_t xgmac_mtl_set_tc_pmap0(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_prty_m0 = wvalue;
    return 0;
}

/*
 * Set TC priority map1
 */
int32_t xgmac_mtl_set_tc_pmap1(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_prty_m1 = wvalue;
    return 0;
}

/*
 * Set TBS control
 */
int32_t xgmac_mtl_set_tbs_ctrl(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_tbs_ctrl = wvalue;
    return 0;
}

/*
 * Set TBS Status
 */
int32_t xgmac_mtl_set_tbs_sts(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_tbs_sts = wvalue;
    return 0;
}

/*
 * Set EST control
 */
int32_t xgmac_mtl_set_est_ctrl(int32_t base_address, uint32_t wvalue) {
    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_ctrl = wvalue;
    return 0;
}

/*
 * Set EST over head
 */
int32_t xgmac_mtl_set_est_ohead(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_ovrhd = wvalue;
    return 0;
}

/*
 * Set EST status
 */
int32_t xgmac_mtl_set_est_sts(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_sts = wvalue;
    return 0;
}

/*
 * Set EST scheduling error
 */
int32_t xgmac_mtl_set_est_scerror(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_sch_err = wvalue;
    return 0;
}

/*
 * Set EST frame size error
 */
int32_t xgmac_mtl_set_est_fsz_error(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_frm_szerr = wvalue;
    return 0;
}

/*
 * Set EST interrupt enable bits
 */
int32_t xgmac_mtl_set_est_intr_en(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_est_int_en = wvalue;
    return 0;
}

/*
 * Set gate control lists information
 */
int32_t xgmac_mtl_set_gcl_ctrl(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_gcl_ctrl = wvalue;
    return 0;
}

/*
 * Set gate control lists read and write data
 */
int32_t xgmac_mtl_set_gcl_data(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_gcl_data = wvalue;
    return 0;
}

/*
 * Set frame preemption control status
 */
int32_t xgmac_mtl_set_fpe_csts(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_fpe_ctrl_sts = wvalue;
    return 0;
}

/*
 * Set frame preemption hold and release advance time
 */
int32_t xgmac_mtl_set_fpe_adv(int32_t base_address, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;
    xgmac_ptr->xgmac_mtl.xgmac_mtl_base.mtl_fpe_adv = wvalue;
    return 0;
}

/*
 * Set Queue # "N" operation mode
 */
int32_t xgmac_mtl_set_tcq_tx_opmode(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_txqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_txq7_op_mode = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N" traffic class transmission configuration algorithm control
 */
int32_t xgmac_mtl_set_tcq_ets_ctrl(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_tcN_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_ets_ctrl = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N"  quantum weight "average traffic transmitted in traffic class"
 */
int32_t xgmac_mtl_set_tcq_qwght(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_tcN_qntm_wght = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_tcN_qntm_wght = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_tcN_qntm_wght = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_tcN_qntm_wght = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_tcN_qntm_wght = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_tcN_qntm_wght = wvalue;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_tcN_qntm_wght = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_tc7_qntm_wght = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N" receive queue operation mode
 */
int32_t xgmac_mtl_set_tcq_rx_opmode(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_op_mode = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_op_mode = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N" received control configuration "receive arbitration and passing of received packets
 */
int32_t xgmac_mtl_set_tcq_rx_ctrl(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_ctrl = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_ctrl = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N" receive de-activation and activation threshold for pause/pfc flow control
 */
int32_t xgmac_mtl_set_tcq_rx_fctrl(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_rxqN_fctrl = wvalue;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_rxqN_fctrl = wvalue;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_rxqN_fctrl = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_rxqN_fctrl = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_rxqN_fctrl = wvalue;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_rxqN_fctrl = wvalue;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_rxqN_fctrl = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_rxq7_fctrl = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N" receive interrupt enable bits for traffic class/queue
 */
int32_t xgmac_mtl_set_tcq_queue_int_en(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_qN_int_en = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_q7_int_en = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}

/*
 * Set Queue # "N" receive interrupt status bits for traffic class/queue
 */
int32_t xgmac_mtl_set_tcq_queue_int_sts(int32_t base_address, uint32_t queue_num, uint32_t wvalue) {

    // Get pointer to address space
    xgmac_t *xgmac_ptr = (xgmac_t *)base_address;

    int32_t ret_val = -1;
    switch (queue_num) {
    case 0:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[0].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 1:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[1].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 2:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[2].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 3:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[3].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 4:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[4].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 5:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[5].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 6:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq0_6g[6].mtl_qN_int_sts = wvalue;
        ret_val = 0;
        break;
    case 7:
        xgmac_ptr->xgmac_mtl.xgmac_mtl_tcq_7g.mtl_q7_int_sts = wvalue;
        ret_val = 0;
        break;
    default:
        // invalid value return -1 or all ff's
        break;
    }
    // retrieve variable
    return ret_val;
}
/* MTL SET METHODS DEFINITION END */

/* CORE METHOD DEFINITION START */
/*
 * Read tx mac configuration register
 */
uint32_t xgmac_get_tx_mac_config(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tx_cfg;
}

/*
 * Read rx mac configuration register
 */
uint32_t xgmac_get_rx_mac_config(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rx_cfg;
}

/*
 * Read mac packet filter configuration
 */
uint32_t xgmac_get_mac_pckt_filter(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pkt_fltr;
}

/*
 * Read mac watchdog and jabber timeout
 */
uint32_t xgmac_get_mac_wdt_jb_tout(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_wdt_jb_tout;
}

/*
 * Read mac hash table reg0
 */
uint32_t xgmac_get_mac_htbl_reg0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hash_tbl_reg0;
}

/*
 * Read mac hash table reg1
 */
uint32_t xgmac_get_mac_htbl_reg1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hash_tbl_reg1;
}

/*
 * Read mac vlan tag control
 */
uint32_t xgmac_get_mac_vlan_tctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_vlan_tag_ctrl;
}

/*
 * Read mac vlan hash table
 */
uint32_t xgmac_get_mac_vlan_htbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_vlan_tag_ctrl;
}

/*
 * Read mac vlan tag data
 */
uint32_t xgmac_get_mac_vlan_tdata(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_vlan_tag_dt;
}

/*
 * Read mac vlan inclusion replacement register
 */
uint32_t xgmac_get_mac_vlan_incl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_vlan_incl;
}

/*
 * Read mac vlan inner inclusion replacement register
 */
uint32_t xgmac_get_mac_vlan_nincl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_vlan_incl;
}

/*
 * Read mac receive ethernet type match register
 */
uint32_t xgmac_get_mac_rx_etmtch(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rx_eth_tp_mch;
}

/*
 * Read mac Q0 flow control register
 */
uint32_t xgmac_get_mac_q0_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q0_tx_fl_ctrl;
}

/*
 * Read mac Q1 flow control register
 */
uint32_t xgmac_get_mac_q1_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q1_tx_fl_ctrl;
}

/*
 * Read mac Q2 flow control register
 */
uint32_t xgmac_get_mac_q2_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q2_tx_fl_ctrl;
}

/*
 * Read mac Q3 flow control register
 */
uint32_t xgmac_get_mac_q3_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q3_tx_fl_ctrl;
}

/*
 * Read mac Q4 flow control register
 */
uint32_t xgmac_get_mac_q4_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q4_tx_fl_ctrl;
}

/*
 * Read mac Q5 flow control register
 */
uint32_t xgmac_get_mac_q5_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q5_tx_fl_ctrl;
}

/*
 * Read mac Q6 flow control register
 */
uint32_t xgmac_get_mac_q6_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q6_tx_fl_ctrl;
}

/*
 * Read mac Q7 flow control register
 */
uint32_t xgmac_get_mac_q7_fctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_q7_tx_fl_ctrl;
}

/*
 * Read mac max receive flow control
 */
uint32_t xgmac_get_mac_max_rxfctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rx_fl_ctrl;
}

/*
 * Read mac max receive queue control 4
 */
uint32_t xgmac_get_mac_rx_qctrl4(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rxq_ctrl4;
}

/*
 * Read mac max receive queue control 5
 */
uint32_t xgmac_get_mac_rx_qctrl5(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rxq_ctrl5;
}

/*
 * Read mac max receive queue control 0
 */
uint32_t xgmac_get_mac_rx_qctrl0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rxq_ctrl0;
}

/*
 * Read mac max receive queue control 1
 */
uint32_t xgmac_get_mac_rx_qctrl1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rxq_ctrl1;
}
/*
 * Read mac max receive queue control 2
 */
uint32_t xgmac_get_mac_rx_qctrl2(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rxq_ctrl2;
}

/*
 * Read mac max receive queue control 3
 */
uint32_t xgmac_get_mac_rx_qctrl3(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rxq_ctrl3;
}

/*
 * Read mac interrupt status
 */
uint32_t xgmac_get_mac_int_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_int_sts;
}

/*
 * Read mac interrupt enable
 */
uint32_t xgmac_get_mac_int_en(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_int_en;
}

/*
 * Read mac transmit & receive status
 */
uint32_t xgmac_get_mac_rx_tx_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_rx_tx_sts;
}

/*
 * Read mac LPI control status
 */
uint32_t xgmac_get_mac_lpi_ctrl_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_lpi_ctr_sts;
}

/*
 * Read mac LPI timeout control register
 */
uint32_t xgmac_get_mac_lpi_tm_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_lpi_tm_ctrl;
}

/*
 * Read mac LPI auto entry timeout control register
 */
uint32_t xgmac_get_mac_lpi_aet_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_lpi_au_en_tm;
}

/*
 * Read mac tick counter microseconds
 */
uint32_t xgmac_get_mac_tic_ucntr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_us_tk_cntr;
}

/*
 * Read mac version
 */
uint32_t xgmac_get_mac_version(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_ver;
}

/*
 * Read mac debug
 */
uint32_t xgmac_get_mac_debug(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_dbg;
}

/*
 * Read mac feature 0
 */
uint32_t xgmac_get_mac_feat0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hw_feat0;
}

/*
 * Read mac feature 1
 */
uint32_t xgmac_get_mac_feat1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hw_feat1;
}

/*
 * Read mac feature 2
 */
uint32_t xgmac_get_mac_feat2(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hw_feat2;
}

/*
 * Read mac feature 3
 */
uint32_t xgmac_get_mac_feat3(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hw_feat3;
}

/*
 * Read mac feature 4
 */
uint32_t xgmac_get_mac_feat4(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_hw_feat4;
}

/*
 * Read mac extended configuration
 */
uint32_t xgmac_get_mac_ext_cfg0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_ext_cfg;
}

/*
 * Read mac extended configuration 1
 */
uint32_t xgmac_get_mac_ext_cfg1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_ext_cfg1;
}

/*
 * Read mac FPE control status
 */
uint32_t xgmac_get_mac_fpe_ctrl_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_fpe_ctrl_sts;
}

/*
 * Read mac csr programmable controls
 */
uint32_t xgmac_get_mac_csr_pg_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_csr_sw_ctrl;
}

/*
 * Read mac address 0 high
 */
uint32_t xgmac_get_mac_haddr0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr0_high;
}

/*
 * Read mac address 0 low
 */
uint32_t xgmac_get_mac_laddr0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr0_low;
}

/*
 * Read mac address 1 high
 */
uint32_t xgmac_get_mac_haddr1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr1_high;
}

/*
 * Read mac address 1 low
 */
uint32_t xgmac_get_mac_laddr1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr1_low;
}

/*
 * Read mac address 2 high
 */
uint32_t xgmac_get_mac_haddr2(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr2_high;
}

/*
 * Read mac address 2 low
 */
uint32_t xgmac_get_mac_laddr2(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr2_low;
}

/*
 * Read mac address 3 high
 */
uint32_t xgmac_get_mac_haddr3(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr3_high;
}

/*
 * Read mac address 3 low
 */
uint32_t xgmac_get_mac_laddr3(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr3_low;
}

/*
 * Read mac address 4 high
 */
uint32_t xgmac_get_mac_haddr4(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr4_high;
}

/*
 * Read mac address 4 low
 */
uint32_t xgmac_get_mac_laddr4(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr4_low;
}

/*
 * Read mac address 5 high
 */
uint32_t xgmac_get_mac_haddr5(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr5_high;
}

/*
 * Read mac address 5 low
 */
uint32_t xgmac_get_mac_laddr5(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr5_low;
}

/*
 * Read mac address 6 high
 */
uint32_t xgmac_get_mac_haddr6(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr6_high;
}

/*
 * Read mac address 6 low
 */
uint32_t xgmac_get_mac_laddr6(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr6_low;
}

/*
 * Read mac address 7 high
 */
uint32_t xgmac_get_mac_haddr7(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr7_high;
}

/*
 * Read mac address 7 low
 */
uint32_t xgmac_get_mac_laddr7(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr7_low;
}

/*
 * Read mac address 8 high
 */
uint32_t xgmac_get_mac_haddr8(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr8_high;
}

/*
 * Read mac address 8 low
 */
uint32_t xgmac_get_mac_laddr8(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr8_low;
}

/*
 * Read mac address 9 high
 */
uint32_t xgmac_get_mac_haddr9(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr9_high;
}

/*
 * Read mac address 9 low
 */
uint32_t xgmac_get_mac_laddr9(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr9_low;
}

/*
 * Read mac address 10 high
 */
uint32_t xgmac_get_mac_haddr10(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr10_high;
}

/*
 * Read mac address 10 low
 */
uint32_t xgmac_get_mac_laddr10(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr10_low;
}

/*
 * Read mac address 11 high
 */
uint32_t xgmac_get_mac_haddr11(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr11_high;
}

/*
 * Read mac address 11 low
 */
uint32_t xgmac_get_mac_laddr11(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr11_low;
}

/*
 * Read mac address 12 high
 */
uint32_t xgmac_get_mac_haddr12(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr12_high;
}

/*
 * Read mac address 12 low
 */
uint32_t xgmac_get_mac_laddr12(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr12_low;
}

/*
 * Read mac address 13 high
 */
uint32_t xgmac_get_mac_haddr13(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr13_high;
}

/*
 * Read mac address 13 low
 */
uint32_t xgmac_get_mac_laddr13(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr13_low;
}

/*
 * Read mac address 14 high
 */
uint32_t xgmac_get_mac_haddr14(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr14_high;
}

/*
 * Read mac address 14 low
 */
uint32_t xgmac_get_mac_laddr14(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr14_low;
}

/*
 * Read mac address 15 high
 */
uint32_t xgmac_get_mac_haddr15(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr15_high;
}

/*
 * Read mac address 15 low
 */
uint32_t xgmac_get_mac_laddr15(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr15_low;
}

/*
 * Read mac address 16 high
 */
uint32_t xgmac_get_mac_haddr16(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr16_high;
}

/*
 * Read mac address 16 low
 */
uint32_t xgmac_get_mac_laddr16(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr16_low;
}

/*
 * Read mac address 17 high
 */
uint32_t xgmac_get_mac_haddr17(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr17_high;
}

/*
 * Read mac address 17 low
 */
uint32_t xgmac_get_mac_laddr17(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr17_low;
}

/*
 * Read mac address 18 high
 */
uint32_t xgmac_get_mac_haddr18(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr18_high;
}

/*
 * Read mac address 18 low
 */
uint32_t xgmac_get_mac_laddr18(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr18_low;
}

/*
 * Read mac address 19 high
 */
uint32_t xgmac_get_mac_haddr19(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr9_high;
}

/*
 * Read mac address 19 low
 */
uint32_t xgmac_get_mac_laddr19(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr19_low;
}

/*
 * Read mac address 20 high
 */
uint32_t xgmac_get_mac_haddr20(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr20_high;
}

/*
 * Read mac address 20 low
 */
uint32_t xgmac_get_mac_laddr20(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr20_low;
}

/*
 * Read mac address 21 high
 */
uint32_t xgmac_get_mac_haddr21(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr21_high;
}

/*
 * Read mac address 21 low
 */
uint32_t xgmac_get_mac_laddr21(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr21_low;
}

/*
 * Read mac address 22 high
 */
uint32_t xgmac_get_mac_haddr22(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr22_high;
}

/*
 * Read mac address 22 low
 */
uint32_t xgmac_get_mac_laddr22(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr22_low;
}

/*
 * Read mac address 23 high
 */
uint32_t xgmac_get_mac_haddr23(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr23_high;
}

/*
 * Read mac address 23 low
 */
uint32_t xgmac_get_mac_laddr23(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr23_low;
}

/*
 * Read mac address 24 high
 */
uint32_t xgmac_get_mac_haddr24(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr24_high;
}

/*
 * Read mac address 24 low
 */
uint32_t xgmac_get_mac_laddr24(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr24_low;
}

/*
 * Read mac address 25 high
 */
uint32_t xgmac_get_mac_haddr25(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr25_high;
}

/*
 * Read mac address 25 low
 */
uint32_t xgmac_get_mac_laddr25(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr25_low;
}

/*
 * Read mac address 26 high
 */
uint32_t xgmac_get_mac_haddr26(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr26_high;
}

/*
 * Read mac address 26 low
 */
uint32_t xgmac_get_mac_laddr26(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr26_low;
}

/*
 * Read mac address 27 high
 */
uint32_t xgmac_get_mac_haddr27(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr27_high;
}

/*
 * Read mac address 27 low
 */
uint32_t xgmac_get_mac_laddr27(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr27_low;
}

/*
 * Read mac address 28 high
 */
uint32_t xgmac_get_mac_haddr28(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr28_high;
}

/*
 * Read mac address 28 low
 */
uint32_t xgmac_get_mac_laddr28(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr28_low;
}

/*
 * Read mac address 29 high
 */
uint32_t xgmac_get_mac_haddr29(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr29_high;
}

/*
 * Read mac address 29 low
 */
uint32_t xgmac_get_mac_laddr29(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr29_low;
}

/*
 * Read mac address 30 high
 */
uint32_t xgmac_get_mac_haddr30(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr30_high;
}

/*
 * Read mac address 30 low
 */
uint32_t xgmac_get_mac_laddr30(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr30_low;
}

/*
 * Read mac address 31 high
 */
uint32_t xgmac_get_mac_haddr31(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr31_high;
}

/*
 * Read mac address 31 low
 */
uint32_t xgmac_get_mac_laddr31(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_addr31_low;
}

/*
 * Read mac indirect access control
 */
uint32_t xgmac_get_mac_ind_actrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_ind_acc_ctrl;
}

/*
 * Read mac indirect access data
 */
uint32_t xgmac_get_mac_ind_adata(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_ind_acc_data;
}

/*
 * Read mac l3/l4 access control
 */
uint32_t xgmac_get_mac_l3_l4_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_l3_l4_addr_ctrl;
}

/*
 * Read mac l3/l4 access data
 */
uint32_t xgmac_get_mac_l3_l4_data(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_l3_l4_data;
}

/*
 * Read mac arp address
 */
uint32_t xgmac_get_mac_arp_addr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_arp_addr;
}

/*
 * Read mac system time generator
 */
uint32_t xgmac_get_mac_tmstamp_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmstamp_ctrl;
}

/*
 * Read mac timestampe sub-second generator register
 */
uint32_t xgmac_get_mac_tmstamp_ssec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_sub_sec_incr;
}

/*
 * Read mac system time seconds
 */
uint32_t xgmac_get_mac_syst_sec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_sys_tm_sec;
}

/*
 * Read mac system time nano-seconds
 */
uint32_t xgmac_get_mac_syst_nsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_sys_tm_nsec;
}

/*
 * Read mac system time seconds update register
 */
uint32_t xgmac_get_mac_systu_sec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_sys_tm_sec_updt;
}

/*
 * Read mac system time nano-seconds update register
 */
uint32_t xgmac_get_mac_systu_nsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_sys_tm_nsec_updt;
}

/*
 * Read mac timestamp addend register
 */
uint32_t xgmac_get_mac_tmstamp_addend(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmstamp_addend;
}

/*
 * Read mac timestamp high word seconds register
 */
uint32_t xgmac_get_mac_tmstamp_hsword(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_sys_tm_hgh_wrd_sec;
}

/*
 * Read mac timestamp status register
 */
uint32_t xgmac_get_mac_tmstamp_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmstamp_sts;
}

/*
 * Read mac timestamp PTP nano-second register status
 */
uint32_t xgmac_get_mac_tmstamp_snsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tx_tmstamp_sts_nsec;
}

/*
 * Read mac timestamp PTP second register status
 */
uint32_t xgmac_get_mac_tmstamp_sts_sec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tx_tmstamp_sts_sec;
}

/*
 * Read mac timestamp PTP packet id
 */
uint32_t xgmac_get_mac_tmstamp_pkt_id(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tx_tmstamp_sts_pktid;
}

/*
 * Read mac auxillary time stamp control
 */
uint32_t xgmac_get_mac_aux_tctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_aux_tmstamp_ctrl;
}

/*
 * Read mac auxillary time stamp snapshot nanoseconds
 */
uint32_t xgmac_get_mac_aux_nsec_snshot(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_aux_tmstamp_nsec;
}

/*
 * Read mac auxillary time stamp snapshot seconds
 */
uint32_t xgmac_get_mac_aux_sec_snshot(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_aux_tmstamp_sec;
}

/*
 * Read mac ingress asymmetry correction register
 */
uint32_t xgmac_get_mac_tmstamp_ingress(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmstamp_ingr_asym_corr;
}

/*
 * Read mac eress asymmetry correction register
 */
uint32_t xgmac_get_mac_tmstamp_egress(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmstamp_egr_asym_corr;
}

/*
 * Read mac ingress correction nanosecond register
 */
uint32_t xgmac_get_mac_ingress_cor_nsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmstamp_ingr_corr_nsec;
}

/*
 * Read mac ingress correction sub-nanosecond register
 */
uint32_t xgmac_get_mac_ingress_cor_snsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmpsatmp_ingr_corr_subnsec;
}

/*
 * Read mac egress correction nanosecond register
 */
uint32_t xgmac_get_mac_egress_cor_nsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmpstamp_egr_corr_nsec;
}

/*
 * Read mac egress correction sub-nanosecond register
 */
uint32_t xgmac_get_mac_egress_cor_snsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_tmpstamp_egr_corr_subnsec;
}

/*
 * Read mac PPS control register
 */
uint32_t xgmac_get_mac_pps_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps_ctrl;
}

/*
 * Read mac PPS0 target time in seconds
 */
uint32_t xgmac_get_mac_pps0_tgt_sec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps0_trg_tm_sec;
}

/*
 * Read mac PPS0 target time in nano-seconds
 */
uint32_t xgmac_get_mac_pps0_tgt_nsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps0_trg_tm_nsec;
}

/*
 * Read mac PPS0 interval register
 */
uint32_t xgmac_get_mac_pps0_intv(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps0_intv;
}

/*
 * Read mac PPS0 width register
 */
uint32_t xgmac_get_mac_pps0_width(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps0_wdh;
}

/*
 * Read mac PPS1 target time in seconds
 */
uint32_t xgmac_get_mac_pps1_tgt_sec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps1_trg_tm_sec;
}

/*
 * Read mac PPS1 target time in nano-seconds
 */
uint32_t xgmac_get_mac_pps1_tgt_nsec(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps1_trg_tm_nsec;
}

/*
 * Read mac PPS1 interval register
 */
uint32_t xgmac_get_mac_pps1_intv(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps1_intv;
}

/*
 * Read mac PPS1 width register
 */
uint32_t xgmac_get_mac_pps1_width(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pps1_wdh;
}

/*
 * Read mac control of PTP operation mode
 */
uint32_t xgmac_get_mac_pto_ctrl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_pto_ctrl;
}

/*
 * Read mac port identity 0
 */
uint32_t xgmac_get_mac_port_id0(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_src_pt_iden0;
}

/*
 * Read mac port identity 1
 */
uint32_t xgmac_get_mac_port_id1(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_src_pt_iden1;
}

/*
 * Read mac port identity 2
 */
uint32_t xgmac_get_mac_port_id2(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_src_pt_iden2;
}

/*
 * Read mac interval of automatic PTP packet
 */
uint32_t xgmac_get_mac_ptp_aintv(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mac_log_msg_intv;
}

/*
 * Read mdio single command address register
 */
uint32_t xgmac_get_mdio_sgl_cmd_addr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_sgl_cmd_addr;
}

/*
 * Read mdio single command data register
 */
uint32_t xgmac_get_mdio_sgl_cmd_data(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_sgl_cmd_ctrl_dt;
}

/*
 * Read mdio continuous write address
 */
uint32_t xgmac_get_mdio_cnt_wr_addr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_cnt_wrt_addr;
}

/*
 * Read mdio continuous write data
 */
uint32_t xgmac_get_mdio_cnt_wr_data(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_cnt_wrt_dt;
}

/*
 * Read mdio continuous scan ports enabled
 */
uint32_t xgmac_get_mdio_sctn_pen(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_cnt_scan_pt_en;
}

/*
 * Read mdio sma interrupt status
 */
uint32_t xgmac_get_mdio_sma_int_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_int_sts;
}

/*
 * Read mdio sma interrupts enabled
 */
uint32_t xgmac_get_mdio_sma_int_en(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_int_en;
}

/*
 * Read mdio connect disconnect status
 */
uint32_t xgmac_get_mdio_conn_disc_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_port_ct_dct_sts;
}

/*
 * Read mdio SMA PHY port configuration
 */
uint32_t xgmac_get_mdio_cl22_port(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_cls22_port;
}

/*
 * Read mdio port range select port
 */
uint32_t xgmac_get_mdio_port_rng_sel(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_port_nx4_idrt_ctrl;
}

/*
 * Read mdio nx4 p0 device status
 */
uint32_t xgmac_get_mdio_nx4_p0_dsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p0_dev_in_use;
}

/*
 * Read mdio nx4 p0 link status
 */
uint32_t xgmac_get_mdio_nx4_p0_lsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p0_lnk_sts;
}

/*
 * Read mdio nx4 p0 alive status
 */
uint32_t xgmac_get_mdio_nx4_p0_asts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p0_alv_sts;
}

/*
 * Read mdio nx4 p1 device status
 */
uint32_t xgmac_get_mdio_nx4_p1_dsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p1_dev_in_use;
}

/*
 * Read mdio nx4 p1 link status
 */
uint32_t xgmac_get_mdio_nx4_p1_lsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p1_lnk_sts;
}

/*
 * Read mdio nx4 p1 alive status
 */
uint32_t xgmac_get_mdio_nx4_p1_asts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p1_alv_sts;
}

/*
 * Read mdio nx4 p2 device status
 */
uint32_t xgmac_get_mdio_nx4_p2_dsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p2_dev_in_use;
}

/*
 * Read mdio nx4 p2 link status
 */
uint32_t xgmac_get_mdio_nx4_p2_lsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p2_lnk_sts;
}

/*
 * Read mdio nx4 p2 alive status
 */
uint32_t xgmac_get_mdio_nx4_p2_asts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p2_alv_sts;
}

/*
 * Read mdio nx4 p3 device status
 */
uint32_t xgmac_get_mdio_nx4_p3_dsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p3_dev_in_use;
}

/*
 * Read mdio nx4 p3 link status
 */
uint32_t xgmac_get_mdio_nx4_p3_lsts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p3_lnk_sts;
}

/*
 * Read mdio nx4 p3 alive status
 */
uint32_t xgmac_get_mdio_nx4_p3_asts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mdio_portnx4p3_alv_sts;
}

/*
 * Read mmc control register
 */
uint32_t xgmac_get_mmc_ctrl_reg(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_ctrl;
}

/*
 * Read mmc receive interrupt status
 */
uint32_t xgmac_get_mmc_rx_int_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_rx_int;
}

/*
 * Read mmc transmit interrupt status
 */
uint32_t xgmac_get_mmc_tx_int_sts(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_tx_int;
}

/*
 * Read mmc receive interrupt enable register
 */
uint32_t xgmac_get_mmc_rx_int_en(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_rx_int_en;
}

/*
 * Read mmc transmit interrupt enable register
 */
uint32_t xgmac_get_mmc_tx_int_en(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_tx_int_en;
}

/*
 * Read mmc FPE TX interrupts
 */
uint32_t xgmac_get_fpe_tx_int(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_fpe_tx_int;
}

/*
 * Read mmc FPE TX interrupt masks
 */
uint32_t xgmac_get_fpe_tx_int_msk(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_fpe_tx_int_mask;
}

/*
 * Read mmc FPE frag counter "mpackets transmitted"
 */
uint32_t xgmac_get_fpe_frag_cnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_tx_fpe_frag_cntr;
}

/*
 * Read mmc FPE hold request counter
 */
uint32_t xgmac_get_fpe_hold_req(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_tx_hold_req_cntr;
}

/*
 * Read mmc FPE receive interrupt
 */
uint32_t xgmac_get_fpe_rx_int(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_fpe_rx_int;
}

/*
 * Read mmc FPE receive interrupt masks
 */
uint32_t xgmac_get_fpe_rx_int_mask(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_fpe_rx_int_mask;
}

/*
 * Read mmc FPE packet reassembly error counter
 */
uint32_t xgmac_get_fpe_rx_pae_cntr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_rx_pkt_assm_er_cntr;
}

/*
 * Read mmc FPE packet unknown SMD error counter
 */
uint32_t xgmac_get_fpe_rx_ukn_esmd_cntr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_rx_pkt_smd_er_cntr;
}

/*
 * Read mmc FPE packet re-assembly ok counter
 */
uint32_t xgmac_get_fpe_rx_asok_cntr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_rx_pkt_assm_ok_cntr;
}

/*
 * Read mmc FPE packet receive frag counter
 */
uint32_t xgmac_get_fpe_rx_frag_cntr(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_rx_fpe_frag_cntr;
}

/*
 * Read mmc IPC receive interrupt masks
 */
uint32_t xgmac_get_ipc_rx_int_mask(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_ipc_rx_int_mask;
}

/*
 * Read mmc IPC receive interrupts
 */
uint32_t xgmac_get_ipc_rx_int(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->mmc_ipc_rx_int;
}

/*
 * Read TX octet count good bad packets lower 32 bits
 */
uint32_t xgmac_get_tx_oct_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_oct_cnt_gbl;
}

/*
 * Read TX octet count good bad packets high 32 bits
 */
uint32_t xgmac_get_tx_oct_gbh(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_oct_cnt_gbh;
}

/*
 * Read TX packet count good bad packets lower 32 bits
 */
uint32_t xgmac_get_tx_pkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_pkt_cnt_gbl;
}

/*
 * Read TX broadcast packet count good packets lower 32 bits
 */
uint32_t xgmac_get_tx_bpkg_gl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_bcst_cnt_gl;
}

/*
 * Read TX multicast packet count good packets lower 32 bits
 */
uint32_t xgmac_get_tx_mpkg_gl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_mcst_cnt_gl;
}

/*
 * Read TX group 0 = "64 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_tx_g0_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_64oct_pkt_gbl;
}

/*
 * Read TX group 1 = "65-127 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_tx_g1_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_65_127_oct_pkt_gbl;
}

/*
 * Read TX group 2 = "128-255 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_tx_g2_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_128_255_oct_pkt_gbl;
}

/*
 * Read TX group 3 = "256-511 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_tx_g3_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_256_511_oct_pkt_gbl;
}

/*
 * Read TX group 4 = "512-1023 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_tx_g4_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_512_1023_oct_pkt_gbl;
}

/*
 * Read TX group 5 = "1024-max octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_tx_g5_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_1024_max_oct_pkt_gbl;
}

/*
 * Read TX unicast good and bad packets lower 32 bits
 */
uint32_t xgmac_get_tx_ucast_pkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_ucst_pkt_gbl;
}

/*
 * Read TX multicast good and bad packets lower 32 bits
 */
uint32_t xgmac_get_tx_mcast_pkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_mcst_pkt_gbl;
}

/*
 * Read TX broadcast good and bad packets lower 32 bits
 */
uint32_t xgmac_get_tx_bcast_pkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_bcst_pkt_gbl;
}

/*
 * Read TX underflow error packet lower 32 bits
 */
uint32_t xgmac_get_tx_uferr_pkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_uflw_err_pkt_gbl;
}

/*
 * Read TX octet count lower 32 bits
 */
uint32_t xgmac_get_tx_oct_cnt_gl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_oct_cnt_gl;
}

/*
 * Read TX octet count upper 32 bits
 */
uint32_t xgmac_get_tx_oct_cnt_gh(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_oct_cnt_gh;
}

/*
 * Read TX packet count lower 32 bits
 */
uint32_t xgmac_get_tx_pkt_cnt_gl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_pkt_cnt_gl;
}

/*
 * Read TX pause packet count lower 32 bits
 */
uint32_t xgmac_get_tx_pse_lpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_pause_pkt_low;
}

/*
 * Read TX vlan packet count lower 32 bits
 */
uint32_t xgmac_get_tx_vlan_lpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_vlan_pkt_gl;
}

/*
 * Read TX LPI microseconds count
 */
uint32_t xgmac_get_tx_lpi_uscnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_lpi_usec_cntr;
}

/*
 * Read TX time mac transitioned to LPI TX stateSS
 */
uint32_t xgmac_get_tx_lpi_tr_cnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_lpi_tran_cntr;
}

/*
 * Read TX good packets after single collision
 */
uint32_t xgmac_get_tx_sgl_col_gpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_sgl_col_gpkt;
}

/*
 * Read TX good packets after multiple collision
 */
uint32_t xgmac_get_tx_mtl_col_gpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_mtl_col_gpkt;
}

/*
 * Read TX good packets after half duplex defferal
 */
uint32_t xgmac_get_tx_dfr_gpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_dferd_gpkt;
}

/*
 * Read TX late collision error packets
 */
uint32_t xgmac_get_tx_lcol_epkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_lt_col_epkt;
}

/*
 * Read TX excessive collision error packets
 */
uint32_t xgmac_get_tx_ecol_epkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_exc_col_epkt;
}

/*
 * Read TX carrier sense error packets
 */
uint32_t xgmac_get_tx_ecar_epkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_carr_err_epkt;
}

/*
 * Read TX excessive defferal error packets
 */
uint32_t xgmac_get_tx_edfr_epkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->tx_exc_dferd_epkt;
}

/*
 * Read RX packet count good and bad "lower 32 bits"
 */
uint32_t xgmac_get_rx_pcnt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_pkt_cnt_gbl;
}

/*
 * Read RX octet count good and bad "lower 32 bits"
 */
uint32_t xgmac_get_rx_ocnt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_oct_cnt_gbl;
}

/*
 * Read RX octet count good and bad "upper 32 bits"
 */
uint32_t xgmac_get_rx_ocnt_gbh(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_oct_cnt_gbh;
}

/*
 * Read RX octet count good  "lower 32 bits"
 */
uint32_t xgmac_get_rx_gd_lcnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_oct_gl;
}

/*
 * Read RX octet count good  "upper 32 bits"
 */
uint32_t xgmac_get_rx_gd_hcnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_oct_gh;
}

/*
 * Read RX broadcast packet count good  "lower 32 bits"
 */
uint32_t xgmac_get_rx_bcst_glpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_bcst_pkt_gl;
}

/*
 * Read RX multicast packet count good  "lower 32 bits"
 */
uint32_t xgmac_get_rx_mcst_glpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_mcst_pkt_gl;
}

/*
 * Read RX crc error packets  "lower 32 bits"
 */
uint32_t xgmac_get_rx_ecrc_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_crc_err_pkt_low;
}

/*
 * Read RX runt error packets  "lower 32 bits"
 */
uint32_t xgmac_get_rx_erunt_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_runt_err_pkt;
}

/*
 * Read RX jabber error packets  "lower 32 bits"
 */
uint32_t xgmac_get_rx_ejbr_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_jb_err_pkt;
}

/*
 * Read RX undersize good packets  "lower 32 bits"
 */
uint32_t xgmac_get_rx_usize_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_usze_pkt_gd;
}

/*
 * Read RX oversize good packets  "lower 32 bits"
 */
uint32_t xgmac_get_rx_osize_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_osze_pkt_gd;
}

/*
 * Read RX group 0 = "64 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_rx_g0_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_64_oct_pkt_gbl;
}

/*
 * Read RX group 1 = "65-127 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_rx_g1_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_65_127_oct_pkt_gbl;
}

/*
 * Read RX group 2 = "128-255 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_rx_g2_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_128_255_oct_pkt_gbl;
}

/*
 * Read RX group 3 = "256-511 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_rx_g3_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_256_511_oct_pkt_gbl;
}

/*
 * Read RX group 4 = "512-1023 octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_rx_g4_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_512_1023_oct_pkt_gbl;
}

/*
 * Read RX group 5 = "1024-max octet packet good bad" lower 32 bits
 */
uint32_t xgmac_get_rx_g5_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_1024_max_oct_pkt_gbl;
}

/*
 * Read RX  good unicast packets " lower 32 bits
 */
uint32_t xgmac_get_rx_gupkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ucst_pkt_gl;
}

/*
 * Read RX length error packets "lower 32 bits
 */
uint32_t xgmac_get_rx_lerr_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_lth_er_pkt_low;
}

/*
 * Read RX out of range length packets "lower 32 bits
 */
uint32_t xgmac_get_rx_ornge_lpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_outrng_pkt_low;
}

/*
 * Read RX pause packet count "lower 32 bits
 */
uint32_t xgmac_get_rx_pse_lpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_pause_pkt_low;
}

/*
 * Read RX FIFO overflow packet count "lower 32 bits"
 */
uint32_t xgmac_get_rx_fifo_opkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_fifo_oflw_pkt_low;
}

/*
 * Read RX VLAN packet good bad "lower 32 bits"
 */
uint32_t xgmac_get_rx_vlan_pkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_vlan_pkt_gbl;
}

/*
 * Read RX watchdog error packets
 */
uint32_t xgmac_get_rx_ewdt_pkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_wdt_er_pkt;
}

/*
 * Read RX microseconds mac was in LPI receive
 */
uint32_t xgmac_get_rx_lpi_uscnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_lpi_usec_cntr;
}

/*
 * Read RX count for mac transitioning to receive
 */
uint32_t xgmac_get_rx_trans_cnt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_tran_cntr;
}

/*
 * Read RX number of good and discarded packets "lower 32 bits"
 */
uint32_t xgmac_get_rx_gdpkt_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_dcrd_pkt_gbl;
}

/*
 * Read RX number of good and discarded octet "lower 32 bits"
 */
uint32_t xgmac_get_rx_gdoct_gbl(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_dcrd_oct_gbl;
}

/*
 * Read RX number of good and discarded octet "upper 32 bits"
 */
uint32_t xgmac_get_rx_gdoct_gbh(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_dcrd_oct_gbh;
}

/*
 * Read RX packets with alignment errors
 */
uint32_t xgmac_get_rx_algn_epkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_algn_err_pkt;
}

/*
 * Read RX IPv4 good datagrams received "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_gd_pkt_low;
}

/*
 * Read RX IPv4 header error packets "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_hepkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_hdr_err_pkt_low;
}

/*
 * Read RX IPv4 datagrams received NOT TCP,UDP, or ICMP "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_npyld_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_no_pyld_pkt_low;
}

/*
 * Read RX IPv4 good datagrams with fragmentation "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_frag_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_frag_pkt_low;
}

/*
 * Read RX IPv4 UDP disabled checksum "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_upd_dckpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_udp_cksm_dsbl_pkt_low;
}

/*
 * Read RX IPv6 good datagrams received "lower 32 bits"
 */
uint32_t xgmac_get_rxipv6_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv6_gd_pkt_low;
}

/*
 * Read RX IPv6 header error packets "lower 32 bits"
 */
uint32_t xgmac_get_rxipv6_hepkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv6_hdr_err_pkt_low;
}

/*
 * Read RX IPv6 datagrams received NOT TCP,UDP, or ICMP "lower 32 bits"
 */
uint32_t xgmac_get_rxipv6_npyld_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv6_no_pyld_pkt_low;
}

/*
 * Read RX UDP good datagrams received "lower 32 bits"
 */
uint32_t xgmac_get_rxudp_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_udp_gd_pkt_low;
}

/*
 * Read RX UDP good datagrams received with checksum error "lower 32 bits"
 */
uint32_t xgmac_get_rxudp_eckpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_udp_ecks_pkt_low;
}

/*
 * Read RX TCP good datagrams received "lower 32 bits"
 */
uint32_t xgmac_get_rxtcp_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_tcp_gd_pkt_low;
}

/*
 * Read RX TCP good datagrams received with checksum error "lower 32 bits"
 */
uint32_t xgmac_get_rxtcp_eckpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_tcp_ecks_pkt_low;
}

/*
 * Read RX ICMP good datagrams received "lower 32 bits"
 */
uint32_t xgmac_get_rxicmp_gdpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_icmp_gd_pkt_low;
}

/*
 * Read RX ICMP good datagrams received with checksum error "lower 32 bits"
 */
uint32_t xgmac_get_rxicmp_eckpkt(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_icmp_ecks_pkt_low;
}

/*
 * Read RX IPv4 good datagrams received octet "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_gd_oct_low;
}

/*
 * Read RX IPv4 header error octet "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_heoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_hecks_oct_low;
}

/*
 * Read RX IPv4 datagrams octets received NOT TCP,UDP, or ICMP "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_npyld_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_no_pyld_oct_low;
}

/*
 * Read RX IPv4 good datagrams octets with fragmentation "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_frag_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_frag_oct_low;
}

/*
 * Read RX IPv4 UDP disabled checksum "lower 32 bits"
 */
uint32_t xgmac_get_rxipv4_upd_dckoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv4_udp_ck_dbl_oct_low;
}

/*
 * Read RX IPv6 good datagrams octet received "lower 32 bits"
 */
uint32_t xgmac_get_rxipv6_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv6_gd_oct_low;
}

/*
 * Read RX IPv6 header error octets "lower 32 bits"
 */
uint32_t xgmac_get_rxipv6_heoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv6_hdr_err_oct_low;
}

/*
 * Read RX IPv6 datagrams octets received NOT TCP,UDP, or ICMP "lower 32 bits"
 */
uint32_t xgmac_get_rxipv6_npyld_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_ipv6_no_pyld_oct_low;
}

/*
 * Read RX UDP good datagrams octets received "lower 32 bits"
 */
uint32_t xgmac_get_rxudp_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_udp_gd_oct_low;
}

/*
 * Read RX UDP good datagrams octets received with checksum error "lower 32 bits"
 */
uint32_t xgmac_get_rxudp_eckoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_udp_ecks_oct_low;
}
/*
 * Read RX TCP good datagrams octets received "lower 32 bits"
 */
uint32_t xgmac_get_rxtcp_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_tcp_gd_oct_low;
}

/*
 * Read RX TCP good datagrams octets received with checksum error "lower 32 bits"
 */
uint32_t xgmac_get_rxtcp_eckoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_tcp_ecks_oct_low;
}

/*
 * Read RX ICMP good datagrams octets received "lower 32 bits"
 */
uint32_t xgmac_get_rxicmp_gdoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_icmp_gd_oct_low;
}

/*
 * Read RX ICMP good datagrams octets received with checksum error "lower 32 bits"
 */
uint32_t xgmac_get_rxicmp_eckoct(int32_t base_address) {

    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;

    // retrieve variable
    return (uint32_t)xgmac_ptr->rx_icmp_ecks_oct_low;
}
/* METHODS FOR GETTING REGISTERS END */

/* METHODS FOR SETTING REGISTERS START */

/*
 * Set tx mac configuration register
 */
int32_t xgmac_set_tx_mac_config(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tx_cfg = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set rx mac configuration register
 */
int32_t xgmac_set_rx_mac_config(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rx_cfg = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac packet filter configuration
 */
int32_t xgmac_set_mac_pckt_filter(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pkt_fltr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac watchdog and jabber timeout
 */
int32_t xgmac_set_mac_wdt_jb_tout(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_wdt_jb_tout = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac hash table reg0
 */
int32_t xgmac_set_mac_htbl_reg0(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_hash_tbl_reg0 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac hash table reg1
 */
int32_t xgmac_set_mac_htbl_reg1(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_hash_tbl_reg1 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac vlan tag control
 */
int32_t xgmac_set_mac_vlan_tctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_vlan_tag_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac vlan hash table
 */
int32_t xgmac_set_mac_vlan_htbl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_vlan_tag_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac vlan tag data
 */
int32_t xgmac_set_mac_vlan_tdata(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_vlan_tag_dt = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac vlan inclusion replacement register
 */
int32_t xgmac_set_mac_vlan_incl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_vlan_incl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac vlan inner inclusion replacement register
 */
int32_t xgmac_set_mac_vlan_nincl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_vlan_incl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac receive ethernet type match register
 */
int32_t xgmac_set_mac_rx_etmtch(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rx_eth_tp_mch = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q0 flow control register
 */
int32_t xgmac_set_mac_q0_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q0_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q1 flow control register
 */
int32_t xgmac_set_mac_q1_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q1_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q2 flow control register
 */
int32_t xgmac_set_mac_q2_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q2_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q3 flow control register
 */
int32_t xgmac_set_mac_q3_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q3_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q4 flow control register
 */
int32_t xgmac_set_mac_q4_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q4_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q5 flow control register
 */
int32_t xgmac_set_mac_q5_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q5_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q6 flow control register
 */
int32_t xgmac_set_mac_q6_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q6_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac Q7 flow control register
 */
int32_t xgmac_set_mac_q7_fctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_q7_tx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac max receive flow control
 */
int32_t xgmac_set_mac_max_rxfctrl(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rx_fl_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac max receive queue control 4
 */
int32_t xgmac_set_mac_rx_qctrl4(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rxq_ctrl4 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac max receive queue control 5
 */
int32_t xgmac_set_mac_rx_qctrl5(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rxq_ctrl5 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac max receive queue control 0
 */
int32_t xgmac_set_mac_rx_qctrl0(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rxq_ctrl0 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac max receive queue control 1
 */
int32_t xgmac_set_mac_rx_qctrl1(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rxq_ctrl1 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}
/*
 * Set mac max receive queue control 2
 */
int32_t xgmac_set_mac_rx_qctrl2(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_rxq_ctrl2 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac max receive queue control 3
 */
int32_t xgmac_set_mac_rx_qctrl3(int32_t base_address, uint32_t wvalue) {

    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {

        // retrieve variable
        xgmac_ptr->mac_rxq_ctrl3 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac interrupt enable
 */
int32_t xgmac_set_mac_int_en(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {

        // retrieve variable
        xgmac_ptr->mac_int_en = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac LPI control status
 */
int32_t xgmac_set_mac_lpi_ctrl_sts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_lpi_ctr_sts = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac LPI timeout control register
 */
int32_t xgmac_set_mac_lpi_tm_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_lpi_tm_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac LPI auto entry timeout control register
 */
int32_t xgmac_set_mac_lpi_aet_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_lpi_au_en_tm = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac tick counter microseconds
 */
int32_t xgmac_set_mac_tic_ucntr(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_us_tk_cntr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac extended configuration
 */
int32_t xgmac_set_mac_ext_cfg0(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_ext_cfg = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac extended configuration 1
 */
int32_t xgmac_set_mac_ext_cfg1(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_ext_cfg1 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac FPE control status
 */
int32_t xgmac_set_mac_fpe_ctrl_sts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_fpe_ctrl_sts = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac csr programmable controls
 */
int32_t xgmac_set_mac_csr_pg_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_csr_sw_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 0 high
 */
int32_t xgmac_set_mac_haddr0(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr0_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 0 low
 */
int32_t xgmac_set_mac_laddr0(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr0_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 1 high
 */
int32_t xgmac_set_mac_haddr1(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr1_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 1 low
 */
int32_t xgmac_set_mac_laddr1(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr1_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 2 high
 */
int32_t xgmac_set_mac_haddr2(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr2_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 2 low
 */
int32_t xgmac_set_mac_laddr2(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr2_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 3 high
 */
int32_t xgmac_set_mac_haddr3(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr3_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 3 low
 */
int32_t xgmac_set_mac_laddr3(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr3_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 4 high
 */
int32_t xgmac_set_mac_haddr4(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr4_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 4 low
 */
int32_t xgmac_set_mac_laddr4(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr4_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 5 high
 */
int32_t xgmac_set_mac_haddr5(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr5_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 5 low
 */
int32_t xgmac_set_mac_laddr5(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr5_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 6 high
 */
int32_t xgmac_set_mac_haddr6(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr6_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 6 low
 */
int32_t xgmac_set_mac_laddr6(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr6_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 7 high
 */
int32_t xgmac_set_mac_haddr7(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr7_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 7 low
 */
int32_t xgmac_set_mac_laddr7(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr7_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 8 high
 */
int32_t xgmac_set_mac_haddr8(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr8_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 8 low
 */
int32_t xgmac_set_mac_laddr8(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr8_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 9 high
 */
int32_t xgmac_set_mac_haddr9(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr9_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 9 low
 */
int32_t xgmac_set_mac_laddr9(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr9_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 10 high
 */
int32_t xgmac_set_mac_haddr10(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr10_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 10 low
 */
int32_t xgmac_set_mac_laddr10(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr10_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 11 high
 */
int32_t xgmac_set_mac_haddr11(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr11_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 11 low
 */
int32_t xgmac_set_mac_laddr11(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr11_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 12 high
 */
int32_t xgmac_set_mac_haddr12(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr12_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 12 low
 */
int32_t xgmac_set_mac_laddr12(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr12_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 13 high
 */
int32_t xgmac_set_mac_haddr13(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr13_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 13 low
 */
int32_t xgmac_set_mac_laddr13(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr13_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 14 high
 */
int32_t xgmac_set_mac_haddr14(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr14_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 14 low
 */
int32_t xgmac_set_mac_laddr14(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr14_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 15 high
 */
int32_t xgmac_set_mac_haddr15(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr15_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 15 low
 */
int32_t xgmac_set_mac_laddr15(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr15_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 16 high
 */
int32_t xgmac_set_mac_haddr16(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr16_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 16 low
 */
int32_t xgmac_set_mac_laddr16(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr16_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 17 high
 */
int32_t xgmac_set_mac_haddr17(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr17_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 17 low
 */
int32_t xgmac_set_mac_laddr17(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr17_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 18 high
 */
int32_t xgmac_set_mac_haddr18(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr18_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 18 low
 */
int32_t xgmac_set_mac_laddr18(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr18_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 19 high
 */
int32_t xgmac_set_mac_haddr19(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr9_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 19 low
 */
int32_t xgmac_set_mac_laddr19(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr19_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 20 high
 */
int32_t xgmac_set_mac_haddr20(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr20_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 20 low
 */
int32_t xgmac_set_mac_laddr20(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr20_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 21 high
 */
int32_t xgmac_set_mac_haddr21(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr21_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 21 low
 */
int32_t xgmac_set_mac_laddr21(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr21_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 22 high
 */
int32_t xgmac_set_mac_haddr22(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr22_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 22 low
 */
int32_t xgmac_set_mac_laddr22(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr22_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 23 high
 */
int32_t xgmac_set_mac_haddr23(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr23_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 23 low
 */
int32_t xgmac_set_mac_laddr23(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr23_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 24 high
 */
int32_t xgmac_set_mac_haddr24(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr24_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 24 low
 */
int32_t xgmac_set_mac_laddr24(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr24_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 25 high
 */
int32_t xgmac_set_mac_haddr25(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr25_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 25 low
 */
int32_t xgmac_set_mac_laddr25(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr25_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 26 high
 */
int32_t xgmac_set_mac_haddr26(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr26_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 26 low
 */
int32_t xgmac_set_mac_laddr26(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr26_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 27 high
 */
int32_t xgmac_set_mac_haddr27(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr27_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 27 low
 */
int32_t xgmac_set_mac_laddr27(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr27_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 28 high
 */
int32_t xgmac_set_mac_haddr28(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr28_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 28 low
 */
int32_t xgmac_set_mac_laddr28(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr28_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 29 high
 */
int32_t xgmac_set_mac_haddr29(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr29_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 29 low
 */
int32_t xgmac_set_mac_laddr29(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr29_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 30 high
 */
int32_t xgmac_set_mac_haddr30(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr30_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 30 low
 */
int32_t xgmac_set_mac_laddr30(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr30_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 31 high
 */
int32_t xgmac_set_mac_haddr31(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr31_high = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac address 31 low
 */
int32_t xgmac_set_mac_laddr31(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_addr31_low = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac indirect access control
 */
int32_t xgmac_set_mac_ind_actrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_ind_acc_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac indirect access data
 */
int32_t xgmac_set_mac_ind_adata(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_ind_acc_data = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac l3/l4 access control
 */
int32_t xgmac_set_mac_l3_l4_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_l3_l4_addr_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac l3/l4 access data
 */
int32_t xgmac_set_mac_l3_l4_data(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_l3_l4_data = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}
/*
 * Set mac arp address
 */
int32_t xgmac_set_mac_arp_addr(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_arp_addr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac system time generator
 */
int32_t xgmac_set_mac_tmstamp_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmstamp_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac timestampe sub-second generator register
 */
int32_t xgmac_set_mac_tmstamp_ssec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_sub_sec_incr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac system time seconds update register
 */
int32_t xgmac_set_mac_systu_sec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_sys_tm_sec_updt = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac system time nano-seconds update register
 */
int32_t xgmac_set_mac_systu_nsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_sys_tm_nsec_updt = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac timestamp addend register
 */
int32_t xgmac_set_mac_tmstamp_addend(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmstamp_addend = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac timestamp high word seconds register
 */
int32_t xgmac_set_mac_tmstamp_hsword(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_sys_tm_hgh_wrd_sec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}
/*
 * Set mac auxillary time stamp control
 */
int32_t xgmac_set_mac_aux_tctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_aux_tmstamp_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac ingress asymmetry correction register
 */
int32_t xgmac_set_mac_tmstamp_ingress(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmstamp_ingr_asym_corr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac eress asymmetry correction register
 */
int32_t xgmac_set_mac_tmstamp_egress(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmstamp_egr_asym_corr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac ingress correction nanosecond register
 */
int32_t xgmac_set_mac_ingress_cor_nsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmstamp_ingr_corr_nsec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac ingress correction sub-nanosecond register
 */
int32_t xgmac_set_mac_ingress_cor_snsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmpsatmp_ingr_corr_subnsec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac egress correction nanosecond register
 */
int32_t xgmac_set_mac_egress_cor_nsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmpstamp_egr_corr_nsec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac egress correction sub-nanosecond register
 */
int32_t xgmac_set_mac_egress_cor_snsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_tmpstamp_egr_corr_subnsec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS control register
 */
int32_t xgmac_set_mac_pps_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS0 target time in seconds
 */
int32_t xgmac_set_mac_pps0_tgt_sec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps0_trg_tm_sec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS0 target time in nano-seconds
 */
int32_t xgmac_set_mac_pps0_tgt_nsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps0_trg_tm_nsec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS0 interval register
 */
int32_t xgmac_set_mac_pps0_intv(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps0_intv = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS0 width register
 */
int32_t xgmac_set_mac_pps0_width(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps0_wdh = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS1 target time in seconds
 */
int32_t xgmac_set_mac_pps1_tgt_sec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps1_trg_tm_sec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS1 target time in nano-seconds
 */
int32_t xgmac_set_mac_pps1_tgt_nsec(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps1_trg_tm_nsec = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS1 interval register
 */
int32_t xgmac_set_mac_pps1_intv(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps1_intv = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac PPS1 width register
 */
int32_t xgmac_set_mac_pps1_width(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // set pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pps1_wdh = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac control of PTP operation mode
 */
int32_t xgmac_set_mac_pto_ctrl(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_pto_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac port identity 0
 */
int32_t xgmac_set_mac_port_id0(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_src_pt_iden0 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac port identity 1
 */
int32_t xgmac_set_mac_port_id1(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_src_pt_iden1 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac port identity 2
 */
int32_t xgmac_set_mac_port_id2(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_src_pt_iden2 = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mac interval of automatic PTP packet
 */
int32_t xgmac_set_mac_ptp_aintv(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mac_log_msg_intv = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio single command address register
 */
int32_t xgmac_set_mdio_sgl_cmd_addr(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_sgl_cmd_addr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio single command data register
 */
int32_t xgmac_set_mdio_sgl_cmd_data(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_sgl_cmd_ctrl_dt = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio continuous write address
 */
int32_t xgmac_set_mdio_cnt_wr_addr(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_cnt_wrt_addr = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio continuous write data
 */
int32_t xgmac_set_mdio_cnt_wr_data(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_cnt_wrt_dt = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio continuous scan ports enabled
 */
int32_t xgmac_set_mdio_sctn_pen(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_cnt_scan_pt_en = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio sma interrupt status
 */
int32_t xgmac_set_mdio_sma_int_sts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_int_sts = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio sma interrupts enabled
 */
int32_t xgmac_set_mdio_sma_int_en(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_int_en = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio connect disconnect status
 */
int32_t xgmac_set_mdio_conn_disc_sts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_port_ct_dct_sts = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio SMA PHY port configuration
 */
int32_t xgmac_set_mdio_cl22_port(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_cls22_port = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio port range select port
 */
int32_t xgmac_set_mdio_port_rng_sel(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_port_nx4_idrt_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio nx4 p0 device status
 */
int32_t xgmac_set_mdio_nx4_p0_dsts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_portnx4p0_dev_in_use = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio nx4 p1 device status
 */
int32_t xgmac_set_mdio_nx4_p1_dsts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_portnx4p1_dev_in_use = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio nx4 p2 device status
 */
int32_t xgmac_set_mdio_nx4_p2_dsts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_portnx4p2_dev_in_use = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mdio nx4 p3 device status
 */
int32_t xgmac_set_mdio_nx4_p3_dsts(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mdio_portnx4p3_dev_in_use = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mmc control register
 */
int32_t xgmac_set_mmc_ctrl_reg(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mmc_ctrl = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mmc receive interrupt enable register
 */
int32_t xgmac_set_mmc_rx_int_en(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mmc_rx_int_en = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}

/*
 * Set mmc transmit interrupt enable register
 */
int32_t xgmac_set_mmc_tx_int_en(int32_t base_address, uint32_t wvalue) {
    int32_t ret_val = -1;
    // Get pointer to address space
    xgmac_core_t *xgmac_ptr = (xgmac_core_t *)base_address;
    if ((base_address == XGMAC0_BASE) || (base_address == XGMAC1_BASE) || (base_address == XGMAC2_BASE)) {
        xgmac_ptr->mmc_tx_int_en = wvalue;
        ret_val = 0;
    }
    // return status
    return ret_val;
}
/* CORE METHODS DEFINITION END */

/* XGMA DMA INTERNAL METHODS DEFINITION START */
int32_t xgmac_get_dma_mode(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Mode;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_mode(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Mode = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_sysbus_mode(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_SysBus_Mode;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_sysbus_mode(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_SysBus_Mode = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_interrupt_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Interrupt_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_interrupt_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Interrupt_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_axi_tx_ar_ace_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.AXI_Tx_AR_ACE_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_axi_tx_ar_ace_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.AXI_Tx_AR_ACE_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_axi_rx_aw_ace_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.AXI_Rx_AW_ACE_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_axi_rx_aw_ace_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.AXI_Rx_AW_ACE_Control = param[0];
        return_value = 0;
    }
    return return_value;
}

int32_t xgmac_get_dma_axi_txrx_awar_ace_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.AXI_TxRx_AWAR_ACE_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_axi_txrx_awar_ace_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.AXI_TxRx_AWAR_ACE_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_debug_status0(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Debug_Status0;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_debug_status0(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Debug_Status0 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_debug_status1(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Debug_Status1;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_debug_status1(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Debug_Status1 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_debug_status3(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Debug_Status3;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_debug_status3(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Debug_Status3 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_tx_edma_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Tx_EDMA_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_tx_edma_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Tx_EDMA_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_rx_edma_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_Rx_EDMA_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_rx_edma_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_Rx_EDMA_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_axi_lpi_entry_interval(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.AXI_LPI_Entry_Interval;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_axi_lpi_entry_interval(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.AXI_LPI_Entry_Interval = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_tbs_control0(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL0;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_tbs_control0(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL0 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_tbs_control1(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL1;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_tbs_control1(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL1 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_tbs_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_tbs_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_tbs_control3(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL3;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_tbs_control3(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_TBS_CTRL3 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch_ind_ctrl(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_CH_Ind_Ctrl;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch_ind_ctrl(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_CH_Ind_Ctrl = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch_ind_data(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_base.DMA_CH_Ind_Data;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch_ind_data(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_base.DMA_CH_Ind_Data = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 0
int32_t xgmac_get_dma_ch0_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch0_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch0_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[0].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 1
int32_t xgmac_get_dma_ch1_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch1_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch1_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[1].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 2
int32_t xgmac_get_dma_ch2_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch2_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch2_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[2].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 3
int32_t xgmac_get_dma_ch3_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch3_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch3_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[3].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 4
int32_t xgmac_get_dma_ch4_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch4_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch4_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[4].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 5
int32_t xgmac_get_dma_ch5_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch5_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch5_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[5].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 6
int32_t xgmac_get_dma_ch6_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch6_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch6_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[6].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}

// XGMAC DMA Channel 7
int32_t xgmac_get_dma_ch7_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_tx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Control;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rx_control(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Control = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Slot_Function_Control_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_slot_function_control_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Slot_Function_Control_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_TxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_txdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_TxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_TxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_txdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_TxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_RxDesc_List_HAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rxdesc_list_haddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_RxDesc_List_HAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_RxDesc_List_LAddress;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rxdesc_list_laddress(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_RxDesc_List_LAddress = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_TxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_txdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_TxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_RxDesc_Tail_LPointer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rxdesc_tail_lpointer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_RxDesc_Tail_LPointer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_tx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Control2;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rx_control2(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Control2 = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Interrupt_Enable;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_interrupt_enable(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Interrupt_Enable = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Interrupt_Watchdog_Timer;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rx_interrupt_watchdog_timer(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Interrupt_Watchdog_Timer = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_TxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_current_app_txdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_TxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_RxDesc_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_current_app_rxdesc_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_RxDesc_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_TxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_current_app_txbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_TxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_TxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_current_app_txbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_TxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_RxBuffer_H;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_current_app_rxbuffer_h(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_RxBuffer_H = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_RxBuffer_L;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_current_app_rxbuffer_l(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Current_App_RxBuffer_L = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Debug_Status;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_debug_status(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Debug_Status = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Desc_Mem_Cache_Fill_Level;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_desc_mem_cache_fill_level(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Desc_Mem_Cache_Fill_Level = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Miss_Packet_Cnt;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_miss_packet_cnt(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Miss_Packet_Cnt = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_tx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Data_Xfer_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rx_data_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Data_Xfer_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_tx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Tx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_get_dma_ch7_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        param[0] = xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Desc_Write_Ring_Offset;
        return_value = 0;
    }
    return return_value;
}
int32_t xgmac_set_dma_ch7_rx_desc_xfer_ring_offset(int32_t base_add, uintptr_t buf, size_t size) {
    int32_t return_value = -1;
    uint32_t *param = (uint32_t *)buf;
    xgmac_t *xgmac_reg = (xgmac_t *)(base_add);
    if (size < sizeof(uint32_t)) {
        return_value = -1;
    } else {
        xgmac_reg->xgmac_dma.dma_ch[7].DMA_CH_Rx_Desc_Write_Ring_Offset = param[0];
        return_value = 0;
    }
    return return_value;
}
/* XGMAC DMA INTERNAL METHODS DEFINITION END */
/* METHODS FOR SETTING REGISTERS END */
