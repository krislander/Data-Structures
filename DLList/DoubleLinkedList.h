#pragma once
#include <iostream>

template<class T>
struct Node
{
	T data;
	Node* next;
	Node* prev;

	Node(const T& data, Node* next, Node* prev):
		data(data), next(next), prev(prev)
	{

	}
};

template<class T>
class DLLIterator
{
private:
	Node<T>* currentElem;
public:
	DLLIterator(Node<T>* currentElem);
	T& operator* ();
	DLLIterator& operator++(int);
	DLLIterator& operator--(int);
	bool operator !=(const DLLIterator& other);
};

template<class T>
class DoubleLinkedList
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;

	//private methods
	void copy(const DoubleLinkedList<T>& other);
	void destroy();
public:
	//Fantastic four!
	DoubleLinkedList();
	DoubleLinkedList(const DoubleLinkedList<T>& other);
	DoubleLinkedList& operator=(const DoubleLinkedList& other);
	~DoubleLinkedList();
	//Modifiers, Capacity checks and Operations
	void push_back(const T& data);
	void push_front(const T& data);
	void pop_back();
	void pop_front();
	void push(const T& data, size_t index);
	void pop(size_t index);
	void printData() const;
	void reverse();
	size_t getSize() const;
	bool isEmpty() const;
	T& top() const;
	T& bottom() const;
	T& operator[](int index);

	//DLLIterator methods
	DLLIterator<T> begin();
	DLLIterator<T> end();
	friend class DLLIterator<T>; //DLLIterator class can access DoubleLinkedList
	void map(void(*func)(T&));
};

template<class T>
void DoubleLinkedList<T>::copy(const DoubleLinkedList<T>& other)
{
	//check for empty
	if (other.first == nullptr)
	{
		first = nullptr;
		last = nullptr;
		return;
	}

	this->first = new Node<T>(other.first->data, nullptr, nullptr);
	Node<T>* lastCopy = first;
	Node<T>* nextCopy = other.first->next;

	while (nextCopy != nullptr)
	{
		lastCopy->next = new Node<T>(nextCopy->data, nullptr, lastCopy);
		lastCopy = lastCopy->next;
		nextCopy = nextCopy->next;
	}
	last = lastCopy;
	this->size = other.size;
}

template<class T>
void DoubleLinkedList<T>::destroy()
{
	Node<T>* next;

	while (first != nullptr)
	{
		next = first->next;
		delete first;
		first = next;
	}

	this->size = 0;
	last = nullptr;
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	this->first = nullptr;
	this->last = nullptr;
	this->size = 0;
}

template<class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other)
{
	this->copy(other);
}

template<class T>
DoubleLinkedList<T> & DoubleLinkedList<T>::operator=(const DoubleLinkedList & other)
{
	if (this != &other)
	{
		this->destroy();
		this->copy(other);
	}

	return *this;
}

template<class T>
DoubleLinkedList<T>::~DoubleLinkedList<T>()
{
	this->destroy();
}

template<class T>
void DoubleLinkedList<T>::push_back(const T & data)
{
	Node<T>* temp = new Node<T>(data, nullptr, nullptr);
	if (this->isEmpty())
	{
		this->first = temp;
		this->last = temp;
	}
	else
	{
		this->last->next = temp;
		temp->prev = this->last;
		this->last = temp;
	}
	this->size++;
}

template<class T>
void DoubleLinkedList<T>::push_front(const T & data)
{
	Node<T>* temp = new Node<T>(data, nullptr, nullptr);
	if (this->isEmpty())
	{
		this->first = temp;
		this->last = temp;
	}
	else
	{
		this->first->prev = temp;
		temp->next = first;
		this->first = temp;
	}
	this->size++;
}

template<class T>
void DoubleLinkedList<T>::pop_back()
{
	Node<T>* temp = this->last->prev;
	delete[] this->last;

	this->last = temp;
	this->last->next = nullptr;
	if (this->last == nullptr)
	{
		this->first = nullptr;
	}
	this->size--;
}

template<class T>
void DoubleLinkedList<T>::pop_front()
{
	Node<T>* temp = this->first;
	delete[] this->first;

	this->first = temp;
	if (this->first == nullptr)
	{
		this->last = nullptr;
	}
	this->size--;
}

template<class T>
void DoubleLinkedList<T>::push(const T & data, size_t index)
{
	Node<T>* temp = this->first;
	if (index == 0)
	{
		this->push_front(data);
	}
	else if(index == this->size)
	{
		this->push_back(data);
	}
	else
	{
		for (size_t i = 1; i < index; i++)
		{
			temp = temp->next;
		}

		Node<T>* temp2 = new Node<T>(data, temp->next, temp);
		temp->next->prev = temp2;
		temp->next = temp2;
		this->size++;
	}
}

template<class T>
void DoubleLinkedList<T>::pop(size_t index)
{
	Node<T>* temp = this->first;
	if (index == 0)
	{
		this->pop_front();
	}
	else if (index == this->size - 1)
	{
		this->pop_back();
	}
	else
	{
		//iterate till we get to the index element
		for (size_t i = 0; i < index; i++)
		{
			temp = temp->next;
		}
		Node<T>* temp2 = temp->prev;
		Node<T>* temp3 = temp->next;
		delete[] temp;

		temp2->next = temp3;
		temp3->prev = temp2;
		this->size--;
	}
}

template<class T>
void DoubleLinkedList<T>::printData() const
{
	Node<T>* temp = this->first;
	while (temp != nullptr)
	{
		std::cout << temp->data <<" ";
		temp = temp->next;
	}
	std::cout << std::endl;
}

template<class T>
void DoubleLinkedList<T>::reverse()
{
	Node<T>* current = this->first;
	Node<T>* temp = NULL;
	while (current != NULL)
	{
		temp = current->next;
		current->next = current->prev;
		current->prev = temp;

		if (temp == NULL)
		{
			this->last = this->first;
			this->first = current;
		}
		current = temp;
	}
	
}

template<class T>
size_t DoubleLinkedList<T>::getSize() const
{
	return this->size;
}

template<class T>
bool DoubleLinkedList<T>::isEmpty() const
{
	return (this->size == 0);
}

template<class T>
T & DoubleLinkedList<T>::top() const
{
	return this->first->data;
}

template<class T>
T & DoubleLinkedList<T>::bottom() const
{
	return this->last->data;
}

template<class T>
T & DoubleLinkedList<T>::operator[](int index)
{
	Node<T>* temp = this->first;
	for (size_t i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp->data;
}

template<class T>
DLLIterator<T> DoubleLinkedList<T>::begin()
{
	return DLLIterator<T>(this->first);
}

template<class T>
DLLIterator<T> DoubleLinkedList<T>::end()
{
	return DLLIterator<T>(this->last->next);
}

template<class T>
void DoubleLinkedList<T>::map(void(*func)(T &))
{
	Node<T>* temp = this->first;
	for (size_t i = 0; i < this->size; i++)
	{
		func(temp->data);
		temp = temp->next;
	}
}

template<class T>
void functionadd(T& input)
{
	input = input + 10;
}

template<class T>
 DLLIterator<T>::DLLIterator(Node<T>* currentElem)
	 :currentElem(currentElem)
{
}

template<class T>
T & DLLIterator<T>::operator*()
{
	if (currentElem != nullptr)
		return this->currentElem->data;
	else
		throw std::invalid_argument("Current element is nullptr!");
}

template<class T>
DLLIterator<T> & DLLIterator<T>::operator++(int)
{
	if (currentElem != nullptr)
	{
		this->currentElem = this->currentElem->next;
		return *this;
	}
	else
		throw std::invalid_argument("Current element is nullptr!");
}

template<class T>
DLLIterator<T> & DLLIterator<T>::operator--(int)
{
	if (currentElem != nullptr)
	{
		this->currentElem = this->currentElem->prev;
		return *this;
	}
	else
		throw std::invalid_argument("Current element is nullptr!");
}

template<class T>
bool DLLIterator<T>::operator!=(const DLLIterator & other)
{
	return this->currentElem != other.currentElem;
}
