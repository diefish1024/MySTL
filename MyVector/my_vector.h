#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <iterator>

template <typename T>
class MyVector {
public:
    // 类型别名
    using value_tpe = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // 构造函数
    MyVector();
    MyVector(size_type cnt);
    MyVector(size_type cnt, const_reference value);
    MyVector(std::initializer_list<T> list);
    MyVector(const MyVector& o);
    MyVector(MyVector&& o) noexcept;

    // 析构函数
    ~MyVector();

    // 赋值运算符
    MyVector& operator=(const MyVector& o);
    MyVector& operator=(MyVector&& o) noexcept;
    MyVector& operator=(std::initializer_list<T> list);

    // 容量
    size_type size() const;
    size_type capacity() const;
    bool empty() const;
    void reserve(size_type n);
    void shrink_to_fit();

    // 元素访问
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    pointer data();
    const_pointer data() const;

    // 修改器
    void push_back(const_reference val);
    void push_back(T&& val);
    void pop_back();
    iterator insert(const_iterator pos, const_reference val);
    iterator insert(const_iterator pos, T&& val);
    iterator insert(const_iterator pos, size_type cnt, const_reference val);
    template <typename InputIterator>
    typename std::enable_if_t<
        !std::is_void_v<typename std::iterator_traits<InputIterator>::value_type> &&
        std::is_same_v<T, typename std::iterator_traits<InputIterator>::value_type>,
        iterator
    >
    insert(const_iterator pos, InputIterator first, InputIterator last);
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void clear();
    void resize(size_type n);
    void resize(size_type n, const_reference val);

    // 迭代器
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // 交换
    void swap(MyVector& o) noexcept;

private:
    pointer m_data;
    size_type m_size;
    size_type m_capacity;
    std::allocator<T> m_allocator;

    void allocate_space(size_type new_capacity);
};

// 全局运算符重载
template <typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs);

template <typename T>
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs);

// 具体实现

template <typename T>
MyVector<T>::MyVector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
MyVector<T>::MyVector(size_type cnt) : m_data(nullptr), m_size(cnt), m_capacity(cnt) {
    if (cnt > 0) {
        m_data = m_allocator.allocate(cnt);
        for (size_type i = 0; i < cnt; ++i) {
            m_allocator.construct(m_data + i);
        }
    }
}

template <typename T>
MyVector<T>::MyVector(size_type cnt, const_reference value) : m_data(nullptr), m_size(cnt), m_capacity(cnt) {
    if (cnt > 0) {
        m_data = m_allocator.allocate(cnt);
        for (size_type i = 0; i < cnt; ++i) {
            m_allocator.construct(m_data + i, value);
        }
    }
}

template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> list) : m_data(nullptr), m_size(list.size()), m_capacity(list.size()) {
    if (list.size() > 0) {
        m_data = m_allocator.allocate(list.size());
        std::copy(list.begin(), list.end(), m_data);
    }
}

template <typename T>
MyVector<T>::MyVector(const MyVector& o) : m_data(nullptr), m_size(o.m_size), m_capacity(o.m_capacity) {
    if (o.m_size > 0) {
        m_data = m_allocator.allocate(o.m_capacity);
         std::copy(o.m_data, o.m_data + m_size, m_data);
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector&& o) noexcept : m_data(o.m_data), m_size(o.m_size), m_capacity(o.m_capacity) {
    o.m_data = nullptr;
    o.m_size = 0;
    o.m_capacity = 0;
}

template <typename T>
MyVector<T>::~MyVector() {
    for(size_type i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& o) {
    if(this != &o) {
        if(m_capacity < o.m_size) {
            clear();
            m_allocator.deallocate(m_data, m_capacity);
            m_data = m_allocator.allocate(o.m_capacity);
            m_capacity = o.m_capacity;
        }
        m_size = o.m_size;
        std::copy(o.m_data, o.m_data + m_size, m_data);
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& o) noexcept {
    if(this != &o) {
        clear();
        m_allocator.deallocate(m_data, m_capacity);
        m_data = o.m_data;
        m_size = o.m_size;
        m_capacity = o.m_capacity;
        o.m_data = nullptr;
        o.m_size = 0;
        o.m_capacity = 0;
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(std::initializer_list<T> list) {
    if(m_capacity < list.size()) {
        clear();
        m_allocator.deallocate(m_data, m_capacity);
        m_data = m_allocator.allocate(list.size());
        m_capacity = list.size();
    }
    m_size = list.size();
    std::copy(list.begin(), list.end(), m_data);
    return *this;
}

template <typename T>
typename MyVector<T>::size_type MyVector<T>::size() const {
    return m_size;
}

template <typename T>
typename MyVector<T>::size_type MyVector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
bool MyVector<T>::empty() const {
    return m_size == 0;
}

template <typename T>
void MyVector<T>::reserve(size_type n) {
    if(n > m_capacity) {
        allocate_space(n);
        m_capacity = n;
    }
}

template <typename T>
void MyVector<T>::shrink_to_fit() {
    if(m_capacity > m_size) {
        allocate_space(m_size);
        m_capacity = m_size;
    }
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::operator[](size_type pos) {
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::operator[](size_type pos) const {
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::at(size_type pos) {
    if(pos >= m_size) {
        throw std::out_of_range("MyVector::at");
    }
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::at(size_type pos) const {
    if(pos >= m_size) {
        throw std::out_of_range("MyVector::at");
    }
    return m_data[pos];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::front() {
    return m_data[0];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::front() const {
    return m_data[0];
}

template <typename T>
typename MyVector<T>::reference MyVector<T>::back() {
    return m_data[m_size - 1];
}

template <typename T>
typename MyVector<T>::const_reference MyVector<T>::back() const {
    return m_data[m_size - 1];
}

template <typename T>
typename MyVector<T>::pointer MyVector<T>::data() {
    return m_data;
}

template <typename T>
typename MyVector<T>::const_pointer MyVector<T>::data() const {
    return m_data;
}

template <typename T>
void MyVector<T>::push_back(const_reference val) {
    if(m_size == m_capacity) {
        m_capacity = m_capacity ? m_capacity * 2 : 1;
        allocate_space(m_capacity);
    }
    m_allocator.construct(m_data + m_size, val);
    ++m_size;
}

template <typename T>
void MyVector<T>::push_back(T&& val) {
    if(m_size == m_capacity) {
        m_capacity = m_capacity ? m_capacity * 2 : 1;
        allocate_space(m_capacity);
    }
    m_allocator.construct(m_data + m_size, std::move(val));
    ++m_size;
}

template <typename T>
void MyVector<T>::pop_back() {
    if(m_size > 0) {
        m_allocator.destroy(m_data + m_size - 1);
        --m_size;
    }
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos, const_reference val) {
    return insert(pos, 1, val);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos, T&& val) {
    return insert(pos, 1, std::move(val));
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::insert(const_iterator pos, const size_type cnt, const_reference val) {
    if(pos < begin() || pos > end()) {
        throw std::out_of_range("MyVector::insert");
    }
    size_type offeset = pos - begin();
    if(m_size + cnt > m_capacity) {
        m_capacity = m_capacity ? m_capacity * 2 : 1;
        allocate_space(m_capacity);
        pos = begin() + offeset;
    }
    if(pos < end()) {
        std::copy_backward(const_cast<iterator>(pos), end(), end() + cnt);
    }
    m_size += cnt;
    for(size_type i = 0; i < cnt; ++i) {
        m_allocator.construct(pos + i, val);
    }
    return const_cast<iterator>(pos);
}

template <typename T>
template <typename InputIterator>
typename std::enable_if_t<
    !std::is_void_v<typename std::iterator_traits<InputIterator>::value_type> &&
    std::is_same_v<T, typename std::iterator_traits<InputIterator>::value_type>,
    typename MyVector<T>::iterator
>
MyVector<T>::insert(const_iterator pos, InputIterator first, InputIterator last) {
    if(pos < begin() || pos > end()) {
        throw std::out_of_range("MyVector::insert");
    }
    size_type cnt = static_cast<size_type>(std::distance(first, last));
    size_type offeset = pos - begin();
    if(m_size + cnt > m_capacity) {
        m_capacity = m_capacity ? m_capacity * 2 : 1;
        allocate_space(m_capacity);
        pos = begin() + offeset;
    }
    if(pos < end()) {
        std::copy_backward(const_cast<iterator>(pos), end(), end() + cnt);
    }
    m_size += cnt;
    for(size_type i = 0; i < cnt; ++i) {
        m_allocator.construct(pos + i, *first++);
    }
    return const_cast<iterator>(pos);
}

template <typename T>
template <typename... Args>
typename MyVector<T>::iterator MyVector<T>::emplace(const_iterator pos, Args&&... args) {
    if(pos < begin() || pos > end()) {
        throw std::out_of_range("MyVector::emplace");
    }
    size_type offeset = pos - begin();
    if(m_size == m_capacity) {
        m_capacity = m_capacity ? m_capacity * 2 : 1;
        allocate_space(m_capacity);
        pos = begin() + offeset;
    }
    if(pos < end()) {
        std::copy_backward(const_cast<iterator>(pos), end(), end() + 1);
    }
    ++m_size;
    m_allocator.construct(pos, std::forward<Args>(args)...);
    return const_cast<iterator>(pos);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(const_iterator pos) {
    return erase(pos, pos + 1);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::erase(const_iterator first, const_iterator last) {
    if(first < begin() || last > end() || first >= last) {
        throw std::out_of_range("MyVector::erase");
    }
    size_type cnt = last - first;
    for(size_type i = 0; i < cnt; ++i) {
        m_allocator.destroy(first + i);
    }
    if(last < end()) {
        std::copy(const_cast<iterator>(last), end(), const_cast<iterator>(first));
    }
    m_size -= cnt;
    return const_cast<iterator>(first);
}

template <typename T>
void MyVector<T>::clear() {
    for(size_type i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_size = 0;
}

template <typename T>
void MyVector<T>::resize(size_type n) {
    if(n > m_size) {
        if(n > m_capacity) {
            m_capacity = n;
            allocate_space(m_capacity);
        }
        for(size_type i = m_size; i < n; ++i) {
            m_allocator.construct(m_data + i);
        }
    } else {
        for(size_type i = n; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
    }
    m_size = n;
}

template <typename T>
void MyVector<T>::resize(size_type n, const_reference val) {
    if(n > m_size) {
        if(n > m_capacity) {
            m_capacity = n;
            allocate_space(m_capacity);
        }
        for(size_type i = m_size; i < n; ++i) {
            m_allocator.construct(m_data + i, val);
        }
    } else {
        for(size_type i = n; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
    }
    m_size = n;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() {
    return m_data;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const {
    return m_data;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() {
    return m_data + m_size;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const {
    return m_data + m_size;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::cbegin() const {
    return m_data;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::cend() const {
    return m_data + m_size;
}

template <typename T>
typename MyVector<T>::reverse_iterator MyVector<T>::rbegin() {
    return reverse_iterator(end());
}

template <typename T>
typename MyVector<T>::const_reverse_iterator MyVector<T>::rbegin() const {
    return const_reverse_iterator(end());
}

template <typename T>
typename MyVector<T>::reverse_iterator MyVector<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T>
typename MyVector<T>::const_reverse_iterator MyVector<T>::rend() const {
    return const_reverse_iterator(begin());
}

template <typename T>
typename MyVector<T>::const_reverse_iterator MyVector<T>::crbegin() const {
    return const_reverse_iterator(end());
}

template <typename T>
typename MyVector<T>::const_reverse_iterator MyVector<T>::crend() const {
    return const_reverse_iterator(begin());
}

template <typename T>
void MyVector<T>::swap(MyVector& o) noexcept {
    using std::swap;
    swap(m_data, o.m_data);
    swap(m_size, o.m_size);
    swap(m_capacity, o.m_capacity);
    swap(m_allocator, o.m_allocator);
}

template <typename T>
void MyVector<T>::allocate_space(size_type new_capacity) {
    pointer new_data = m_allocator.allocate(new_capacity);
    for (size_type i = 0; i < m_size; ++i) {
        m_allocator.construct(new_data + i, std::move_if_noexcept(m_data[i]));
    }
    for (size_type i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
    m_data = new_data;
    m_capacity = new_capacity;
}

template <typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    if(lhs.size() != rhs.size()) {
        return false;
    }
    for(typename MyVector<T>::size_type i = 0; i < lhs.size(); ++i) {
        if(lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs) {
    return !(lhs == rhs);
}

#endif