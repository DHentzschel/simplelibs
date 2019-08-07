#ifndef ALIST_H
#define ALIST_H

#include <list>
#include <vector>

#include "avector.h"

template<class T>
class AVector;

/**
 * This class extends the std::list class by auxiliary functions.
 *
 * @author Daniel Hentzschel on 12.05.2019.
 */
template<class T>
class AList : public std::list<T> {
public:
	using std::list<T>::list;
	/**
	 * Initializes the list with default values.
	 */
	AList();

	/**
	 * Initializes the list with the size passed as parameter.
	 *
	 * @param size the size of the list
	 */
	explicit AList(int64 size);

	/**
	 * Copies the values from another list to the current instance.
	 *
	 * @param list the list to copy from
	 */
	AList(const AList& list);

	/**
	 * Moves the values from another list to the current instance.
	 *
	 * @param list the list to move from
	 */
	AList(AList&& list);

	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the reference to the item on the ith position
	 */
	virtual T& at(int i);

	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the const reference to the item on the ith position
	 */
	virtual const T& at(int i) const;

	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the reference to the item on the ith position
	 */
	virtual T& operator[](int i);

	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the const reference to the item on the ith position
	 */
	virtual const T& operator[](int i) const;

	/**
	 * Appends the value passed as parameter to the list.
	 *
	 * @param value the value to append
	 */
	virtual void append(const T& value);

	/**
	 * Appends the value passed as parameter to the list.
	 *
	 * @param value the value to append
	 */
	virtual void append(T&& value);

	/**
	 * Prepends the value passed as parameter to the list.
	 *
	 * @param value the value to prepend
	 */
	virtual void prepend(const T& value);

	/**
	 * Prepends the value passed as parameter to the list.
	 *
	 * @param value the value to prepend
	 */
	virtual void prepend(T&& value);

	/**
	 * Returns whether the list contains the item passed as parameter.
	 *
	 * @param value the value to check
	 * @return whether the list contains the item passed as parameter
	 */
	virtual bool contains(const T& value) const;

	/**
	 * Returns whether the first item in the list is equal to the value passed as parameter.
	 *
	 * @param value the value to check
	 * @return whether the list starts with the item passed as parameter
	 */
	virtual bool startsWith(const T& value) const;

	/**
	 * Returns whether the last item in the list is equal to the value passed as parameter.
	 *
	 * @param value the value to check
	 * @return whether the list ends with the item passed as parameter
	 */
	virtual bool endsWith(const T& value) const;

	/**
	 * Returns whether the list is empty.
	 *
	 * @return whether the list empty
	 */
	virtual bool isEmpty() const;

	/**
	 * Counts the occurrences of the item passed as parameter in list and returns the count.
	 *
	 * @param value the value to count
	 * @return the count of occurrences of the item passed as parameter
	 */
	virtual int64 count(const T& value) const;

	/**
	 * Returns the first index of the item in list which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the first occurrence
	 */
	virtual int64 firstIndexOf(const T& value) const;

	/**
	 * Returns the first index of the item in list which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the first occurrence
	 */
	virtual int64 indexOf(const T& value) const;

	/**
	 * Returns the last index of the item in list which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the last occurrence
	 */
	virtual int64 lastIndexOf(const T& value) const;

	/**
	 * Replaces the item on the position index passed as parameter by the value passed.
	 *
	 * @param i the position to replace
	 * @param value the value to set
	 */
	virtual void replace(int64 i, const T& value);

	/**
	 * Removes all duplicate items.
	 */
	virtual void removeDuplicates();

	/**
	 * Removes an item on a specific position.
	 *
	 * @param i the position of the item to remove
	 */
	virtual void removeAt(int i);

	/**
	 * Removes the first item in list.
	 */
	virtual void removeFirst();

	/**
	 * Removes the first item in list.
	 * Just here for STL compatibility.
	 */
	virtual void pop_front();

	/**
	 * Removes the last item in list.
	 */
	virtual void removeLast();

	/**
	 * Removes the first occurrence in list which is equal to the item passed as parameter.
	 *
	 * @param value the value to remove
	 */
	virtual void removeFirst(const T& value);

	/**
	 * Removes all occurrences in list which are equal to the item passed as parameter.
	 *
	 * @param value the value to remove
	 */
	virtual void removeAll(const T& value);

	/**
	 * Returns a list that contains length characters of this list, starting at the specified position index.
	 * Returns an empty list if the position index exceeds the length of the list.
	 * If n is -1 (default), the function returns all items that are available from the specified position.
	 *
	 * @param position the position to start from
	 * @param length the length to use
	 * @return a list copying the values of the current instance starting from position
	 */
	virtual AList<T> mid(int position, int length = -1) const;

	/**
	 * Exchanges the value on position from with the value on position to.
	 *
	 * @param from the first exchangable
	 * @param to the second exchangable
	 */
	virtual void move(int from, int to);

	/**
	 * Returns the current instance as a new std::vector.
	 *
	 * @return the current instance as new std::vector
	 */
	virtual std::vector<T> toStdVector() const;

	/**
	 * Returns the current instance as a new AVector.
	 *
	 * @return the current instance as new AVector
	 */
	virtual AVector<T> toVector() const;

	/**
	 * Returns the reference of the first item in list.
	 *
	 * @return the reference of the first item in list
	 */
	virtual T& first();

	/**
	 * Returns the const reference of the first item in list.
	 *
	 * @return the const reference of the first item in list
	 */
	virtual const T& first() const;

	/**
	 * Returns the reference of the last item in list.
	 *
	 * @return the reference of the last item in list
	 */
	virtual T& last();

	/**
	 * Returns the const reference of the last item in list.
	 *
	 * @return the const reference of the last item in list
	 */
	virtual const T& last() const;

	/**
	 * Removes the item at the specified position and returns it.
	 *
	 * @param i the position to take at
	 * @return the item to take
	 */
	virtual T takeAt(int64 i);

	/**
	 * Removes the first item and returns it.
	 *
	 * @return the first item
	 */
	virtual T takeFirst();

	/**
	 * Removes the last item and returns it.
	 *
	 * @return the lats item
	 */
	virtual T takeLast();

private:
	using list_t = std::list<T>;
};

template<class T>
AList<T>::AList() :
	list_t()
{}

template<class T>
inline AList<T>::AList(int64 size) :
	list_t(size)
{}

template<class T>
AList<T>::AList(const AList& vector) :
	list_t(vector)
{}

template<class T>
AList<T>::AList(AList&& vector) :
	list_t(vector)
{}

template<class T>
T& AList<T>::at(int i)
{
	auto it = list_t::begin();
	for (int64 c = 0; it != list_t::end(); ++c, ++it) {
		if (c == i) {
			return *it;
		}
	}
	return T();
}

template<class T>
const T& AList<T>::at(int i) const
{
	auto it = list_t::begin();
	for (int64 c = 0; it != list_t::end() && c != -1; ++c, ++it) {
		if (c == i) {
			return *it;
		}
	}
	throw std::out_of_range("AList::at(): out of range");
}

template<class T>
inline T& AList<T>::operator[](int i)
{
	return at(i);
}

template<class T>
inline const T& AList<T>::operator[](int i) const
{
	return at(i);
}

template<class T>
void AList<T>::append(const T& value)
{
	list_t::push_back(value);
}

template<class T>
void AList<T>::append(T&& value)
{
	list_t::push_back(value);
}

template<class T>
void AList<T>::prepend(const T& value)
{
	list_t::insert(list_t::begin(), value);
}

template<class T>
void AList<T>::prepend(T&& value)
{
	list_t::insert(list_t::begin(), value);
}

template<class T>
inline bool AList<T>::contains(const T& value) const
{
	for (auto it = list_t::begin(); it != list_t::end(); ++it) {
		if (*it == value) {
			return true;
		}
	}
	return false;
}

template<class T>
bool AList<T>::startsWith(const T& value) const
{
	return *list_t::begin() == value;
}

template<class T>
bool AList<T>::endsWith(const T& value) const
{
	return *(list_t::end() - 1) == value;
}

template<class T>
bool AList<T>::isEmpty() const
{
	return list_t::empty();
}

template<class T>
int64 AList<T>::count(const T& value) const
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
int64 AList<T>::firstIndexOf(const T& value) const
{
	return indexOf(value);
}

template<class T>
int64 AList<T>::indexOf(const T& value) const
{
	auto it = list_t::begin();
	for (int64 i = 0; it != list_t::end(); ++i, ++it) {
		if (*it == value) {
			return i;
		}
	}
	return -1;
}

template<class T>
int64 AList<T>::lastIndexOf(const T& value) const
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
void AList<T>::replace(const int64 i, const T& value)
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
void AList<T>::removeAt(int i)
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
void AList<T>::removeFirst(const T& value)
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
void AList<T>::removeAll(const T& value)
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
AList<T> AList<T>::mid(int position, int length) const
{
	AList<T> result;
	int64 limit = length == -1 ? list_t::size() : position + length;
	auto it = list_t::begin();
	for (auto i = position; i < limit; ++i) {
		result.append(*it);
	}
	return result;
}

template<class T>
void AList<T>::move(int from, int to)
{
	T copyFrom = at(from);
	T copyTo = at(to);
	replace(from, copyTo);
	replace(to, copyFrom);
}

template<class T>
std::vector<T> AList<T>::toStdVector() const
{
	std::vector<T> result(list_t::size());
	result.assign(list_t::begin(), list_t::end());
	return result;
}

template<class T>
AVector<T> AList<T>::toVector() const
{
	AVector<T> result(list_t::size());
	result.assign(list_t::begin(), list_t::end());
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
T AList<T>::takeAt(int64 i)
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
