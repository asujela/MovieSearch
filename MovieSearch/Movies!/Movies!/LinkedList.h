#include "Node.h"
#include <iostream>
#pragma once

//simulates a linked list
template <typename T>
class LinkedList
{
protected:
	Node<T>* first; //pointers to the first and last node
	Node<T>* last;
	int length; //number of nodes in the list
public:
	LinkedList();
	void clear();
	void add(T dat, int index = 0);
	Node<T>* remove(int index = 0);
	int find(T data);
	int getLength()
	{
		return length;
	}
    void printList();
    std::ostream& printToFile(std::ostream&);
	T get(int index = 0);
	~LinkedList();
};

/*
Basic constructor for a linked list which sets everything to default values
*/
template <typename T>
LinkedList<T>::LinkedList()
{
	first = nullptr;
	last = nullptr;
	length = 0;
}

/*
Clears this by simply calling the destructor
*/
template <typename T>
void LinkedList<T>::clear()
{
	//Talked to professor about error with clear:
	//clear function should loop remove instead of calling deconstructor
	int size = length;
	for (int i = 0; i < size; i++)
	{
		Node<T>* temp = remove(0);
		delete temp;
	}
	first = nullptr;
	last = nullptr;
	length = 0;
}

/*
PRE: T dat: the data to be added, int index: the index at which the data will be added
Adds dat to the linked list at index, assumes user want to add to the front by default
*/
template <typename T>
void LinkedList<T>::add(T dat, int index)
{	
	//cout << index << " ";
    Node<T> *node = new Node<T>(dat,nullptr);
	if (length == 0)
	{
		first = node;
		last = node;
	}
	else if (index == 0)
	{
		node->setNext(first);
		first = node;
		//cout << (first == node);
	}
	else if (index > 0 && index < length)
	{
		Node<T>* prevNode = nullptr;
		Node<T>* currentNode = first;
		for (int i = 0; i < index; i++)
		{
			prevNode = currentNode;
			currentNode = currentNode->getNext();
		}
		prevNode->setNext(node);
		node->setNext(currentNode);
	}
	else
	{
		last->setNext(node);
		last = node;
	}
	//cout << first << " " << node<< endl;
	length++;
}

/*
PRE: int index: the index whose node will be removed
POST: the removed node
Removes the node at the index of this linked list
*/
template <typename T>
Node<T>* LinkedList<T>::remove(int index)
{
	Node<T>* toReturn = nullptr;
	if (length == 0)
		return toReturn;
	else if (length == 1)
	{
//        toReturn = new Node<T>(first->getData());
		first = nullptr;
		last = nullptr;
	}
	else if (index == 0)
	{
		toReturn = first;
		first = first->getNext();
	}
	else if (index > 0 && index < length - 1)
	{
		Node<T>* prevNode = nullptr;
		Node<T>* currentNode = first;
		for (int i = 0; i < index; i++)
		{
			prevNode = currentNode;
			currentNode = currentNode->getNext();
		}
		toReturn = currentNode;
		prevNode->setNext(currentNode->getNext());
	}
	else
	{
		Node<T>* currentNode = first;
		while (currentNode->getNext()->getNext() != nullptr)
		{
			currentNode = currentNode->getNext();
		}
		toReturn = currentNode->getNext();
		currentNode->setNext(nullptr);
	}
	length--;
	return toReturn;
}

/*
PRE: T data: the data of the target node to be found
POST: the index of the target node
Iterates through the entire list to find a node with data which matches the input
*/
template <typename T>
int LinkedList<T>::find(T data)
{
	if (length == 0)
		return -1;
	int index = 0;
	Node<T>* currentNode = first;
	do
	{
		if (currentNode->getData() == data)
			return index;
		index++;
		currentNode = currentNode->getNext();
	} while (currentNode->getNext() != nullptr);
	return -1;
}

/*
PRE: int index: the index of the node to retrieve
POST: the data within the node specified by index
Retrieves the data which resides within the node at index 
*/
template <typename T>
T LinkedList<T>::get(int index)
{
	Node<T>* currentNode = first;
	for (int i = 0; i < index; i++)
		currentNode = currentNode->getNext();
	return currentNode->getData();
}

/*
Prints all of the elements in the linked list
*/
template <class T>
void LinkedList<T>::printList()
{
    Node<T>* currentNode = first;
    
    for (int i = 0; i < length; i++)
    {
        std::cout << currentNode->getData();
        if (i+1 < length)
        {
            std::cout << "  -->  ";
            currentNode = currentNode->getNext();
        }
    }
}

/*
 Prints the linked list to a given text
 */
template <class T>
std::ostream& LinkedList<T>::printToFile(std::ostream& outS)
{
    Node<T>* currentNode = first;
    
    for (int i = 0; i < length; i++)
    {
        outS << currentNode->getData();
        if (i+1 < length)
        {
            outS << "\n\t-->  ";
            currentNode = currentNode->getNext();
        }
    }
    return outS;
}

/*
Iterates through the linked list and deletes all node pointers, then sets all member variables to default values
*/
template <typename T>
LinkedList<T>::~LinkedList()
{
	//Talked to professor about exception thrown:
	//Need to include a check to make sure the list isn't empty before executing deconstructor
	if (length == 0)
		return;
	Node<T>* prevNode = nullptr;
	Node<T>* currentNode = first;
	while (currentNode->getNext() != nullptr)
	{
		prevNode = currentNode;
		currentNode = currentNode->getNext();
		delete prevNode;
	}
	if (currentNode != nullptr)
		delete currentNode;
	first = nullptr;
	last = nullptr;

	length = 0;
}
