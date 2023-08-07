#pragma once
#include "BST.h"
#include <cmath>

/*
PRE: some data
POST: void
Calls add function with an additional paramater of current root
*/
template <typename T>
void BST<T>::add(T data)
{
	steps = 0;
	steps++;
	this->add(root, data);
}

/*
PRE: a pointer to a treenode and some data
POST: void
Base Case: if the root is null, create a new treenode with the given data
Determines whether or not to include information in the sort by name or sort by birthday BST and then adds
data recursively based on the root node and its children
*/
template <typename T>
void BST<T>::add(TreeNode<T> *n, T data)
{
	steps++;
	if (n == nullptr)
	{
		root = new TreeNode<T>(data);
	}
	else
	{
		if (data < n->getData())
		{
			if (n->hasLeft())
			{
				add(n->getLeft(), data);
			}
			else
			{
				TreeNode<T> * pTreeNode = new TreeNode<T>(data);
				n->setLeft(pTreeNode);
				return;
			}
			if (this->getDepth(n->getLeft()->getLeft()) > this->getDepth(n->getLeft()->getRight()) + 1)
				n->setLeft(leftBalance(n->getLeft()));
			else if (this->getDepth(n->getLeft()) > this->getDepth(n->getRight()) + 1 && n == root)
				root = leftBalance(n);
		}
		else
		{
			if (n->hasRight())
			{
				add(n->getRight(), data);
			}
			else
			{
				TreeNode<T> * pTreeNode = new TreeNode<T>(data);
				n->setRight(pTreeNode);
				return;
			}
			if (this->getDepth(n->getRight()->getLeft()) + 1 < this->getDepth(n->getRight()->getRight()))
				n->setRight(rightBalance(n->getRight()));
			else if (this->getDepth(n->getLeft()) + 1 < this->getDepth(n->getRight())&& n == root)
				root = rightBalance(n);
		}
	}
}

/*
PRE: a pointer to the TreeNode to be balanced
POST: the pointer to the now balanced TreeNode
Changes links of the subtree with node as its root to make it no longer unbalanced on the left
*/
template <typename T>
TreeNode<T>* BST<T>::leftBalance(TreeNode<T>* node)
{
	if (this->getDepth(node->getLeft()->getLeft()) > this->getDepth(node->getLeft()->getRight()))
		node = rotateRight(node);
	else
	{
		node->setLeft(rotateLeft(node->getLeft()));
		node = rotateRight(node);
	}
	return node;
}

/*
PRE: a pointer to the TreeNode to be balanced
POST: the pointer to the now balanced TreeNode
Changes links of the subtree with node as its root to make it no longer unbalanced on the right
*/
template <typename T>
TreeNode<T>* BST<T>::rightBalance(TreeNode<T>* node)
{
	if (this->getDepth(node->getRight()->getLeft()) < this->getDepth(node->getRight()->getRight()))
	{
		node = rotateLeft(node);
	}
	else
	{
		node->setRight(rotateRight(node->getRight()));
		node = rotateLeft(node);
	}
	return node;
}

/*
PRE: the pointer to the node to be rotated
POST: the pointer to the rotated node
Changes links of the subtree with node to rotate the TreeNode to the right
*/
template <typename T>
TreeNode<T>* BST<T>::rotateRight(TreeNode<T>* node)
{
	TreeNode<T>* temp = node->getLeft();
	node->setLeft(temp->getRight());
	temp->setRight(node);
	//std::cout << temp->getData() << endl;
	//cout << node->getData() << endl;
	return temp;
}

/*
PRE: the pointer to the node to be rotated
POST: the pointer to the rotated node
Changes links of the subtree with node to rotate the TreeNode to the left
*/
template <typename T>
TreeNode<T>* BST<T>::rotateLeft(TreeNode<T>* node)
{
	TreeNode<T>* temp = node->getRight();
	node->setRight(temp->getLeft());
	temp->setLeft(node);
	return temp;
}

/*
PRE: nothing
POST: returns depth the root
-Calls getDepth recursively with current root
*/
template <typename T>
int BST<T>::getDepth()
{
	return getDepth(root);
}

/*
PRE: pointer to TreeNode
POST: integer representing the depth of the the BST
Gets the depth of both left and right and totals the depth of the tree recursively
*/
template <typename T>
int BST<T>::getDepth(TreeNode<T> *node)
{
	if (node == nullptr)
		return 0;
	int a = getDepth(node->getRight());
	int b = getDepth(node->getLeft());
	if (a > b)
		return 1 + a;
	return 1 + b;
}

/*
PRE: some data to remove
POST: result of seperate remove function with root
Removes the data from the root
*/
template <typename T>
TreeNode<T>* BST<T>::remove(T data)
{
	steps = 1;
	return remove(root, data);
}

/*
PRE: pointer to treenode
POST: true or false
Removes a data node from the binary search tree recursively, balances tree automatically
*/
template <typename T>
TreeNode<T>* BST<T>::remove(TreeNode<T> *n, T data)
{
	steps++;
	if (n == root&&data == root->getData())
	{
		TreeNode<T> * toReturn = root;
		if (!root->hasLeft())
		{
			if (!root->hasRight())
				root = nullptr;
			else
				*root = *root->getRight();
		}
		else if (!root->hasRight())
			*root = *root->getLeft();
		else
		{
			if (!root->getLeft()->hasRight())
			{
				TreeNode<T> * left = root->getLeft();
				root->setData(left->getData());
				root->setLeft(left->getLeft());
				return toReturn;
			}
			else
			{
				TreeNode<T> * max = getMax(root->getLeft());
				root->setData(max->getData());
				remove(root->getLeft(), max->getData());
				return toReturn;
			}
		}	
		return toReturn;
	}
	else if (data < n->getData())
	{
		if (n->getLeft() == nullptr)
			return nullptr;
		else if (data == n->getLeft()->getData())
		{
			TreeNode<T> * left = n->getLeft();
			TreeNode<T> * toReturn = n->getLeft();
			if (!left->hasLeft())
			{
				if (!left->hasRight())
				{
					n->setLeft(nullptr);
				}
				else
				{
					n->setLeft(left->getRight());
				}
			}
			else if (!left->hasRight())
			{
				n->setLeft(left->getLeft());
			}
			else
			{
				if (!left->getLeft()->hasRight())
				{
					TreeNode<T> * ll = left->getLeft();
					left->setData(ll->getData());
					left->setLeft(ll->getLeft());
					return toReturn;
				}
				else
				{
					TreeNode<T> * max = getMax(left->getLeft());
					left->setData(max->getData());
					remove(left->getLeft(), max->getData());
					return toReturn;
				}
			}
			return left;
		}
		else
		{
			remove(n->getLeft(), data);
		}
	}
	else if (data > n->getData())
	{
		if (n->getRight() == nullptr)
			return nullptr;
		else if (data == n->getRight()->getData())
		{
			TreeNode<T> * right = n->getRight();
			TreeNode<T> * toReturn = n->getRight();
			if (!right->hasLeft())
			{
				if (!right->hasRight())
				{
					n->setRight(nullptr);
				}
				else
				{
					n->setRight(right->getRight());
				}
			}
			else if (!right->hasRight())
			{
				n->setRight(right->getLeft());
			}
			else
			{
				if (!right->getLeft()->hasRight())
				{
					TreeNode<T> * rr = right->getLeft();
					right->setData(rr->getData());
					right->setLeft(rr->getLeft());
					return toReturn;
				}
				else
				{
					TreeNode<T> * max = getMax(right->getLeft());
					right->setData(max->getData());
					remove(right->getLeft(), max->getData());
					return toReturn;
				}
			}
			return right;
		}
		else
		{
			remove(n->getRight(), data);
		}
	}
}

/*
PRE: pointer to the node to be balanced
POST: the now right-balanced node
Right-balances the node passed in
*/
template <typename T>
TreeNode<T>* BST<T>::deleteRightBalance(TreeNode<T>* node)
{
	if (abs((node->getLeft()->getDepth() - node->getRight()->getDepth()) * 1.0) > 1)
	{
		TreeNode<T>* roR = node->getRight();
		if (roR->getLeft()->getDepth() > roR->getRight()->getDepth())
		{
			TreeNode<T>* loR = roR->getLeft();
			node->setRight(rotateRight(roR));
			node = rotateLeft(node);
		}
		else
			node = rotateLeft(node);
	}
	return node;
}

/*
PRE: pointer to the node to be balanced
POST: the now left-balanced node
Left-balances the node passed in
*/
template <typename T>
TreeNode<T>* BST<T>::deleteLeftBalance(TreeNode<T>* node)
{
	if (abs((node->getLeft()->getDepth() - node->getRight()->getDepth()) * 1.0) > 1)
	{
		TreeNode<T>* loL = node->getLeft();
		if (loL->getRight()->getDepth() > loL->getLeft()->getDepth())
		{
			TreeNode<T>* roL = loL->getRight();
			loL = rotateLeft(loL);
			node = rotateRight(node);
		}
		else
			node = rotateRight(node);
	}
	return node;
}

/*
PRE: pointer to treenode to get maximum
POST: pointer to a treenode
Returns greatest data point in tree
*/
template <typename T>
TreeNode<T>* BST<T>::getMax(TreeNode<T>* n)
{
	while (n->hasRight())
		n = n->getRight();
	return n;
}

/*
PRE: pointer to treenode to get minimum
POST: pointer to a treenode
Returns smallest data point in tree
*/
template <typename T>
TreeNode<T>* BST<T>::getMin(TreeNode<T>* n)
{
	while (n->hasLeft())
		n = n->getLeft();
	return n;
}

/*
PRE: the data to be found
POST: the pointer to the found TreeNode
returns the pointer to the treenode containing data, nullptr if not found
*/
template <typename T>
TreeNode<T>* BST<T>::find(T data)
{
	steps = 1;
	return find(root, data);
}

/*
recursive function referenced in find
*/
template <typename T>
TreeNode<T>* BST<T>::find(TreeNode<T>* node, T data)
{
	steps++;
	if (node == nullptr)
		return nullptr;
	if (data < node->getData())
		return find(node->getLeft(), data);
	if (data > node->getData())
		return find(node->getRight(), data);
	return node;
}

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
std::ostream& operator<<(std::ostream &out, BST<U> &bst)
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
		return bst.visualDisplay(out, bst.getRoot(), 1);
}

/*
PRE: ostream and pointer to treenode
POST: ostream of data to write
Writes out using pre order
*/
template <typename T>
std::ostream& BST<T>::preOrderTree(std::ostream &out, TreeNode<T> *n)
{
	if (n == nullptr) {
		return out;
	}
	out << n->getData();
	this->preOrderTree(out, n->getLeft());
	this->preOrderTree(out, n->getRight());
	return out;
}

/*
PRE: ostream and pointer to treenode
POST: ostream of data to write
Writes out using post order
*/
template <typename T>
std::ostream& BST<T>::postOrderTree(std::ostream &out, TreeNode<T> *n)
{
	if (n == nullptr) {
		return out;
	}
	this->postOrderTree(out, n->getLeft());
	this->postOrderTree(out, n->getRight());
	out << n->getData();
	return out;
}

/*
PRE: ostream and pointer to treenode
POST: ostream of data to write
Writes out using in order
*/
template <typename T>
std::ostream& BST<T>::inOrderTree(std::ostream &out, TreeNode<T> *n)
{
	if (n == nullptr)
		return out;
	this->inOrderTree(out, n->getLeft());
	out << n->getData() << endl;;
	this->inOrderTree(out, n->getRight());
	return out;
}

/*
PRE: ostream and pointer a treenode
POST: ostream of data to write
*/
template <typename T>
std::ostream& BST<T>::BFTTree(std::ostream &out, TreeNode<T> *n)
{
	for (int d = 1; d < this->getDepth() + 1; d++)
		printLevel(out, n, d);
	return out;
}

/*
PRE: ostream, pointer to treenode, and integer for tree level
POST: ostream of data to write
*/
template <typename T>
std::ostream& BST<T>::printLevel(std::ostream &out, TreeNode<T> *n, int level)
{
	if (n == nullptr)
		return out;
	if (level == 1)
		out << n->getData();
	else
	{
		printLevel(out, n->getLeft(), level - 1);
		printLevel(out, n->getRight(), level - 1);
	}
	return out;
}

/*
PRE: ostream, pointer to treenode, and integer for tree level
POST: ostream of data to write
prints out the diagram of the tree
*/
template <typename T>
std::ostream& BST<T>::visualDisplay(std::ostream &out, TreeNode<T> *n, int level)
{
	if (n == nullptr)
		return out;
	visualDisplay(out, n->getLeft(), level + 1);
	for (int i = 0; i < root->getDepth() - level; i++)
		out << '\t';
	out << n->getData();
	out << '\n';
	visualDisplay(out, n->getRight(), level + 1);
	return out;
}

/*
Default deconstructor
Calls delete function with root
*/
template <typename T>
BST<T>::~BST<T>()
{
	deleteTree(root);
}

/*
PRE: pointer to a treenode
POST: void
Deletes the root and its children until it is nullptr
*/
template <typename T>
void BST<T>::deleteTree(TreeNode<T>* n)
{
	if (n == nullptr)
		return;
	deleteTree(n->getLeft());
	deleteTree(n->getRight());
	delete n;
}
