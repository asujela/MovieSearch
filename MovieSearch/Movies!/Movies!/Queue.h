#pragma once
#include "LinkedList.h"

//simulates a queue
template <typename T>
class Queue : public LinkedList<T>
{
public:
	Queue() : LinkedList<T>() {};
	void enqueue(const T& data);
	T dequeue();
	T front();
	T rear();
	void empty();
	virtual ~Queue() {}
	class EmptyQueueException { };
};

/*
PRE: The data to be enqueued
Adds the data to the queue at the front
*/
template <typename T>
void Queue<T>::enqueue(const T& data)
{
	this->add(data,0);
}

/*
POST: the value that was dequeued at the rear
Dequeues the value at the rear
*/
template <typename T>
T Queue<T>::dequeue()
{
	if (this->length == 0)
		throw EmptyQueueException();
	Node<T>* node = this->remove(this->length - 1);
	T toReturn = node->getData();
	delete node;
	return toReturn;
}

/*
POST: the value at the front
Returns the value at the front
*/
template <typename T>
T Queue<T>::front()
{
	if (this->length == 0)
		throw EmptyQueueException();
	return this->get(this->length - 1);
}

/*
POST: the value at the back
Returns the value at the back
*/
template <typename T>
T Queue<T>::rear()
{
	if (this->length == 0)
		throw EmptyQueueException();
	return this->get(0);
}

/*
Empties the queue
*/
template <typename T>
void Queue<T>::empty()
{
	this->clear();
}