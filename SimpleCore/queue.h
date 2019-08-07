#ifndef QUEUE_H
#define QUEUE_H

#include "alist.h"

template<class T>
class Queue : protected AList<T> {
	Queue() = default;

	void enqueue();

	T dequeue();
};


#endif // !QUEUE_H

template<class T>
inline void Queue<T>::enqueue(const T& value)
{
	append(value);
}

template<class T>
inline T Queue<T>::dequeue()
{
	return takeFirst();
}
