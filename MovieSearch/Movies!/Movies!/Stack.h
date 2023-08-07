#pragma once
#include "LinkedList.h"

template <typename T>
class Stack : public LinkedList<T>
{
public:
	Stack() : LinkedList<T>() {};
	bool isEmpty();
	void push(const T& dat);
	bool pop(T& dat);
	bool peek(T& dat);
	virtual ~Stack() {};
};

/*
PRE: No input
POST: True or false
Checks the length of the stack and returns true if it is empty, else false
*/
template <typename T>
bool Stack<T>::isEmpty()
{
	return this->length == 0;
}


/*
PRE: T dat: the data to push to the stack passed by reference
POST: No output
Calls the add member functino from LinkedList and passes the input data to the function
*/
template <typename T>
void Stack<T>::push(const T& data)
{
	this->add(data,0);
}

/*
PRE: T dat: the data popped from the stack passed by reference
POST: True or false
Tests to see whether or not the stack is empty
If true, set test to false, else assign the reference data to the top of the list
Remove the top node (default)
Return test result
*/
template <typename T>
bool Stack<T>::pop(T& data)
{
	bool test;
	if (isEmpty())
		test = false;
	else
	{
		data = this->get(0);
		Node<T>* temp = this->remove();
		test = true;
		delete temp;
	}

	return test;
}

/*
PRE: T dat: the data accessed from peek passed by reference
POST: True or false
Tests to see if the stack is empty
If true, test is set to false, else the data from the top of the stack
is set to the parameter referenced data
Return result of test
*/
template <typename T>
bool Stack<T>::peek(T& data)
{
	bool test;
	if (isEmpty())
	{
		test = false;
	}
	else {
		data = this->get(0);
		test = true;
	}
	return test;
}