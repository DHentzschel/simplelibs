#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "astring.h"
#include "avector.h"

/**
 * Provides an abstract class for a cryptography.
 *
 * @author Daniel Hentzschel on 11.05.2019.
 */
class SIMPLECORE_API IEncryption {
protected:
	/**
	 * Encrypts the plain byte vector and returns the encrypted byte vector.
	 *
	 * @param clearBuffer the clear byte vector
	 */
	virtual AVector<byte> encrypt(const AVector<byte>& clearBuffer) = 0;

	/**
	 * Encrypts the plain byte vector and returns the encrypted string.
	 *
	 * @param clearBuffer the clear byte vector
	 */
	virtual AString encryptToText(const AVector<byte>& clearBuffer) = 0;

	/**
	 * Decrypts the encrypted byte vector and returns the decrypted byte vector.
	 *
	 * @param cipherBuffer the encrypted byte vector
	 */
	virtual AVector<byte> decrypt(const AVector<byte>& cipherBuffer) = 0;

	/**
	 * Decrypts the encrypted byte vector and returns the decrypted string.
	 *
	 * @param cipherBuffer the encrypted byte vector
	 */
	virtual AString decryptToText(const AVector<byte>& cipherBuffer) = 0;
};

#endif // !ENCRYPTION_H
