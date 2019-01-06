#pragma once
#include <iostream>

template <class T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;

	Node(const T& data, Node<T>* left, Node<T>* right)
		:data(data), left(left), right(right)
	{
	}
};

template <class T>
class BTree
{
private:
	Node<T>* root;

	//private methods
	void addLeafprvt(const T& data, Node<T>* parent);
	void printInOrderprvt(Node<T>* ptr);
	void deleteNodeprvt(const T& data, Node<T>* parent);
	//void removeRootMatch();
	//void removeMatch(Node<T>* parent, Node<T>* match, bool left);
	void normalPrint(Node<T>* pointer)const;
	void removeSubTree(Node<T>* pointer);
	Node<T>* returnNodeprvt(const T& data, Node<T>* pointer);
	T& findSmallestprvt(Node<T>* pointer) const;

public:
	BTree();
	~BTree();
	Node<T> * createNode(const T& data);
	Node<T>* returnNode(const T& data);
	T& returnRootData();
	T& findSmallest() const;
	void addLeaf(const T& data);
	void printInOrder();
	void deleteNode(const T& data);
	void print()const;
	void printChildren(const T& data);

	//ZZS
	int count(Node<T>* node);
	int height(Node<T>* parent);
};

template<class T>
void BTree<T>::addLeafprvt(const T & data, Node<T>* parent)
{
	if (root == nullptr)
	{
		this->root = createNode(data);
	}
	else if (parent->data > data)
	{
		if (parent->left != nullptr)
			addLeafprvt(data, parent->left);
		else
			parent->left = createNode(data);
	}
	else if (parent->data<data)
	{
		if (parent->right != nullptr)
			addLeafprvt(data, parent->right);
		else
			parent->right = createNode(data);
	}
}

template<class T>
void BTree<T>::printInOrderprvt(Node<T>* ptr)
{
	if (this->root != nullptr)
	{
		if (ptr->left != nullptr)
		{
			printInOrderprvt(ptr->left);
		}
		
		if (ptr->right != nullptr)
		{
			printInOrderprvt(ptr->right);
		}
		std::cout << ptr->data << std::endl;
	}
	else
		std::cout << "Empty tree!" << std::endl;
}

template<class T>
void BTree<T>::deleteNodeprvt(const T & data, Node<T>* parent)
{
	if (this->root != nullptr)
	{
		if (root->data == data)
			std::cout << "Here we do magic!!!" << std::endl;
		else
		{
			if (data < parent->data && parent->left != nullptr) {
				parent->left->data == data ? removeMatch(parent, parent->left, true) : deleteNodeprvt(data, parent->left);

			}
			else if (data > parent->data && parent->right != nullptr) {
				parent->right->data == data ? removeMatch(parent, parent->right, false) : deleteNodeprvt(data, parent->right);
			}
			else {
				std::cout << "Invalid Node!" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Empty Tree!" << std::endl;
	}
}

template<class T>
void BTree<T>::normalPrint(Node<T>* pointer) const
{
	if (pointer != nullptr)
	{
		normalPrint(pointer->left);
		std::cout << pointer->data << " ";
		normalPrint(pointer->right);
	}
}

template<class T>
void BTree<T>::removeSubTree(Node<T>* pointer)
{
	if (pointer != nullptr)
	{
		if (pointer->left)
			removeSubTree(pointer->left);
		if (pointer->right)
			removeSubTree(pointer->right);

		std::cout << "Deleted: " << pointer->data << std::endl;
		delete[] pointer;
	}
}

template<class T>
Node<T>* BTree<T>::returnNodeprvt(const T & data, Node<T>* pointer)
{
	if (pointer != nullptr)
	{
		if (pointer->data == data)
			return pointer;
		else
		{
			if (data < pointer->data)
			{
				return returnNodeprvt(data, pointer->left);
			}
			else if(data > pointer->data)
			{
				return returnNodeprvt(data, pointer->right);
			}
		}
	}
	else
	{
		return nullptr;
	}
	
}

template<class T>
T & BTree<T>::findSmallestprvt(Node<T>* pointer) const
{
	if (this->root != nullptr)
	{
		if (pointer->left != nullptr)
			return findSmallestprvt(pointer->left);
		else
			return pointer->data;
	}
}


template<class T>
T & BTree<T>::findSmallest() const
{
	return findSmallestprvt(this->root);
}

template<class T>
void BTree<T>::addLeaf(const T & data)
{
	addLeafprvt(data, this->root);
}

template<class T>
void BTree<T>::printInOrder()
{
	printInOrderprvt(this->root);
}

template<class T>
void BTree<T>::deleteNode(const T & data)
{
	deleteNodeprvt(data, root);
}

template<class T>
void BTree<T>::print() const
{
	normalPrint(this->root);
}

template<class T>
void BTree<T>::printChildren(const T & data)
{
	Node<T>* temp = returnNode(data);

	if (temp)
	{
		std::cout << "Parent node: "<< temp->data << std::endl;
		if(temp->left)
			std::cout << "Left child node: " << temp->left->data << std::endl;
		else
			std::cout << "NULL left" << std::endl;

		if(temp->right)
			std::cout << "Right child node: " << temp->right->data << std::endl;
		else
			std::cout << "NULL right " << std::endl;
	}
	else
	{
		std::cout << "No valid node!"<< std::endl;
	}
}

template<class T>
int BTree<T>::count(Node<T>* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	else
		return (count(node->left) + count(node->right) + 1);
	
}

template<class T>
int BTree<T>::height(Node<T>* parent)
{
	if (parent == nullptr)
	{
		return 0;
	}
	else
	{
		int leftDepth = 1;
		int rightDepth = 1;
		leftDepth = height(parent->left);
		rightDepth = height(parent->right);

		if (leftDepth >= rightDepth)
			return leftDepth;
		else
			return rightDepth;
	}
}

template<class T>
BTree<T>::BTree()
{
	this->root = nullptr;
}

template<class T>
BTree<T>::~BTree()
{
	removeSubTree(this->root);
}

template<class T>
Node<T>* BTree<T>::createNode(const T & data)
{
	Node<T>* node = new Node<T>(data, nullptr, nullptr);
	return node;
}

template<class T>
Node<T>* BTree<T>::returnNode(const T & data)
{
	return returnNodeprvt(data, this->root);
}

template<class T>
T & BTree<T>::returnRootData()
{
	if (root != nullptr)
	{
		return root->data;
	}
}


