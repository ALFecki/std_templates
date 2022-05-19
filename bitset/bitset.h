#pragma once
#include <cstring>
#include <iostream>

template <int N>
class Bitset {
private:

	unsigned long long bits[(N + 63) / 64];
	size_t size = (N + 63) / 64;

	void trim() {
		bool need_to_correct_last_element_bits = N == 0 || N % 64 != 0;
		if (need_to_correct_last_element_bits) {
			bits[size - 1] &= (1ULL << N % 64) - 1;
		}
	}

public:

	class reference {
	private:
		Bitset& ref;
		size_t pos;

	public:

		reference(Bitset& ref, size_t pos) : ref(ref), pos(pos) {}

		reference& operator=(bool value) {

			ref.set(pos, value);
			return *this;
		}

		reference& operator=(const reference& other) {
			ref.set(pos, other.ref.test(pos));
			return *this;
		}

		operator bool() const {
			return ref.test(pos);
		}

		reference& operator~()
		{
			ref.flip(pos);
			return *this;
		}

		reference& flip() {
			ref.flip(pos);
			return *this;
		}



	};

	Bitset() {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] = 0ULL;
		}
	}

	Bitset(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] = other.bits[i];
		}
	}

	Bitset(const char* str)
	{
		reset();
		size_t length = strlen(str);
		if (length > N)
		{
			length = N;
		}
		for (size_t i = 0; i < length; i++)
		{
			if (str[length - i - 1] == '1')
			{
				set(i);
			}
		}
	}

	Bitset(unsigned long long value)
	{
		reset();
		bits[0] = value;
		trim();
	}


	bool test(size_t num) {
		if (num >= N)
		{
			throw std::out_of_range("Out of range");
		}
		size_t index = num / 64;
		size_t offset = num % 64;
		return (bits[index] & (1ULL << offset)) != 0;
	}

	bool all() {
		if (N == 0)
		{
			return true;
		}
		bool padding = N % 64 == 0;
		for (size_t i = 0; i < size - 1 + padding; i++)
		{
			if (bits[i] != ~0ULL)
			{
				return false;
			}

		}
		return padding || bits[size - 1] == (1ULL << (N % 64)) - 1;
	}

	bool any() {
		for (size_t i = 0; i < size; i++)
		{
			if (bits[i] != 0ULL)
			{
				return true;
			}
		}
		return false;
	}

	bool none() {
		return !any();
	}

	size_t count() {
		size_t res = 0;
		for (size_t i = 0; i < size; i++)
		{
			res += __popcnt64(bits[i]);
		}
		return res;
	}

	size_t get_size() {
		return N;
	}

	Bitset& flip() {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] = ~bits[i];
		}
		trim();
		return *this;
	}

	Bitset& flip(size_t pos) {
		bits[pos / 64] ^= (1ULL << (pos % 64));
		return *this;
	}

	Bitset& set() {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] = ULLONG_MAX;
		}
		trim();
		return *this;
	}

	Bitset& set(size_t pos, bool value = true) {
		if (value)
		{
			bits[pos / 64] |= (1ULL << (pos % 64));
		}
		else
		{
			bits[pos / 64] &= ~(1ULL << (pos % 64));

		}
		return *this;
	}

	Bitset& reset() {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] = 0ULL;
		}
		return *this;
	}

	Bitset& reset(size_t pos) {
		bits[pos / 64] &= ~(1ULL << (pos % 64));
		return *this;
	}

	std::string to_string() {
		std::string res;
		res.reserve(N);
		for (size_t i = N; i > 0; )
		{
			i--;
			if (test(i))
			{
				res += '1';
			}
			else
			{
				res += '0';
			}
		}
		return res;
	}

	unsigned long long to_ullong() const {
		if (N == 0)
		{
			return 0;
		}
		if (N > 64)
		{
			for (size_t i = 1; i < size; i++)
			{
				if (bits[i] != 0ULL)
				{
					throw std::out_of_range("Out of range");
				}
			}

		}
		return bits[0];

	}


	unsigned long to_ulong() const {
		bool bits_zero = N == 0;
		bool bits_small = N <= 32;
		bool bits_large = N > 64;
		if (bits_zero)
		{
			return 0;
		}
		if (bits_small)
		{
			return static_cast<unsigned long>(bits[0]);
		}
		if (bits_large)
		{
			for (size_t i = 1; i < size; i++)
			{
				if (bits[i] != 0ULL)
				{
					throw std::out_of_range("Out of range");
				}
			}
		}
		return static_cast<unsigned long>(bits[0]);
	}

	reference operator[](size_t num) {
		if (num >= N)
		{
			throw std::out_of_range("Index out of range");
		}
		return reference(*this, num);
	}

	bool operator[](size_t num) const {
		if (num >= N)
		{
			throw std::out_of_range("Index out of range");
		}
		return bits[num / 64] & (1ULL << (num % 64));
	}

	bool operator==(const Bitset& oi) {
		if (N != oi.N)
		{
			return false;
		}
		for (size_t i = 0; i < size; i++)
		{
			if (bits[i] != oi.bits[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(const Bitset& oi) {
		return !(*this == oi);
	}

	Bitset operator~() {
		Bitset res(*this);
		res.flip();
		return res;
	}


	Bitset& operator&=(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] &= other.bits[i];
		}
		return *this;
	}

	Bitset& operator|=(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] |= other.bits[i];
		}
		return *this;
	}

	Bitset& operator^=(const Bitset& other) {
		for (size_t i = 0; i < size; i++)
		{
			bits[i] ^= other.bits[i];
		}
		return *this;
	}

	Bitset& cycle_(size_t pos)
	{
		for (size_t i = 0; i < size; i++)
		{

			if (this->test(size - 1))
			{
				bits[i] <<= (N % 64);
				this->set(0, 1);
			}
			else this->set(0, 0);
		}
	}
};


template <int N>
inline Bitset<N> operator&(const Bitset<N>& lhs, const Bitset<N>& rhs) {
	Bitset<N> res(lhs);
	res &= rhs;
	return res;
}


template <int N>
inline Bitset<N> operator|(const Bitset<N>& lhs, const Bitset<N>& rhs) {
	Bitset<N> res(lhs);
	res |= rhs;
	return res;
}


template <int N>
inline Bitset<N> operator^(const Bitset<N>& lhs, const Bitset<N>& rhs) {
	Bitset<N> res(lhs);
	res ^= rhs;
	return res;
}

