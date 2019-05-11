#include "stringvector.h"

StringVector::StringVector(const AVector<AString>& right) :
    AVector<AString>(right)
{}

void StringVector::removeEmpties()
{
    erase(std::remove(begin(), end(), ""), end());
}

void StringVector::removeWhitespaces()
{
    for (size_type i = 0; i < size() && i < STATIC_CAST(size_type, -1); ++i) {
        if (stringvector_t::operator[](i).isOnlyWhitespaces()) {
            removeAt(i);
        }
    }
}

void StringVector::removeEscapes()
{
    for (size_type i = 0; i < size() && i < STATIC_CAST(size_type, -1); ++i) {
        if (stringvector_t::operator[](i).isOnlyEscapes()) {
            removeAt(i);
        }
    }
}
