#pragma once

#include "RedBlackTree.h"

template <typename Value>
class Set {
private:

	RBTree<Value> tree;
	size_t size;

public:

	class Iterator {
	private:
		typename RBTree<Value>::Iterator it;

	public:

		Iterator() {
			it = tree.begin();
		}

		Iterator(typename RBTree<Value>::Iterator it) {
			this->it = it;
		}

		Iterator& operator++() {
			++it;
			return *this;
		}

		Iterator& operator++(int) {
			Iterator it = *this;
			++it;
			return it;
		}

		Iterator& operator--() {
			--it;
			return *this;
		}

		Iterator& operator--(int) {
			Iterator it = *this;
			--it;
			return it;
		}


		Value& operator*() {
			return *it;
		}

		Value* operator->() {
			return &*it;
		}

		bool operator==(const Iterator& other) {
			return it == other.it;
		}

		bool operator!=(const Iterator& other) {
			return it != other.it;
		}


	};


	class SecondIterator {
	private:
		typename std::list<Value>::iterator it;
	public:
		SecondIterator() {
			this->it = std::list<Value>::iterator(RBTree<Value>::inorder(tree));
		}

		SecondIterator(typename std::list<Value>::iterator it) {
			this->it = it;
		}
		SecondIterator& operator++() {
			++it;
			return *this;
		}
		SecondIterator operator++(int) {
			SecondIterator it = *this;
			++it;
			return it;
		}

		SecondIterator operator--() {
			--it;
			return *this;
		}

		SecondIterator operator--(int) {
			SecondIterator it = *this;
			--it;
			return it;
		}
		Value& operator*() {
			return *it;
		}
		Value* operator->() {
			return &*it;
		}
		bool operator==(const SecondIterator& other) {
			return it == other.it;
		}

		bool operator!=(const SecondIterator& other) {
			return it != other.it;
		}


	};


	Set() {
		this->size = 0;
	}

	~Set() {
	}

	void insert(Value v) {
		if (this->contains(v))
		{
			return;
		}
		this->tree.insert(v);
		this->size++;
	}

	void remove(Value v) {
		this->tree.remove(v);
		this->size--;
	}

	bool isEmpty()
	{
		return this->size == 0;
	}

	bool contains(Value v) {
		return this->tree.search(this->tree.getRoot(), v) != tree.NIL();
	}

	Value search(Value v) {
		return *this->tree.search(v)->value;
	}

	size_t getSize() {
		return this->size;
	}

	std::list<Value> getElements() {
		return this->tree.inorder(this->tree.root);
	}

	Iterator begin() {
		return Iterator(this->tree.begin());
	}

	Iterator end() {
		return Iterator(this->tree.end());
	}

	SecondIterator sbegin() {
		this->tree.list_to_print.clear();
		this->tree.inorder(this->tree.getRoot());
		return SecondIterator(this->tree.list_to_print.begin());
	}

	SecondIterator send() {
		//this->tree.list_to_print.clear();
		//this->tree.inorder(this->tree.getRoot());
		return SecondIterator(this->tree.list_to_print.end());
	}
};