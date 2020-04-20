#pragma once
#include <unordered_map>
#include <vector>
#include <string>
struct Symbol
{
	Symbol(std::string s)
		:info(s)
	{}
	std::string info;
	virtual ~Symbol() {}
};
struct Option :Symbol
{
	Option(std::string s)
		:Symbol(s)
	{}
	virtual ~Option() {}
};
struct Number :Symbol
{
	Number(std::string s)
		:Symbol(s)
	{}
	virtual ~Number() {}
};
struct Identificator :Symbol
{
	Identificator(std::string s)
		:Symbol(s)
	{}
	virtual ~Identificator() {}
};
struct OpenBracket :Symbol
{
	OpenBracket(std::string s)
		:Symbol(s)
	{}
	virtual ~OpenBracket() {}
};
struct CloseBracket :Symbol
{
	CloseBracket(std::string s)
		:Symbol(s)
	{}
	virtual ~CloseBracket() {}
};
class Expression
{
public:
	Expression();
	Expression(const std::string&);
	Expression(const Expression&);
	Expression& operator=(const Expression&);
	virtual ~Expression();
public:
	virtual int Calculate(std::unordered_map<std::string, int>&) const = 0;
private:
	void Deallocate();
	void Allocate(const Expression&);
protected:
	int StringToInteger(const std::string) const;
	int Priority(char) const;
	int CalculateOption(int, int, char) const;
protected:
	void AllocateVector(std::vector<Symbol*>&,const std::vector<Symbol*>&);
	void DeallocateVector(std::vector<Symbol*>&);
protected:
	void ToPostfix(std::vector<Symbol*>&, bool = true);
private:
	void PushInfixSymbol(std::string&, char);
	void PushChar(std::string&, char, std::vector<Symbol*>&);
	void PushNum(std::string&, std::vector<Symbol*>&);
protected:
	std::vector<Symbol*> m_infix;
};