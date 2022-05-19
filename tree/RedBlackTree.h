#pragma once


#include <string>
#include <list>
#include <utility>



template <typename Value>
class RBTree {

public:

	struct Node {

		Value value;
		Node* parent;
		Node* left;
		Node* right;
		std::string color;
	};
	
	std::list<Value> list_to_print;

	class Iterator {
	private:
		Node* current;
		Node* root;

	public:
		bool is_end;

		Iterator() {

		}

		Iterator(Node* current, Node* root) {
			this->current = current;
			this->root = root;
			this->is_end = false;
		}

		Iterator(Node* root) {
			this->current = root;
			this->root = root;
			this->is_end = false;
		}


		Iterator& operator++() {
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
			}
			else {
				while (current == current->parent->right) {
					current = current->parent;
					current->parent = current->parent->parent;
				}
				if (current->right != current->parent)
				{
					current = current->parent;
				}
			}
			return *this;
		}

		Iterator& operator++(int) {
			Iterator temp = *this;
			++* this;
			return temp;
		}

		Iterator& operator--() {
			if (current->left) {
				current = current->left;
				while (current->right) {
					current = current->right;
				}
			}
			else {
				while (current == current->parent->left) {
					current = current->parent;
					current->parent = current->parent->parent;
				}
				if (current->left != current->parent)
				{
					current = current->parent;
				}
			}
			return *this;
		}

		Iterator& operator--(int) {
			Iterator temp = *this;
			--* this;
			return temp;
		}

		Value& operator*() {
			return current->value;
		}

		Value* operator->() {
			return &current->value;
		}


		bool operator==(const Iterator& other) {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) {
			return current != other.current;
		}



	};

	class Const_Iterator {
	private:
		
		Node* current;
		Node* root;

	public:

		bool is_end;

		Const_Iterator() {

		}

		Const_Iterator(Node* current, Node* root) {
			this->current = current;
			this->root = root;
			this->is_end = false;
		}

		Const_Iterator(Node* root) {
			this->current = root;
			this->root = root;
			this->is_end = false;
		}
		
		Const_Iterator& operator++() {
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
			}
			else {
				while (current == current->parent->right) {
					current = current->parent;
					current->parent = current->parent->parent;
				}
				if (current->right != current->parent)
				{
					current = current->parent;
				}
			}
			return *this;
		}

		Const_Iterator& operator++(int) {
			Const_Iterator temp = *this;
			++* this;
			return temp;
		}
		
		Const_Iterator& operator--() {
			if (current->left) {
				current = current->left;
				while (current->right) {
					current = current->right;
				}
			}
			else {
				while (current == current->parent->left) {
					current = current->parent;
					current->parent = current->parent->parent;
				}
				if (current->left != current->parent)
				{
					current = current->parent;
				}
			}
			return *this;
		}

		Const_Iterator& operator--(int) {
			Const_Iterator temp = *this;
			--* this;
			return temp;
		}
		
		const Value& operator*() {
			return current->value;
		}

		const Value* operator->() {
			return &current->value;
		}

		bool operator==(const Const_Iterator& other) {
			return current == other.current;
		}

		bool operator!=(const Const_Iterator& other) {
			return current != other.current;
		}
	
	};

	class Reverse_Iterator {
		private:
		Node* current;
		Node* root;

		public:

			bool is_end;
			
			Reverse_Iterator() {

			}

			Reverse_Iterator(Node* current, Node* root) {
				this->current = current;
				this->root = root;
				this->is_end = false;
			}

			Reverse_Iterator(Node* root) {
				this->current = root;
				this->root = root;
				this->is_end = false;
			}

			Reverse_Iterator& operator++() {
				if (current->left) {
					current = current->left;
					while (current->right) {
						current = current->right;
					}
				}
				else {
					while (current == current->parent->left) {
						current = current->parent;
						current->parent = current->parent->parent;
					}
					if (current->left != current->parent)
					{
						current = current->parent;
					}
				}
				return *this;
			}

			Reverse_Iterator& operator++(int) {
				Reverse_Iterator temp = *this;
				++* this;
				return temp;
			}

			Reverse_Iterator& operator--() {
				if (current->right) {
					current = current->right;
					while (current->left) {
						current = current->left;
					}
				}
				else {
					while (current == current->parent->right) {
						current = current->parent;
						current->parent = current->parent->parent;
					}
					if (current->right != current->parent)
					{
						current = current->parent;
					}
				}
				return *this;
			}

			Reverse_Iterator& operator--(int) {
				Reverse_Iterator temp = *this;
				--* this;
				return temp;
			}

			Value& operator*() {
				return current->value;
			}
			
			Value* operator->() {
				return &current->value;
			}

			bool operator==(const Reverse_Iterator& other) {
				return current == other.current;
			}

			bool operator!=(const Reverse_Iterator& other) {
				return current != other.current;
			}
			
	};

	class Const_Reverse_Iterator {
		
	private:
		Node* current;
		Node* root;

	public:

		bool is_end;

		Const_Reverse_Iterator() {

		}

		Const_Reverse_Iterator(Node* current, Node* root) {
			this->current = current;
			this->root = root;
			this->is_end = false;
		}

		Const_Reverse_Iterator(Node* root) {
			this->current = root;
			this->root = root;
			this->is_end = false;
		}

		Const_Reverse_Iterator& operator++() {
			if (current->left) {
				current = current->left;
				while (current->right) {
					current = current->right;
				}
			}
			else {
				while (current == current->parent->left) {
					current = current->parent;
					current->parent = current->parent->parent;
				}
				if (current->left != current->parent)
				{
					current = current->parent;
				}
			}
			return *this;
		}

		Const_Reverse_Iterator& operator++(int) {
			Const_Reverse_Iterator temp = *this;
			++* this;
			return temp;
		}

		Const_Reverse_Iterator& operator--() {
			if (current->right) {
				current = current->right;
				while (current->left) {
					current = current->left;
				}
			}
			else {
				while (current == current->parent->right) {
					current = current->parent;
					current->parent = current->parent->parent;
				}
				if (current->right != current->parent)
				{
					current = current->parent;
				}
			}
			return *this;
		}

		Const_Reverse_Iterator& operator--(int) {
			Const_Reverse_Iterator temp = *this;
			--* this;
			return temp;
		}

		const Value& operator*() {
			return current->value;
		}

		const Value* operator->() {
			return &current->value;
		}

		bool operator==(const Const_Reverse_Iterator& other) {
			return current == other.current;
		}

		bool operator!=(const Const_Reverse_Iterator& other) {
			return current != other.current;
		}
	};

	RBTree() {
		nil = new Node;
		nil->parent = nullptr;
		nil->left = nullptr;
		nil->right = nullptr;
		nil->color = "black";
		root = nil;
	}

	~RBTree() {
		//delete nil;
	}


	void insert(Value v) {
		Node* new_node = new Node;
		new_node->value = v;
		new_node->parent = nil;
		new_node->left = nil;
		new_node->right = nil;
		new_node->color = "red";
		Node* y = nullptr;
		Node* x = this->root;
		while (x != nil) {
			y = x;
			if (new_node->value <= x->value) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		new_node->parent = y;
		if (y == nullptr) {
			this->root = new_node;
		}
		else if (new_node->value < y->value) {
			y->left = new_node;
		}
		else {
			y->right = new_node;
		}

		if (new_node->parent == nullptr) {
			new_node->color = "black";
			return;
		}

		if (new_node->parent->parent == nullptr) {
			return;
		}
		InsertFixup(new_node);
	}


	Node* search(Node* node, Value k) {

		if (node == nil || k == node->value)
		{
			return node;
		}
		if (k < node->value)
		{
			return search(node->left, k);
		}
		else
		{
			return search(node->right, k);
		}
	}


	Node* searchMap(Node* node, Value k) {

		if (node == nil || k.first == node->value.first)
		{
			return node;
		}
		if (k.first < node->value.first)
		{
			return searchMap(node->left, k);
		}
		else
		{
			return searchMap(node->right, k);
		}
	}

	void removeMap(Value k) {
		Node* node_to_delete = searchMap(this->root, k);
		if (node_to_delete == nullptr) {
			return;
		}
		Node* y = node_to_delete;
		Node* x;
		std::string y_original_color = y->color;
		if (node_to_delete->left == nil) {
			x = node_to_delete->right;
			transplant(node_to_delete, node_to_delete->right);
		}
		else if (node_to_delete->right == nil) {
			x = node_to_delete->left;
			transplant(node_to_delete, node_to_delete->left);
		}
		else {
			y = minimum(node_to_delete->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == node_to_delete) {
				x->parent = y;
			}
			else {
				transplant(y, y->right);
				y->right = node_to_delete->right;
				y->right->parent = y;
			}
			transplant(node_to_delete, y);
			y->left = node_to_delete->left;
			y->left->parent = y;
			y->color = node_to_delete->color;
		}
		delete node_to_delete;
		if (y_original_color == "black") {
			deleteFix(x);
		}
	}


	void remove(Value k) {
		Node* node_to_delete = search(this->root, k);
		if (node_to_delete == nullptr) {
			return;
		}
		Node* y = node_to_delete;
		Node* x;
		std::string y_original_color = y->color;
		if (node_to_delete->left == nil) {
			x = node_to_delete->right;
			transplant(node_to_delete, node_to_delete->right);
		}
		else if (node_to_delete->right == nil) {
			x = node_to_delete->left;
			transplant(node_to_delete, node_to_delete->left);
		}
		else {
			y = minimum(node_to_delete->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == node_to_delete) {
				x->parent = y;
			}
			else {
				transplant(y, y->right);
				y->right = node_to_delete->right;
				y->right->parent = y;
			}
			transplant(node_to_delete, y);
			y->left = node_to_delete->left;
			y->left->parent = y;
			y->color = node_to_delete->color;
		}
		delete node_to_delete;
		if (y_original_color == "black") {
			deleteFix(x);
		}
	}

	Node* minimum(Node* node) {
		while (node->left != nil)
		{
			node = node->left;
		}
		return node;
	}

	Node* maximum(Node* node) {
		while (node->right != nil)
		{
			node = node->right;
		}
		return node;
	}

	Node* getRoot() {
		return this->root;
	}

	Node* NIL() {
		return this->nil;
	}

	void inorder(Node* node) {

		if (node != nil) {
			inorder(node->left);
			list_to_print.push_back(node->value);
			inorder(node->right);
		}
	}

	Iterator begin() {
		Iterator it(minimum(this->root), this->root);
		return it;
	}

	Iterator end() {
		Iterator it(maximum(this->root), this->root);
		it.is_end = true;
		return it;
	}

	Const_Iterator cbegin()
	{
		Const_Iterator it(minimum(this->root), this->root);
		return it;
	}

	Const_Iterator cend()
	{
		Const_Iterator it(maximum(this->root), this->root);
		it.is_end = true;
		return it;
	}

	Reverse_Iterator rbegin()
	{
		Reverse_Iterator it(maximum(this->root), this->root);
		return it;
	}

	Reverse_Iterator rend()
	{
		Reverse_Iterator it(minimum(this->root), this->root);
		it.is_end = true;
		return it;
	}

	Const_Reverse_Iterator crbegin()
	{
		Const_Reverse_Iterator it(maximum(this->root), this->root);
		return it;
	}

	Const_Reverse_Iterator crend()
	{
		Const_Reverse_Iterator it(minimum(this->root), this->root);
		it.is_end = true;
		return it;
	}


private:


	Node* root;
	Node* nil;


	void LeftRotate(Node* x) {
		Node* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void RightRotate(Node* x) {
		Node* y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->right = x;
		x->parent = y;
	}

	void InsertFixup(Node* new_node) {
		Node* u;
		while (new_node->parent->color == "red") {
			if (new_node->parent == new_node->parent->parent->right) {
				u = new_node->parent->parent->left;
				if (u->color == "red") {
					u->color = "black";
					new_node->parent->color = "black";
					new_node->parent->parent->color = "red";
					new_node = new_node->parent->parent;
				}
				else {
					if (new_node == new_node->parent->left)
					{
						new_node = new_node->parent;
						RightRotate(new_node);
					}
					new_node->parent->color = "black";
					new_node->parent->parent->color = "red";
					LeftRotate(new_node->parent->parent);
				}
			}
			else {
				u = new_node->parent->parent->right;
				if (u->color == "red") {
					u->color = "black";
					new_node->parent->color = "black";
					new_node->parent->parent->color = "red";
					new_node = new_node->parent->parent;
				}
				else {
					if (new_node == new_node->parent->right)
					{
						new_node = new_node->parent;
						LeftRotate(new_node);
					}
					new_node->parent->color = "black";
					new_node->parent->parent->color = "red";
					RightRotate(new_node->parent->parent);
				}
			}
			if (new_node == this->root) {
				break;
			}
		}
		this->root->color = "black";
	}

	void transplant(Node* u, Node* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	void deleteFix(Node* node_to_fix) {
		Node* temp;
		while (node_to_fix != root && node_to_fix->color == "black") {
			if (node_to_fix == node_to_fix->parent->left)
			{
				temp = node_to_fix->parent->right;
				if (temp->color == "red")
				{
					temp->color = "black";
					node_to_fix->parent->color = "red";
					LeftRotate(node_to_fix->parent);
					temp = node_to_fix->parent->right;
				}
				if (temp->left->color == "black" && temp->right->color == "black")
				{
					temp->color = "red";
					node_to_fix = node_to_fix->parent;
				}
				else
				{
					if (temp->right->color == "black")
					{
						temp->left->color = "black";
						temp->color = "red";
						RightRotate(temp);
						temp = node_to_fix->parent->right;

					}
					temp->color = node_to_fix->parent->color;
					node_to_fix->parent->color = "black";
					temp->right->color = "black";
					LeftRotate(node_to_fix->parent);
					node_to_fix = root;
				}
			}
			else
			{
				temp = node_to_fix->parent->left;
				if (temp->color == "red")
				{
					temp->color = "black";
					node_to_fix->parent->color = "red";
					RightRotate(node_to_fix->parent);
					temp = node_to_fix->parent->left;
				}
				if (temp->left->color == "black" && temp->right->color == "black")
				{
					temp->color = "red";
					node_to_fix = node_to_fix->parent;
				}
				else
				{
					if (temp->left->color == "black")
					{
						temp->right->color = "black";
						temp->color = "red";
						LeftRotate(temp);
						temp = node_to_fix->parent->left;
					}

					temp->color = node_to_fix->parent->color;
					node_to_fix->parent->color = "black";
					temp->left->color = "black";
					RightRotate(node_to_fix->parent);
					node_to_fix = root;
				}
			}

		}
		node_to_fix->color = "black";
	}
};

