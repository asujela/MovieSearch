#pragma once

//simulates a node
template <typename T>
class Node
{
private:
	T data; //the value stored in the node
	Node<T>* nextNode; //the pointer to the next node
public:
	Node<T>()
	{
		nextNode = nullptr;
	}
	Node<T>(T dat, Node<T>* nodeptr = nullptr);
	//inline accessors and mutators
	void setData(T input)
	{
		data = input;
	}
	T getData()
	{
		return data;
	}
	void setNext(Node<T>* ptr)
	{
		nextNode = ptr;
	}
	Node<T>* getNext()
	{
		return nextNode;
	}
	virtual ~Node<T>() { delete nextNode; }
};

/*
PRE: T dat: the data to be stored, Node<T>* nodeptr specifies the next node to point to, default nullptr
*/
template <typename T>
Node<T>::Node(T dat, Node<T>* nodeptr)
{
	data = dat;
	nextNode = nodeptr;
}


