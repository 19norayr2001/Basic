#pragma once
#include <iostream>
#include <vector>
struct Node
{
	int pow;
	int coefficient;
	Node* next;
	Node(int p = 0, int c = 0)
		: pow(p)
		, coefficient(c)
		, next(nullptr)
	{}
};
class Polynomial
{
	friend std::ostream& operator<<(std::ostream&, const Polynomial&);
public:
	Polynomial();
	Polynomial(const std::vector<std::pair<int, int>>&);
	Polynomial(const Polynomial&);
	Polynomial& operator=(const Polynomial&);
	~Polynomial();
	Polynomial& operator+=(const Polynomial&);
	Polynomial& operator*=(const Polynomial&);
	Polynomial& Derivative();
	int Calculate(int x0);
private:
	void Deallocate();
	void Allocate(const Polynomial&);
private:
	Node* m_head;
};
Polynomial operator+(Polynomial, const Polynomial&);
Polynomial operator*(Polynomial, const Polynomial&);

