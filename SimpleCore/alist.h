#ifndef ALIST_H
#define ALIST_H

#define STLIST std::list<T>
#define IT_BEGIN STLIST::begin()
#define IT_END STLIST::end()

#include <list>
#include <vector>

#include "functions.h"
#include "types.h"

template<class T>
class AList : public STLIST {
public:
    using std::list<T>::list;

    AList();

    explicit AList(uint64 size);

    AList(const AList& vector);

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
};

template<class T>
AList<T>::AList() : STLIST()
{}

template<class T>
AList<T>::AList(uint64 size) : STLIST(size)
{}

template<class T>
AList<T>::AList(const AList& vector) : STLIST(vector)
{}

template<class T>
AList<T>::~AList()
{}

template<class T>
T& AList<T>::at(const uint64 i)
{
    auto it = IT_BEGIN;
    for (auto c = 0; it != IT_END; ++c, ++it) {
        if (c == i) {
            return *it;
        }
    }
    return T();
}

template<class T>
const T& AList<T>::at(const uint64 i) const
{
    auto it = IT_BEGIN;
    for (long double c = 0; it != IT_END; ++c, ++it) {
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
inline const T & AList<T>::operator[](uint64 i) const
{
    return at(i);
}

template<class T>
void AList<T>::append(const T& value)
{
    STLIST::push_back(value);
}

template<class T>
void AList<T>::append(T&& value)
{
    STLIST::push_back(value);
}

template<class T>
void AList<T>::prepend(const T& value)
{
    STLIST::insert(IT_BEGIN, value);
}

template<class T>
void AList<T>::prepend(T&& value)
{
    STLIST::insert(IT_BEGIN, value);
}

template<class T>
inline bool AList<T>::contains(const T& value) const
{
    for (auto it = IT_BEGIN; it != IT_END; ++it) {
        if (*it == value) {
            return true;
        }
    }
    return false;
}

template<class T>
bool AList<T>::startsWith(const T& value) const
{
    return *IT_BEGIN == value;
}

template<class T>
bool AList<T>::endsWith(const T& value) const
{
    return *(IT_END - 1) == value;
}

template<class T>
bool AList<T>::isEmpty() const
{
    return STLIST::empty();
}

template<class T>
uint64 AList<T>::count(const T& value) const
{
    auto c = 0;
    for (auto it = IT_BEGIN; it != IT_END; ++it) {
        if (*it == value) {
            ++c;
        }
    }
    return c;
}

template<class T>
uint64 AList<T>::firstIndexOf(const T& value) const
{
    return indexOf(value);
}

template<class T>
uint64 AList<T>::indexOf(const T& value) const
{
    auto it = IT_BEGIN;
    for (uint64 i = 0; it != IT_END; ++i, ++it) {
        if (*it == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
uint64 AList<T>::lastIndexOf(const T& value) const
{
    auto it = IT_END;
    for (auto i = 0; it != IT_BEGIN; ++i, --it) {
        if (*it == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
void AList<T>::replace(const uint64 i, const T& value)
{
    auto it = IT_BEGIN;
    for (auto c = 0; it != IT_END; ++c, ++it) {
        if (c == i) {
            *it = value;
        }
    }
}

template<class T>
void AList<T>::removeDuplicates()
{
    /* STLIST::sort();
     STLIST::unique();*/
}

template<class T>
void AList<T>::removeAt(const uint64 i)
{
    auto it = IT_BEGIN;
    for (auto c = 0; it != IT_END; ++c, ++it) {
        if (c == i) {
            STLIST::erase(it);
            return;
        }
    }
}

template<class T>
void AList<T>::removeFirst()
{
    STLIST::erase(IT_BEGIN);
}

template<class T>
void AList<T>::pop_front()
{
    removeFirst();
}

template<class T>
void AList<T>::removeLast()
{
    STLIST::pop_back();
}

template<class T>
void AList<T>::removeFirst(const T& value)
{
    auto it = IT_BEGIN;
    for (; it != IT_END; ++it) {
        if (*it == value) {
            STLIST::erase(it);
            return;
        }
    }
}

template<class T>
void AList<T>::removeAll(const T& value)
{
    auto it = IT_BEGIN;
    for (; it != IT_END; ++it) {
        if (*it == value) {
            it = STLIST::erase(it);
            if (it == IT_END) {
                break;
            }
        }
    }
}

template<class T>
AList<T> AList<T>::mid(const uint64 pos, const uint64 length) const
{
    List<T> result;
    uint64 limit = length == -1 ? STLIST::size() : pos + length;
    auto it = IT_BEGIN;
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
    std::vector<T> result(STLIST::size());
    auto it = IT_BEGIN;
    for (auto i = 0; it != IT_END; ++i, ++it) {
        result[i] = *it;
    }
    return result;
}

template<class T>
T& AList<T>::first()
{
    return *IT_BEGIN;
}

template<class T>
const T& AList<T>::first() const
{
    return *IT_BEGIN;
}

template<class T>
T& AList<T>::last()
{
    auto it = IT_END;
    return *--it;
}

template<class T>
const T& AList<T>::last() const
{
    auto it = IT_END;
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
    T result = *IT_BEGIN;
    removeFirst();
    return result;
}

template<class T>
T AList<T>::takeLast()
{
    T result = *IT_END;
    removeLast();
    return result;
}

#undef STLIST
#undef IT_BEGIN
#undef IT_END

#endif   // ALIST_H
