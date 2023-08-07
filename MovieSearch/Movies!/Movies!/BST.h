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
	int steps;
public:
	BST<T>(int disp = 4) { root = nullptr; display = disp; steps = 0; };
	int getDepth();
	int getDepth(TreeNode<T> *node);
	int getDisplay() { return display; }
	int getSteps() { return steps; }
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
	std::ostream& visualDisplay(std::ostream &out, TreeNode<T> *n, int level);

	template <typename U>
	friend std::ostream& operator<<(std::ostream &out, BST<U> &bst);

	void deleteTree(TreeNode<T>* n = root);

	~BST<T>();
};