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
    for (uint64 i = 0; i < size() && i < STATIC_CAST(uint64, -1); ++i) {
        if (at(i).isOnlyWhitespaces()) {
            removeAt(static_cast<int>(i));
        }
    }
}

void StringVector::removeEscapes()
{
    for (uint64 i = 0; i < size() && i < STATIC_CAST(uint64, -1); ++i) {
        if (at(i).isOnlyEscapes()) {
            removeAt(static_cast<int>(i));
        }
    }
}
