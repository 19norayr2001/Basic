#ifndef SEQUENTIAL_LIST_H
#define SEQUENTIAL_LIST_H

#include <memory>
#include <iostream>
#include <type_traits>

#include <reverse_iterator.h>

namespace nstd {

template<typename T, typename Alloc = std::allocator<T>>
class vector {
public:
    typedef T value_type;
    typedef std::allocator_traits<Alloc> AllocTraits;
private:
    size_t _capacity;
    size_t _size;
    Alloc _allocator;
    value_type* _array;
private:
    template<bool B>
    class common_iterator {
        friend class common_iterator<!B>;

    public:
        using value_type = std::conditional_t<B, const vector::value_type, vector::value_type>;
    private:
        value_type* _ptr;
    public:
        explicit common_iterator(value_type*);

        common_iterator(const common_iterator<false>& other);

    public:
        common_iterator<B>& operator++();

        common_iterator<B> operator++(int)&;

        common_iterator<B>& operator+=(ptrdiff_t);

        common_iterator<B>& operator--();

        common_iterator<B> operator--(int)&;

        common_iterator<B>& operator-=(ptrdiff_t);

    public:
        ptrdiff_t operator-(const common_iterator<B>&) const;

    public:
        value_type& operator*() const;

        value_type* operator->() const;

    public:
        bool operator==(const common_iterator<B>&) const;

        bool operator!=(const common_iterator<B>&) const;

        bool operator<(const common_iterator<B>&) const;

        bool operator>(const common_iterator<B>&) const;

        bool operator<=(const common_iterator<B>&) const;

        bool operator>=(const common_iterator<B>&) const;

    public:
        common_iterator<B> operator+(ptrdiff_t) const;

        common_iterator<B> operator-(ptrdiff_t) const;
    };

public:
    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;
    using reverse_iterator = nstd::common_reverse_iterator<iterator>;
    using const_reverse_iterator = nstd::common_reverse_iterator<const_iterator>;
public:
    vector(const Alloc& = Alloc());

    vector(const vector<T, Alloc>&);

    vector(vector<T, Alloc>&&) noexcept;

    vector& operator=(const vector<T, Alloc>&)&;

    vector& operator=(vector<T, Alloc>&&)& noexcept;

    ~vector();

public:
    template<typename... Args>
    void emplace_back(Args&& ...);

    void push_back(const value_type&);

    void push_back(value_type&&);

    void pop_back();

public:
    void reserve(size_t);

    value_type& back() { return _array[_size - 1]; }

    const value_type& back() const { return _array[_size - 1]; }

public:
    iterator begin();

    iterator end();

    const_iterator cbegin() const;

    const_iterator cend() const;

    const_iterator begin() const;

    const_iterator end() const;

public:
    reverse_iterator rbegin();

    reverse_iterator rend();

    const_reverse_iterator crbegin() const;

    const_reverse_iterator crend() const;

    const_reverse_iterator rbegin() const;

    const_reverse_iterator rend() const;

public:
    value_type& operator[](size_t);

    const value_type& operator[](size_t) const;

public:
    size_t size() const { return _size; }

    bool empty() const { return _size == 0; }

    void swap(vector&);

private:
    bool is_full() const { return _size == _capacity; }

    void destroy();

private:
    static const size_t MAX_SIZE = 2;
};

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream&, const vector<T, Alloc>&);

//======================common_iterator implementation==========================================

template<typename T, typename Alloc>
template<bool B>
vector<T, Alloc>::common_iterator<B>::common_iterator(value_type* ptr)
        :_ptr(ptr) {}

template<typename T, typename Alloc>
template<bool B>
vector<T, Alloc>::common_iterator<B>::common_iterator(const common_iterator<false>& other)
        :_ptr(other._ptr) {}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator++() {
    ++_ptr;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B> vector<T, Alloc>::common_iterator<B>::operator++(int)& {
    common_iterator iter = *this;
    ++_ptr;
    return iter;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator+=(ptrdiff_t n) {
    _ptr += n;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator--() {
    --_ptr;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B> vector<T, Alloc>::common_iterator<B>::operator--(int)& {
    common_iterator iter = *this;
    --_ptr;
    return iter;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator-=(ptrdiff_t n) {
    _ptr -= n;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
ptrdiff_t vector<T, Alloc>::common_iterator<B>::operator-(const common_iterator<B>& iter) const {
    return _ptr - iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
auto vector<T, Alloc>::common_iterator<B>::operator*() const -> value_type& {
    return *_ptr;
}

template<typename T, typename Alloc>
template<bool B>
auto vector<T, Alloc>::common_iterator<B>::operator->() const -> value_type* {
    return _ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator==(const common_iterator<B>& iter) const {
    return _ptr == iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator!=(const common_iterator<B>& iter) const {
    return _ptr != iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator<(const common_iterator<B>& iter) const {
    return _ptr < iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator>(const common_iterator<B>& iter) const {
    return _ptr > iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator<=(const common_iterator<B>& iter) const {
    return _ptr <= iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator>=(const common_iterator<B>& iter) const {
    return _ptr >= iter._ptr;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>
vector<T, Alloc>::common_iterator<B>::operator+(ptrdiff_t n) const {
    common_iterator<B> iter = *this;
    return iter += n;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>
vector<T, Alloc>::common_iterator<B>::operator-(ptrdiff_t n) const {
    common_iterator<B> iter = *this;
    return iter -= n;
}

//=================================== Sequential List implementation ===================================

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const Alloc& allocator)
        : _capacity(MAX_SIZE), _size(0), _allocator(allocator),
          _array(AllocTraits::allocate(_allocator, _capacity)) {}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const vector& obj)
        : _capacity(obj._capacity), _size(obj._size), _allocator(obj._allocator),
          _array(AllocTraits::allocate(_allocator, _capacity)) {
    // variable is initialized here for catch block
    size_t i = 0;
    try {
        for (i = 0; i < _size; ++i) {
            // try to construct
            AllocTraits::construct(_allocator, _array + i, obj._array[i]);
        }
    }
    catch (...) {
        // destroy all already constructed objects
        for (; i > 0; --i) {
            AllocTraits::destroy(_allocator, _array + i - 1);
        }
        // deallocate memory
        AllocTraits::deallocate(_allocator, _array, _capacity);
        // rethrow caught exception
        throw;
    }
}


template<typename T, typename Alloc>
vector<T, Alloc>::vector(vector<T, Alloc>&& obj) noexcept
        :_capacity(obj._capacity), _size(obj._size), _allocator(obj._allocator), _array(obj._array) {
    obj._capacity = 0;
    obj._size = 0;
    obj._array = nullptr;
}

template<typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& obj)& {
    if (this != &obj) {
        vector copy_obj(obj);
        this->swap(copy_obj);
    }
    return *this;
}

template<typename T, typename Alloc>
vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& obj)& noexcept {
    if (this != &obj) {
        vector moved_obj(std::move(obj));
        this->swap(moved_obj);
    }
    return *this;
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector() {
    destroy();
}

template<typename T, typename Alloc>
template<typename... Args>
void vector<T, Alloc>::emplace_back(Args&& ... args) {
    // reserve more capacity if current is fully filled
    if (is_full()) {
        reserve(2 * _capacity);
    }
    AllocTraits::construct(_allocator, _array + _size, std::forward<Args>(args)...);
    ++_size;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::push_back(const value_type& elem) {
    emplace_back(elem);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::push_back(value_type&& elem) {
    emplace_back(std::move(elem));
}

template<typename T, typename Alloc>
void vector<T, Alloc>::pop_back() {
    if (!empty()) {
        --_size;
        AllocTraits::destroy(_allocator, _array + _size);
    }
}

template<typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_t n) {
    // if there already present enought memory, just return
    if (n <= _capacity) return;

    // allocate and construct new memory
    value_type* new_array = AllocTraits::allocate(_allocator, n);
    // variable initialized here for catch block
    size_t i = 0;
    try {
        for (i = 0; i < _size; ++i) {
            AllocTraits::construct(_allocator, new_array + i, std::move_if_noexcept(_array[i]));
        }
    }
    catch (...) {
        // destroy all already constructed objects
        for (; i > 0; --i) {
            // if move assignment is safe, then move in old memory
            if constexpr (std::is_nothrow_move_constructible_v<value_type>
                          && std::is_nothrow_move_assignable_v<value_type>) {
                _array[i] = new_array[i];
                continue;
            } else {
                // else destroy the element
                AllocTraits::destroy(_allocator, new_array + i - 1);
            }
        }
        // deallocate memory
        AllocTraits::deallocate(_allocator, new_array, n);
        // rethrow caught exception
        throw;
    }

    destroy();

    _capacity = n;
    _array = new_array;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
    return iterator(_array);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
    return iterator(_array + _size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cbegin() const {
    return begin();
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::cend() const {
    return end();
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
    return const_iterator(_array);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
    return const_iterator(_array + _size);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {
    return {end()};
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
    return {begin()};
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crbegin() const {
    return rbegin();
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::crend() const {
    return rend();
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const {
    return {end()};
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const {
    return {begin()};
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::value_type& vector<T, Alloc>::operator[](size_t ind) {
    return _array[ind];
}

template<typename T, typename Alloc>
const typename vector<T, Alloc>::value_type& vector<T, Alloc>::operator[](size_t ind) const {
    return _array[ind];
}

template<typename T, typename Alloc>
void vector<T, Alloc>::swap(vector<T, Alloc>& obj) {
    std::swap(_capacity, obj._capacity);
    std::swap(_size, obj._size);
    std::swap(_array, obj._array);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::destroy() {
    // destroy elements and deallocate memory
    for (size_t i = _size; i > 0; --i) {
        AllocTraits::destroy(_allocator, _array + i - 1);
    }
    AllocTraits::deallocate(_allocator, _array, _capacity);
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream& out, const vector<T, Alloc>& obj) {
    for (auto it = obj.cbegin(); it != obj.cend(); ++it) {
        std::cout << *it << ' ';
    }
    out << std::endl;
    return out;
}

} // nstd namespace

#endif // SEQUENTIAL_LIST_H