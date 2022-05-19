#pragma once

#include "shared_ptr.h"

template <typename Type>
class My_shared_ptr;



template <typename Type>
class My_weak_ptr
{

private:

	CBlock* c_block_ptr = nullptr;
	Type* object_ptr;

public:

	My_weak_ptr() {}

	My_weak_ptr(My_shared_ptr<Type> new_p)
	{
		c_block_ptr = new_p.c_block_ptr;
		(*(c_block_ptr->weak_count))++;
		object_ptr = new_p.object_ptr;
	}

	My_weak_ptr(const My_weak_ptr<Type>& new_ptr)
		: c_block_ptr(new_ptr.c_block_ptr), object_ptr(new_ptr.object_ptr)
	{
		(*(c_block_ptr->weak_count))++;
	}


	bool expired() const
	{
		return *(c_block_ptr->shared_count) == 0;
	}

	My_shared_ptr<Type> lock() const
	{
		if (expired())
		{
			return My_shared_ptr<Type>();
		}
		else return My_shared_ptr<Type>(*this);
	}

	My_weak_ptr operator=(const My_weak_ptr& new_ptr)
	{
		c_block_ptr = new_ptr.c_block_ptr;
		object_ptr = new_ptr.object_ptr;
		(*(c_block_ptr->weak_count))++;
		return *this;
	}

	~My_weak_ptr()
	{
		if (!c_block_ptr) return;
		(*(c_block_ptr->weak_count))--;
		if (*(c_block_ptr->weak_count) == 0 && *(c_block_ptr->shared_count) == 0)
		{
			delete c_block_ptr;
		}
	}

<<<<<<< HEAD
=======
	Type* get()
	{
		return object_ptr;
	}

>>>>>>> main
	friend class My_shared_ptr<Type>;
};