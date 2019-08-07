#ifndef IQUEUE_H
#define IQUEUE_H

template <class T>
class IQueue {
public:
	virtual void enqueue(T right) = 0;

	virtual T dequeue() = 0;

	virtual bool isEmpty() = 0;
};

#endif // !IQUEUE_H
