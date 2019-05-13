#include "stringvector.h"

StringVector::StringVector(const AVector<AString>& stringVector) :
	AVector<AString>(stringVector)
{}

void StringVector::removeEmpties()
{
	erase(std::remove(begin(), end(), ""), end());
}

void StringVector::removeWhitespaces()
{
	for (size_type i = 0; i < size() && i < static_cast<size_type>(-1); ++i) {
		if (at(i).isOnlyWhitespaces()) {
			removeAt(i);
		}
	}
}

void StringVector::removeEscapes()
{
	for (size_type i = 0; i < size() && i < static_cast<size_type>(-1); ++i) {
		if (at(i).isOnlyEscapes()) {
			removeAt(i);
		}
	}
}
