#pragma once

#include <iostream>
#include <forward_list>
#include <functional>
#include <xutility>


template <typename KeyType, typename ValueType>
class Unordered_map {

private:
	std::forward_list<std::pair<KeyType, ValueType>>* map;
	size_t size;
	size_t capacity;


	void rehash()
	{
		capacity *= 2;
		std::forward_list<std::pair<KeyType, ValueType>>* new_map = new std::forward_list<std::pair<KeyType, ValueType>>[capacity];
		for (size_t i = 0; i < capacity / 2; i++)
		{
			for (auto& it : map[i])
			{
				new_map[hash_function(it.first) % capacity].push_front(it);
			}
		}
		delete[] map;
		map = new_map;
	}


	size_t hash_function(KeyType key)
	{
		return std::hash<KeyType>{}(key) % capacity;
	}

public:

	Unordered_map()
	{
		capacity = 5;
		map = new std::forward_list<std::pair<KeyType, ValueType>>[capacity];
		size = 0;
	}

	Unordered_map(size_t capacity)
	{
		this->capacity = capacity;
		map = new std::forward_list<std::pair<KeyType, ValueType>>[capacity];
		size = 0;
	}

	~Unordered_map()
	{

	}

	typename std::forward_list<std::pair<KeyType, ValueType>>::iterator search(KeyType key)
	{
		size_t index = hash_function(key);
		for (auto it = map[index].begin(); it != map[index].end(); it++)
		{
			if (it->first == key)
			{
				return it;
			}
		}
		return map[index].end();
	}

	void insert(KeyType key, ValueType value)
	{
		auto it = search(key);
		if (it != (map[hash_function(key)].end()))
		{
			//it->second = value;
			return;
		}
		else
		{
			map[hash_function(key)].push_front(std::make_pair(key, value));
			size++;
			if (size >= 0.75 * capacity)
			{
				rehash();
			}
		}
	}

	bool empty()
	{
		return this->size == 0;
	}

	void remove(KeyType key)
	{
		auto it = search(key);
		if (it != map[hash_function(key)].end())
		{
			map[hash_function(key)].remove(*it);
			size--;
		}
	}

	void clear() {
		delete[] map;
		capacity = 15;
		map = new std::forward_list<std::pair<KeyType, ValueType>>[capacity];
		size = 0;
	}

	size_t get_size() const {
		return size;
	}

	bool contains(KeyType key) {
		auto it = search(key);
		if (it != map[hash_function(key)].end())
		{
			return true;
		}
		return false;
	}

	ValueType& operator[](const KeyType& key)
	{
		auto it = search(key);
		if (it != map[hash_function(key)].end())
		{
			return it->second;
		}
		else
		{
			insert(key, ValueType());
			return map[hash_function(key)].back().second;
		}
	}

	std::list < std::pair<KeyType, ValueType>> print() {
		std::list < std::pair<KeyType, ValueType> > list;
		for (size_t i = 0; i < capacity; i++)
		{
			for (auto& it : map[i])
			{
				list.push_back(it);
			}
		}
		return list;
	}
};