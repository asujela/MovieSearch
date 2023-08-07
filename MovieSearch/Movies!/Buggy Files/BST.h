#pragma once
#include "TreeNode.h"
#include "Queue.h"
#include <fstream>
#include <iostream>

template <typename T>
class BST
{
private:
	TreeNode<T> *root;
	int display;
public:
	BST<T>(int disp = 4) { root = nullptr; display = disp; };
	int getDepth();
	int getDepth(TreeNode<T> *node);
	int getDisplay() { return display; }
	TreeNode<T>* getRoot() { return root; }
	void setDisplay(int d) { display = d; }
	void add(T data);
	void add(TreeNode<T> *n, T data);
	TreeNode<T>* remove(T data);
	TreeNode<T>* remove(TreeNode<T> *n, T data);
	TreeNode<T>* getMin(TreeNode<T>* n = root);
	TreeNode<T>* getMax(TreeNode<T>* n = root);
	TreeNode<T>* find(T data);
	TreeNode<T>* find(TreeNode<T>* node, T data);
	TreeNode<T>* leftBalance(TreeNode<T>* node);
	TreeNode<T>* rightBalance(TreeNode<T>* node);
	TreeNode<T>* rotateRight(TreeNode<T>* node);
	TreeNode<T>* rotateLeft(TreeNode<T>* node);
	TreeNode<T>* deleteRightBalance(TreeNode<T>* node);
	TreeNode<T>* deleteLeftBalance(TreeNode<T>* node);

	std::ostream& preOrderTree(std::ostream &out, TreeNode<T> *n);
	std::ostream& postOrderTree(std::ostream &out, TreeNode<T> *n);
	std::ostream& inOrderTree(std::ostream &out, TreeNode<T> *n);
	std::ostream& BFTTree(std::ostream &out, TreeNode<T> *n);
	std::ostream& printLevel(std::ostream &out, TreeNode<T> *n, int level);
	std::ostream& visualDisplay(std::ostream &out, TreeNode<T> *n);
	/*
	PRE: ostream and a binary search tree object
	POST: ostream operator<<
	Determines which output format to use based on internal number
	0 to pre order
	1 to post order
	2 to in order
	3 to breadth first traversal
	*/
	template <typename U>
	friend std::ostream& operator<<(std::ostream &out, BST<U> &bst)
	{
		if (bst.getDisplay() == 0)
			return bst.preOrderTree(out, bst.getRoot());
		else if (bst.getDisplay() == 1)
			return bst.postOrderTree(out, bst.getRoot());
		else if (bst.getDisplay() == 2)
			return bst.inOrderTree(out, bst.getRoot());
		else if (bst.getDisplay() == 3)
			return bst.BFTTree(out, bst.getRoot());
		else if (bst.getDisplay() == 4)
			return bst.visualDisplay(out, bst.getRoot());
	}

	void deleteTree(TreeNode<T>* n = root);

	~BST<T>();
};