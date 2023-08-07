#pragma once
#include "Node.h"
template <typename T>
class TreeNode : public Node<T>
{
private:
	TreeNode<T> *left, *right;
public:

	TreeNode<T>(T d, TreeNode<T>* l = nullptr, TreeNode<T>* r = nullptr)
	{
		this->setData(d);
		left = l;
		right = r;
	}
	bool hasLeft() { return this->getLeft() != nullptr; }
	bool hasRight() { return this->getRight() != nullptr; }
	void setLeft(TreeNode<T> * l) { left = l; }
	void setRight(TreeNode<T> * r) { right = r; }
	int getDepth()
	{
		int a = 0, b = 0;
		if (hasLeft())
			a = getLeft()->getDepth();
		if (hasRight())
			b = getRight()->getDepth();
		if (a > b)
			return a + 1;
		return b + 1;
		
	}
	TreeNode<T>* getLeft() { return left; }
	TreeNode<T>* getRight() { return right; }
	virtual ~TreeNode<T>() { }
};