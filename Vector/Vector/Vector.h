#pragma once
#include <iostream>

template <typename T>

class Vector
{
private:
	T * data;
	size_t size;
	size_t capacity;

	void copy(const Vector& other)
	{
		this->size = other.size;
		this->capacity = other.capacity;
		this->data = new T[this->capacity];
		for (size_t i = 0; i < this->size; i++) 
			this->data[i] = other.data[i];
	}

	void destroy() 
	{
		delete this->data;
	}

	void resize() 
	{
		if (this->size >= this->capacity) 
		{
			this->capacity *= 2;

			T* temp = new T[this->capacity];
			for (size_t i = 0; i < this->size; i++) 
			{
				temp[i] = this->data[i];
			}

			this->destroy();
			this->data = temp;
		}
	}

public:
	class Iterator 
	{
		T * current;
	public:
		Iterator(T * current) : current(current) 
		{
		}
		//prefix
		Iterator& operator++(int) 
		{
			this->current += 1;
			return *this;
		}
		bool operator == (const Iterator& other) 
		{
			return this->current == other.current;
		}
		bool operator != (const Iterator& other) 
		{
			return this->current != other.current;
		}
		T& operator * () 
		{
			return *current;
		}
	};
	Iterator begin()
	{
		return Iterator(this->data);
	}
	Iterator end()
	{
		return Iterator(this->data + this->getSize());
	}

	//Fantastic Four!!!
	Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void clear();
	void push_back(T data);
	void pop_back();
	void insertAtPos(size_t index, T value);
	void eraseAtPos(size_t index);
	void print() const;
	int getSize() const;
	int getCapacity() const;
	bool isEmpty() const;
	T operator[](size_t index);
	bool operator == (const Vector& other);
	Vector& operator += (const Vector& other);
	Vector operator + (const Vector& other);
};

template <typename T>
Vector<T> ::Vector()
{
	this->size = 0;
	this->capacity = 2;
	this->data = new T[this->capacity];
}

template <typename T>
Vector<T> :: ~Vector() 
{
	this->destroy();
}

template <typename T>
Vector<T> ::Vector(const Vector& other) 
{
	this->copy(other);
}

template <typename T>
Vector<T>& Vector<T> :: operator=(const Vector& other) 
{
	if (this != &other)
	{
		this->destroy();
		this->copy(other);
	}

	return *this;

}
template <typename T>
void Vector<T> ::print()const 
{
	for (size_t i = 0; i < this->size; i++) 
	{
		std::cout << "index " << i + 1 << " : " << this->data[i] << std::endl;
	}
}

template <typename T>
int Vector<T> ::getSize()const 
{
	return this->size;
}

template <typename T>
int Vector<T> ::getCapacity()const 
{
	return this->capacity;
}

template <typename T>
bool Vector<T> ::isEmpty()const 
{
	return this->size == 0;
}

template <typename T>
T Vector<T> :: operator[](size_t index) 
{
	if (index > this->size) 
	{
		std::cout << "Invalid index!" << std::endl;
	}
	else 
	{
		return this->data[index - 1];
	}
}

template <typename T>
bool Vector<T> :: operator == (const Vector& other)
{
	bool flag = true;
	if (this->size != other.size)
	{
		return false;
	}
	else 
	{
		for (int i = 0; i < this->size; i++) 
		{
			if (this->data[i] != other.data[i])
				flag = false;
		}
	}
	return flag;
}
template <typename T>
void Vector<T> ::push_back(T data) 
{
	if (this->size == capacity) 
		this->resize(); 

	this->data[this->size++] = data;
}

template <typename T>
void Vector<T> ::pop_back()
{
	this->size--;
}

template <typename T>
void Vector<T> ::clear()
{
	while (this->size > 0) 
	{
		this->pop_back();
	}
}

template <typename T>
void Vector<T> ::insertAtPos(size_t index, T value) 
{
	if (index > this->size) 
	{
		std::cout << "Invalid index!" << std::endl;
	}
	else 
	{
		if (this->size == capacity) 
			this->resize();

		for (size_t i = (this->size - 1); i >= index - 1; i--)
		{
			this->data[i + 1] = this->data[i];
		}

		this->data[index - 1] = value;
		this->size++;
	}
}

template <typename T>
void Vector<T> ::eraseAtPos(size_t index) 
{
	if (index > this->size)
	{
		std::cout << "Invalid index!" << std::endl;
	}
	else 
	{
		for (size_t i = index - 1; i < this->size; i++)
		{
			this->data[i] = this->data[i + 1];
		}
		this->size--;
	}
}

template <typename T>
Vector<T>& Vector<T> :: operator += (const Vector& other)
{

	for (size_t i = 0; i < other.size; i++) 
	{
		this->push_back(other.data[i]);
	}
	return *this;
}

template <typename T>
Vector<T> Vector<T> :: operator + (const Vector& other)
{
	Vector sum;
	for (size_t i = 0; i < this->size; i++)
	{
		sum.push_back(this->data[i]);
	}
	for (size_t j = 0; j < other.size; j++) 
	{
		sum.push_back(other.data[j]);
	}
	return Vector(sum);
}
