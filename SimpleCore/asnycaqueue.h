#ifndef ASYNCAQUEUE_H
#define ASYNCAQUEUE_H

#include "aqueue.h"
#include "alist.h"
#include "simplecore.h"
#include <mutex>

/**
 * This class implements the IQueue interface thread safely and an advanced queue data structure.
 *
 * @author Daniel Hentzschel on 07.08.2019.
 */
template <class T>
class AsyncAQueue : protected AQueue<T> {
public:
	/**
	  * Enqueues the specified element asyncronously to the queue.
	  *
	  * @param right the enqueuable template class
	  */
	void enqueue(const T& value) override;

	/**
	  * Dequeues the first element asyncronously from the queue and returns it.
	  *
	  * @param right the enqueuable template class
	  * @return the first element
	  */
	T dequeue() override;

	/**
	  * Determines asyncronously whether the queue is empty and returns the result.
	  *
	  * @return whether the size of the list behind is empty
	  */
	bool isEmpty() override;

private:
	std::mutex mutex_;

};

template<class T>
inline void AsyncAQueue<T>::enqueue(const T& value)
{
	mutex_.lock();
	AList<T>::append(value);
	mutex_.unlock();
}

template<class T>
inline T AsyncAQueue<T>::dequeue()
{
	mutex_.lock();
	auto result = AList<T>::takeFirst();
	mutex_.unlock();
	return result;
}

template<class T>
inline bool AsyncAQueue<T>::isEmpty()
{
	mutex_.lock();
	auto result = AQueue<T>::isEmpty();
	mutex_.unlock();
	return result;
}

#endif // !ASYNCAQUEUE_H
