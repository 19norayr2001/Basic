#include "Expression.h"
#include <cctype>
#include <stack>

Expression::Expression()
{}

Expression::Expression(const std::string& s)
{
	int sz = s.size();
	std::string smb;
	for (int i = 0; i < sz; ++i)
	{
		PushInfixSymbol(smb, s[i]);
	}
	PushNum(smb, m_infix);
}

Expression::Expression(const Expression& obj)
{
	Allocate(obj);
}

Expression& Expression::operator=(const Expression& obj)
{
	if (this != &obj)
	{
		Deallocate();
		Allocate(obj);
	}
	return *this;
}

Expression::~Expression()
{
	Deallocate();
}

int Expression::StringToInteger(const std::string s) const
{
	int result = 0;
	int ten_pow = 1;
	int sz = s.size();
	for (int i = sz - 1; i >= 0; --i)
	{
		result += (s[i] - '0') * ten_pow;
		ten_pow *= 10;
	}
	return result;
}

int Expression::Priority(char ch) const
{
	if (ch == '+' || ch == '-')
		return 1;
	else if (ch == '*' || ch == '/')
		return 2;
	else 
		return 0;
}

int Expression::CalculateOption(int num1, int num2, char ch) const
{
	if (ch == '*')
		return num1 * num2;
	if (ch == '/')
		return num1 / num2;
	if (ch == '+')
		return num1 + num2;
	if (ch == '-')
		return num1 - num2;
}

void Expression::Allocate(const Expression& obj)
{
	AllocateVector(m_infix, obj.m_infix);
}

void Expression::Deallocate()
{
	DeallocateVector(m_infix);
}

void Expression::AllocateVector(std::vector<Symbol*>& alloc_vec,const std::vector<Symbol*>& copy_vec)
{
	int sz = copy_vec.size();
	for (int i = 0; i < sz; ++i)
	{
		PushChar(copy_vec[i]->info, copy_vec[i]->info[0], alloc_vec);
	}
}

void Expression::DeallocateVector(std::vector<Symbol*>& dealloc_vec)
{
	for (Symbol*& smb:dealloc_vec)
	{
		delete smb;
	}
	dealloc_vec.clear();
}

void Expression::ToPostfix(std::vector<Symbol*>& vec, bool postfix)
{
	std::stack<int> index;
	int sz = m_infix.size();
	for (int i = 0; i < sz; ++i)
	{
		Symbol* s = m_infix[i];
		if (isdigit(s->info[0]))
			vec.push_back(s);
		else if (isalpha(s->info[0]))
			vec.push_back(s);
		else if (s->info[0] == '(')
			index.push(i);
		else if (s->info[0] == ')')
		{
			while (dynamic_cast<OpenBracket*>(m_infix[index.top()]) == nullptr)
			{
				vec.push_back(m_infix[index.top()]);
				index.pop();
			}
			index.pop();
		}
		else
		{
			if (postfix)
			{
				while (!index.empty() && Priority(m_infix[index.top()]->info[0]) >= Priority(m_infix[i]->info[0]))
				{
					vec.push_back(m_infix[index.top()]);
					index.pop();
				}
			}
			else
			{
				while (!index.empty() && Priority(m_infix[index.top()]->info[0]) > Priority(m_infix[i]->info[0]))
				{
					vec.push_back(m_infix[index.top()]);
					index.pop();
				}
			}
			index.push(i);
		}
	}
	while (!index.empty())
	{
		vec.push_back(m_infix[index.top()]);
		index.pop();
	}
}

void Expression::PushInfixSymbol(std::string& smb, char ch)
{
	if (isdigit(ch))
		smb += ch;
	else if (isalpha(ch))
		smb += ch;
	else
	{
		PushChar(smb, ch, m_infix);
		smb = "";
	}
}

void Expression::PushChar(std::string& smb, char ch, std::vector<Symbol*>& alloc_vec)
{
	std::string pb;
	pb += ch;
	PushNum(smb, alloc_vec);
	if (pb == "(")
		alloc_vec.push_back(new OpenBracket(pb));
	else if (pb == ")")
		alloc_vec.push_back(new CloseBracket(pb));
	else
	{
		alloc_vec.push_back(new Option(pb));
	}
}
void Expression::PushNum(std::string& smb, std::vector<Symbol*>& alloc_vec)
{
	if (smb != "")
	{
		if (isdigit(smb[0]))
			alloc_vec.push_back(new Number(smb));
		else
			alloc_vec.push_back(new Identificator(smb));
	}
}