#pragma once
#include "stdafx.h"
#include <iostream>
using namespace std;

template <class T>
class LinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data, Node* next)
		{
			this->data = data;
			this->next = next;
		}
	};

	Node* first;
	Node* last;
	size_t size;

	Node* goToElem(size_t index)
	{
		if (index < 0 || index >= this->size)
		{
			std::cout << "Index can't be negative or bigger than list size" << std::endl;
			return nullptr;
		}
		Node* temp = this->first;
		for (size_t i = 0; i < index - 1; i++)
		{
			temp = temp->next;
		}
		return temp;
	}
	void copy(const LinkedList& other)
	{
		Node* temp = other.first;
		for (size_t i = 0; i < other.getSize(); i++)
		{
			this->push_back(temp->data);
			temp = temp->next;
		}
	}
	void destroy()
	{
		while (size > 0)
		{
			this->pop_front();
		}
		this->init();
	}
public:
	//Fantastic four!
	LinkedList();
	LinkedList(const LinkedList<T>& other);
	LinkedList& operator=(const LinkedList<T>& other); //assign content
	~LinkedList();

	//Modifiers and Capacity checks!
	void pop_front();
	void pop_back();
	void push_back(const T& data);
	void push_front(const T& data);
	void printData() const;
	bool isEmpty() const;
	void push(const T& data, size_t index);
	size_t getSize() const;
	void init();//initialize

	//Operations!
	void remove(size_t index);
	void changeValAtIndex(const T& data, size_t index);
	void removeAllocc(const T& elem);
	void reverse();
	LinkedList& operator + (const LinkedList<T>& other);
	LinkedList& operator += (const LinkedList<T>& other);
	T& operator[](unsigned int index);

public:
	class Iterator
	{
	private:
		Node * current;
	public:
		Iterator(Node* start)
		{
			this->current = start;
		}
		Iterator& operator++()
		{
			this->current = this->current->next;
			return *this;
		}
		bool operator==(const Iterator& other)
		{
			return this->current == other.current;
		}
		bool operator !=(const Iterator& other)
		{
			return this->current != other.current;
		}
		T& operator *()
		{
			return current->data;
		}
	};
	Iterator begin()
	{
		return Iterator(this->first);
	}
	Iterator end()
	{
		return Iterator(this->last->next);
	}
};


template<class T>
LinkedList<T> ::LinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->size = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	this->destroy();
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	this->copy(other);
}

template<class T>
LinkedList<T>& LinkedList<T>:: operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
		destroy();
		copy(other);
	}

	return *this;
}

template<class T>
void LinkedList<T>::pop_front()
{
	if (!this->isEmpty())
	{
		Node* node = this->first;
		this->first = this->first->next;
		if (this->size == 1)
		{
			this->first = nullptr;
			this->last = nullptr;
		}
		this->size--;

		delete node;
	}
	else cout << "Empty List, There is nothing to delete" << endl;
}

template<class T>
void LinkedList<T>::push_back(const T& data)
{
	Node* temp = new Node(data, nullptr);
	if (this->size == 0)
	{
		this->first = temp;
		this->last = temp;
	}
	else
	{
		this->last->next = temp;
		this->last = temp;
	}
	size++;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
	return (this->size == 0);
}

template<class T>
size_t LinkedList<T> ::getSize() const
{
	return this->size;
}

template<class T>
void LinkedList<T>::push_front(const T& data)
{
	Node* newNode = new Node(data, nullptr);
	if (this->size > 0)
	{
		Node* temp = this->first;
		this->first = newNode;
		newNode->next = temp;
	}
	else
	{
		this->first = newNode;
		this->last = newNode;
	}
	this->size++;
}

template<class T>
void LinkedList<T>::pop_back()
{
	Node* temp = this->first;
	Node* temp2 = this->last;
	while (temp->next != this->last)
	{
		temp = temp->next;
	}
	this->last = temp2;
	delete[] temp2;
	this->size--;
}

template<class T>
void LinkedList<T>::push(const T& data, size_t index)
{
	if (!isEmpty()) {
		if (index < 0 || index > size) {
			cout << "NO";
		}
		else if (index == 0) {
			push_front(data);
		}
		else if (index == this->size - 1) {
			push_back(data);
		}
		else {

			Node * newElem = new Node(data, this->goToElem(index)->next);

			this->goToElem(index)->next = newElem;

		}
		this->size++;
	}
}


template<class T>
void LinkedList<T>::init()
{
	this->first = nullptr;
	this->last = nullptr;
	this->size = 0;
}

template<class T>
void LinkedList<T>::remove(size_t index)
{
	if (!isEmpty())
	{
		if (index<0 || index > size)
		{
			cout << "NO" << endl;
		}
		else if (index == 1)
		{
			pop_front();
		}
		else if (index == size - 1)
		{
			pop_back();
		}
		else
		{
			Node* temp = first;
			while (index != 1)
			{
				temp = temp->next;
				index--;
			}

			Node* save = temp->next;
			temp->next = temp->next->next;
			delete save;
			size--;
		}
	}
}

template<class T>
void LinkedList<T>::changeValAtIndex(const T & data, size_t index)
{
	if (!isEmpty())
	{
		if (index<0 || index>size)
		{
			cout << "No" << endl;
		}
		else
		{
			goToElem(index)->data = data;
		}
	}
	else
	{
		cout << "List is empty" << endl;
	}
}

template<class T>
void LinkedList<T>::removeAllocc(const T & elem)
{
	Node* temp = first;
	Node* prev = first;

	while (temp != NULL)
	{
		if (temp->data == elem)
		{
			if (temp == first)
			{
				first = temp->next;
				delete temp;
				temp = first;
				size--;
			}
			else
			{
				prev->next = temp->next;
				delete temp;
				temp = prev->next;
				size--;
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}

template<class T>
void LinkedList<T>::reverse()
{
	Node* previous = nullptr;
	Node* curr = first;
	Node* next = nullptr;
	while (curr != nullptr)
	{
		next = curr->next;
		curr->next = previous;
		previous = curr;
		curr = next;
	}
	first = previous;
}

template<class T>
void LinkedList<T>::printData() const
{
	Node* temp = this->first;

	for (size_t i = 0; i < this->size; i++)
	{
		cout << temp->data <<" ";
		temp = temp->next;
	}
}

template<class T>
LinkedList<T> & LinkedList<T>::operator+(const LinkedList<T>& other)
{
	LinkedList<T> * newlist = new LinkedList<T>(*this);
	Node * temp = other.first;
	for (int i = 0; i < other.getSize(); i++) {
		newlist->push_back(temp->data);
		temp = temp->next;
	}
	return *newlist;
}

template<class T>
LinkedList<T> & LinkedList<T>::operator+=(const LinkedList<T>& other)
{
	Node * temp = other.first;
	while (temp != nullptr)
	{
		this->push_back(temp->data);
		temp = temp->next;
	}
	return *this;
}

template<class T>
T & LinkedList<T>::operator[](unsigned int index)
{
	return this->goToElem(index)->data;
}


