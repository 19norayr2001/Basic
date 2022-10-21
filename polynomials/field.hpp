#ifndef FIELD_H
#define FIELD_H

#include <iostream>
#include <type_traits>
#include "divided_by_zero_exception.hpp"

template<int mod, typename T>
class Field;

template<int mod, typename T>
std::istream& operator>>(std::istream&, Field<mod, T>&);

template<int mod, typename T = int>
class Field {
public:
    using integer_type = T;

    friend std::istream& operator>><mod, integer_type>(std::istream&, Field<mod, T>&);

public:
    Field(integer_type value = 0)
            : _value((value % mod + mod) % mod) {
    }

    Field<mod, T>& operator=(const Field<mod, T>&);

    Field<mod, T>& operator*=(const Field<mod, T>&);

    Field<mod, T>& operator/=(const Field<mod, T>&);

    Field<mod, T>& operator%=(const Field<mod, T>&);

    Field<mod, T>& operator+=(const Field<mod, T>&);

    Field<mod, T>& operator-=(const Field<mod, T>&);

    bool operator==(const Field<mod, T>&) const;

    bool operator<(const Field<mod, T>&) const;

    Field<mod, T> pow(integer_type) const;

    explicit operator integer_type() const;

public:
    static Field<mod, T> factorial(integer_type);

    static Field<mod, T> C(integer_type, integer_type);

private:
    static Field<mod, T> binpow(const Field<mod, T>&, integer_type);

private:
    static constexpr bool checkMod();

    static_assert(checkMod(), "Mod must be a prime number");
private:
    integer_type _value;
};

template<int mod, typename T>
Field<mod, T> operator*(Field<mod, T>, const Field<mod, T>&);

template<int mod, typename T>
Field<mod, T> operator/(Field<mod, T>, const Field<mod, T>&);

template<int mod, typename T>
Field<mod, T> operator%(Field<mod, T>, const Field<mod, T>&);

template<int mod, typename T>
Field<mod, T> operator+(Field<mod, T>, const Field<mod, T>&);

template<int mod, typename T>
Field<mod, T> operator-(Field<mod, T>, const Field<mod, T>&);

template<int mod, typename T>
Field<mod, T> operator-(const Field<mod, T>&);

template<int mod, typename T>
bool operator>=(const Field<mod, T>&, const Field<mod, T>&);

template<int mod, typename T>
bool operator>(const Field<mod, T>&, const Field<mod, T>&);

template<int mod, typename T>
bool operator<=(const Field<mod, T>&, const Field<mod, T>&);

template<int mod, typename T>
bool operator!=(const Field<mod, T>&, const Field<mod, T>&);

template<int mod, typename T>
std::ostream& operator<<(std::ostream& out, const Field<mod, T>& num) {
    typename Field<mod, T>::integer_type value(num);
    return out << value;
}

template<int mod, typename T>
std::istream& operator>>(std::istream& in, Field<mod, T>& num) {
    in >> num._value;
    return in;
}

template<int mod, typename T>
Field<mod, T>& Field<mod, T>::operator=(const Field<mod, T>& num) {
    if (this != &num) {
        this->_value = num._value;
    }
    return *this;
}

template<int mod, typename T>
Field<mod, T>& Field<mod, T>::operator*=(const Field<mod, T>& num) {
    this->_value *= num._value;
    this->_value %= mod;
    return *this;
}

template<int mod, typename T>
Field<mod, T>& Field<mod, T>::operator/=(const Field<mod, T>& num) {
    if (num == 0) {
        throw DividedByZeroException();
    }
    return *this *= (num.pow(mod - 2));
}

template<int mod, typename T>
Field<mod, T>& Field<mod, T>::operator%=(const Field<mod, T>& num) {
    if (num == 0) {
        throw DividedByZeroException();
    }
    this->_value %= num._value;
    return *this;
}

template<int mod, typename T>
Field<mod, T>& Field<mod, T>::operator+=(const Field<mod, T>& num) {
    this->_value += num._value;
    this->_value %= mod;
    return *this;
}

template<int mod, typename T>
Field<mod, T>& Field<mod, T>::operator-=(const Field<mod, T>& num) {
    this->_value += (mod - num._value);
    this->_value %= mod;
    return *this;
}

template<int mod, typename T>
Field<mod, T> Field<mod, T>::pow(integer_type num) const {
    return binpow(*this, num);
}

template<int mod, typename T>
bool Field<mod, T>::operator==(const Field<mod, T>& num) const {
    return this->_value == num._value;
}

template<int mod, typename T>
bool Field<mod, T>::operator<(const Field<mod, T>& num) const {
    return this->_value < num._value;
}

template<int mod, typename T>
Field<mod, T> operator*(Field<mod, T> num1, const Field<mod, T>& num2) {
    return num1 *= num2;
}

template<int mod, typename T>
Field<mod, T> operator/(Field<mod, T> num1, const Field<mod, T>& num2) {
    return num1 /= num2;
}

template<int mod, typename T>
Field<mod, T> operator%(Field<mod, T> num1, const Field<mod, T>& num2) {
    return num1 %= num2;
}

template<int mod, typename T>
Field<mod, T> operator+(Field<mod, T> num1, const Field<mod, T>& num2) {
    return num1 += num2;
}

template<int mod, typename T>
Field<mod, T> operator-(Field<mod, T> num1, const Field<mod, T>& num2) {
    return num1 -= num2;
}

template<int mod, typename T>
Field<mod, T> operator-(const Field<mod, T>& num2) {
    return Field<mod, T>(0) -= num2;
}

template<int mod, typename T>
bool operator>=(const Field<mod, T>& num1, const Field<mod, T>& num2) {
    return !(num1 < num2);
}

template<int mod, typename T>
bool operator>(const Field<mod, T>& num1, const Field<mod, T>& num2) {
    return !(num1 < num2 || num1 == num2);
}

template<int mod, typename T>
bool operator<=(const Field<mod, T>& num1, const Field<mod, T>& num2) {
    return (num1 < num2 || num1 == num2);
}

template<int mod, typename T>
bool operator!=(const Field<mod, T>& num1, const Field<mod, T>& num2) {
    return !(num1 == num2);
}

template<int mod, typename T>
Field<mod, T>::operator integer_type() const {
    return this->_value;
}

template<int mod, typename T>
Field<mod, T> Field<mod, T>::factorial(integer_type n) {
    static std::vector<Field<mod, T>> fact{1, 1};
    if (n < fact.size())
        return fact[n];
    for (size_t i = fact.size(); i <= n; ++i)
        fact.push_back(Field<mod, T>(i) * fact[i - 1]);
    return fact[n];
}

template<int mod, typename T>
Field<mod, T> Field<mod, T>::C(integer_type n, integer_type k) {
    return Field<mod, T>::factorial(n) / Field<mod, T>::factorial(k) / Field<mod, T>::factorial(n - k);
}

template<int mod, typename T>
Field<mod, T> Field<mod, T>::binpow(const Field<mod, T>& a, integer_type n) {
    if (n == 0) return 1;
    if (n % 2 == 1) return binpow(a, n - 1) * a;
    else {
        Field<mod, T> b = binpow(a, n / 2);
        return b * b;
    }
}

template<int mod, typename T>
constexpr bool Field<mod, T>::checkMod() {
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

#endif // FIELD_H