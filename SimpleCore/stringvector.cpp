#include "stringvector.h"

StringVector::StringVector(const StringVector& stringVector) :
	AVector<AString>(stringVector)
{
}

StringVector::StringVector(const AVector<AString>& stringVector) :
	AVector<AString>(stringVector)
{}

void StringVector::removeEmpties()
{
	erase(std::remove(begin(), end(), ""), end());
}

void StringVector::removeWhitespaces()
{
	for (auto it = begin(); it < end(); ++it) {
		if ((*it).isOnlyWhitespaces()) {
			erase(it);
		}
	}
}

void StringVector::removeEscapes()
{
	for (auto it = begin(); it < end(); ++it) {
		if ((*it).isOnlyEscapes()) {
			erase(it);
		}
	}
}
