#ifndef AVECTOR_H
#define AVECTOR_H

#include <list>
#include <vector>

#include <algorithm>
#include <unordered_set>

#include "functions.h"
#include "types.h"

template<class T>
class AVector : public std::vector<T> {
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

private:
    using vector_t = std::vector<T>;

};

template<class T>
using Vector = AVector<T>;

template<class T>
void AVector<T>::append(const T& value)
{
    vector_t::push_back(value);
}

template<class T>
void AVector<T>::append(T&& value)
{
    vector_t::push_back(value);
}

template<class T>
void AVector<T>::prepend(const T& value)
{
    vector_t::insert(vector_t::begin(), value);
}

template<class T>
void AVector<T>::prepend(T&& value)
{
    vector_t::insert(vector_t::begin(), value);
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
    return *vector_t::begin() == value;
}

template<class T>
bool AVector<T>::endsWith(const T& value) const
{
    return *(vector_t::end() - 1) == value;
}

template<class T>
bool AVector<T>::isEmpty() const
{
    return vector_t::empty();
}

template<class T>
inline bool AVector<T>::contains(const T & value) const
{
    for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

template<class T>
uint64 AVector<T>::count(const T & value) const
{
    uint64 result = 0;
    for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
        if (*it == value) {
            ++result;
        }
    }
    return result;
}

template<class T>
uint64 AVector<T>::firstIndexOf(const T & value) const
{
    return indexOf(value);
}

template<class T>
uint64 AVector<T>::indexOf(const T & value) const
{
    for (auto i = 0; i != vector_t::size(); ++i) {
        if (vector_t::operator[](i) == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
uint64 AVector<T>::lastIndexOf(const T & value) const
{
    for (auto i = vector_t::size() - 1; i >= 0 && i < vector_t::size(); --i) {
        if (vector_t::operator[](i) == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
void AVector<T>::replace(uint64 i, const T & value)
{
    vector_t::data()[i] = value;
}

template<class T>
void AVector<T>::removeAt(uint64 i)
{
    vector_t::erase(vector_t::begin() + i);
}

template<class T>
void AVector<T>::removeFirst()
{
    if (vector_t::size() == 0) {
        return;
    }
    vector_t::erase(vector_t::begin());
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
    result.reserve(vector_t::size());

    for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
        if (!result.contains(*it)) {
            result.append(*it);
        }
    }
    *this = result;
}

template<class T>
void AVector<T>::removeLast()
{
    vector_t::pop_back();
}

template<class T>
void AVector<T>::removeFirst(const T & value)
{
    if (vector_t::size() > 0) {
        for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
            if (*it == value) {
                vector_t::erase(it);
                return;
            }
        }
    }
}

template<class T>
void AVector<T>::removeAll(const T & value)
{
    for (auto i = vector_t::size() - 1; i >= 0 && i < vector_t::size(); --i) {
        if (vector_t::operator[](i) == value) {
            removeAt(i);
        }
    }
}

template<class T>
AVector<T> AVector<T>::mid(const uint64 pos, const uint64 length) const
{
    if (vector_t::size() == 0) {
        return AVector<T>();
    }

    AVector<T> result;
    uint64 limit = length == -1 ? vector_t::size() : pos + length;
    for (auto i = pos; i < limit; ++i) {
        result.append(vector_t::operator[](i));
    }
    return result;
}

template<class T>
void AVector<T>::move(const uint64 from, const uint64 to)
{
    if (vector_t::size() == 0) {
        return;
    }
    T copyFrom = vector_t::operator[](from);
    T copyTo = vector_t::operator[](to);
    replace(from, copyTo);
    replace(to, copyFrom);
}

template<class T>
T& AVector<T>::first()
{
    return vector_t::operator[](0);
}

template<class T>
const T& AVector<T>::first() const
{
    return vector_t::operator[](0);
}

template<class T>
T& AVector<T>::last()
{
    return *(vector_t::end() - 1);
}

template<class T>
const T& AVector<T>::last() const
{
    return *(vector_t::end() - 1);
}

template<class T>
T AVector<T>::takeAt(uint64 i)
{
    T result = vector_t::operator[](i);
    removeAt(i);
    return result;
}

template<class T>
T AVector<T>::takeFirst()
{
    T result = *vector_t::begin();
    removeFirst();
    return result;
}

template<class T>
T AVector<T>::takeLast()
{
    T result = *(vector_t::end() - 1);
    removeLast();
    return result;
}

template<class T>
std::list<T> AVector<T>::toList() const
{
    std::list<T> result;
    for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

template<class T>
inline AVector<byte> AVector<T>::toByteArray()
{
    AVector<byte> result;
    result.assign(vector_t::begin(), vector_t::end());
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

#endif   // AVECTOR_H
