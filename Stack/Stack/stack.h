#include <iostream>

using namespace std;

template<typename T>
struct Node
{
	T data;
	Node<T>* next;

	Node(const T& dt, Node<T>* nxt = NULL)
	{
		this->data = dt;
		this->next = nxt;
	}
};

template<typename T>
class Stack
{
private:
	Node<T>* first;
	size_t size;
public:
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();
	T top() const;
	size_t getSize() const;
	void push(const T& element);
	void pop();
	void empty(); //raboti i kato print
	void print();
private:
	//private methods
	void copy(const Stack<T>& other);
	void init();
	bool isEmpty() const;

};

template<typename T>
Stack<T>::Stack()
{
	this->first = NULL;
	this->size = 0;
}

template<typename T>
Stack<T>::Stack(const Stack & other)
{
	this->copy(other);
}

template<typename T>
Stack<T> & Stack<T>::operator=(const Stack & other)
{
	if (this != &other)
	{
		this->empty();
		this->init();
		this->copy(other);
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack()
{
	this->empty();
}

template<typename T>
T Stack<T>::top() const
{
	return T();
}

template<typename T>
size_t Stack<T>::getSize() const
{
	return this->size;
}

template<typename T>
void Stack<T>::push(const T & element)
{
	Node<T>* temp = new Node<T>(element, this->first);

	if (temp)//if it exists and is not nullptr
	{
		this->first = temp;
		this->size++;
	}
}

template<typename T>
void Stack<T>::pop()
{
	if (!this->isEmpty())
	{
		Node<T>* temp = this->first;
		//prenasochvame adresa kam sledvashtata
		this->first = this->first->next;
		delete temp;
		size--;
	}
}

template<typename T>
void Stack<T>::copy(const Stack<T>& other)
{
	this->first = new Node<T>(other.first->data, other.first->next);

	Node<T>* temp1 = this->first;
	Node<T>* temp2 = other.first->next;

	while (temp2)//dokato temp2 ne e nullptr
	{
		temp1->next = new Node<T>(temp2->data, temp2->next);
		temp2 = temp2->next;
		temp1 = temp1->next;
	}
}

template<typename T>
void Stack<T>::empty()
{
	for (size_t i = 0; i <= this->size; i++)
	{
		this->pop();
	}
}

template<typename T>
void Stack<T>::print()
{
	Node<T>* temp = this->first;

	while (temp)
	{
		cout << this->first->data << endl;
		this->first = this->first->next;
	}
}

template<typename T>
void Stack<T>::init()
{
	this->first = NULL;
	this->size = 0;
}

template<typename T>
bool Stack<T>::isEmpty() const
{
	return this->first == NULL;
}