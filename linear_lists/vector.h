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
    size_t m_capacity;
    size_t m_size;
    Alloc m_allocator;
    value_type* m_array;
private:
    template<bool B>
    class common_iterator {
        friend class common_iterator<!B>;

    public:
        using value_type = std::conditional_t<B, const vector::value_type, vector::value_type>;
    private:
        value_type* m_ptr;
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

    value_type& back() { return m_array[m_size - 1]; }

    const value_type& back() const { return m_array[m_size - 1]; }

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
    size_t size() const { return m_size; }

    bool empty() const { return m_size == 0; }

    void swap(vector&);

private:
    bool is_full() const { return m_size == m_capacity; }

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
        :m_ptr(ptr) {}

template<typename T, typename Alloc>
template<bool B>
vector<T, Alloc>::common_iterator<B>::common_iterator(const common_iterator<false>& other)
        :m_ptr(other.m_ptr) {}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator++() {
    ++m_ptr;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B> vector<T, Alloc>::common_iterator<B>::operator++(int)& {
    common_iterator iter = *this;
    ++m_ptr;
    return iter;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator+=(ptrdiff_t n) {
    m_ptr += n;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator--() {
    --m_ptr;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B> vector<T, Alloc>::common_iterator<B>::operator--(int)& {
    common_iterator iter = *this;
    --m_ptr;
    return iter;
}

template<typename T, typename Alloc>
template<bool B>
typename vector<T, Alloc>::template common_iterator<B>& vector<T, Alloc>::common_iterator<B>::operator-=(ptrdiff_t n) {
    m_ptr -= n;
    return *this;
}

template<typename T, typename Alloc>
template<bool B>
ptrdiff_t vector<T, Alloc>::common_iterator<B>::operator-(const common_iterator<B>& iter) const {
    return m_ptr - iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
auto vector<T, Alloc>::common_iterator<B>::operator*() const -> value_type& {
    return *m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
auto vector<T, Alloc>::common_iterator<B>::operator->() const -> value_type* {
    return m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator==(const common_iterator<B>& iter) const {
    return m_ptr == iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator!=(const common_iterator<B>& iter) const {
    return m_ptr != iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator<(const common_iterator<B>& iter) const {
    return m_ptr < iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator>(const common_iterator<B>& iter) const {
    return m_ptr > iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator<=(const common_iterator<B>& iter) const {
    return m_ptr <= iter.m_ptr;
}

template<typename T, typename Alloc>
template<bool B>
bool vector<T, Alloc>::common_iterator<B>::operator>=(const common_iterator<B>& iter) const {
    return m_ptr >= iter.m_ptr;
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
        : m_capacity(MAX_SIZE), m_size(0), m_allocator(allocator),
          m_array(AllocTraits::allocate(m_allocator, m_capacity)) {}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const vector& obj)
        : m_capacity(obj.m_capacity), m_size(obj.m_size), m_allocator(obj.m_allocator),
          m_array(AllocTraits::allocate(m_allocator, m_capacity)) {
    // variable is initialized here for catch block
    size_t i = 0;
    try {
        for (i = 0; i < m_size; ++i) {
            // try to construct
            AllocTraits::construct(m_allocator, m_array + i, obj.m_array[i]);
        }
    }
    catch (...) {
        // destroy all already constructed objects
        for (; i > 0; --i) {
            AllocTraits::destroy(m_allocator, m_array + i - 1);
        }
        // deallocate memory
        AllocTraits::deallocate(m_allocator, m_array, m_capacity);
        // rethrow caught exception
        throw;
    }
}


template<typename T, typename Alloc>
vector<T, Alloc>::vector(vector<T, Alloc>&& obj) noexcept
        :m_capacity(obj.m_capacity), m_size(obj.m_size), m_allocator(obj.m_allocator), m_array(obj.m_array) {
    obj.m_capacity = 0;
    obj.m_size = 0;
    obj.m_array = nullptr;
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
        reserve(2 * m_capacity);
    }
    AllocTraits::construct(m_allocator, m_array + m_size, std::forward<Args>(args)...);
    ++m_size;
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
        --m_size;
        AllocTraits::destroy(m_allocator, m_array + m_size);
    }
}

template<typename T, typename Alloc>
void vector<T, Alloc>::reserve(size_t n) {
    // if there already present enought memory, just return
    if (n <= m_capacity) return;

    // allocate and construct new memory
    value_type* new_array = AllocTraits::allocate(m_allocator, n);
    // variable initialized here for catch block
    size_t i = 0;
    try {
        for (i = 0; i < m_size; ++i) {
            AllocTraits::construct(m_allocator, new_array + i, std::move_if_noexcept(m_array[i]));
        }
    }
    catch (...) {
        // destroy all already constructed objects
        for (; i > 0; --i) {
            // if move assignment is safe, then move in old memory
            if constexpr (std::is_nothrow_move_constructible_v<value_type>
                          && std::is_nothrow_move_assignable_v<value_type>) {
                m_array[i] = new_array[i];
                continue;
            } else {
                // else destroy the element
                AllocTraits::destroy(m_allocator, new_array + i - 1);
            }
        }
        // deallocate memory
        AllocTraits::deallocate(m_allocator, new_array, n);
        // rethrow caught exception
        throw;
    }

    destroy();

    m_capacity = n;
    m_array = new_array;
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
    return iterator(m_array);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
    return iterator(m_array + m_size);
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
    return const_iterator(m_array);
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
    return const_iterator(m_array + m_size);
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
    return m_array[ind];
}

template<typename T, typename Alloc>
const typename vector<T, Alloc>::value_type& vector<T, Alloc>::operator[](size_t ind) const {
    return m_array[ind];
}

template<typename T, typename Alloc>
void vector<T, Alloc>::swap(vector<T, Alloc>& obj) {
    std::swap(m_capacity, obj.m_capacity);
    std::swap(m_size, obj.m_size);
    std::swap(m_array, obj.m_array);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::destroy() {
    // destroy elements and deallocate memory
    for (size_t i = m_size; i > 0; --i) {
        AllocTraits::destroy(m_allocator, m_array + i - 1);
    }
    AllocTraits::deallocate(m_allocator, m_array, m_capacity);
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