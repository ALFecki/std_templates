#pragma once
#include <iostream>

template <class T>
class Queue
{
private:
	T* data;
	int front, rear, size;
	unsigned capacity;
	
public:
	Queue(int new_capacity = 1000);
	Queue(int size, int new_capacity = 1000);
	~Queue();
	void enqueue(T item);
	T dequeue();
	T peek();
	bool isFull();
	bool isEmpty();
	int getSize();
};

template <class T>
Queue<T>::Queue(int new_capacity)
{
	capacity = new_capacity;
	size = 0;
	front = 0;
	rear = -1;
	data = reinterpret_cast<T*>(new __int8[new_capacity * sizeof(T)]);
}

template <class T>
Queue<T>::Queue(int size, int new_capacity)
{
	capacity = new_capacity;
	this->size = size;
	front = 0;
	rear = -1;
	data = reinterpret_cast<T*>(new __int8[size * sizeof(T)]);
}

template <class T>
Queue<T>::~Queue()
{
	delete[] data;
}

template <class T>
bool Queue<T>::isFull()
{
	return size == capacity;
}

template <class T>
bool Queue<T>::isEmpty()
{
	return size == 0;
}

template <class T>
void Queue<T>::enqueue(T item)
{
	if (isFull())
	{
		throw std::out_of_range("Queue is full");
	}
	rear++;
	data[rear] = item;
	size++;
}

template <class T>
T Queue<T>::dequeue()
{
	if (isEmpty())
	{
		throw std::out_of_range("Queue is empty!");
	}
	T item = data[front];
	front++;
	size--;
	return item;
}

template <class T>
T Queue<T>::peek()
{
	if (isEmpty())
	{
		throw std::out_of_range("Queue is empty");
	}
	return data[front];
}

template <class T>
int Queue<T>::getSize()
{
	return size;
}


