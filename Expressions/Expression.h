#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <string>

struct Symbol
{
	explicit Symbol(std::string s)
		:info(std::move(s))
	{}
	std::string info;
	virtual ~Symbol() = default;
};
struct Option : Symbol
{
	explicit Option(std::string s)
		:Symbol(std::move(s))
	{}
	~Option() override = default;
};
struct Number : Symbol
{
	explicit Number(std::string s)
		:Symbol(std::move(s))
	{}
	~Number() override = default;
};
struct Identifier : Symbol
{
	explicit Identifier(std::string s)
		:Symbol(std::move(s))
	{}
	~Identifier() override = default;
};
struct OpenBracket :Symbol
{
	explicit OpenBracket(std::string s)
		:Symbol(std::move(s))
	{}
	~OpenBracket() override = default;
};
struct CloseBracket :Symbol
{
	explicit CloseBracket(std::string s)
		:Symbol(std::move(s))
	{}
	~CloseBracket() override = default;
};


class SymbolFactory {
public:
	static Symbol* createInstance(const std::string&);
};

class Expression
{
public:
	Expression();
	explicit Expression(const std::string&);
	Expression(const Expression&);
	Expression& operator=(const Expression&);
	virtual ~Expression();
public:
	virtual int Calculate(std::unordered_map<std::string, int>&) const = 0;
private:
	void Deallocate();
	void Allocate(const Expression&);
protected:
	static int StringToInteger(const std::string&);
	static int Priority(char);
	static int CalculateOption(int, int, char);
protected:
	void AllocateVector(std::vector<Symbol*>&,const std::vector<Symbol*>&);
	void DeallocateVector(std::vector<Symbol*>&);
protected:
	void ToPostfix(std::vector<Symbol*>&, bool = true);
protected:
	std::vector<Symbol*> m_infix;
};

#endif // EXPRESSION_H