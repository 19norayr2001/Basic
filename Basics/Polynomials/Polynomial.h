#pragma once
#include <iostream>
#include <utility>
#include <vector>
template<typename T>
struct Node
{
	int pow;
	T coefficient;
	Node<T>* next;
	Node<T>(int p = 0, T c = T(0))
		: pow(p)
		, coefficient(c)
		, next(nullptr)
	{}
};
template<typename T>
class Polynomial
{
	template<typename T>
	friend std::ostream& operator<<(std::ostream&, const Polynomial<T>&);
public:
	Polynomial();
	Polynomial(const std::vector<std::pair<int, T>>&);
	Polynomial(const Polynomial<T>&);
	Polynomial<T>& operator=(const Polynomial<T>&);
	~Polynomial();
	Polynomial<T>& operator+=(const Polynomial<T>&);
	Polynomial<T>& operator*=(const Polynomial<T>&);
	template<typename U>
	auto calculate(U) ->decltype(std::declval<T>() * std::declval<U>());
private:
	void deallocate();
	void allocate(const Polynomial<T>&);
private:
	Node<T>* m_head;
};
template<typename T>
Polynomial<T> operator+(Polynomial<T>, const Polynomial<T>&);
template<typename T>
Polynomial<T> operator*(Polynomial<T>, const Polynomial<T>&);

template<typename T>
Polynomial<T>::Polynomial()
	:m_head(new Node<T>)
{}

template<typename T>
Polynomial<T>::Polynomial(const std::vector<std::pair<int, T>>& vec)
	: m_head(new Node<T>) 
{
	size_t len = vec.size();
	Node<T>* ptr = m_head;
	for (size_t i = 0; i < len; ++i) {
		ptr->next = new Node<T>(vec[i].first, vec[i].second);
		ptr = ptr->next;
	}
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& obj)
	:m_head(nullptr)
{
	allocate(obj);
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& obj) {
	if (this != &obj) {
		deallocate();
		allocate(obj);
	}
	return *this;
}

template<typename T>
Polynomial<T>::~Polynomial() {
	deallocate();
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& obj) {
	Node<T>* ptr = this->m_head;
	Node<T>* objptr = obj.m_head->next;
	while (objptr != nullptr) {
		while (ptr->next != nullptr && ptr->next->pow < objptr->pow) {
			ptr = ptr->next;
		}
		if (ptr->next == nullptr || ptr->next->pow > objptr->pow) {
			Node<T>* nx = ptr->next;
			ptr->next = new Node<T>(objptr->pow, objptr->coefficient);
		}
		else {
			ptr->next->coefficient += objptr->coefficient;
			if (ptr->next->coefficient == 0) {
				Node<T>* nx = ptr->next->next;
				delete ptr->next;
				ptr->next = nx;
			}
		}
		objptr = objptr->next;
	}
	return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& obj) {
	Node<T>* objptr = obj.m_head->next;
	Polynomial ret;
	while (objptr != nullptr) {
		Polynomial plus;
		Node<T>* ptr = this->m_head->next;
		Node<T>* plusptr = plus.m_head;
		while (ptr != nullptr) {
			plusptr->next = new Node<T>(ptr->pow + objptr->pow, ptr->coefficient * objptr->coefficient);
			ptr = ptr->next;
			plusptr = plusptr->next;
		}
		ret += plus;
		objptr = objptr->next;
	}
	return *this = ret;
}

template<typename T>
template<typename U>
auto Polynomial<T>::calculate(U x0) ->decltype(std::declval<T>() * std::declval<U>()) {
	decltype(std::declval<T>() * std::declval<U>()) res(0);
	U powx(1);
	int lastpow = 0;
	Node<T>* ptr = m_head;
	while (ptr->next != nullptr)
	{
		while (lastpow < ptr->next->pow)
		{
			powx *= x0;
			lastpow++;
		}
		res += powx * ptr->next->coefficient;
		ptr = ptr->next;
	}
	return res;
}

template<typename T>
void Polynomial<T>::deallocate() {
	Node<T>* ptr = m_head;
	while (ptr != nullptr) {
		Node<T>* del = ptr;
		ptr = ptr->next;
		delete del;
	}
	m_head = nullptr;
}

template<typename T>
void Polynomial<T>::allocate(const Polynomial<T>& obj) {
	m_head = new Node<T>;
	Node<T>* ptr = m_head;
	Node<T>* objptr = obj.m_head->next;
	while (objptr != nullptr) {
		ptr->next = new Node<T>(objptr->pow, objptr->coefficient);
		ptr = ptr->next;
		objptr = objptr->next;
	}
}

template<typename T>
Polynomial<T> operator+(Polynomial<T> obj1, const Polynomial<T>& obj2) {
	return obj1 += obj2;
}

template<typename T>
Polynomial<T> operator*(Polynomial<T> obj1, const Polynomial<T>& obj2) {
	return obj1 *= obj2;
}

template<typename T>
std::ostream& operator<<(std::ostream& print, const Polynomial<T>& obj) {
	Node<T>* ptr = obj.m_head->next;
	while (ptr != nullptr) {
		print << "(" << ptr->coefficient << ")x" << "^" << ptr->pow;
		ptr = ptr->next;
		print << (ptr != nullptr ? "+" : "\n") << std::flush;
	}
	return print;
}
