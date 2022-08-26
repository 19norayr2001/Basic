#ifndef PREFIX_H
#define PREFIX_H

#include "Expression.h"
#include <unordered_map>
class Prefix :public Expression
{
public:
	Prefix() = default;
	explicit Prefix(const std::string&);
	Prefix(const Prefix&);
	Prefix& operator=(const Prefix&);
	~Prefix() override;
public:
	int Calculate(std::unordered_map<std::string, int>&) const override;
	friend std::ostream& operator<<(std::ostream&, const Prefix&);
private:
	void Allocate(const Prefix&);
	void Deallocate();
private:
	void SwapBrackets();
private:
	std::vector<Symbol*> m_prefix;
};

#endif // PREFIX_H