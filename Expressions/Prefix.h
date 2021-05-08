#pragma once
#include "Expression.h"
#include <unordered_map>
class Prefix :public Expression
{
public:
	Prefix();
	Prefix(const std::string&);
	Prefix(const Prefix&);
	Prefix& operator=(const Prefix&);
	virtual ~Prefix();
public:
	virtual int Calculate(std::unordered_map<std::string, int>&) const;
	friend std::ostream& operator<<(std::ostream&, const Prefix&);
private:
	void Allocate(const Prefix&);
	void Deallocate();
private:
	void SwapBrackets();
private:
	std::vector<Symbol*> m_prefix;
};

