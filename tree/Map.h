#pragma once
#include "RedBlackTree.h"

template <typename KeyType, typename ValueType>
class Map {

private:
	RBTree<std::pair<KeyType, ValueType>> tree;
	size_t size;


public:

	class Iterator {

	private:

		typename RBTree<std::pair<KeyType, ValueType>>::Iterator it;

	public:

		Iterator()
		{
			it = RBTree<std::pair<KeyType, ValueType>>::Iterator();
		}

		Iterator(typename RBTree<std::pair<KeyType, ValueType>>::Iterator it) : it(it) {}

		Iterator& operator++() {
			++it;
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++it;
			return tmp;
		}

		Iterator& operator--() {
			--it;
			return *this;
		}

		Iterator operator--(int) {
			Iterator tmp = *this;
			--it;
			return tmp;
		}

		std::pair<KeyType, ValueType>& operator*() {
			return it.operator*();
		}

		std::pair<KeyType, ValueType>* operator->() {
			return it.operator->();
		}

		bool operator==(const Iterator& other) const {
			return it == other.it;
		}

		bool operator!=(const Iterator& other) {
			return it != other.it;
		}
	};

	class SecondIterator {

	private:
		typename std::list<std::pair<KeyType, ValueType>>::iterator it;

	public:

		SecondIterator() {
			this->it = std::list<std::pair<KeyType, ValueType>>::iterator(RBTree<std::pair<KeyType, ValueType>>::inorder(tree));
		}

		SecondIterator(typename std::list<std::pair<KeyType, ValueType>>::iterator it) {
			this->it = it;
		}

		SecondIterator& operator++() {
			++it;
			return *this;
		}

		SecondIterator operator++(int) {
			SecondIterator tmp = *this;
			++it;
			return tmp;
		}

		SecondIterator& operator--() {
			--it;
			return *this;
		}

		SecondIterator operator--(int) {
			SecondIterator tmp = *this;
			--it;
			return tmp;
		}

		std::pair<KeyType, ValueType>& operator*() {
			return it.operator*();
		}

		std::pair<KeyType, ValueType>* operator->() {
			return &it.operator*();
		}

		bool operator==(const SecondIterator& other) const {
			return it == other.it;
		}

		bool operator!=(const SecondIterator& other) {
			return it != other.it;
		}
	};

	Map() : size(0) {}

	Map(const Map& other) : size(other.size) {
		tree = other.tree;
	}

	Map(Map&& other) : size(other.size) {
		tree = std::move(other.tree);
	}

	RBTree<std::pair<KeyType, ValueType>> getTree() {
		return this->tree;
	}

	Map& operator=(const Map& other) {
		if (this != &other) {
			tree = other.tree;
			size = other.size;
		}
		return *this;
	}

	~Map() {}

	bool empty() const {
		return size == 0;
	}

	size_t getSize() const {
		return size;
	}

	void insert(const KeyType& key, const ValueType& value) {
		tree.insert(std::make_pair(key, value));
		size++;
	}

	void remove(const KeyType& key) {
		tree.removeMap(std::make_pair(key, ValueType()));
		size--;
	}

	typename RBTree<std::pair<KeyType, ValueType>>::Node* search(const KeyType& key) {
		return tree.searchMap(tree.getRoot(), std::make_pair(key, ValueType()));
	}

	ValueType& operator[](const KeyType& key) {
		return tree.search(key)->value;
	}

	const ValueType& operator[](const KeyType& key) const {
		return tree.search(key)->value;
	}

	Iterator begin() const {
		return Iterator(tree.begin());
	}

	Iterator end() const {
		return Iterator(tree.end());
	}

	SecondIterator sbegin() {
		this->tree.list_to_print.clear();
		this->tree.inorder(this->tree.getRoot());
		return SecondIterator(this->tree.list_to_print.begin());
	}

	SecondIterator send() {
		return SecondIterator(this->tree.list_to_print.end());
	}



};