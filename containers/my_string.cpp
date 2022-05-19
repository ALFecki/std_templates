#include "pch.h"
#include "my_string.h"

void* String::mem_cpy(void* s1, const void* s2, size_t count)
{
	assert(s1);
	assert(s2);
	char* p1 = (char*)s1;
	const char* p2 = (const char*)s2;
	while (count--)
	{
		*p1 = *p2;
		p1++;
		p2++;
	}
	return s1;
}

void* String::mem_move(void* s1, const void* s2, size_t count)
{
	void* ret = s1;
	if (s1 <= s2 || (char*)s1 >= ((char*)s2 + count))
	{
		while (count--)
		{
			*(char*)s1 = *(char*)s2;
			s1 = (char*)s1 + 1;
			s2 = (char*)s2 + 1;
		}
	}
	else
	{
		s1 = (char*)s1 + count - 1;
		s2 = (char*)s2 + count - 1;
		while (count--)
		{
			*(char*)s1 = *(char*)s2;
			s1 = (char*)s1 - 1;
			s2 = (char*)s2 - 1;
		}
	}
	return(ret);
}

void* String::mem_set(void* s, int new_data, size_t count)
{
	assert(s);
	char* p = static_cast<char*>(s);
	while (count--)
	{
		*p = static_cast<char>(new_data);
		p++;
	}
	return s;
}

int String::mem_cmp(const void* s1, const void* s2, size_t count)
{
	assert(s1);
	assert(s2);
	const char* p1 = (const char*)s1;
	const char* p2 = (const char*)s2;
	while (count--)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		p1++;
		p2++;
	}
	return 0;
}

char* String::str_cpy(char* s1, const char* s2)
{
	assert(s1);
	assert(s2);
	char* p1 = s1;
	const char* p2 = s2;
	while (*p2)
	{
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

char* String::str_ncpy(char* s1, const char* s2, size_t count)
{
	assert(s1);
	assert(s2);
	char* p1 = s1;
	const char* p2 = s2;
	while (count--)
	{
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

char* String::str_cat(char* s1, const char* s2)
{
	assert(s1);
	assert(s2);
	char* p1 = s1;
	while (*p1)
		p1++;
	const char* p2 = s2;
	while (*p2)
	{
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

char* String::str_ncat(char* s1, const char* s2, size_t count)
{
	assert(s1);
	assert(s2);
	char* p1 = s1;
	while (*p1)
		p1++;
	const char* p2 = s2;
	while (count--)
	{
		*p1 = *p2;
		p1++;
		p2++;
	}
	*p1 = '\0';
	return s1;
}

int String::str_cmp(const char* s1, const char* s2)
{
	assert(s1);
	assert(s2);
	const char* p1 = s1;
	const char* p2 = s2;
	while (*p1 && *p2)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}

int String::str_ncmp(const char* s1, const char* s2, size_t count)
{
	assert(s1);
	assert(s2);
	const char* p1 = s1;
	const char* p2 = s2;
	while (count-- && *p1 && *p2)
	{
		if (*p1 != *p2)
		{

			return (*p1 - *p2);
		}
		p1++;
		p2++;
	}
	return 0;
}

int String::str_coll(const char* s1, const char* s2)
{
	return strcoll(s1, s2);
}

char* String::str_chr(const char* s, int c)
{
	assert(s);
	const char* p = s;
	while (*p)
	{
		if (*p == c)
			return (char*)p;
		p++;
	}
	return NULL;
}

char* String::str_tok(char* s, const char* delim)
{
	assert(s);
	assert(delim);
	char* p = s;
	while (*p && !str_chr(delim, *p))
		p++;
	if (*p)
	{
		*p = '\0';
		p++;
	}
	return p;
}

size_t String::str_len() const
{
	auto p1 = this->data;
	auto p2 = this->data + this->length;
	size_t count = 0;
	while (p1 != p2)
	{
		count++;
		p1++;
	}
	return count;
}

size_t String::str_len(const char* s) const
{
	auto p = s;
	size_t count = 0;
	while (*p)
	{
		count++;
		p++;
	}
	return count;
}
size_t String::str_xfrm(char* s1, const char* s2, size_t n)
{
	return strxfrm(s1, s2, n);
}

void String::resize(size_t new_size)
{
	if (new_size > this->length)
	{
		this->length = new_size;
		this->data = (char*)realloc(this->data, this->length);
	}
	else
	{
		this->length = new_size;
	}
}

void String::clear()
{
	this->length = 0;
	this->data = nullptr;
}

void String::push_back(char new_data)
{
	this->resize(this->length + 1);
	this->data[this->length - 1] = new_data;
	data[length] = '\0';
}

void String::push_back(size_t count, char new_data)
{
	this->resize(this->length + count + 1);
	for (size_t i = 0; i < count; i++)
	{
		this->data[this->length - 1 - i] = new_data;
	}
	data[length] = '\0';
}

void String::push_back(const char* new_data)
{
	this->resize(this->length + str_len(new_data));
	str_cpy(this->data + this->length - str_len(new_data), new_data);
}

void String::push_back(const char* new_data, size_t count)
{
	this->resize(this->length + count);
	str_ncpy(this->data + this->length - count, new_data, count);
}

void String::push_back(const String& new_data)
{
	this->resize(this->length + new_data.length);
	str_cpy(this->data + this->length - new_data.length, new_data.data);
}

void String::push_back(const String& new_data, size_t count)
{
	this->resize(this->length + count);
	str_ncpy(this->data + this->length - count, new_data.data, count);
}

void String::pop_back()
{
	this->resize(this->length - 1);
}

void String::erase(size_t index, size_t count)
{
	if (index + count > this->length)
		return;
	for (size_t i = index; i < this->length - count; i++)
	{
		this->data[i] = this->data[i + count];
	}
	this->resize(this->length - count);

}

char& String::operator[](size_t index)
{
	return data[index];
}

char String::operator[](size_t index) const
{
	return data[index];
}



bool String::operator==(String other)
{
	return this->data == other.data;
}

bool String::operator==(const char* other)
{
	return this->data == other;
}

bool String::operator!=(String other)
{
	return this->data != other.data;
}

bool String::operator!=(const char* other)
{
	return this->data != other;
}



void String::operator=(String other)
{
	this->resize(other.length);
	this->str_cpy(this->data, (const char*)other.data);
}

String& String::operator+=(String& other)
{
	this->resize(this->length + other.length);
	str_cat(this->data, other.data);
	return *this;
}

String& String::operator+=(char other)
{
	this->resize(this->length + 1);
	this->data[this->length - 1] = other;
	data[length] = '\0';
	return *this;
}

String& String::operator+(const char* other)
{
	this->resize(this->length + str_len(other));
	str_cat(this->data, other);
	return *this;
}

