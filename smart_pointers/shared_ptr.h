#pragma once
#include "unique_ptr.h"


template <class Type>
class My_weak_ptr;


struct CBlock
{
	int* shared_count = nullptr;
	int* weak_count = nullptr;
	CBlock(int a, int b)
	{
		shared_count = new int(a);
		weak_count = new int(b);
	}
};

template <typename Type>
class My_shared_ptr
{
private:

	Type* object_ptr = nullptr;
	CBlock* c_block_ptr = nullptr;

	template <typename Type, typename... Args>
	friend My_shared_ptr<Type> make_shared_ptr(Args&&... args);

public:

	My_shared_ptr() {}

	My_shared_ptr(Type* other_ptr)
		: object_ptr(other_ptr)
	{
		c_block_ptr = new CBlock(1, 0);
	}

	My_shared_ptr(const My_shared_ptr& new_pointer)
	{
		this->~My_shared_ptr();
		c_block_ptr = new_pointer.c_block_ptr;
		object_ptr = new_pointer.object_ptr;
		*(c_block_ptr->shared_count) += 1;
	}

	My_shared_ptr(My_weak_ptr<Type> weak_ptr)
	{
		c_block_ptr = weak_ptr.c_block_ptr;
		object_ptr = weak_ptr.object_ptr;

		(*(c_block_ptr->shared_count))++;
	}


	My_shared_ptr(My_shared_ptr&& new_pointer)
		: c_block_ptr(new_pointer.c_block_ptr), object_ptr(new_pointer.object_ptr)
	{
		new_pointer.object_ptr = nullptr;
		new_pointer.c_block_ptr = nullptr;
	}

	My_shared_ptr(My_unique_ptr<Type>&& new_pointer)
	{
		*this = new_pointer.release();
	}

	My_shared_ptr operator=(const My_shared_ptr& new_pointer)
	{
		this->~My_shared_ptr();
		c_block_ptr = new_pointer.c_block_ptr;
		object_ptr = new_pointer.object_ptr;
		(*(c_block_ptr->shared_count))++;
		return *this;
	}


	My_shared_ptr operator=(My_shared_ptr&& new_pointer)
	{
		this->~My_shared_ptr();
		c_block_ptr = new_pointer.c_block_ptr;
		object_ptr = new_pointer.object_ptr;
		new_pointer.object_ptr = nullptr;
		new_pointer.c_block_ptr = nullptr;
		return *this;
	}
	Type& operator*() const
	{
		assert(object_ptr);
		return *object_ptr;
	}
	Type* operator->() const
	{
		assert(object_ptr);
		return object_ptr;
	}
	explicit operator bool()
	{
		return this->get() != nullptr;
	}

	Type* get()
	{
		return object_ptr;
	}
	int get_count() const
	{
		return *(c_block_ptr->shared_count);
	}
	void reset(Type* new_obj)
	{
		this->~My_shared_ptr();
		*this = My_shared_ptr<Type>(new_obj);
	}


	~My_shared_ptr()
	{
		if (c_block_ptr == nullptr)
		{
			return;
		}
		(*(c_block_ptr->shared_count))--;
		if (*(c_block_ptr->shared_count) == 0 && *(c_block_ptr->weak_count) == 0)
		{
			delete c_block_ptr->shared_count;
			delete c_block_ptr->weak_count;
			delete c_block_ptr;
			delete object_ptr;
		}
		else if (*(c_block_ptr->shared_count) == 0)
		{
			delete object_ptr;
		}

		object_ptr = nullptr;
		c_block_ptr = nullptr;
	}

	friend class My_weak_ptr<Type>;

};

template <typename Type, typename... Args>
My_shared_ptr<Type> make_shared_ptr(Args&&... args)
{
	return My_shared_ptr<Type>(new Type(std::forward<Args>(args)...));
}


