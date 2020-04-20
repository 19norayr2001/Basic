#pragma once
#include "Expression.h"
#include <unordered_map>
class Postfix :public Expression
{
public:
	Postfix();
	Postfix(const std::string&);
	Postfix(const Postfix&);
	Postfix& operator=(const Postfix&);
	virtual ~Postfix();
public:
	virtual int Calculate(std::unordered_map<std::string, int>&) const;
	friend std::ostream& operator<<(std::ostream&, const Postfix&);
private:
	void Allocate(const Postfix&);
	void Deallocate();
private:
	std::vector<Symbol*> m_postfix;
};

