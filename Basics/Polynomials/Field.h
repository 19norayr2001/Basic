#pragma once
#include <iostream>
#include "DividedByZeroException.h"
typedef int Integer;

template<int mod>
class Field {
	template<int mod>
	friend std::ostream& operator<<(std::ostream&, const Field<mod>&);
	template<int mod>
	friend std::istream& operator>>(std::istream&, Field<mod>&);
public:
	Field(Integer x = 0)
		:value((x % mod + mod) % mod) {
	}
	Field<mod>& operator=(const Field<mod>&);
	Field<mod>& operator*=(const Field<mod>&);
	Field<mod>& operator/=(const Field<mod>&);
	Field<mod>& operator%=(const Field<mod>&);
	Field<mod>& operator+=(const Field<mod>&);
	Field<mod>& operator-=(const Field<mod>&);
	bool operator==(const Field<mod>&) const;
	bool operator<(const Field<mod>&) const;
	Field<mod> pow(Integer) const;
	explicit operator Integer() const;
public:
	static Field<mod> factorial(Integer);
	static Field<mod> C(Integer, Integer);
private:
	static Field<mod> binpow(const Field<mod>&, Integer);
private:
	static constexpr bool checkMod();
	static_assert(checkMod(), "Mod must be a prime number");
private:
	Integer value;
};

template<int mod>
Field<mod> operator*(Field<mod>, const Field<mod>&);
template<int mod>
Field<mod> operator/(Field<mod>, const Field<mod>&);
template<int mod>
Field<mod> operator%(Field<mod>, const Field<mod>&);
template<int mod>
Field<mod> operator+(Field<mod>, const Field<mod>&);
template<int mod>
Field<mod> operator-(Field<mod>, const Field<mod>&);
template<int mod>
Field<mod> operator-(const Field<mod>&);
template<int mod>
bool operator>=(const Field<mod>&, const Field<mod>&);
template<int mod>
bool operator>(const Field<mod>&, const Field<mod>&);
template<int mod>
bool operator<=(const Field<mod>&, const Field<mod>&);
template<int mod>
bool operator!=(const Field<mod>&, const Field<mod>&);

template<int mod>
std::ostream& operator<<(std::ostream& out, const Field<mod>& num) {
	out << num.value;
	return out;
}

template<int mod>
std::istream& operator>>(std::istream& in, Field<mod>& num) {
	in >> num.value;
	return in;
}

template<int mod>
Field<mod>& Field<mod>::operator=(const Field<mod>& num) {
	if (this != &num) {
		this->value = num.value;
	}
	return *this;
}

template<int mod>
Field<mod>& Field<mod>::operator*=(const Field<mod>& num) {
	this->value *= num.value;
	this->value %= mod;
	return *this;
}

template<int mod>
Field<mod>& Field<mod>::operator/=(const Field<mod>& num) {
	if (num == 0) {
		throw DividedByZeroException();
	}
	return *this *= (num.pow(mod - 2));
}

template<int mod>
Field<mod>& Field<mod>::operator%=(const Field<mod>& num) {
	if (num == 0) {
		throw DividedByZeroException();
	}
	this->value %= num.value;
	return *this;
}

template<int mod>
Field<mod>& Field<mod>::operator+=(const Field<mod>& num) {
	this->value += num.value;
	this->value %= mod;
	return *this;
}

template<int mod>
Field<mod>& Field<mod>::operator-=(const Field<mod>& num) {
	this->value += (mod - num.value);
	this->value %= mod;
	return *this;
}

template<int mod>
Field<mod> Field<mod>::pow(Integer num) const {
	return binpow(*this, num);
}

template<int mod>
bool Field<mod>::operator==(const Field<mod>& num) const {
	return this->value == num.value;
}

template<int mod>
bool Field<mod>::operator<(const Field<mod>& num) const {
	return this->value < num.value;
}

template<int mod>
Field<mod> operator*(Field<mod> num1, const Field<mod>& num2) {
	return num1 *= num2;
}

template<int mod>
Field<mod> operator/(Field<mod> num1, const Field<mod>& num2) {
	return num1 /= num2;
}

template<int mod>
Field<mod> operator%(Field<mod> num1, const Field<mod>& num2) {
	return num1 %= num2;
}

template<int mod>
Field<mod> operator+(Field<mod> num1, const Field<mod>& num2) {
	return num1 += num2;
}

template<int mod>
Field<mod> operator-(Field<mod> num1, const Field<mod>& num2) {
	return num1 -= num2;
}

template<int mod>
Field<mod> operator-(const Field<mod>& num2) {
	return Field<mod>(0) -= num2;
}
template<int mod>
bool operator>=(const Field<mod>& num1, const Field<mod>& num2) {
	return !(num1 < num2);
}

template<int mod>
bool operator>(const Field<mod>& num1, const Field<mod>& num2) {
	return !(num1 < num2 || num1 == num2);
}

template<int mod>
bool operator<=(const Field<mod>& num1, const Field<mod>& num2) {
	return (num1 < num2 || num1 == num2);
}

template<int mod>
bool operator!=(const Field<mod>& num1, const Field<mod>& num2) {
	return !(num1 == num2);
}

template<int mod>
Field<mod>::operator Integer() const {
	return this->value;
}

template<int mod>
Field<mod> Field<mod>::factorial(Integer n) {
	static std::vector<Field<mod>> fact{ 1, 1 };
	if (n < fact.size())
		return fact[n];
	for (size_t i = fact.size(); i <= n; ++i)
		fact.push_back(Field<mod>(i) * fact[i - 1]);
	return fact[n];
}

template<int mod>
Field<mod> Field<mod>::C(Integer n, Integer k) {
	return Field<mod>::factorial(n) / Field<mod>::factorial(k) / Field<mod>::factorial(n - k);
}

template<int mod>
Field<mod> Field<mod>::binpow(const Field<mod>& a, Integer n) {
	if (n == 0) return 1;
	if (n % 2 == 1) return binpow(a, n - 1) * a;
	else {
		Field<mod> b = binpow(a, n / 2);
		return b * b;
	}
}

template<int mod>
constexpr bool Field<mod>::checkMod() {
	for (int i = 2; i * i <= mod; ++i) {
		if (mod % i == 0) {
			return false;
		}
	}
	return true;
}

typedef Field<998244353> lll;
auto factorial = lll::factorial;
auto C = lll::C;