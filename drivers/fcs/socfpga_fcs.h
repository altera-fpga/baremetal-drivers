/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

/* File: socfpga_fcs.h
 *
 * Flexible Cryptographic Subsystem (FCS) driver. It talks to the Secure
 * Device Manager mailbox for AES, ECDSA, digests, and keys.
 *
 */

#ifndef _SOCFPGA_FCS_H_
#define _SOCFPGA_FCS_H_

#include <stdint.h>

/* Constants: Buffer and key sizes
 *
 * Sizes for crypto buffers and keys, in bytes.
 *
 * FCS_RNG_MAX_SIZE           - Most random bytes one call may ask for.
 * FCS_UUID_SIZE              - Session UUID length.
 * FCS_MAX_KEY_SIZE           - Largest key import and create will accept.
 * FCS_SDOS_MIN_INPUT         - Smallest SDOS input.
 * FCS_SDOS_MAX_INPUT         - Largest SDOS input.
 * FCS_SDOS_ENC_MAX_RESP      - Largest SDOS encrypt response. Passed to the mailbox as the response size.
 * FCS_SDOS_DEC_MAX_RESP      - Largest SDOS decrypt response. Passed to the mailbox as the response size.
 * FCS_ATTEST_CERT_MAX_SIZE   - Largest attestation certificate the driver prepares a buffer for.
 * FCS_MCTP_MAX_SIZE          - Largest MCTP response the driver prepares a buffer for.
 * FCS_PROV_DATA_MAX_SIZE     - Largest provisioning blob the driver prepares a buffer for.
 * FCS_DEV_IDENTITY_RESP_SIZE - Device-identity buffer size.
 * FCS_ECDH_MAX_RESP          - Largest ECDH response. The driver uses it as the shared-secret buffer size.
 */
#define FCS_RNG_MAX_SIZE             4084U
#define FCS_UUID_SIZE                16U
#define FCS_MAX_KEY_SIZE             240U
#define FCS_SDOS_MIN_INPUT           32U
#define FCS_SDOS_MAX_INPUT           32672U
#define FCS_SDOS_ENC_MAX_RESP        32760U
#define FCS_SDOS_DEC_MAX_RESP        32712U
#define FCS_ATTEST_CERT_MAX_SIZE     4096U
#define FCS_MCTP_MAX_SIZE            4096U
#define FCS_PROV_DATA_MAX_SIZE       1024U
#define FCS_DEV_IDENTITY_RESP_SIZE   32
#define FCS_ECDH_MAX_RESP            120U

/* Constants: SDOS configuration
 *
 * Values for the Secure Data Object Service (SDOS).
 *
 * FCS_SDOS_MAGIC_NUMBER   - Magic number for an SDOS header.
 * FCS_SDOS_HEADER_PADDING - Padding word for an SDOS header.
 * FCS_SDOS_ENCRYPT_MODE   - Mailbox mode for SDOS encrypt (1).
 * FCS_SDOS_DECRYPT_MODE   - Mailbox mode for SDOS decrypt (0).
 */
#define FCS_SDOS_MAGIC_NUMBER        0xACBDBDEDU
#define FCS_SDOS_HEADER_PADDING      0x01020304U
#define FCS_SDOS_ENCRYPT_MODE        0x1U
#define FCS_SDOS_DECRYPT_MODE        0x0U

/* Constants: Digest and hashing modes
 *
 * Digest mode and size codes. In SHA-2 mode the driver clears the key id.
 *
 * FCS_DIGEST_OPMODE_SHA2 - SHA-2 hash mode (1).
 * FCS_DIGEST_OPMODE_HMAC - HMAC mode (2).
 * FCS_DIGEST_SIZE_256    - 256-bit digest size code (0).
 * FCS_DIGEST_SIZE_384    - 384-bit digest size code (1).
 * FCS_DIGEST_SIZE_512    - 512-bit digest size code (2).
 */
#define FCS_DIGEST_OPMODE_SHA2       0x1U
#define FCS_DIGEST_OPMODE_HMAC       0x2U
#define FCS_DIGEST_SIZE_256          0x0U
#define FCS_DIGEST_SIZE_384          0x1U
#define FCS_DIGEST_SIZE_512          0x2U

/* Constants: AES configuration
 *
 * AES mode, GCM tag, and IV-source codes. The driver rejects a block
 * mode outside this list, a tag code above the 128-bit code, and an IV source
 * above the internal-base code. GCM-GHASH forces the crypt mode to 0.
 *
 * FCS_AES_ENCRYPT_MODE - Encrypt (0).
 * FCS_AES_DECRYPT_MODE - Decrypt (1).
 * FCS_AES_ECB          - ECB block mode (0).
 * FCS_AES_CBC          - CBC block mode (1).
 * FCS_AES_CTR          - CTR block mode (2).
 * FCS_AES_GCM          - GCM block mode (3).
 * FCS_AES_GCM_GHASH    - GCM-GHASH block mode (4).
 * FCS_AES_TAG_32       - 32-bit GCM tag code (0).
 * FCS_AES_TAG_64       - 64-bit GCM tag code (1).
 * FCS_AES_TAG_96       - 96-bit GCM tag code (2).
 * FCS_AES_TAG_128      - 128-bit GCM tag code (3).
 * FCS_GCM_TAG_SIZE     - GCM tag length, in bytes (16). Added to a GCM buffer.
 * FCS_IV_EXTERNAL      - IV-source code 0 (external).
 * FCS_IV_INTERNAL_DRNG - IV-source code 1 (internal DRNG).
 * FCS_IV_INTERNAL_BASE - IV-source code 2 (internal base).
 */
#define FCS_AES_ENCRYPT_MODE         0x0U
#define FCS_AES_DECRYPT_MODE         0x1U
#define FCS_AES_ECB                  0x0U
#define FCS_AES_CBC                  0x1U
#define FCS_AES_CTR                  0x2U
#define FCS_AES_GCM                  0x3U
#define FCS_AES_GCM_GHASH            0x4U
#define FCS_AES_TAG_32               0x0U
#define FCS_AES_TAG_64               0x1U
#define FCS_AES_TAG_96               0x2U
#define FCS_AES_TAG_128              0x3U
#define FCS_GCM_TAG_SIZE             16U
#define FCS_IV_EXTERNAL              0x0U
#define FCS_IV_INTERNAL_DRNG         0x1U
#define FCS_IV_INTERNAL_BASE         0x2U

/* Constants: ECC and key exchange configuration
 *
 * Curve, HKDF, and size values. The driver rejects an ECC algorithm
 * that is not one of the four curve codes.
 *
 * FCS_ECC_NISTP_256      - NIST P-256 curve code (1).
 * FCS_ECC_NISTP_384      - NIST P-384 curve code (2).
 * FCS_ECC_BRAINPOOL_256  - Brainpool 256-bit curve code (3).
 * FCS_ECC_BRAINPOOL_384  - Brainpool 384-bit curve code (4).
 * FCS_EXTRACT_AND_EXPAND - HKDF step code for extract and expand (0).
 * FCS_EXPAND             - HKDF step code for expand (1).
 * FCS_EXPAND_GCM         - HKDF step code 2 (expand with GCM).
 * FCS_HKDF_256           - HKDF MAC-mode code for 256 bits (0).
 * FCS_HKDF_384           - HKDF MAC-mode code for 384 bits (1).
 * FCS_HKDF_512           - HKDF MAC-mode code for 512 bits (2).
 * FCS_SHARED_SEC_SIZE    - Shared-secret size, in bytes (48).
 * FCS_MAX_SIG_SIZE       - Largest signature, in bytes (96).
 * FCS_MAX_PUBKEY_SIZE    - Largest public key, in bytes (96).
 */
#define FCS_ECC_NISTP_256            0x1U
#define FCS_ECC_NISTP_384            0x2U
#define FCS_ECC_BRAINPOOL_256        0x3U
#define FCS_ECC_BRAINPOOL_384        0x4U
#define FCS_EXTRACT_AND_EXPAND       0x0
#define FCS_EXPAND                   0x1
#define FCS_EXPAND_GCM               0x2
#define FCS_HKDF_256                 0x0
#define FCS_HKDF_384                 0x1
#define FCS_HKDF_512                 0x2
#define FCS_SHARED_SEC_SIZE          48U
#define FCS_MAX_SIG_SIZE             96U
#define FCS_MAX_PUBKEY_SIZE          96U


/* Struct: fcs_sdos_crypt_header
 *
 * Defines the header structure for Secure Data Object Service (SDOS) 
 * cryptographic payloads.
 */
struct fcs_sdos_crypt_header
{
    uint32_t magic_number;
    uint32_t data_len;
    uint8_t pad;
    uint8_t srk_indx;
    uint16_t app_spec_obj_info;
    uint8_t owner_id[8];
    uint32_t hdr_pad;
    uint8_t iv_field[16];
};


/* Function: fcs_init
 *
 * Initializes the FCS driver layer and the underlying SIP_SVC mailbox interface.
 *
 * Returns:
 *
 * 0 on success; -EIO if the FCS service cannot be contacted, or -EINVAL if 
 * internal driver memory allocation fails.
 */
int fcs_init(void);

/* Function: fcs_deinit
 *
 * Shuts down the FCS driver, clearing internal buffers and relinquishing mailbox 
 * resources.
 *
 * Returns:
 *
 * 0 on success; -EIO if the FCS service is unresponsive.
 */
int fcs_deinit(void);

/* Function: run_fcs_open_service_session
 *
 * Initiates a cryptographic session with the SDM. This binds the host's 
 * mailbox client to a unique session identifier (UUID).
 *
 * Parameters:
 *
 * uuid - Pointer to a buffer where the generated 16-byte session UUID will be stored.
 *
 * Returns:
 *
 * 0 on success; -EIO or -EINVAL if the session request is rejected.
 */
int run_fcs_open_service_session(char *uuid);

/* Function: run_fcs_close_service_session
 *
 * Tears down a cryptographic session and releases the associated mailbox client resources.
 *
 * Parameters:
 *
 * uuid - The UUID of the session to terminate.
 *
 * Returns:
 *
 * 0 on success; -EIO if the session closure fails.
 */
int run_fcs_close_service_session(char *uuid);

/* Function: run_fcs_random_number_ext
 *
 * Requests the SDM to generate cryptographically secure random bytes using 
 * the internal True Random Number Generator (TRNG).
 *
 * Parameters:
 *
 * rand_buf   - Destination buffer for the random data.
 * uuid       - The session UUID.
 * context_id - Operation context identifier.
 * rand_size  - Number of bytes to generate (<= FCS_RNG_MAX_SIZE).
 *
 * Returns:
 *
 * 0 on success; -EINVAL or -EIO if the request fails.
 */
int run_fcs_random_number_ext(char *rand_buf, char *uuid, uint32_t context_id,
        uint32_t rand_size);

/* Function: run_fcs_import_service_key
 *
 * Imports an encrypted or raw key into the FCS secure storage.
 *
 * Parameters:
 *
 * uuid        - The session UUID.
 * key         - Buffer containing the key material.
 * key_size    - Length of key data.
 * status      - Buffer to receive import success/failure status.
 * status_size - Pointer to variable receiving the size of the status response.
 *
 * Returns:
 *
 * 0 on success; -EINVAL or -EIO if the key is rejected.
 */
int run_fcs_import_service_key(char *uuid, char *key, uint32_t key_size,
        char *status, unsigned int *status_size);

/* Function: run_fcs_export_service_key
 *
 * Exports a key from secure storage. Note that only non-secure or wrapped 
 * keys are eligible for export depending on device security policy.
 *
 * Parameters:
 *
 * uuid     - The session UUID.
 * key_id   - Identifier of the key to export.
 * key_dest - Destination buffer for the exported key.
 * key_size - Pointer to variable receiving the size of the key.
 *
 * Returns:
 *
 * 0 on success; -EIO if export is not permitted.
 */
int run_fcs_export_service_key(char *uuid, uint32_t key_id, char *key_dest,
        unsigned int *key_size);

/* Function: run_fcs_remove_service_key
 *
 * Permanently deletes a key from secure storage.
 *
 * Parameters:
 *
 * uuid   - The session UUID.
 * key_id - Identifier of the key to delete.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_remove_service_key(char *uuid, uint32_t key_id);

/* Function: run_fcs_get_service_key_info
 *
 * Retrieves metadata regarding a specific key ID, such as its usage policy or 
 * constraints, without exporting the key material itself.
 *
 * Parameters:
 *
 * uuid          - The session UUID.
 * key_id        - Identifier of the key.
 * key_info      - Destination buffer for metadata.
 * key_info_size - Pointer to variable receiving the size of the info.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_get_service_key_info(char *uuid, uint32_t key_id, char *key_info,
        unsigned int *key_info_size);

/* Function: run_fcs_create_service_key
 *
 * Directs the FCS to generate a new key within its internal secure storage 
 * based on specified parameters.
 *
 * Parameters:
 *
 * uuid        - The session UUID.
 * key         - (Reserved/Input) Key generation configuration.
 * key_size    - Size of key parameters.
 * status      - Buffer receiving the creation status.
 * status_size - Pointer to variable receiving the size of the status.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_create_service_key(char *uuid, char *key, uint32_t key_size,
        char *status, unsigned int *status_size);

/* Function: run_fcs_service_get_provision_data
 *
 * Fetches provisioning data bundles from the FCS secure storage.
 *
 * Parameters:
 *
 * prov_data      - Destination buffer for the provisioning blob.
 * prov_data_size - Pointer to variable receiving the blob size.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_service_get_provision_data(char *prov_data,
        uint32_t *prov_data_size);

/* Function: run_fcs_send_certificate
 *
 * Uploads a signed certificate to the SDM for device attestation or identity verification.
 *
 * Parameters:
 *
 * cert_data - Pointer to certificate data.
 * cert_size - Size of the certificate.
 * status    - Pointer to receive the SDM verification status.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_send_certificate(char *cert_data, uint32_t cert_size,
        uint32_t *status);

/* Function: run_fcs_service_counter_set_preauthorized
 *
 * Updates a pre-authorized service counter (e.g., for anti-rollback or 
 * lifecycle management).
 *
 * Parameters:
 *
 * type  - Counter type identifier.
 * value - New counter value.
 * test  - Test flag (reserved for non-production environments).
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_service_counter_set_preauthorized(uint8_t type, uint32_t value,
        uint32_t test);

/* Function: run_fcs_get_digest
 *
 * Computes a cryptographic hash or HMAC on the provided source buffer using 
 * the FCS hardware engine.
 *
 * Parameters:
 *
 * uuid        - The session UUID.
 * context_id  - Operation context identifier.
 * key_id      - Key ID for HMAC operations (or 0 for SHA-only).
 * op_mode     - Digest mode (<FCS_DIGEST_OPMODE_SHA2> or <FCS_DIGEST_OPMODE_HMAC>).
 * dig_size    - Requested digest size (256/384/512 bits).
 * src_data    - Pointer to data to hash.
 * src_size    - Size of source data.
 * digest_data - Destination buffer for the digest.
 * digest_size - Pointer to variable receiving the size of the digest.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_get_digest(char *uuid, uint32_t context_id, uint32_t key_id,
        uint32_t op_mode, uint32_t dig_size, char *src_data, uint32_t src_size,
        char *digest_data, uint32_t *digest_size);

/* Function: run_fcs_mac_verify
 *
 * Validates a Message Authentication Code (MAC) against the provided data.
 *
 * Parameters:
 *
 * uuid           - The session UUID.
 * context_id     - Operation context identifier.
 * key_id         - Key ID used for the verification.
 * dig_size       - Digest size identifier.
 * src_data       - Source data buffer.
 * src_size       - Size of source data.
 * dest_data      - Buffer containing the MAC to verify.
 * dest_size      - Size of the MAC.
 * user_data_size - User-defined data size.
 *
 * Returns:
 *
 * 0 on success (MAC valid); negative if verification fails.
 */
int run_fcs_mac_verify(char *uuid, uint32_t context_id, uint32_t key_id,
        uint32_t dig_size, char *src_data, uint32_t src_size, char *dest_data,
        uint32_t *dest_size, uint32_t user_data_size);

/* Function: run_fcs_sdos_encrypt
 *
 * Performs hardware-accelerated AES encryption using the SDOS (Secure Data Object Service).
 *
 * Parameters:
 *
 * uuid       - The session UUID.
 * context_id - Context identifier.
 * src_data   - Plaintext source data.
 * src_size   - Size of plaintext.
 * resp_data  - Destination buffer for ciphertext.
 * resp_size  - Pointer to variable receiving the size of ciphertext.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_sdos_encrypt(char *uuid, uint32_t context_id, char *src_data,
        uint32_t src_size, char *resp_data, uint32_t *resp_size);

/* Function: run_fcs_sdos_decrypt
 *
 * Performs hardware-accelerated AES decryption using the SDOS.
 *
 * Parameters:
 *
 * uuid       - The session UUID.
 * context_id - Context identifier.
 * src_data   - Ciphertext source data.
 * src_size   - Size of ciphertext.
 * resp_data  - Destination buffer for plaintext.
 * resp_size  - Pointer to variable receiving the size of plaintext.
 * owner_flag - Ownership/Policy flags for the decryption operation.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_sdos_decrypt(char *uuid, uint32_t context_id, char *src_data,
        uint32_t src_size, char *resp_data, uint32_t *resp_size, uint64_t
        owner_flag);

/* Function: run_fcs_hkdf_request
 *
 * Executes a Key Derivation Function (HKDF) to derive sub-keys from an 
 * initial keying material (IKM).
 *
 * Parameters:
 *
 * uuid            - The session UUID.
 * key_id          - The base key ID.
 * step_type       - Derivation step (extract/expand).
 * mac_mode        - HMAC algorithm mode.
 * input_buffer    - Context/Salt input data.
 * output_key_size - Requested length of the derived key.
 * hkdf_status     - Pointer to receive the HKDF operation status.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_hkdf_request(char *uuid, uint32_t key_id, uint32_t step_type,
        uint32_t mac_mode, char *input_buffer, uint32_t output_key_size,
        uint32_t *hkdf_status);

/* Function: run_fcs_get_chip_id
 *
 * Retrieves the unique silicon chip identification.
 *
 * Parameters:
 *
 * chip_low  - Pointer to receive the lower 32 bits of the ID.
 * chip_high - Pointer to receive the upper 32 bits of the ID.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_get_chip_id(uint32_t *chip_low, uint32_t *chip_high);

/* Function: run_fcs_attestation_get_certificate
 *
 * Retrieves a device attestation certificate managed by the SDM.
 *
 * Parameters:
 *
 * cert_req  - Certificate request identifier.
 * cert_data - Destination buffer.
 * cert_size - Pointer to receive the certificate size.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_attestation_get_certificate(int cert_req, char *cert_data,
        uint32_t *cert_size);

/* Function: run_fcs_attestation_certificate_reload
 *
 * Forces the SDM to reload/re-authenticate the attestation certificate 
 * stored in secure memory.
 *
 * Parameters:
 *
 * cert_req - Certificate request identifier.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_attestation_certificate_reload(int cert_req);

/* Function: run_fcs_mctp_cmd_send
 *
 * Transmits an MCTP command packet to the SDM for cryptographic processing 
 * or management.
 *
 * Parameters:
 *
 * src_data  - Pointer to MCTP command packet.
 * src_size  - Length of the packet.
 * resp_data - Destination buffer for the response.
 * resp_size - Pointer to receive the size of the response.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_mctp_cmd_send(char *src_data, uint32_t src_size, char *resp_data,
        uint32_t *resp_size);

/* Function: run_fcs_get_jtag_idcode
 *
 * Reads the JTAG IDCODE for the device.
 *
 * Parameters:
 *
 * jtag_id_code - Pointer to receive the 32-bit IDCODE.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_get_jtag_idcode(uint32_t *jtag_id_code);

/* Function: run_fcs_get_device_identity
 *
 * Retrieves the device identity string/structure from the SDM.
 *
 * Parameters:
 *
 * dev_identity - Destination buffer for the identity data.
 * dev_id_size  - Pointer to receive the size of the data.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_get_device_identity(char *dev_identity, uint32_t *dev_id_size);

/* Function: run_fcs_aes_cryption
 *
 * Performs generalized AES-based encryption/decryption.
 *
 * Parameters:
 *
 * uuid        - The session UUID.
 * key_id      - Key ID.
 * context_id  - Context identifier.
 * crypt_mode  - Encryption vs Decryption.
 * block_mode  - Mode (ECB, CBC, GCM).
 * iv_src      - IV Source (External, Internal, or Base).
 * iv_data     - Initialization Vector.
 * tag_size    - Authentication tag size (for GCM).
 * aad_size    - AAD length.
 * aad_data    - AAD data.
 * tag_data    - Authentication tag data.
 * input_data  - Source data.
 * input_size  - Size of source data.
 * output_data - Destination buffer.
 * output_size - Size of destination buffer.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_aes_cryption(char *uuid, uint32_t key_id, uint32_t context_id,
        uint32_t crypt_mode, uint32_t block_mode, uint32_t iv_src,
        char *iv_data, uint32_t tag_size, uint32_t aad_size, char *aad_data,
        char *tag_data, char *input_data, uint32_t input_size,
        char *output_data, uint32_t output_size);

/* Function: run_fcs_ecdsa_hash_sign
 *
 * Generates an ECDSA signature for a pre-calculated hash.
 *
 * Parameters:
 *
 * uuid             - The session UUID.
 * context_id       - Context identifier.
 * key_id           - Key ID.
 * ecc_algo         - ECC Algorithm (NIST/Brainpool).
 * hash_data        - The hash payload.
 * hash_data_size   - Size of hash data.
 * signed_data      - Destination buffer for signature.
 * signed_data_size - Pointer to receive signature size.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_ecdsa_hash_sign(char *uuid, uint32_t context_id, uint32_t key_id,
        uint32_t ecc_algo, char *hash_data, uint32_t hash_data_size,
        char *signed_data, uint32_t *signed_data_size);

/* Function: run_fcs_ecdsa_hash_verify
 *
 * Verifies an ECDSA signature against a provided hash.
 *
 * Parameters:
 *
 * uuid           - The session UUID.
 * context_id     - Context identifier.
 * key_id         - Key ID.
 * ecc_algo       - ECC Algorithm.
 * hash_data      - The hash payload.
 * hash_data_size - Size of hash data.
 * sig_data       - The signature buffer.
 * sig_size       - Size of the signature.
 * pub_key_data   - Public key material.
 * pub_key_size   - Size of the public key.
 * dest_data      - Verification result buffer.
 * dest_size      - Size of result buffer.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_ecdsa_hash_verify(char *uuid, uint32_t context_id, uint32_t key_id,
        uint32_t ecc_algo, char *hash_data, uint32_t hash_data_size,
        char *sig_data, uint32_t sig_size, char *pub_key_data, uint32_t
        pub_key_size, char *dest_data, uint32_t *dest_size);

/* Function: run_fcs_ecdsa_sha2_data_sign
 *
 * Performs a complete ECDSA signature sequence (hashing + signing) on raw data.
 *
 * Parameters:
 *
 * uuid       - The session UUID.
 * context_id - Context identifier.
 * key_id     - Key ID.
 * ecc_algo   - ECC Algorithm.
 * src_data   - Source data to hash and sign.
 * src_size   - Size of source data.
 * dest_data  - Destination buffer for signature.
 * dest_size  - Pointer to receive signature size.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_ecdsa_sha2_data_sign(char *uuid, uint32_t context_id, uint32_t
        key_id, uint32_t ecc_algo, char *src_data, uint32_t src_size,
        char *dest_data, uint32_t *dest_size);

/* Function: run_fcs_ecdsa_sha2_data_sign_verify
 *
 * Performs a complete ECDSA signature verification sequence (hashing + verifying) 
 * on raw data.
 *
 * Parameters:
 *
 * uuid         - The session UUID.
 * context_id   - Context identifier.
 * key_id       - Key ID.
 * ecc_algo     - ECC Algorithm.
 * src_data     - Source data.
 * src_size     - Size of source data.
 * signed_data  - Signature buffer to verify.
 * sig_size     - Size of the signature.
 * pub_key_data - Public key material.
 * pub_key_size - Size of the public key.
 * dest_data    - Verification result buffer.
 * dest_size    - Size of result buffer.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_ecdsa_sha2_data_sign_verify(char *uuid, uint32_t context_id,
        uint32_t key_id, uint32_t ecc_algo, char *src_data, uint32_t src_size,
        char *signed_data, uint32_t sig_size, char *pub_key_data, uint32_t
        pub_key_size, char *dest_data, uint32_t *dest_size);

/* Function: run_fcs_ecdsa_get_public_key
 *
 * Extracts the public key for an existing ECC key pair managed by the FCS.
 *
 * Parameters:
 *
 * uuid         - The session UUID.
 * context_id   - Context identifier.
 * key_id       - Key ID.
 * ecc_algo     - ECC Algorithm.
 * pub_key_data - Destination buffer for public key.
 * pub_key_size - Pointer to receive the public key size.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_ecdsa_get_public_key(char *uuid, uint32_t context_id, uint32_t
        key_id, uint32_t ecc_algo, char *pub_key_data, uint32_t *pub_key_size);

/* Function: run_fcs_ecdh_request
 *
 * Initiates an ECDH key exchange operation to derive a shared secret.
 *
 * Parameters:
 *
 * uuid            - The session UUID.
 * key_id          - The local ECC key ID.
 * context_id      - Context identifier.
 * ecc_algo        - ECC Algorithm.
 * pub_key_data    - Remote party's public key.
 * pub_key_size    - Size of the remote public key.
 * shared_sec_data - Destination buffer for shared secret.
 * shared_sec_size - Pointer to receive size of shared secret.
 *
 * Returns:
 *
 * 0 on success.
 */
int run_fcs_ecdh_request(char *uuid, uint32_t key_id, uint32_t context_id,
        uint32_t ecc_algo, char *pub_key_data, uint32_t pub_key_size,
        char *shared_sec_data, uint32_t *shared_sec_size);

#endif /* _SOCFPGA_FCS_H_ */