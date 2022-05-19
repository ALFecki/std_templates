#pragma once


template<class T1, class T2>
class Pair
{
private:
	T1 first;
	T2 second;
	
public:
	
	Pair() : first(), second() {}
	Pair(const T1& first_, const T2& second_) : first(first_), second(second_) {}
	Pair(Pair&& new_pair) : first(std::move(new_pair.first)), second(std::move(new_pair.second)) {}
	
	template<class U1, class U2>
	Pair(const Pair<U1, U2>& new_pair) : first(new_pair.first), second(new_pair.second) {}
	Pair(const Pair<U1, U2>&& new_pair) : first(std::move(new_pair.first)), second(std::move(new_pair.second)) {}
	
	Pair& operator=(Pair&& new_pair)
	{
		first = std::move(new_pair.first);
		second = std::move(new_pair.second);
		return *this;
	}

	template <class U1, class U2>
	Pair& operator=(Pair<U1, U2>&& new_pair)
	{
		first = std::move(new_pair.first);
		second = std::move(new_pair.second);
		return *this;
	}
	
	void swap(Pair&& new_pair)
	{
		auto temp = new_pair;
		new_pair.first = std::move(first);
		new_pair.second = std::move(second);
		first = std::move(temp.first);
		second = std::move(temp.second);
	}
};
