#pragma once
#include <iostream>


template <class T>
class Vector
{
private:
	T* array_of_elements;
	size_t size;
	size_t capacity;

public:

	// ITERATORS
	struct Iterator;
	struct ReverseIterator;
	Iterator begin();
	Iterator end();
	const Iterator cbegin() const;
	const Iterator cend() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	const ReverseIterator crbegin() const;
	const ReverseIterator crend() const;


	Vector();
	Vector(size_t new_size, const T& value = T());

	// CAPACITY 

	size_t getSize();
	size_t max_size();
	size_t getCapacity();
	bool isEmpty();
	void reserve(size_t new_capacity);
	void resize(size_t new_size, const T& value = T());


	// EDIT

	void push_back(const T& value);
	void pop_back();
	void assign(size_t new_size, const T& value);
	void clear();


	void erase(size_t position);
	void insert(size_t postion, const T& value);
	void swap(Vector<T>&);

	// OPERATORS
	T& at(size_t index);
	T& back();
	T& front();
	T* data();
	T& operator[](size_t);
	const T& operator[](size_t) const;

};


template <typename T>
struct Vector<T>::Iterator
{
public:

	using iterator_category = std::forward_iterator_tag;
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	Iterator(pointer ptr) : pointer_to_type(ptr) {}

	Iterator(Vector<T> ptr) : pointer_to_type(ptr) {}

	reference operator*() const
	{
		return *pointer_to_type;
	}
	pointer operator->() const
	{
		return pointer_to_type;
	}

	Iterator& operator++()
	{
		pointer_to_type++;
		return *this;
	}

	Iterator& operator++(int)
	{
		Iterator temp = *this;
		++(*this);
		return *this;
	}

	friend bool operator==(const Iterator& first, const Iterator& second)
	{
		return first.pointer_to_type == second.pointer_to_type;
	}

	friend bool operator!=(const Iterator& first, const Iterator& second)
	{
		return first.pointer_to_type != second.pointer_to_type;
	}


private:
	pointer pointer_to_type;

};

template <typename T>
struct Vector<T>::ReverseIterator
{
	using value_type = T;
	using pointer = T*;
	using reference = T&;

	ReverseIterator(pointer ptr) : pointer_to_type(ptr) {}

	ReverseIterator(Vector<T> ptr) : pointer_to_type(ptr) {}

	reference operator*() const
	{
		return *pointer_to_type;
	}
	pointer operator->() const
	{
		return pointer_to_type;
	}

	Iterator& operator++()
	{
		pointer_to_type--;
		return *this;
	}

	Iterator& operator++(int)
	{
		Iterator temp = *this;
		--(*this);
		return *this;
	}

	friend bool operator==(const Iterator& first, const Iterator& second)
	{
		return first.pointer_to_type == second.pointer_to_type;
	}

	friend bool operator!=(const Iterator& first, const Iterator& second)
	{
		return first.pointer_to_type != second.pointer_to_type;
	}

private:
	pointer pointer_to_type;
};



template <typename T>
inline typename Vector<T>::Iterator Vector<T>::begin()
{
	return Vector<T>::Iterator(std::addressof(array_of_elements[0]));
}

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::end()
{
	if (size == 0)
	{
		return begin();
	}
	return Vector<T>::Iterator(std::addressof(array_of_elements[size]));
}

template <typename T>
inline typename const Vector<T>::Iterator Vector<T>::cbegin() const
{

	return Vector<T>::Iterator(std::addressof(array_of_elements[0]));
}

template <typename T>
inline typename const Vector<T>::Iterator Vector<T>::cend() const
{
	if (size == 0)
	{
		return cbegin();
	}
	return Vector<T>::Iterator(std::addressof(array_of_elements[size]));
}

template <typename T>
inline typename Vector<T>::ReverseIterator Vector<T>::rbegin()
{
	if (size == 0)
	{
		return rend();
	}
	return Vector<T>::ReverseIterator(std::addressof(array_of_elements[size - 1]));
}

template <typename T>
inline typename Vector<T>::ReverseIterator Vector<T>::rend()
{
	return Vector<T>::ReverseIterator(std::addressof(array_of_elements[0]));
}

template <typename T>
inline typename const Vector<T>::ReverseIterator Vector<T>::crbegin() const
{
	if (size == 0)
	{
		return crend();
	}
	return Vector<T>::ReverseIterator(std::addressof(array_of_elements[size - 1]));
}

template <typename T>
inline typename const Vector<T>::ReverseIterator Vector<T>::crend() const
{
	return Vector<T>::Iterator(std::addressof(array_of_elements[0]));
}

template <typename T>
Vector<T>::Vector()
{
	size = 0;
	capacity = 0;
	array_of_elements = nullptr;
}

template <typename T>
Vector<T>::Vector(size_t new_size, const T& value)
{
	reserve(2 * new_size);
	resize(new_size);
}

template <typename T>
inline size_t Vector<T>::getSize()
{
	return size;
}

template <typename T>
inline size_t Vector<T>::max_size()
{
	return std::numeric_limits<T>::max();
}

template <typename T>
inline size_t Vector<T>::getCapacity()
{
	return capacity;
}

template <typename T>
inline bool Vector<T>::isEmpty()
{
	return size == 0;
}

template <typename T>
inline void Vector<T>::reserve(size_t new_capacity)
{
	if (new_capacity <= capacity) return;
	T* new_array = reinterpret_cast<T*>(new __int8[new_capacity * sizeof(T)]);
	try
	{
		std::uninitialized_copy(array_of_elements, array_of_elements + size, new_array);
	}
	catch (std::exception&)
	{
		delete[] reinterpret_cast<__int8*>(new_array);
		throw;
	}
	for (size_t i = 0; i < size; i++)
	{
		(array_of_elements + i)->~T();
	}
	delete[] reinterpret_cast<__int8*>(array_of_elements);
	array_of_elements = new_array;
	capacity = new_capacity;
}

template <typename T>
inline void Vector<T>::resize(size_t new_size, const T& value)
{
	if (new_size >= capacity) reserve(2 * new_size);
	if (new_size < size) return;
	try
	{
		for (size_t i = size; i < new_size; i++)
		{
			new(array_of_elements + i) T(value);
		}
		if (new_size < size)
		{
			size = new_size;
		}
		//std::uninitialized_copy(array_of_elements + size, array_of_elements + new_size, value);
	}
	catch (std::exception&)
	{
		delete[] reinterpret_cast<__int8*>(array_of_elements);
		throw;
	}
	
}

template <typename T>
inline void Vector<T>::push_back(const T& value)
{
	if (size == 0) reserve(1);
	if (capacity == size) reserve(2 * size);
	new(array_of_elements + size) T(value);
	size++;
}

template <typename T>
inline void Vector<T>::pop_back()
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of vector range");
	}
	size--;
	(array_of_elements + size)->~T();
}

template <typename T>
inline void Vector<T>::assign(size_t new_size, const T& value)
{
	T* new_array = reinterpret_cast<T*>(new __int8[new_size * sizeof(T)]);
	try
	{
		std::uninitialized_copy(new_array, new_array + new_size, value);
	}
	catch (std::exception&)
	{
		delete[] reinterpret_cast<__int8*>(new_array);
		throw;
	}
	delete[] reinterpret_cast<__int8*>(array_of_elements);
	array_of_elements = new_array;
}

template <typename T>
inline void Vector<T>::clear()
{
	for (size_t i = 0; i < size; i++)
	{
		(array_of_elements + i)->~T();
	}
}

template <typename T>
inline void Vector<T>::erase(size_t position)
{
	if (position < 0 || position > size)
	{
		throw std::out_of_range("Out of vector range.");
	}
	(array_of_elements + position)->~T();
	T* new_array = reinterpret_cast<T*>(new __int8[(size - 1) * sizeof(T)]);
	try
	{
		std::uninitialized_copy(array_of_elements, array_of_elements + position, new_array);
		std::uninitialized_copy(array_of_elements + position + 1, array_of_elements + size, new_array + position);
	}
	catch (std::exception&)
	{
		delete[] reinterpret_cast<__int8*>(new_array);
		throw;
	}
	delete[] reinterpret_cast<__int8*>(array_of_elements);
	size--;
	array_of_elements = new_array;
}


template <typename T>
inline void Vector<T>::insert(size_t position, const T& value)
{
	if (size == capacity) {
		capacity <<= 1;
		reserve(capacity);
	}
	if (position < 0 || position > size)
	{
		throw std::out_of_range("Out of vector range.");
	}
	size++;
	for (size_t i = size - 1; i > position - 1; i--)
	{
		new (array_of_elements + i) T(array_of_elements[i - 1]);
	}
	new (array_of_elements + position - 1) T(value);
}

template <typename T>
inline void Vector<T>::swap(Vector<T>& other)
{
	Vector<T> temp;
	temp.resize(other.size);
	temp.array_of_elements = std::move(other.array_of_elements);
	other.resize(size);
	other.array_of_elements = std::move(this->array_of_elements);
	this->resize(temp.size);
	this->array_of_elements = std::move(temp.array_of_elements);
}

template <typename T>
inline T& Vector<T>::at(size_t index)
{
	if (index < 0 || index > size)
	{
		throw std::out_of_range("Out of vector range");
	}
	return array_of_elements[index];
}

template <typename T>
inline T& Vector<T>::front()
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of vector range");
	}
	return array_of_elements[size - 1];
}

template <typename T>
inline T& Vector<T>::back()
{
	if (size <= 0)
	{
		throw std::out_of_range("Out of vector range");
	}
	return array_of_elements[0];
}


template <typename T>
inline T* Vector<T>::data()
{
	return array_of_elements;
}

template <typename T>
inline T& Vector<T>::operator[](size_t index)
{
	return array_of_elements[index];
}

template <typename T>
inline const T& Vector<T>::operator[](size_t index) const
{
	return array_of_elements[index];
}
