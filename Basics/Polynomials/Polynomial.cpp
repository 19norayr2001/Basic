#include "Polynomial.h"

Polynomial::Polynomial()
	:m_head(new Node)
{}

Polynomial::Polynomial(const std::vector<std::pair<int, int>>& vec)
	:m_head(new Node)
{
	int len = vec.size();
	Node* ptr = m_head;
	for (int i = 0; i < len; ++i)
	{
		ptr->next = new Node(vec[i].first, vec[i].second);
		ptr = ptr->next;
	}
}

Polynomial::Polynomial(const Polynomial& obj)
	:m_head(nullptr)
{
	Allocate(obj);
}

Polynomial& Polynomial::operator=(const Polynomial& obj)
{
	if (this != &obj)
	{
		Deallocate();
		Allocate(obj);
	}
	return *this;
}

Polynomial::~Polynomial()
{
	Deallocate();
}

Polynomial& Polynomial::operator+=(const Polynomial& obj)
{
	Node* ptr = this->m_head;
	Node* objptr = obj.m_head->next;
	while (objptr != nullptr)
	{
		while (ptr->next != nullptr && ptr->next->pow < objptr->pow)
		{
			ptr = ptr->next;
		}
		if (ptr->next == nullptr || ptr->next->pow > objptr->pow)
		{
			Node* nx = ptr->next;
			ptr->next = new Node(objptr->pow, objptr->coefficient);
		}
		else
		{
			ptr->next->coefficient += objptr->coefficient;
			if (ptr->next->coefficient == 0)
			{
				Node* nx = ptr->next->next;
				delete ptr->next;
				ptr->next = nx;
			}
		}
		objptr = objptr->next;
	}
	return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& obj)
{
	Node* objptr = obj.m_head->next;
	Polynomial ret;
	while (objptr != nullptr)
	{
		Polynomial plus;
		Node* ptr = this->m_head->next;
		Node* plusptr = plus.m_head;
		while (ptr != nullptr)
		{
			plusptr->next = new Node(ptr->pow + objptr->pow, ptr->coefficient*objptr->coefficient);
			ptr = ptr->next;
			plusptr = plusptr->next;
		}
		ret += plus;
		objptr = objptr->next;
	}
	return *this = ret;
}

Polynomial& Polynomial::Derivative()
{
	Node* ptr = m_head;
	while (ptr->next != nullptr)
	{
		if (ptr->next->pow == 0)
		{
			Node* nx = ptr->next->next;
			delete ptr->next;
			ptr->next = nx;
			continue;
		}
		ptr->next->coefficient *= ptr->next->pow;
		ptr->next->pow--;
		ptr = ptr->next;
	}
	return *this;
}

int Polynomial::Calculate(int x0)
{
	int res = 0, lastpow = 0, powx = 1;
	Node* ptr = m_head;
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

void Polynomial::Deallocate()
{
	Node* ptr = m_head;
	while (ptr != nullptr)
	{
		Node* del = ptr;
		ptr = ptr->next;
		delete del;
	}
	m_head = nullptr;
}

void Polynomial::Allocate(const Polynomial& obj)
{
	m_head = new Node;
	Node* ptr = m_head;
	Node* objptr = obj.m_head->next;
	while (objptr != nullptr)
	{
		ptr->next = new Node(objptr->pow, objptr->coefficient);
		ptr = ptr->next;
		objptr = objptr->next;
	}
}

Polynomial operator+(Polynomial obj1, const Polynomial& obj2)
{
	return obj1 += obj2;
}

Polynomial operator*(Polynomial obj1, const Polynomial& obj2)
{
	return obj1 *= obj2;
}

std::ostream& operator<<(std::ostream& print, const Polynomial& obj)
{
	Node* ptr = obj.m_head->next;
	while (ptr != nullptr)
	{
		print << "(" << ptr->coefficient << ")x" << "^" << ptr->pow;
		ptr = ptr->next;
		print << (ptr != nullptr ? "+" : "\n") << std::flush;
	}
	return print;
}