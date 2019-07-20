#ifndef AVECTOR_H
#define AVECTOR_H

#include <list>
#include <vector>

#include <algorithm>
#include <stdexcept>
#include <unordered_set>

#include "functions.h"
#include "types.h"
#include "alist.h"

template<class T>
class AList;
/**
 * This class extends the std::vector class by auxiliary functions.
 *
 * @author Daniel Hentzschel on 13.05.2019.
 */
template<class T>
class AVector : public std::vector<T> {
public:
	using std::vector<T>::vector;

	/**
	 * Appends the specified item to the current vector.
	 *
	 * @param value the value to append
	 */
	void append(const T& value);

	/**
	 * Appends the specified item to the current vector.
	 *
	 * @param value the value to append
	 */
	void append(T&& value);

	/**
	 * Prepends the specified item to the current vector.
	 *
	 * @param value the value to prepend
	 */
	void prepend(const T& value);

	/**
	 * Prepends the specified item to the current vector.
	 *
	 * @param value the value to prepend
	 */
	void prepend(T&& value);

	/**
	 * Prepends the specified item to the current vector.
	 * Just for STL compatibility.
	 *
	 * @param value the value to prepend
	 */
	void push_front(const T& value);

	/**
	 * Prepends the specified item to the current vector.
	 * Just for STL compatibility.
	 *
	 * @param value the value to prepend
	 */
	void push_front(T&& value);

	/**
	 * Returns whether the vector starts with the specified item.
	 *
	 * @param value the value to compare
	 * @return whether the vector starts with the specified item
	 */
	bool startsWith(const T& value) const;

	/**
	 * Returns whether the vector ends with the specified item.
	 *
	 * @param value the value to compare
	 * @return whether the vector ends with the specified item
	 */
	bool endsWith(const T& value) const;

	/**
	 * Returns whether the vector is empty.
	 */
	bool isEmpty() const;

	/**
	 * Returns whether the vector contains the specified item.
	 *
	 * @param value the value to find
	 * @return whether the vector contains the specified item
	 */
	bool contains(const T& value) const;

	/**
	 * Counts the occurrences of the specified item in the vector
	 * and returns the value.
	 *
	 * @param value the value to count
	 * @return the count of the specified item in the vector
	 */
	int64 count(const T& value) const;

	/**
	 * Returns the first index of the item in vector which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the first occurrence
	 */
	int64 firstIndexOf(const T& value) const;

	/**
	 * Returns the first index of the item in vector which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the first occurrence
	 */
	int64 indexOf(const T& value) const;

	/**
	 * Returns the last index of the first item in vector which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the last occurrence
	 */
	int64 lastIndexOf(const T& value) const;

	/**
	 * Replaces the item at the ith index by the specified value.
	 *
	 * @param i the index to replace
	 * @param value the value to set
	 */
	void replace(int64 i, const T& value);

	/**
	 * Removes the item at the ith index.
	 *
	 * @param i the index to remove
	 */
	void removeAt(int64 i);

	/**
	 * Removes the first item in vector.
	 */
	void removeFirst();

	/**
	 * Removes the first item in vector.
	 */
	void pop_front();

	/**
	 * Removes any duplicate items in vector.
	 */
	void removeDuplicates();

	/**
	 * Removes the last item in vector.
	 */
	void removeLast();

	/**
	 * Removes the first item in vector equals to the specified item.
	 *
	 * @param value the value to remove
	 */
	void removeFirst(const T& value);

	/**
	 * Removes all items in vector equals to the specified item.
	 *
	 * @param value the value to remove
	 */
	void removeAll(const T& value);

	/**
	 * Returns a vector that contains length characters of this vector, starting at the specified position index.
	 * Returns an empty vector if the position index exceeds the length of the list.
	 * If n is -1 (default), the function returns all items that are available from the specified position.
	 *
	 * @param position the position to start from
	 * @param length the length to use
	 * @return a vector copying the values of the current instance starting from position
	 */
	AVector<T> mid(int64 position, int64 length = -1) const;

	/**
	 * Exchanges the item at index "from" with the item at index "to".
	 *
	 * @param from the first item
	 * @param to the second item
	 */
	void move(int64 from, int64 to);

	/**
	 * Returns the reference to the first item in vector.
	 *
	 * @return the reference to the first item
	 */
	T& first();

	/**
	 * Returns the const reference to the first item in vector.
	 *
	 * @return the const reference to the first item
	 */
	const T& first() const;

	/**
	 * Returns the reference to the last item in vector.
	 *
	 * @return the reference to the last item
	 */
	T& last();

	/**
	 * Returns the const reference to the last item in vector.
	 *
	 * @return the const reference to the last item
	 */
	const T& last() const;

	/**
	 * Removes the item at the specified index and returns it.
	 *
	 * @param i the index to take
	 * @return the item at index i
	 */
	T takeAt(int64 i);

	/**
	 * Removes the first item and returns it.
	 *
	 * @return the first item
	 */
	T takeFirst();

	/**
	 * Removes the last item and returns it.
	 *
	 * @return the last item
	 */
	T takeLast();

	/**
	 * Converts the current vector to std::list and returns it.
	 *
	 * @return the std::list converted from the current vector
	 */
	std::list<T> toStdList() const;

	/**
	 * Converts the current vector to AList and returns it.
	 *
	 * @return the AList converted from the current vector
	 */
	AList<T> toList() const;
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
inline bool AVector<T>::contains(const T& value) const
{
	for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
		if (*it == value) {
			return true;
		}
	}
	return false;
}

template<class T>
int64 AVector<T>::count(const T& value) const
{
	auto result = 0;
	for (auto it = vector_t::begin(); it != vector_t::end(); ++it) {
		if (*it == value) {
			++result;
		}
	}
	return result;
}

template<class T>
int64 AVector<T>::firstIndexOf(const T& value) const
{
	return indexOf(value);
}

template<class T>
int64 AVector<T>::indexOf(const T& value) const
{
	for (auto i = 0; i != vector_t::size(); ++i) {
		if (vector_t::operator[](i) == value) {
			return i;
		}
	}
	return -1;
}

template<class T>
int64 AVector<T>::lastIndexOf(const T& value) const
{
	for (auto i = vector_t::size() - 1; i >= 0 && i < vector_t::size(); --i) {
		if (vector_t::operator[](i) == value) {
			return i;
		}
	}
	return static_cast<int64>(-1);
}

template<class T>
void AVector<T>::replace(int64 i, const T& value)
{
	vector_t::data()[i] = value;
}

template<class T>
void AVector<T>::removeAt(int64 i)
{
	vector_t::erase(vector_t::begin() + i);
}

template<class T>
void AVector<T>::removeFirst()
{
	if (vector_t::size() > 0) {
		vector_t::erase(vector_t::begin());
	}
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
void AVector<T>::removeFirst(const T& value)
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
void AVector<T>::removeAll(const T& value)
{
	for (auto i = vector_t::size() - 1; i >= 0 && i < vector_t::size(); --i) {
		if (vector_t::operator[](i) == value) {
			removeAt(i);
		}
	}
}

template<class T>
AVector<T> AVector<T>::mid(int64 position, int64 length) const
{
	if (vector_t::size() == 0) {
		return AVector<T>();
	}

	AVector<T> result;
	int64 limit = length == -1 ? vector_t::size() : position + length;
	const auto itEnd = vector_t::begin() + limit;
	for (auto it = vector_t::begin() + position; it != itEnd; ++it) {
		result.append(*it);
	}
	return result;
}

template<class T>
void AVector<T>::move(int64 from, int64 to)
{
	if (vector_t::size() >= 0) {
		T copyFrom = vector_t::operator[](from);
		T copyTo = vector_t::operator[](to);
		replace(from, copyTo);
		replace(to, copyFrom);
	}
}

template<class T>
T& AVector<T>::first()
{
	if (vector_t::size() > 0) {
		return vector_t::operator[](0);
	}
	throw std::out_of_range("AVector::first(): size is 0");
}

template<class T>
const T& AVector<T>::first() const
{
	if (vector_t::size() > 0) {
		return vector_t::operator[](0);
	}
	throw std::out_of_range("AVector::first(): size is 0");
}

template<class T>
T& AVector<T>::last()
{
	if (vector_t::size() > 0) {
		return *(vector_t::end() - 1);
	}
	throw std::out_of_range("AVector::last(): size is 0");
}

template<class T>
const T& AVector<T>::last() const
{
	if (vector_t::size() > 0) {
		return *(vector_t::end() - 1);
	}
	throw std::out_of_range("AVector::last(): size is 0");
}

template<class T>
T AVector<T>::takeAt(int64 i)
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
std::list<T> AVector<T>::toStdList() const
{
	std::list<T> result;
	result.assign(vector_t::begin(), vector_t::end());
	return result;
}

template<class T>
inline AList<T> AVector<T>::toList() const
{
	AList<T> result;
	result.assign(vector_t::begin(), vector_t::end());
	return result;
}

#endif   // AVECTOR_H
