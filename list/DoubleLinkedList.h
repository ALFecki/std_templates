#pragma once
#include <iostream>
#include <memory>

template <typename T>
class DoubleLinkedList
{
public:
	
	struct Node
	{
		T value;
		std::shared_ptr<Node> next;
		std::weak_ptr<Node> prev;
		Node(T data) : value(data), next(nullptr) {}
	};

	template <typename T>
	struct Iterator
	{
	public:

		using iterator_category = std::forward_iterator_tag;
		using value_type = Node;
		using pointer = Node*;
		using reference = Node&;

		Iterator(pointer ptr) : pointer_to_type(ptr) {}

		Iterator(DoubleLinkedList ptr) : pointer_to_type(ptr.head.get()) {}

		pointer get()
		{
			return pointer_to_type;
		}

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
			pointer_to_type++;
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

	DoubleLinkedList();
	DoubleLinkedList(const DoubleLinkedList<T>&);
	~DoubleLinkedList();

	int getCount();
	bool deleteElem(Node*);
	void insert(T data, int index = 0);
	void addToEnd(T data);
	void addToHead(T data);
	void swap(Node&, Node&);

	Iterator<T> begin();
	Iterator<T> end();
private:

	std::shared_ptr<Node> head;
	std::shared_ptr<Node> tail;
	int size;
};

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& new_list)
{
	head = nullptr;
	tail = nullptr;
	size = new_list.size;

	Node* temp = new_list.head.get();
	while (temp)
	{
		DoubleLinkedList<T>::addToHead(temp->value);
		temp = temp->next.get();
	}
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{

}

template <typename T>
int DoubleLinkedList<T>::getCount()
{
	return size;
}

template <typename T>
bool DoubleLinkedList<T>::deleteElem(Node* data_to_delete)
{
	if (data_to_delete == nullptr)
	{
		return 0;
	}
	Node* element = data_to_delete;
	Node* temp = head.get();
	if (element == temp)
	{
		head = temp->next;
		size--;
		return 1;
	}
	else
	{
		while (element != nullptr)
		{
			if (temp->next.get() == element)
			{
				if (element->next == nullptr)
				{
					temp->next = nullptr;
					tail = std::make_shared<Node>(*temp);
					//delete element;
					size--;
					return 1;
				}
				temp->next = std::move(element->next);

				//delete element;
				size--;
				return 1;

			}
			temp = temp->next.get();
		}
	}

}

template <typename T>
void DoubleLinkedList<T>::insert(T data, int index)
{
	Node* new_data = new Node(data);
	if (index == 0 || index < 1 || index > size + 1) // проверка на правильность позиции
	{
		return;
	}

	if (index == size + 1) // вставка в конец и начало
	{
		addToEnd(data);
		return;
	}
	else if (index == 1)
	{
		addToHead(data);
		return;
	}

	Node* insert_element = head;
	for (int i = 0; i < index; i++) // поиск нужной позиции
	{
		insert_element = insert_element->next;
	}
	Node* previous = insert_element->prev;

	if (previous != nullptr && size != 1) // проверка на начало
	{
		previous->next = new_data;
	}
	insert_element->next = new_data;
	new_data->prev = insert_element;
	new_data->next = insert_element->next;
	insert_element->next->prev = new_data;
	size++;
}

template <typename T>
void DoubleLinkedList<T>::addToEnd(T data)
{
	Node* new_data = new Node(data);
	if (tail->next == nullptr)
	{
		tail->next = std::make_shared<Node>(*new_data);
		tail = tail->next;
	}
}

template <typename T>
void DoubleLinkedList<T>::addToHead(T data)
{
	Node* new_node = new Node(data);
	Node* temp = head.get();

	if (head == nullptr)
	{
		head = std::make_shared<Node>(*new_node);
		tail = std::make_shared<Node>(*new_node);
	}
	else
	{
		new_node->next = std::move(head);
		head = std::make_shared<Node>(*new_node);
	}
	size++;
}


template <typename T>
void DoubleLinkedList<T>::swap(Node& first, Node& second)
{
	auto temp = std::move(first.value);
	first.value = std::move(second.value);
	second.value = std::move(temp);
}


template <typename T>
DoubleLinkedList<T>::Iterator<T> DoubleLinkedList<T>::begin()
{
	return Iterator<T>(head.get());
}

template <typename T>
DoubleLinkedList<T>::Iterator<T> DoubleLinkedList<T>::end()
{
	return Iterator<T>(tail.get());
}

