/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_fcs_ll.h
 *
 * FCS low-level driver interface for the SoCFPGA bare-metal software stack.
 *
 */

#ifndef _SOCFPGA_FCS_LL_H_
#define _SOCFPGA_FCS_LL_H_

#define FCS_MAX_INSTANCES    6U
#define FCS_GET_COMM_SOURCE(session_id)    (((session_id) & 0xF0000000U) >> 28)
#define FCS_COMM_SOURCE_HPS    2U
/*
 * if source is on HPS max size is usually 256MB
 * if source is on FPGA max size is usually 512MB
 */
#define FCS_MAX_SIZE_HPS           0x10000000U
#define FCS_MAX_SIZE_FPGA          0x20000000U
#define FCS_EXPORT_KEY_MAX_SIZE    364U
#define FCS_RESP_STATUS            0U
#define FCS_RESP_KEY_STATUS        1U
#define FCS_RESP_CERT_STATUS       1U
#define FCS_RESP_SIZE              1U
#define FCS_RESP_DATA              3U
#define FCS_RESP_HEADER_SIZE       12U
#define FCS_KEY_HEADER_SIZE        12U
#define FCS_UPDATE                 0U
#define FCS_FINALIZE               1U
/*0x5 are bits set for init and finalize*/
#define FCS_KEY_INFO_MAX_RESP                20U
#define FCS_DIGEST_PARAM_SIZE                4U
#define FCS_MAC_PARAM_SIZE                   4U
#define FCS_MAC_VERIFY_RESP                  16U
#define FCS_DIGEST_MAX_RESP                  84
#define FCS_GCM_BLOCK_SIZE                   16U
#define FCS_AES_GCM_MAX_SIZE                 0x10000U
#define FCS_AES_ECB_PARAM_SIZE               8U
#define FCS_AES_MAX_PARAM_SIZE               28U
#define FCS_AES_IV_SIZE                      16U
#define FCS_AAD_MAX_SIZE                     0xFFFFU
#define FCS_ECDSA_HASH_SIGN_MAX_RESP         108U
#define FCS_ECDSA_HASH_SHA2_SIGN_MAX_RESP    108U
#define FCS_ECDSA_HASH_VERIFY_RESP           84U
#define FCS_ECDSA_HASH_SHA2_VERIFY_RESP      84U
#define FCS_GET_PUBKEY_RESP                  184U
#define FCS_ECDSA_PARAM_SIZE                 4U
/* Function IDs for SMC calls*/
/* Session Management SMC function ids */
#define FCS_OPEN_SESSION     0x4200013AU
#define FCS_CLOSE_SESSION    0x4200013BU
/* Key Management SMC function ids */
#define FCS_IMPORT_SERVICE_KEY      0x4200013CU
#define FCS_EXPORT_SERVICE_KEY      0x4200013DU
#define FCS_REMOVE_SERVICE_KEY      0x4200013EU
#define FCS_GET_SERVICE_KEY_INFO    0x4200013FU
#define FCS_CREATE_SERVICE_KEY      0x42000167U
#define FCS_HKDF_REQUEST            0x42000166U

#define FCS_GET_DEVICE_IDENTITY                0x420000D2U
#define FCS_GET_IDCODE                         0x420000D3U
#define FCS_RANDOM_NUMBER                      0x4200012DU
#define FCS_SDOS_CRYPTION                      0x4200012FU
#define FCS_SEND_CERTIFICATE                   0x42000131U
#define FCS_GET_PROVISION_DATA                 0x42000132U
#define FCS_CNTR_SET_PREAUTH                   0x42000133U
#define FCS_GET_CHIP_ID                        0x42000135U
#define FCS_GET_ATTESTATION_CERT               0x42000138U
#define FCS_CREATE_CERT_ON_RELOAD              0x42000139U
#define FCS_AES_INIT                           0x42000140U
#define FCS_AES_UPDATE                         0x42000141U
#define FCS_AES_FINALIZE                       0x42000142U
#define FCS_GET_DIGEST_INIT                    0x42000143U
#define FCS_GET_DIGEST_UPDATE                  0x42000144U
#define FCS_GET_DIGEST_FINALIZE                0x42000145U
#define FCS_MAC_VERIFY_INIT                    0x42000148U
#define FCS_MAC_VERIFY_UPDATE                  0x42000149U
#define FCS_MAC_VERIFY_FINALIZE                0x4200014AU
#define FCS_ECDSA_HASH_SIGN_INIT               0x4200014DU
#define FCS_ECDSA_HASH_SIGN_FINALIZE           0x4200014EU
#define FCS_ECDSA_SHA2_SIGN_INIT               0x4200014FU
#define FCS_ECDSA_SHA2_SIGN_UPDATE             0x42000150U
#define FCS_ECDSA_SHA2_SIGN_FINALIZE           0x42000151U
#define FCS_ECDSA_HASH_SIGN_VERIFY_INIT        0x42000154U
#define FCS_ECDSA_HASH_SIGN_VERIFY_FINALIZE    0x42000155U
#define FCS_ECDSA_SHA2_SIGN_VERIFY_INIT        0x42000156U
#define FCS_ECDSA_SHA2_SIGN_VERIFY_UPDATE      0x42000157U
#define FCS_ECDSA_SHA2_SIGN_VERIFY_FINALIZE    0x42000158U
#define FCS_GET_PUBKEY_INIT                    0x42000160U
#define FCS_GET_PUBKEY_FINALIZE                0x42000161U
#define FCS_ECDH_INIT                          0x42000162U
#define FCS_ECDH_FINALIZE                      0x42000163U
#define FCS_MCTP_SEND_MSG                      0x42000165U

#define FCS_AES_BLOCK_MODE(crypto_param)     (crypto_param & 0xFFU)
#define FCS_SET_CRYPT_MODE(crypt_mode)       (((crypt_mode) & 0x1U) << 8U)
#define FCS_SET_TAG_LEN(crypto_param)        (((crypto_param) & 0xFFU) << 16U)
#define FCS_SET_DIGEST_SIZE(crypto_param)    (((crypto_param) & 0xFFU) << 4U)
#define FCS_SMMU_GET_ADDR(addr) ((uint64_t)((uintptr_t)(addr) - (uintptr_t)0x80000000U))

#endif /* _SOCFPGA_FCS_LL_H_ */
