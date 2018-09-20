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
    for (size_t i = size() - 1; i >= 0; --i) {
        if (at(i).isOnlyWhitespaces()) {
            removeAt(static_cast<int>(i));
        }
    }
}

void StringVector::removeEscapes()
{
    for (size_t i = size() - 1; i >= 0; --i) {
        if (at(i).isOnlyEscapes()) {
            removeAt(static_cast<int>(i));
        }
    }
}
