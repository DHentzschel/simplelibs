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

private:
    using stringvector_t = std::vector<AString>;

    using size_type = stringvector_t::size_type;
};

#endif // STRINGVECTOR_H
