#ifndef ASYNCLIST_H
#define ASYNCLIST_H

#include "alist.h"
#include <mutex>
#include "avector.h"

template <class T>
class AsyncAList : protected AList<T> {
public:
	/**
	 * Initializes the list with default values.
	 */
	AsyncAList() override;

	/**
	 * Initializes the list with the size passed as parameter.
	 *
	 * @param size the size of the list
	 */
	explicit AsyncAList(int64 size) override;

	/**
	 * Copies the values from another list to the current instance.
	 *
	 * @param list the list to copy from
	 */
	AsyncAList(const AsyncAList& list) override;

	/**
	 * Moves the values from another list to the current instance.
	 *
	 * @param list the list to move from
	 */
	AsyncAList(AsyncAList&& list) override;
	
	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the const reference to the item on the ith position
	 */
	const T& at(int i) const override;

	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the reference to the item on the ith position
	 */
	T& operator[](int i) override;

	/**
	 * Returns the item on the ith position in the list.
	 *
	 * @param i the position index of the item
	 * @return the const reference to the item on the ith position
	 */
	const T& operator[](int i) const override;

	/**
	 * Appends the value passed as parameter to the list.
	 *
	 * @param value the value to append
	 */
	void append(const T& value) override;

	/**
	 * Appends the value passed as parameter to the list.
	 *
	 * @param value the value to append
	 */
	void append(T&& value) override;

	/**
	 * Prepends the value passed as parameter to the list.
	 *
	 * @param value the value to prepend
	 */
	void prepend(const T& value) override;

	/**
	 * Prepends the value passed as parameter to the list.
	 *
	 * @param value the value to prepend
	 */
	void prepend(T&& value) override;

	/**
	 * Returns whether the list contains the item passed as parameter.
	 *
	 * @param value the value to check
	 * @return whether the list contains the item passed as parameter
	 */
	bool contains(const T& value) const override;

	/**
	 * Returns whether the first item in the list is equal to the value passed as parameter.
	 *
	 * @param value the value to check
	 * @return whether the list starts with the item passed as parameter
	 */
	bool startsWith(const T& value) const override;

	/**
	 * Returns whether the last item in the list is equal to the value passed as parameter.
	 *
	 * @param value the value to check
	 * @return whether the list ends with the item passed as parameter
	 */
	bool endsWith(const T& value) const override;

	/**
	 * Returns whether the list is empty.
	 *
	 * @return whether the list empty
	 */
	bool isEmpty() const override;

	/**
	 * Counts the occurrences of the item passed as parameter in list and returns the count.
	 *
	 * @param value the value to count
	 * @return the count of occurrences of the item passed as parameter
	 */
	int64 count(const T& value) const override;

	/**
	 * Returns the first index of the item in list which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the first occurrence
	 */
	int64 firstIndexOf(const T& value) const override;

	/**
	 * Returns the first index of the item in list which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the first occurrence
	 */
	int64 indexOf(const T& value) const override;

	/**
	 * Returns the last index of the item in list which is equal to the specified item.
	 * Returns -1 when there is no such item.
	 *
	 * @param value the value to find
	 * @return the index of the last occurrence
	 */
	int64 lastIndexOf(const T& value) const override;

	/**
	 * Replaces the item on the position index passed as parameter by the value passed.
	 *
	 * @param i the position to replace
	 * @param value the value to set
	 */
	void replace(int64 i, const T& value) override;

	/**
	 * Removes all duplicate items.
	 */
	void removeDuplicates() override;

	/**
	 * Removes an item on a specific position.
	 *
	 * @param i the position of the item to remove
	 */
	void removeAt(int i) override;

	/**
	 * Removes the first item in list.
	 */
	void removeFirst() override;

	/**
	 * Removes the first item in list.
	 * Just here for STL compatibility.
	 */
	void pop_front() override;

	/**
	 * Removes the last item in list.
	 */
	void removeLast() override;

	/**
	 * Removes the first occurrence in list which is equal to the item passed as parameter.
	 *
	 * @param value the value to remove
	 */
	void removeFirst(const T& value) override;

	/**
	 * Removes all occurrences in list which are equal to the item passed as parameter.
	 *
	 * @param value the value to remove
	 */
	void removeAll(const T& value) override;

	/**
	 * Returns a list that contains length characters of this list, starting at the specified position index.
	 * Returns an empty list if the position index exceeds the length of the list.
	 * If n is -1 (default), the function returns all items that are available from the specified position.
	 *
	 * @param position the position to start from
	 * @param length the length to use
	 * @return a list copying the values of the current instance starting from position
	 */
	AList<T> mid(int position, int length = -1) const override;

	/**
	 * Exchanges the value on position from with the value on position to.
	 *
	 * @param from the first exchangable
	 * @param to the second exchangable
	 */
	void move(int from, int to) override;

	/**
	 * Returns the current instance as a new std::vector.
	 *
	 * @return the current instance as new std::vector
	 */
	std::vector<T> toStdVector() const override;

	/**
	 * Returns the current instance as a new AVector.
	 *
	 * @return the current instance as new AVector
	 */
	AVector<T> toVector() const override;

	/**
	 * Returns the reference of the first item in list.
	 *
	 * @return the reference of the first item in list
	 */
	T& first() override;

	/**
	 * Returns the const reference of the first item in list.
	 *
	 * @return the const reference of the first item in list
	 */
	const T& first() const override;

	/**
	 * Returns the reference of the last item in list.
	 *
	 * @return the reference of the last item in list
	 */
	T& last() override;

	/**
	 * Returns the const reference of the last item in list.
	 *
	 * @return the const reference of the last item in list
	 */
	const T& last() const override;

	/**
	 * Removes the item at the specified position and returns it.
	 *
	 * @param i the position to take at
	 * @return the item to take
	 */
	T takeAt(int64 i) override;

	/**
	 * Removes the first item and returns it.
	 *
	 * @return the first item
	 */
	T takeFirst() override;

	/**
	 * Removes the last item and returns it.
	 *
	 * @return the lats item
	 */
	T takeLast() override;

private:
	using list_t = std::list<T>;

	std::mutex mutex_;
};

template<class T>
AsyncAList<T>::AsyncAList() :
	AList<T>()
{
	mutex_.unlock();
}

template<class T>
AsyncAList<T>::AsyncAList(int64 size) :
	AList<T>(size)
{
	mutex_.unlock();
}

template<class T>
AsyncAList<T>::AsyncAList(const AsyncAList& vector) :
	AList<T>(vector)
{
	mutex_.unlock();
}

template<class T>
AsyncAList<T>::AsyncAList(AsyncAList&& vector) :
	AList<T>(vector)
{
	mutex_.unlock();
}

template<class T>
const T& AsyncAList<T>::at(int i) const
{
	mutex_.lock();
	auto result = AList<T>::at(i);
	mutex_.unlock();
	return result;
}

template<class T>
inline T& AsyncAList<T>::operator[](int i)
{
	return at(i);
}

template<class T>
inline const T& AsyncAList<T>::operator[](int i) const
{
	return at(i);
}

template<class T>
void AsyncAList<T>::append(const T& value)
{
	mutex_.lock();
	AList<T>::append(value);
	mutex_.lock();
}

template<class T>
void AsyncAList<T>::append(T&& value)
{
	mutex_.lock();
	AList<T>::append(value);
	mutex_.lock();
}

template<class T>
void AsyncAList<T>::prepend(const T& value)
{
	mutex_.lock();
	AList<T>::prepend(value);
	mutex_.unlock();
}

template<class T>
void AsyncAList<T>::prepend(T&& value)
{
	mutex_.lock();
	AList<T>::prepend(value);
	mutex_.unlock();
}

template<class T>
inline bool AsyncAList<T>::contains(const T& value) const
{
	mutex_.lock();
	auto result = AList<T>::contains(value);
	mutex_.unlock();
	return result;
}

template<class T>
bool AsyncAList<T>::startsWith(const T& value) const
{
	mutex_.lock();
	auto result = AList<T>::startsWith(value);
	mutex_.unlock();
	return result;
}

template<class T>
bool AsyncAList<T>::endsWith(const T& value) const
{
	mutex_.lock();
	auto result = AList<T>::endsWith(value);
	mutex_.unlock();
	return result;
}

template<class T>
bool AsyncAList<T>::isEmpty() const
{
	mutex_.lock();
	auto result = AList<T>::isEmpty();
	mutex_.unlock();
	return result;
}

template<class T>
int64 AsyncAList<T>::count(const T& value) const
{
	mutex_.lock();
	auto result = AList<T>::count(value);
	mutex_.unlock();
	return result;
}

template<class T>
int64 AsyncAList<T>::firstIndexOf(const T& value) const
{
	return indexOf(value);
}

template<class T>
int64 AsyncAList<T>::indexOf(const T& value) const
{
	mutex_.lock();
	auto result = AList<T>::indexOf(value);
	mutex_.unlock();
	return result;
}

template<class T>
int64 AsyncAList<T>::lastIndexOf(const T& value) const
{
	mutex_.lock();
	auto result = AList<T>::lastIndexOf(value);
	mutex_.unlock();
	return result;
}

template<class T>
void AsyncAList<T>::replace(const int64 i, const T& value)
{
	mutex_.lock();
	AList<T>::replace(i, value);
	mutex_.unlock();
}

template<class T>
void AsyncAList<T>::removeDuplicates()
{
	/* list_t::sort();
	 list_t::unique();*/
}

template<class T>
void AsyncAList<T>::removeAt(int i)
{
	mutex_.lock();
	AList<T>::removeAt(i);
	mutex_.unlock();
}

template<class T>
void AsyncAList<T>::removeFirst()
{
	mutex_.lock();
	AList<T>::removeFirst();
	mutex_.unlock();
}

template<class T>
void AsyncAList<T>::pop_front()
{
	removeFirst();
}

template<class T>
void AsyncAList<T>::removeLast()
{
	mutex_.lock();
	AList<T>::removeLast();
	mutex_.unlock();
}

template<class T>
void AsyncAList<T>::removeFirst(const T& value)
{
	mutex_.lock();
	AList<T>::removeFirst(value);
	mutex_.unlock();
}

template<class T>
void AsyncAList<T>::removeAll(const T& value)
{
	mutex_.lock();
	AList<T>::removeAll(value);
	mutex_.unlock();
}

template<class T>
AList<T> AsyncAList<T>::mid(int position, int length) const
{
	mutex_.lock();
	auto result = AList<T>::mid(position, length);
	mutex_.unlock();
	return result;
}

template<class T>
void AsyncAList<T>::move(int from, int to)
{
	mutex_.lock();
	AList<T>::move(from, to);
	mutex_.unlock();
}

template<class T>
std::vector<T> AsyncAList<T>::toStdVector() const
{
	mutex_.lock();
	auto result = AList<T>::toStdVector();
	mutex_.unlock();
	return result;
}

template<class T>
AVector<T> AsyncAList<T>::toVector() const
{
	mutex_.lock();
	auto result = AList<T>::toVector();
	mutex_.unlock();
	return result;
}

template<class T>
T& AsyncAList<T>::first()
{
	mutex_.lock();
	auto result = AList<T>::first();
	mutex_.unlock();
	return result;
}

template<class T>
const T& AsyncAList<T>::first() const
{
	mutex_.lock();
	auto result = AList<T>::first();
	mutex_.unlock();
	return result;
}

template<class T>
T& AsyncAList<T>::last()
{
	mutex_.lock();
	auto result = AList<T>::last();
	mutex_.unlock();
	return result;
}

template<class T>
const T& AsyncAList<T>::last() const
{
	mutex_.lock();
	auto result = AList<T>::last();
	mutex_.unlock();
	return result;
}

template<class T>
T AsyncAList<T>::takeAt(int64 i)
{
	mutex_.lock();
	auto result = AList<T>::takeAt();
	mutex_.unlock();
	return result;
}

template<class T>
T AsyncAList<T>::takeFirst()
{
	mutex_.lock();
	auto result = AList<T>::takeFirst();
	mutex_.unlock();
	return result;
}

template<class T>
T AsyncAList<T>::takeLast()
{
	mutex_.lock();
	auto result = AList<T>::takeLast();
	mutex_.unlock();
	return result;
}

#endif // !ASYNCLIST_H
