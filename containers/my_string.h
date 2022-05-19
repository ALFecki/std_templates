#pragma once

#include <cassert>
#include <stdlib.h>
#include <string>

#define DLL_EXPORT __declspec(dllexport)


class DLL_EXPORT String
{
private:
	char* data;
	size_t length;


public:

	char* getData()
	{
		return data;
	}

	std::string getStr()
	{
		if (data == nullptr)
			return "";
		return std::string(data);
	}

	size_t getLength()
	{
		return length;
	}

	String()
	{
		data = nullptr;
		length = 0;
	}

	String(const char* new_data)
	{
		length = str_len(new_data);
		data = new char[length + 1];
		str_ncpy(data, new_data, length + 1);
	}

	String(size_t size)
	{
		length = size;
		data = new char[length + 1];
	}

	String(const String& new_data)
	{
		length = new_data.length;
		data = new char[length + 1];
		str_cpy(data, new_data.data);
	}

	void* mem_cpy(void* s1, const void* s2, size_t count);
	void* mem_move(void* s1, const void* s2, size_t count);
	void* mem_set(void* s, int new_data, size_t count);
	int mem_cmp(const void* s1, const void* s2, size_t count);
	char* str_cpy(char* s1, const char* s2);
	char* str_ncpy(char* s1, const char* s2, size_t count);
	char* str_cat(char* s1, const char* s2);
	char* str_ncat(char* s1, const char* s2, size_t count);
	int str_cmp(const char* s1, const char* s2);
	int str_ncmp(const char* s1, const char* s2, size_t count);
	int str_coll(const char* s1, const char* s2);
	size_t str_xfrm(char*, const char*, size_t);
	size_t str_len() const;
	size_t str_len(const char* s) const;
	void resize(size_t new_size);
	void clear();
	void push_back(char new_data);
	void push_back(size_t count, char new_data);
	void push_back(const char* new_data);
	void push_back(const char* new_data, size_t count);
	void push_back(const String& new_data);
	void push_back(const String& new_data, size_t count);
	void pop_back();
	void erase(size_t index, size_t count = 1);
	char& operator[](size_t index);
	char operator[](size_t index) const;
	bool operator==(String other);
	bool operator==(const char* other);
	bool operator!=(String other);
	bool operator!=(const char* other);
	void operator=(String other);
	String& operator+=(String& other);
	String& operator+=(char other);
	String& operator+(const char* other);
	char* str_chr(const char*, int);
	char* str_tok(char*, const char*);
};