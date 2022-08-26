#include "expression.h"
#include <stdexcept>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>

namespace {
	bool isOption(char ch) {
		switch (ch)
		{
		case '-':
		case '+':
		case '*':
		case '/':
			return true;
		default:
			return false;
		}
	}

	bool isNumber(const std::string& s) {
		for (size_t i = 0; i < s.size(); ++i) {
			if (!isdigit(s[i])) {
				return false;
			}
		}
		return true;
	}
}

Symbol* SymbolFactory::createInstance(const std::string& s) {
	if (s == "(") {
		return new OpenBracket(s);
	}
	if (s == ")") {
		return new CloseBracket(s);
	}
	if (s.size() == 1 && isOption(s[0])) {
		return new Option(s);
	}
	if(isNumber(s)) {
		return new Number(s);
	}
	if (isalpha(s[0])) {
		return new Identifier(s);
	}
	throw std::invalid_argument("Invalid expression input");
}

Expression::Expression()
{}

Expression::Expression(const std::string& s)
{
	std::string str;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (isspace(s[i])) {
			continue;
		}
		if (isOption(s[i]) || s[i] == '(' || s[i] == ')') {
			if (str != "") {
				m_infix.push_back(SymbolFactory::createInstance(str));
			}
			str = s[i];
			m_infix.push_back(SymbolFactory::createInstance(str));
			str = "";
			continue;
		}
		str += s[i];
	}
	if (str != "") {
		m_infix.push_back(SymbolFactory::createInstance(str));
	}
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

int Expression::Priority(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	else if (ch == '*' || ch == '/')
		return 2;
	else 
		return 0;
}

int Expression::CalculateOption(int num1, int num2, char ch)
{
	using std::string_literals::operator""s;
	switch (ch)
	{
	case '*':
		return num1 * num2;
	case '/':
		return num1 / num2;
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	default:
		throw std::invalid_argument("Not compatible operation "s + ch);
	}
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
	for (size_t i = 0; i < copy_vec.size(); ++i)
	{
		alloc_vec.push_back(SymbolFactory::createInstance(copy_vec[i]->info));
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
	size_t sz = m_infix.size();
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
