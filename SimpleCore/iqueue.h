#ifndef IQUEUE_H
#define IQUEUE_H

/**
 * This class is an interface for queue data structures.
 *
 * @author Daniel Hentzschel on 07.08.2019.
 */
template <class T>
class IQueue {
public:
	/**
	  * Enqueues the specified element to the queue.
	  * Must be overridden.
	  *
	  * @param right the enqueuable template class
	  */
	virtual void enqueue(const T& right) = 0;

	/**
	  * Dequeues the first element from the queue and returns it.
	  * Must be overridden.
	  *
	  * @param right the enqueuable template class
	  * @return the first element
	  */
	virtual T dequeue() = 0;

	/**
	  * Returns whether the queue is empty.
	  * Must be overridden.
	  *
	  * @return whether the size of the list behind is empty
	  */
	virtual bool isEmpty() = 0;
};

#endif // !IQUEUE_H
