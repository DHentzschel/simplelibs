#ifndef STRINGVECTOR_H
#define STRINGVECTOR_H

#include "astring.h"
#include "avector.h"

class StringVector : public AVector<AString> {
public:
    StringVector() = default;

    StringVector(const AVector<AString>& right);

    void removeEmpties();

    void removeWhitespaces();

    void removeEscapes();
};

#endif // STRINGVECTOR_H
