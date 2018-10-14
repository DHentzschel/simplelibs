#ifndef ALIST_H
#define ALIST_H

#define STLIST std::list<T>
#define IT_BEGIN STLIST::begin()
#define IT_END STLIST::end()

#include <list>
#include <vector>

#include "functions.h"

template<class T>
class AList : public STLIST {
public:
    using std::list<T>::list;
    AList();

    explicit AList(unsigned long long size);

    AList(const AList& vector);

    ~AList();

    T& at(int i);

    const T& at(int i) const;

    void append(const T& value);

    void append(T&& value);

    void prepend(const T& value);

    void prepend(T&& value);

    bool contains(const T& value) const;

    bool startsWith(const T& value) const;

    bool endsWith(const T& value) const;

    bool isEmpty() const;

    int count(const T& value) const;

    int firstIndexOf(const T& value) const;

    int indexOf(const T& value) const;

    int lastIndexOf(const T& value) const;

    void replace(int i, const T& value);

    void removeDuplicates();

    void removeAt(int i);

    void removeFirst();

    void pop_front();

    void removeLast();

    void removeFirst(const T& value);

    void removeAll(const T& value);

    AList<T> mid(int pos, int length = -1) const;

    void move(int from, int to);

    std::vector<T> toVector() const;

    T& first();

    const T& first() const;

    T& last();

    const T& last() const;

    T takeAt(int i);

    T takeFirst();

    T takeLast();
};

template<class T>
AList<T>::AList() : STLIST()
{}

template<class T>
AList<T>::AList(const unsigned long long size) : STLIST(size)
{}

template<class T>
AList<T>::AList(const AList& vector) : STLIST(vector)
{}

template<class T>
AList<T>::~AList()
{}

template<class T>
T& AList<T>::at(const int i)
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
const T& AList<T>::at(const int i) const
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
int AList<T>::count(const T& value) const
{
    auto it = IT_BEGIN;
    auto c = 0;
    for (; it != IT_END; ++it) {
        if (*it == value) {
            ++c;
        }
    }
    return c;
}

template<class T>
int AList<T>::firstIndexOf(const T& value) const
{
    return indexOf(value);
}

template<class T>
int AList<T>::indexOf(const T& value) const
{
    auto it = IT_BEGIN;
    for (auto i = 0; it != IT_END; ++i, ++it) {
        if (*it == value) {
            return i;
        }
    }
    return -1;
}

template<class T>
int AList<T>::lastIndexOf(const T& value) const
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
void AList<T>::replace(const int i, const T& value)
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
    STLIST::sort();
    STLIST::unique();
}

template<class T>
void AList<T>::removeAt(const int i)
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
AList<T> AList<T>::mid(const int pos, const int length) const
{
    AList<T> result;
    int limit = length == -1 ? STLIST::size() : pos + length;
    auto it = IT_BEGIN;
    for (auto i = pos; i < limit; ++i) {
        result.append(*it);
    }
    return result;
}

template<class T>
void AList<T>::move(const int from, const int to)
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
T AList<T>::takeAt(int i)
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
