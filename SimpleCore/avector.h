#ifndef AVECTOR_H
#define AVECTOR_H

#define STVECTOR std::vector<T>
#define IT_BEGIN STVECTOR::begin()
#define IT_END STVECTOR::end()

#include <list>
#include <vector>

#include <algorithm>
#include <unordered_set>

#include "functions.h"
#include "types.h"

template<class T>
class AVector : public STVECTOR {
public:
    using std::vector<T>::vector;

    void append(const T& value);

    void append(T&& value);

    void prepend(const T& value);

    void prepend(T&& value);

    void push_front(const T& value);

    void push_front(T&& value);

    bool startsWith(const T& value) const;

    bool endsWith(const T& value) const;

    bool isEmpty() const;

    bool contains(const T& value) const;

    uint64 count(const T& value) const;

    uint64 firstIndexOf(const T& value) const;

    uint64 indexOf(const T& value) const;

    uint64 lastIndexOf(const T& value) const;

    void replace(uint64 i, const T& value);

    void removeAt(uint64 i);

    void removeFirst();

    void pop_front();

    void removeDuplicates();

    void removeLast();

    void removeFirst(const T& value);

    void removeAll(const T& value);

    AVector<T> mid(uint64 pos, uint64 length = -1) const;

    void move(uint64 from, uint64 to);

    T& first();

    const T& first() const;

    T& last();

    const T& last() const;

    T takeAt(uint64 i);

    T takeFirst();

    T takeLast();

    std::list<T> toList() const;

    AVector<byte> toByteArray();

    static AVector<byte> toByteArray(const char* string, uint64 length);

};

template<class T>
using Vector = AVector<T>;

template<class T>
void AVector<T>::append(const T& value)
{
    STVECTOR::push_back(value);
}

template<class T>
void AVector<T>::append(T&& value)
{
    STVECTOR::push_back(value);
}

template<class T>
void AVector<T>::prepend(const T& value)
{
    STVECTOR::insert(IT_BEGIN, value);
}

template<class T>
void AVector<T>::prepend(T&& value)
{
    STVECTOR::insert(IT_BEGIN, value);
}

template<class T>
void AVector<T>::push_front(const T& value)
{
    prepend(value);
}

template<class T>
void AVector<T>::push_front(T&& value)
{
    prepend(value);
}

template<class T>
bool AVector<T>::startsWith(const T& value) const
{
    return *IT_BEGIN == value;
}

template<class T>
bool AVector<T>::endsWith(const T& value) const
{
    return *(IT_END - 1) == value;
}

template<class T>
bool AVector<T>::isEmpty() const
{
    return STVECTOR::empty();
}

template<class T>
inline bool AVector<T>::contains(const T& value) const
{
    for (auto it = IT_BEGIN; it != IT_END; ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

template<class T>
uint64 AVector<T>::count(const T& value) const
{
    uint64 result = 0;
    for (auto it = IT_BEGIN; it != IT_END; ++it) {
        if (*it == value) {
            ++result;
        }
    }
    return result;
}

template<class T>
uint64 AVector<T>::firstIndexOf(const T& value) const
{
    return indexOf(value);
}

template<class T>
uint64 AVector<T>::indexOf(const T& value) const
{
    for (auto i = 0; i != STVECTOR::size(); ++i) {
        if (operator[](i) == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
uint64 AVector<T>::lastIndexOf(const T& value) const
{
    for (auto i = STVECTOR::size() - 1; i >= 0 && i < STVECTOR::size(); --i) {
        if (operator[](i) == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
void AVector<T>::replace(uint64 i, const T& value)
{
    STVECTOR::data()[i] = value;
}

template<class T>
void AVector<T>::removeAt(uint64 i)
{
    STVECTOR::erase(IT_BEGIN + i);
}

template<class T>
void AVector<T>::removeFirst()
{
    if (STVECTOR::size() == 0) {
        return;
    }
    STVECTOR::erase(IT_BEGIN);
}

template<class T>
void AVector<T>::pop_front()
{
    removeFirst();
}

template<class T>
void AVector<T>::removeDuplicates()
{
    AVector<T> result;
    result.reserve(STVECTOR::size());

    for (auto it = IT_BEGIN; it != IT_END; ++it) {
        if (!result.contains(*it)) {
            result.append(*it);
        }
    }
    *this = result;
}

template<class T>
void AVector<T>::removeLast()
{
    STVECTOR::pop_back();
}

template<class T>
void AVector<T>::removeFirst(const T& value)
{
    if (STVECTOR::size() > 0) {
        for (auto it = IT_BEGIN; it != IT_END; ++it) {
            if (*it == value) {
                STVECTOR::erase(it);
                return;
            }
        }
    }
}

template<class T>
void AVector<T>::removeAll(const T& value)
{
    for (auto i = STVECTOR::size() - 1; i >= 0 && i < STVECTOR::size(); --i) {
        if (operator[](i) == value) {
            removeAt(i);
        }
    }
}

template<class T>
AVector<T> AVector<T>::mid(const uint64 pos, const uint64 length) const
{
    if (STVECTOR::size() == 0) {
        return AVector<T>();
    }

    AVector<T> result;
    uint64 limit = length == -1 ? STVECTOR::size() : pos + length;
    for (auto i = pos; i < limit; ++i) {
        result.append(STVECTOR::at(i));
    }
    return result;
}

template<class T>
void AVector<T>::move(const uint64 from, const uint64 to)
{
    if (STVECTOR::size() == 0) {
        return;
    }
    T copyFrom = STVECTOR::at(from);
    T copyTo = STVECTOR::at(to);
    replace(from, copyTo);
    replace(to, copyFrom);
}

template<class T>
T& AVector<T>::first()
{
    return STVECTOR::at(0);
}

template<class T>
const T& AVector<T>::first() const
{
    return STVECTOR::at(0);
}

template<class T>
T& AVector<T>::last()
{
    return *(STVECTOR::end() - 1);
}

template<class T>
const T& AVector<T>::last() const
{
    return *(STVECTOR::end() - 1);
}

template<class T>
T AVector<T>::takeAt(uint64 i)
{
    T result = STVECTOR::at(i);
    removeAt(i);
    return result;
}

template<class T>
T AVector<T>::takeFirst()
{
    T result = *IT_BEGIN;
    removeFirst();
    return result;
}

template<class T>
T AVector<T>::takeLast()
{
    T result = *(IT_END - 1);
    removeLast();
    return result;
}

template<class T>
std::list<T> AVector<T>::toList() const
{
    std::list<T> result;
    for (auto it = IT_BEGIN; it != IT_END; ++it) {
        result.push_back(*it);
    }
    return result;
}

template<class T>
inline AVector<byte> AVector<T>::toByteArray()
{
    AVector<byte> result;
    result.assign(IT_BEGIN, IT_END);
    return result;
}

template <class T>
AVector<byte> AVector<T>::toByteArray(const char* string, const uint64 length)
{
    AVector<byte> result;
    for (uint64 i = 0; i < length - 1; ++i) {
        result.append(string[i]);
    }
    return result;
}

#undef STVECTOR
#undef IT_BEGIN
#undef IT_END

#endif   // AVECTOR_H
