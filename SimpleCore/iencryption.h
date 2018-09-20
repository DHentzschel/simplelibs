#ifndef IENCRYPTION_H
#define IENCRYPTION_H

#include "astring.h"
#include "avector.h"

class IEncryption {
protected:
    virtual AVector<byte> encrypt(const AVector<byte>& clearBuffer) = 0;

    virtual AString encryptToText(const AVector<byte>& clearBuffer) = 0;

    virtual AVector<byte> decrypt(const AVector<byte>& cipherBuffer) = 0;

    virtual AString decryptToText(const AVector<byte>& cipherBuffer) = 0;

};

#endif // IENCRYPTION_H
