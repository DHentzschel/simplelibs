#ifndef AVECTOR_H
#define AVECTOR_H

#define STVECTOR std::vector<T>

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

    int count(const T& value) const;

    int firstIndexOf(const T& value) const;

    int indexOf(const T& value) const;

    int lastIndexOf(const T& value) const;

    void replace(int i, const T& value);

    void removeAt(int i);

    void removeFirst();

    void pop_front();

    void removeDuplicates();

    void removeLast();

    void removeFirst(const T& value);

    void removeAll(const T& value);

    AVector<T> mid(int pos, int length = -1) const;

    void move(int from, int to);

    T& first();

    const T& first() const;

    T& last();

    const T& last() const;

    T takeAt(int i);

    T takeFirst();

    T takeLast();

    std::list<T> toList() const;

    AVector<char> toByteArray();

    static AVector<byte> toByteArray(const char* string, uint length);
};

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
    STVECTOR::insert(STVECTOR::begin(), value);
}

template<class T>
void AVector<T>::prepend(T&& value)
{
    STVECTOR::insert(STVECTOR::begin(), value);
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
    return *STVECTOR::begin() == value;
}

template<class T>
bool AVector<T>::endsWith(const T& value) const
{
    return *(STVECTOR::end() - 1) == value;
}

template<class T>
bool AVector<T>::isEmpty() const
{
    return STVECTOR::empty();
}

template<class T>
inline bool AVector<T>::contains(const T& value) const
{
    for (int i = 0; i < STVECTOR::size(); ++i) {
        if (STVECTOR::at(i) == value) {
            return true;
        }
    }
    return false;
}

template<class T>
int AVector<T>::count(const T& value) const
{
    auto c = 0;
    for (int i = STVECTOR::size() - 1; i >= 0; --i) {
        if (STVECTOR::at(i) == value) {
            ++c;
        }
    }
    return c;
}

template<class T>
int AVector<T>::firstIndexOf(const T& value) const
{
    return indexOf(value);
}

template<class T>
int AVector<T>::indexOf(const T& value) const
{
    for (auto i = 0; i < STVECTOR::size(); ++i) {
        if (value == STVECTOR::at(i)) {
            return i;
        }
    }
    return -1;
}

template<class T>
int AVector<T>::lastIndexOf(const T& value) const
{
    for (int i = STVECTOR::size() - 1; i >= 0; --i) {
        if (value == STVECTOR::at(i)) {
            return i;
        }
    }
    return -1;
}

template<class T>
void AVector<T>::replace(int i, const T& value)
{
    STVECTOR::data()[i] = value;
}

template<class T>
void AVector<T>::removeAt(int i)
{
    STVECTOR::erase(STVECTOR::begin() + i);
}

template<class T>
void AVector<T>::removeFirst()
{
    if (STVECTOR::size() == 0) {
        return;
    }
    STVECTOR::erase(STVECTOR::begin());
}

template<class T>
void AVector<T>::pop_front()
{
    removeFirst();
}

template<class T>
void AVector<T>::removeDuplicates()
{
    std::unordered_set<T> set;
    for (T& t : *this) {
        set.insert(t);
    }
    STVECTOR::assign(set.begin(), set.end());
    std::sort(STVECTOR::begin(), STVECTOR::end());
}

template<class T>
void AVector<T>::removeLast()
{
    STVECTOR::pop_back();
}

template<class T>
void AVector<T>::removeFirst(const T& value)
{
    if (STVECTOR::size() == 0) {
        return;
    }
    auto it = STVECTOR::begin();
    for (; it != STVECTOR::end(); ++it) {
        if (*it == value) {
            STVECTOR::erase(it);
            return;
        }
    }
}

template<class T>
void AVector<T>::removeAll(const T& value)
{
    if (STVECTOR::size() == 0) {
        return;
    }
    auto it = STVECTOR::begin();
    for (; it != STVECTOR::end(); ++it) {
        if (*it == value) {
            it = STVECTOR::erase(it);
            if (it == STVECTOR::end()) {
                break;
            }
        }
    }
}

template<class T>
AVector<T> AVector<T>::mid(const int pos, const int length) const
{
    if (STVECTOR::size() == 0) {
        return;
    }
    AVector<T> result;
    int limit = length == -1 ? STVECTOR::size() : pos + length;
    for (auto i = pos; i < limit; ++i) {
        result.append(STVECTOR::at(i));
    }
    return result;
}

template<class T>
void AVector<T>::move(int from, int to)
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
T AVector<T>::takeAt(int i)
{
    T result = STVECTOR::at(i);
    removeAt(i);
    return result;
}

template<class T>
T AVector<T>::takeFirst()
{
    T result = *STVECTOR::begin();
    removeFirst();
    return result;
}

template<class T>
T AVector<T>::takeLast()
{
    T result = *(STVECTOR::end() - 1);
    removeLast();
    return result;
}

template<class T>
std::list<T> AVector<T>::toList() const
{
    std::list<T> result;
    for (auto it = STVECTOR::begin(); it != STVECTOR::end(); ++it) {
        result.append(*it);
    }
    return result;
}

template<class T>
inline AVector<char> AVector<T>::toByteArray()
{
    AVector<char> result;
    result.assign(STVECTOR::begin(), STVECTOR::end());
    return result;
}

template <class T>
AVector<byte> AVector<T>::toByteArray(const char* string, const uint length)
{
    AVector<byte> result;
    for (uint i = 0; i < length - 1; ++i) {
        result.append(string[i]);
    }
    return result;
}

#undef STVECTOR

#endif   // AVECTOR_H
