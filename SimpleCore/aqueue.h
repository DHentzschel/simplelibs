#ifndef QUEUE_H
#define QUEUE_H

#include "alist.h"
#include "iqueue.h"

/**
 * This class implements the IQueue interface and an advanced queue data structure.
 *
 * @author Daniel Hentzschel on 07.08.2019.
 */
template<class T>
class AQueue : protected AList<T>, public IQueue<T> {
public:
	/**
	  * Initializes the class with an empty queue.
	  */
	AQueue();

	/**
	  * Enqueues the specified element to the queue.
	  *
	  * @param right the enqueuable template class
	  */
	void enqueue(const T& value) override;

	/**
	  * Dequeues the first element from the queue and returns it.
	  *
	  * @param right the enqueuable template class
	  * @return the first element
	  */
	T dequeue() override;

	/**
	  * Returns whether the queue is empty.
	  *
	  * @return whether the size of the list behind is empty
	  */
	bool isEmpty() override;
};

template<class T>
inline AQueue<T>::AQueue() :
	AList<T>()
{
}

template<class T>
void AQueue<T>::enqueue(const T& value)
{
	AList<T>::append(value);
}

template<class T>
T AQueue<T>::dequeue()
{
	return AList<T>::takeFirst();
}

template<class T>
bool AQueue<T>::isEmpty()
{
	return AList<T>::size() == 0;
}

#endif // !QUEUE_H
