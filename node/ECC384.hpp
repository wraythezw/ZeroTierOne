/*
 * ZeroTier One - Network Virtualization Everywhere
 * Copyright (C) 2011-2019  ZeroTier, Inc.  https://www.zerotier.com/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * --
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial closed-source software that incorporates or links
 * directly against ZeroTier software without disclosing the source code
 * of your own application.
 */

// This is glue code to ease the use of the NIST P-384 elliptic curve.

// Note that some of the code inside ECC384.cpp is third party code and
// is under the BSD 2-clause license rather than ZeroTier's license.

#ifndef ZT_ECC384_HPP
#define ZT_ECC384_HPP

#include "Constants.hpp"

/**
 * Size of a (point compressed) P-384 public key
 */
#define ZT_ECC384_PUBLIC_KEY_SIZE 49

/**
 * Size of a P-384 private key
 */
#define ZT_ECC384_PRIVATE_KEY_SIZE 48

/**
 * Size of the hash that should be signed using P-384
 */
#define ZT_ECC384_SIGNATURE_HASH_SIZE 48

/**
 * Size of a P-384 signature
 */
#define ZT_ECC384_SIGNATURE_SIZE 96

/**
 * Size of shared secret generated by ECDH key agreement
 */
#define ZT_ECC384_SHARED_SECRET_SIZE 48

namespace ZeroTier {

/**
 * Generate a NIST P-384 key pair
 * 
 * @param pub Buffer to receive point compressed public key
 * @param priv Buffer to receiver private key
 */
void ECC384GenerateKey(uint8_t pub[ZT_ECC384_PUBLIC_KEY_SIZE],uint8_t priv[ZT_ECC384_PRIVATE_KEY_SIZE]);

/**
 * Sign a hash with a NIST P-384 private key
 * 
 * The hash must be 48 bytes in size and is typically the first 48 bytes
 * of a SHA512 hash or something similar. Extra bytes of course are ignored.
 * 
 * @param priv Private key
 * @param hash 48-byte hash
 * @param sig Buffer to receive signature
 */
void ECC384ECDSASign(const uint8_t priv[ZT_ECC384_PRIVATE_KEY_SIZE],const uint8_t hash[ZT_ECC384_SIGNATURE_HASH_SIZE],uint8_t sig[ZT_ECC384_SIGNATURE_SIZE]);

/**
 * Verify a signature
 * 
 * @param pub Public key
 * @param hash 48-byte hash (usually first 48 bytes of SHA512(msg))
 * @param sig Signature to check
 * @return True if signature is valid
 */
bool ECC384ECDSAVerify(const uint8_t pub[ZT_ECC384_PUBLIC_KEY_SIZE],const uint8_t hash[ZT_ECC384_SIGNATURE_HASH_SIZE],const uint8_t sig[ZT_ECC384_SIGNATURE_SIZE]);

/**
 * Perform ECDH key agreement
 * 
 * The secret generated here is the raw 48-byte result of ECDH.
 * It's typically hashed prior to use.
 * 
 * @param theirPub Remote public key
 * @param ourPriv Local private key
 * @param secret Buffer to receive 48-byte secret
 */
bool ECC384ECDH(const uint8_t theirPub[ZT_ECC384_PUBLIC_KEY_SIZE],const uint8_t ourPriv[ZT_ECC384_PRIVATE_KEY_SIZE],uint8_t secret[ZT_ECC384_SHARED_SECRET_SIZE]);

} // namespace ZeroTier

#endif
