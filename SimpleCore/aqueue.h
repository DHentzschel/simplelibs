#ifndef QUEUE_H
#define QUEUE_H

#include "alist.h"
#include "iqueue.h"

template<class T>
class Queue : protected AList<T>, public IQueue<T> {
	void enqueue(const T& value) override;

	T dequeue() override;

	bool isEmpty() override;
};

template<class T>
inline void Queue<T>::enqueue(const T& value)
{
	AList<T>::append(value);
}

template<class T>
inline T Queue<T>::dequeue()
{
	return AList<T>::takeFirst();
}

template<class T>
inline bool Queue<T>::isEmpty()
{
	return AList<T>::size() == 0;
}

#endif // !QUEUE_H
