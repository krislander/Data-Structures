#pragma once
#include <iostream>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node<T>* next;

	Node(const T& dt, Node<T>* nxt = nullptr)
	{
		this->data = dt;
		this->next = nxt;
	}
};

template <typename T>
class Queue
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;

	void copy(const Queue& other)
	{
		Node<T>* temp = other.first;

		for (size_t i = 0; i < other.getSize(); i++)
		{
			this->push(temp->data);
			temp = temp->next;
		}
	}
	void erase()
	{
		while (!isEmpty())
		{
			this->pop();
		}
	}
public:
	//Fantastic four!
	Queue()
	{
		this->first = nullptr;
		this->last = nullptr;
		this->size = 0;
	}
	Queue(const Queue& other)
	{
		this->copy(other);
	}
	Queue& operator=(const Queue& other)
	{
		if (this != &other)
		{
			this->erase();
			this->copy(other);
		}
		return *this;
	}
	~Queue()
	{
		this->erase();
	}

	//other methods - push, pop, front, back, getSize, isEmpty, 
	void push(const T& element);
	void pop();
	const T& front() const;
	const T& back() const;
	size_t getSize() const;
	bool isEmpty() const;

};

template<typename T>
void Queue<T>::push(const T& element)
{
	Node<T>* addElement = new Node<T>(element);

	if (this->isEmpty())
	{
		this->first = addElement;
		this->last = addElement;
	}
	else
	{
		this->last->next = addElement;
		this->last = addElement;
	}
	this->size++;
}

template<typename T>
void Queue<T>::pop()
{
	if (!isEmpty())
	{
		Node<T>* temp = first;
		this->first = this->first->next;
		delete temp;
		this->size--;
	}
}

template<typename T>
const T & Queue<T>::front() const
{
	if (this->first != nullptr)
	{
		return this->first->data;
	}
	throw "Queue is empty!";
}

template<typename T>
const T & Queue<T>::back() const
{
	if (this->last != nullptr)
	{
		return this->last->data;
	}
	throw "Queue is empty!";
}

template<typename T>
size_t Queue<T>::getSize() const
{
	return this->size;
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return this->size == 0;
}
