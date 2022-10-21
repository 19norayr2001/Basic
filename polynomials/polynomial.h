#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "divided_by_zero_exception.h"
#include <iostream>
#include <utility>
#include <vector>

template<typename T>
class Polynomial {
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Polynomial<U>&);

private:
    struct Node {
        int pow;
        T coefficient;
        Node* next;

        explicit Node(int p = 0, T c = T(0), Node* ptr = nullptr)
                : pow(p), coefficient(c), next(ptr) {}
    };

public:
    explicit Polynomial(T = T(0));

    explicit Polynomial(const std::vector<std::pair<int, T>>&);

    Polynomial(const Polynomial<T>&);

    Polynomial<T>& operator=(const Polynomial<T>&);

    ~Polynomial();

public:
    Polynomial<T>& operator+=(const Polynomial<T>&);

    Polynomial<T>& operator-=(const Polynomial<T>&);

    Polynomial<T>& operator*=(const Polynomial<T>&);

    Polynomial<T>& operator/=(const Polynomial<T>&);

    Polynomial<T>& operator%=(const Polynomial<T>&);

    Polynomial<T> operator-() const;

public:
    int degree() const { return _tail == _head ? -1 : _tail->pow; }

    bool isZero() const { return _tail == _head; }

    template<typename U>
    auto calculate(U) const -> decltype(std::declval<T>() * std::declval<U>());

private:
    void deallocate();

    void allocate(const Polynomial<T>&);

    void restoreTail();

private:
    Node* _head;
    Node* _tail;
};

template<typename T>
Polynomial<T> operator+(Polynomial<T>, const Polynomial<T>&);

template<typename T>
Polynomial<T> operator-(Polynomial<T>, const Polynomial<T>&);

template<typename T>
Polynomial<T> operator*(Polynomial<T>, const Polynomial<T>&);

template<typename T>
Polynomial<T> operator/(Polynomial<T>, const Polynomial<T>&);

template<typename T>
Polynomial<T> operator%(Polynomial<T>, const Polynomial<T>&);

template<typename T>
Polynomial<T> gcd(const Polynomial<T>&, const Polynomial<T>&);

template<typename T>
Polynomial<T>::Polynomial(T elem)
        :_head(new Node), _tail(_head) {
    if (elem != T(0)) {
        _head->next = new Node(0, elem);
        _tail = _head->next;
    }
}

template<typename T>
Polynomial<T>::Polynomial(const std::vector<std::pair<int, T>>& vec)
        : _head(new Node) {
    Node* ptr = _head;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i].second == T(0)) {
            continue;
        }
        ptr->next = new Node(vec[i].first, vec[i].second);
        ptr = ptr->next;
    }
    _tail = ptr;
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& obj)
        :_head(nullptr) {
    allocate(obj);
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& obj) {
    if (this != &obj) {
        deallocate();
        allocate(obj);
    }
    return *this;
}

template<typename T>
Polynomial<T>::~Polynomial() {
    deallocate();
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& obj) {
    Node* ptr = this->_head;
    Node* objptr = obj._head->next;
    while (objptr != nullptr) {
        while (ptr->next != nullptr && ptr->next->pow < objptr->pow) {
            ptr = ptr->next;
        }
        if (ptr->next == nullptr || ptr->next->pow > objptr->pow) {
            Node* nx = ptr->next;
            ptr->next = new Node(objptr->pow, objptr->coefficient, nx);
        } else {
            ptr->next->coefficient += objptr->coefficient;
            if (ptr->next->coefficient == 0) {
                Node* nx = ptr->next->next;
                delete ptr->next;
                ptr->next = nx;
            }
        }
        objptr = objptr->next;
    }
    restoreTail();
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& obj) {
    return *this += (-obj);
}

template<typename T>
Polynomial<T> Polynomial<T>::operator-() const {
    Polynomial pol = *this;
    Node* ptr = pol._head;
    while (ptr->next != nullptr) {
        ptr->next->coefficient = -ptr->next->coefficient;
        ptr = ptr->next;
    }
    return pol;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& obj) {
    Node* objptr = obj._head->next;
    Polynomial ret;
    while (objptr != nullptr) {
        Polynomial plus;
        Node* ptr = this->_head->next;
        Node* plusptr = plus._head;
        while (ptr != nullptr) {
            plusptr->next = new Node(ptr->pow + objptr->pow, ptr->coefficient * objptr->coefficient);
            ptr = ptr->next;
            plusptr = plusptr->next;
        }
        ret += plus;
        objptr = objptr->next;
    }
    return *this = ret;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator/=(const Polynomial<T>& obj) {
    int deg1 = this->degree(), deg2 = obj.degree();
    if (obj.isZero()) {
        throw DividedByZeroException();
    }
    if (deg1 < deg2) return *this = Polynomial<T>(T(0));
    T majorValue1 = this->_tail->coefficient;
    T majorValue2 = obj._tail->coefficient;
    Polynomial<T> result = Polynomial<T>({{deg1 - deg2, majorValue1 / majorValue2}});
    Polynomial<T> pol = *this - result * obj;

    return *this = result + pol / obj;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator%=(const Polynomial<T>& obj) {
    return *this = *this - *this / obj * obj;
}

template<typename T>
template<typename U>
auto Polynomial<T>::calculate(U x0) const -> decltype(std::declval<T>() * std::declval<U>()) {
    decltype(std::declval<T>() * std::declval<U>()) res(0);
    U powx(1);
    int lastpow = 0;
    Node* ptr = _head;
    while (ptr->next != nullptr) {
        while (lastpow < ptr->next->pow) {
            powx *= x0;
            lastpow++;
        }
        res += powx * ptr->next->coefficient;
        ptr = ptr->next;
    }
    return res;
}

template<typename T>
void Polynomial<T>::deallocate() {
    Node* ptr = _head;
    while (ptr != nullptr) {
        Node* del = ptr;
        ptr = ptr->next;
        delete del;
    }
    _head = _tail = nullptr;
}

template<typename T>
void Polynomial<T>::allocate(const Polynomial<T>& obj) {
    _head = new Node;
    Node* ptr = _head;
    Node* objptr = obj._head->next;
    while (objptr != nullptr) {
        ptr->next = new Node(objptr->pow, objptr->coefficient);
        ptr = ptr->next;
        objptr = objptr->next;
    }
    _tail = ptr;
}

template<typename T>
void Polynomial<T>::restoreTail() {
    Node* ptr = _head;
    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }
    _tail = ptr;
}


template<typename T>
Polynomial<T> operator+(Polynomial<T> obj1, const Polynomial<T>& obj2) {
    return obj1 += obj2;
}

template<typename T>
Polynomial<T> operator-(Polynomial<T> obj1, const Polynomial<T>& obj2) {
    return obj1 -= obj2;
}

template<typename T>
Polynomial<T> operator*(Polynomial<T> obj1, const Polynomial<T>& obj2) {
    return obj1 *= obj2;
}

template<typename T>
Polynomial<T> operator/(Polynomial<T> obj1, const Polynomial<T>& obj2) {
    return obj1 /= obj2;
}

template<typename T>
Polynomial<T> operator%(Polynomial<T> obj1, const Polynomial<T>& obj2) {
    return obj1 %= obj2;
}

template<typename T>
Polynomial<T> gcd(const Polynomial<T>& a, const Polynomial<T>& b) {
    return (b.isZero() ? a : gcd(b, a % b));
}

template<typename T>
std::ostream& operator<<(std::ostream& print, const Polynomial<T>& obj) {
    typename Polynomial<T>::Node* ptr = obj._head->next;
    if (ptr == nullptr) {
        std::cout << "Empty polynomial" << std::endl;
        return print;
    }
    while (ptr != nullptr) {
        print << "(" << ptr->coefficient << ")x" << "^" << ptr->pow;
        ptr = ptr->next;
        print << (ptr != nullptr ? "+" : "\n") << std::flush;
    }
    return print;
}

#endif // POLYNOMIAL_H
