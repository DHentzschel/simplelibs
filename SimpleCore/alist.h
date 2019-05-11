#ifndef ALIST_H
#define ALIST_H

#include <list>
#include <vector>

#include "functions.h"
#include "types.h"

template<class T>
class AList : public list_t {
public:
    using std::list<T>::list;

    AList();

    explicit AList(uint64 size);

    AList(const AList& list);

    AList(AList&& list);

    ~AList();

    T& at(uint64 i);

    const T& at(uint64 i) const;

    T& operator[](uint64 i);

    const T& operator[](uint64 i) const;

    void append(const T& value);

    void append(T&& value);

    void prepend(const T& value);

    void prepend(T&& value);

    bool contains(const T& value) const;

    bool startsWith(const T& value) const;

    bool endsWith(const T& value) const;

    bool isEmpty() const;

    uint64 count(const T& value) const;

    uint64 firstIndexOf(const T& value) const;

    uint64 indexOf(const T& value) const;

    uint64 lastIndexOf(const T& value) const;

    void replace(uint64 i, const T& value);

    void removeDuplicates();

    void removeAt(uint64 i);

    void removeFirst();

    void pop_front();

    void removeLast();

    void removeFirst(const T& value);

    void removeAll(const T& value);

    AList<T> mid(uint64 pos, uint64 length = -1) const;

    void move(uint64 from, uint64 to);

    std::vector<T> toVector() const;

    T& first();

    const T& first() const;

    T& last();

    const T& last() const;

    T takeAt(uint64 i);

    T takeFirst();

    T takeLast();

private:
    using list_t = std::list<T>;
};

template<class T>
AList<T>::AList() : list_t()
{}

template<class T>
AList<T>::AList(uint64 size) : list_t(size)
{}

template<class T>
AList<T>::AList(const AList& vector) : list_t(vector)
{}

template<class T>
AList<T>::AList(AList&& vector) : AList<T>(vector)
{}

template<class T>
AList<T>::~AList()
{}

template<class T>
T& AList<T>::at(const uint64 i)
{
    auto it = list_t::begin();
    for (auto c = 0; it != list_t::end(); ++c, ++it) {
        if (c == i) {
            return *it;
        }
    }
    return T();
}

template<class T>
const T& AList<T>::at(const uint64 i) const
{
    auto it = list_t::begin();
    for (uint64 c = 0; it != list_t::end() && c != STATIC_CAST(uint64, -1); ++c, ++it) {
        if (c == i) {
            return *it;
        }
    }
    throw std::out_of_range("Invalid index i (" + TO_STRING(i) + ")");
    return T();
}

template<class T>
inline T& AList<T>::operator[](uint64 i)
{
    return at(i);
}

template<class T>
inline const T& AList<T>::operator[](uint64 i) const
{
    return at(i);
}

template<class T>
void AList<T>::append(const T & value)
{
    list_t::push_back(value);
}

template<class T>
void AList<T>::append(T && value)
{
    list_t::push_back(value);
}

template<class T>
void AList<T>::prepend(const T & value)
{
    list_t::insert(list_t::begin(), value);
}

template<class T>
void AList<T>::prepend(T && value)
{
    list_t::insert(list_t::begin(), value);
}

template<class T>
inline bool AList<T>::contains(const T & value) const
{
    for (auto it = list_t::begin(); it != list_t::end(); ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

template<class T>
bool AList<T>::startsWith(const T & value) const
{
    return *list_t::begin() == value;
}

template<class T>
bool AList<T>::endsWith(const T & value) const
{
    return *(list_t::end() - 1) == value;
}

template<class T>
bool AList<T>::isEmpty() const
{
    return list_t::empty();
}

template<class T>
uint64 AList<T>::count(const T & value) const
{
    auto c = 0;
    for (auto it = list_t::begin(); it != list_t::end(); ++it) {
        if (*it == value) {
            ++c;
        }
    }
    return c;
}

template<class T>
uint64 AList<T>::firstIndexOf(const T & value) const
{
    return indexOf(value);
}

template<class T>
uint64 AList<T>::indexOf(const T & value) const
{
    auto it = list_t::begin();
    for (uint64 i = 0; it != list_t::end(); ++i, ++it) {
        if (*it == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
uint64 AList<T>::lastIndexOf(const T & value) const
{
    auto it = list_t::end();
    for (auto i = 0; it != list_t::begin(); ++i, --it) {
        if (*it == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
void AList<T>::replace(const uint64 i, const T & value)
{
    auto it = list_t::begin();
    for (auto c = 0; it != list_t::end(); ++c, ++it) {
        if (c == i) {
            *it = value;
        }
    }
}

template<class T>
void AList<T>::removeDuplicates()
{
    /* list_t::sort();
     list_t::unique();*/
}

template<class T>
void AList<T>::removeAt(const uint64 i)
{
    auto it = list_t::begin();
    for (auto c = 0; it != list_t::end(); ++c, ++it) {
        if (c == i) {
            list_t::erase(it);
            return;
        }
    }
}

template<class T>
void AList<T>::removeFirst()
{
    list_t::erase(list_t::begin());
}

template<class T>
void AList<T>::pop_front()
{
    removeFirst();
}

template<class T>
void AList<T>::removeLast()
{
    list_t::pop_back();
}

template<class T>
void AList<T>::removeFirst(const T & value)
{
    auto it = list_t::begin();
    for (; it != list_t::end(); ++it) {
        if (*it == value) {
            list_t::erase(it);
            return;
        }
    }
}

template<class T>
void AList<T>::removeAll(const T & value)
{
    auto it = list_t::begin();
    for (; it != list_t::end(); ++it) {
        if (*it == value) {
            it = list_t::erase(it);
            if (it == list_t::end()) {
                break;
            }
        }
    }
}

template<class T>
AList<T> AList<T>::mid(const uint64 pos, const uint64 length) const
{
    AList<T> result;
    uint64 limit = length == -1 ? list_t::size() : pos + length;
    auto it = list_t::begin();
    for (auto i = pos; i < limit; ++i) {
        result.append(*it);
    }
    return result;
}

template<class T>
void AList<T>::move(const uint64 from, const uint64 to)
{
    T copyFrom = at(from);
    T copyTo = at(to);
    replace(from, copyTo);
    replace(to, copyFrom);
}

template<class T>
std::vector<T> AList<T>::toVector() const
{
    std::vector<T> result(list_t::size());
    auto it = list_t::begin();
    for (auto i = 0; it != list_t::end(); ++i, ++it) {
        result[i] = *it;
    }
    return result;
}

template<class T>
T& AList<T>::first()
{
    return *list_t::begin();
}

template<class T>
const T& AList<T>::first() const
{
    return *list_t::begin();
}

template<class T>
T& AList<T>::last()
{
    auto it = list_t::end();
    return *--it;
}

template<class T>
const T& AList<T>::last() const
{
    auto it = list_t::end();
    return *--it;
}

template<class T>
T AList<T>::takeAt(uint64 i)
{
    T result = at(i);
    removeAt(i);
    return result;
}

template<class T>
T AList<T>::takeFirst()
{
    T result = *list_t::begin();
    removeFirst();
    return result;
}

template<class T>
T AList<T>::takeLast()
{
    T result = *list_t::end();
    removeLast();
    return result;
}

#endif   // ALIST_H
