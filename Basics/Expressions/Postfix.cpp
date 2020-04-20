#include "Postfix.h"
#include <stack>
#include <iostream>
Postfix::Postfix()
{}

Postfix::Postfix(const std::string& s)
	:Expression(s)
{
	ToPostfix(m_postfix);
}

Postfix::Postfix(const Postfix& obj)
{
	Allocate(obj);
}

Postfix& Postfix::operator=(const Postfix& obj)
{
	if (this != &obj)
	{
		Deallocate();
		Allocate(obj);
	}
	return *this;
}

Postfix::~Postfix()
{
	Deallocate();
}

int Postfix::Calculate(std::unordered_map<std::string, int>& mp) const
{
	int sz = m_postfix.size();
	std::stack<int> st;
	for (int i = 0; i < sz; ++i)
	{
		if (dynamic_cast<Number*>(m_postfix[i]) != nullptr)
		{
			st.push(StringToInteger(m_postfix[i]->info));
		}
		else if (dynamic_cast<Identificator*>(m_postfix[i]) != nullptr)
		{
			st.push(mp[m_postfix[i]->info]);
		}
		else
		{
			int num2 = st.top(); st.pop();
			int num1 = st.top(); st.pop();
			st.push(CalculateOption(num1, num2, m_postfix[i]->info[0]));
		}
	}
	return st.top();
}

void Postfix::Allocate(const Postfix& obj)
{
	AllocateVector(m_infix, obj.m_infix);
	AllocateVector(m_postfix, obj.m_postfix);
}

void Postfix::Deallocate()
{
	DeallocateVector(m_infix);
	m_postfix.clear();
}

std::ostream& operator<<(std::ostream& print, const Postfix& obj)
{
	for (auto smb : obj.m_postfix)
	{
		print << smb->info << " ";
	}
	print << std::endl;
	return print;
}