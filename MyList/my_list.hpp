#ifndef MY_LIST_H
#define MY_LIST_H

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <iterator>

template <typename T>
class MyList {
public:
    // 类型别名
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    class iterator;
    class const_iterator;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // 构造函数
    MyList() : m_size(0) { init_sentinel(); }
    explicit MyList(size_type count) : m_size(count) {
        init_sentinel();
        Node* p = m_head;
        for(size_type i = 0; i < count; ++i) {
            link(p, create_node(T()));
            p = p->next;
        }
    }
    MyList(size_type count, const_reference value) : m_size(count) {
        init_sentinel();
        Node* p = m_head;
        for(size_type i = 0; i < count; ++i) {
            link(p, create_node(value));
            p = p->next;
        }
    }
    MyList(std::initializer_list<T> init) : m_size(init.size()) {
        init_sentinel();
        Node* p = m_head;
        for(const_reference val : init) {
            link(p, create_node(val));
            p = p->next;
        }
    }
    MyList(const MyList& o) : m_size(o.m_size) {
        init_sentinel();
        Node* p = m_head;
        for(const_iterator it = o.cbegin(); it != o.cend(); ++it) {
            link(p, create_node(*it));
            p = p->next;
        }
    }
    MyList(MyList&& o) noexcept : m_head(o.m_head), m_tail(o.m_tail), m_size(o.m_size) {
        o.m_head = nullptr;
        o.m_tail = nullptr;
        o.m_size = 0;
    }
    // 析构函数
    ~MyList() {
        clear();
        m_alloc.deallocate(m_head, 1);
        m_alloc.deallocate(m_tail, 1);
    }

    // 赋值运算符
    MyList& operator=(const MyList& o) {
        if(this != &o) {
            clear();
            Node* p = m_head;
            for(const_iterator it = o.cbegin(); it != o.cend(); ++it) {
                link(p, create_node(*it));
                p = p->next;
            }
            m_size = o.m_size;
        }
        return *this;
    }
    MyList& operator=(MyList&& o) noexcept{
        if(this != &o) {
            clear();
            m_alloc.deallocate(m_head, 1);
            m_alloc.deallocate(m_tail, 1);
            m_head = o.m_head;
            m_tail = o.m_tail;
            m_size = o.m_size;
            o.m_head = nullptr;
            o.m_tail = nullptr;
            o.m_size = 0;
        }
        return *this;
    }
    MyList& operator=(std::initializer_list<T> init) {
        clear();
        Node* p = m_head;
        for(const_reference val : init) {
            link(p, create_node(val));
            p = p->next;
        }
        m_size = init.size();
        return *this;
    }

    // 容量
    size_type size() const noexcept { return m_size; }
    bool empty() const noexcept { return m_size == 0; }

    // 元素访问
    reference front() {
        if(empty()) {
            throw std::out_of_range("MyList::front");
        }
        return m_head->next->data;
    }
    const_reference front() const {
        if(empty()) {
            throw std::out_of_range("MyList::front");
        }
        return m_head->next->data;
    }
    reference back() {
        if(empty()) {
            throw std::out_of_range("MyList::back");
        }
        return m_tail->prev->data;
    }
    const_reference back() const {
        if(empty()) {
            throw std::out_of_range("MyList::back");
        }
        return m_tail->prev->data;
    }

    // 修改器
    void push_front(const_reference val) {
        link(m_head, create_node(val));
        ++m_size;
    }
    void push_front(T&& val) {
        link(m_head, create_node(std::move(val)));
        ++m_size;
    }
    void pop_front() {
        if(empty()) {
            throw std::out_of_range("MyList::pop_front");
        }
        Node* p = m_head->next;
        unlink(p);
        m_alloc.destroy(p);
        m_alloc.deallocate(p, 1);
        --m_size;
    }
    void push_back(const_reference val) {
        link(m_tail->prev, create_node(val));
        ++m_size;
    }
    void push_back(T&& val) {
        link(m_tail->prev, create_node(std::move(val)));
        ++m_size;
    }
    void pop_back() {
        if(empty()) {
            throw std::out_of_range("MyList::pop_back");
        }
        Node* p = m_tail->prev;
        unlink(p);
        m_alloc.destroy(p);
        m_alloc.deallocate(p, 1);
        --m_size;
    }
    iterator insert(const_iterator pos, const_reference val) {
        Node* p = pos.m_node;
        link(p->prev, create_node(val));
        ++m_size;
        return iterator(p->prev);
    }
    iterator insert(const_iterator pos, T&& val) {
        Node* p = pos.m_node;
        link(p->prev, create_node(std::move(val)));
        ++m_size;
        return iterator(p->prev);
    }
    iterator insert(const_iterator pos, size_type count, const_reference val) {
        Node* p = pos.m_node;
        for(size_type i = 0; i < count; ++i) {
            link(p->prev, create_node(val));
            ++m_size;
        }
        return iterator(p->prev);
    }
    template <
        typename InputIt,
        typename = std::enable_if_t<std::is_same_v<T, typename std::iterator_traits<InputIt>::value_type>>
    >
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        Node* p = pos.m_node;
        for(; first != last; ++first) {
            link(p->prev, create_node(*first));
            ++m_size;
        }
        return iterator(p->prev);
    }
    iterator insert(const_iterator pos, std::initializer_list<T> init) {
        Node* p = pos.m_node;
        for(const_reference val : init) {
            link(p->prev, create_node(val));
            ++m_size;
        }
        return iterator(p->prev);
    }
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        Node* p = pos.m_node;
        link(p->prev, create_node(std::forward<Args>(args)...));
        ++m_size;
        return iterator(p->prev);
    }

    iterator erase(const_iterator pos) {
        if(pos == cend()) {
            throw std::out_of_range("MyList::erase");
        }
        Node* p = pos.m_node;
        unlink(p);
        m_alloc.destroy(p);
        m_alloc.deallocate(p, 1);
        --m_size;
        return iterator(p->next);
    }
    iterator erase(const_iterator first, const_iterator last) {
        for(;first != last; first = erase(first));
        return iterator(last.m_node);
    }
    void clear() {
        if(!m_head || !m_tail) {
            return;
        }
        for(Node* p = m_head->next; p != m_tail;) {
            Node* q = p;
            p = p->next;
            m_alloc.destroy(q);
            m_alloc.deallocate(q, 1);
        }
        m_head->next = m_tail;
        m_tail->prev = m_head;
        m_size = 0;
    }
    void resize(size_type count) {
        if(count < m_size) {
            iterator it = begin();
            std::advance(it, count);
            erase(it, end());
        } else if(count > m_size) {
            insert(end(), count - m_size, T());
        }
    }
    void resize(size_type count, const_reference val) {
        if(count < m_size) {
            iterator it = begin();
            std::advance(it, count);
            erase(it, end());
        } else if(count > m_size) {
            insert(end(), count - m_size, val);
        }
    }

    // 迭代器
    iterator begin() noexcept { return iterator(m_head->next); }
    const_iterator begin() const noexcept { return const_iterator(m_head->next); }
    iterator end() noexcept { return iterator(m_tail); }
    const_iterator end() const noexcept { return const_iterator(m_tail); }
    const_iterator cbegin() const noexcept { return const_iterator(m_head->next); }
    const_iterator cend() const noexcept { return const_iterator(m_tail); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

    // 交换
    void swap(MyList& o) noexcept {
        using std::swap;
        swap(m_head, o.m_head);
        swap(m_tail, o.m_tail);
        swap(m_size, o.m_size);
    }

private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const_reference val = T(), Node* p = nullptr, Node* n = nullptr)
            : data(val), prev(p), next(n) {}
        
        Node(T&& val, Node* p = nullptr, Node* n = nullptr)
            : data(std::move(val)), prev(p), next(n) {}
    };

    Node* m_head;
    Node* m_tail;
    size_type m_size;
    std::allocator<Node> m_alloc;

    // 辅助函数
    void init_sentinel() {
        m_head = m_alloc.allocate(1);
        m_tail = m_alloc.allocate(1);
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }
    Node* create_node(const_reference val, Node* p = nullptr, Node* n = nullptr) {
        Node* new_node = m_alloc.allocate(1);
        m_alloc.construct(new_node, val, p, n);
        return new_node;
    }
    Node* create_node(T&& val, Node* p = nullptr, Node* n = nullptr) {
        Node* new_node = m_alloc.allocate(1);
        m_alloc.construct(new_node, std::move(val), p, n);
        return new_node;
    }
    void link(Node* p, Node* node) {
        node->next = p->next;
        node->prev = p;
        p->next->prev = node;
        p->next = node;
    }
    void unlink(Node* node) {
        node->prev->next = node -> next;
        node->next->prev = node -> prev;
    }
};
template <typename T>
class MyList<T>::iterator {
    friend class MyList<T>;
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator() : m_node(nullptr) {}
    explicit iterator(Node* node) : m_node(node) {}
    iterator(const iterator& o) : m_node(o.m_node) {}

    iterator& operator=(const iterator& o) {
        m_node = o.m_node;
        return *this;
    }
    reference operator*() const { return m_node->data; }
    pointer operator->() const { return &m_node->data; }
    iterator& operator++() {
        m_node = m_node->next;
        return *this;
    }
    iterator operator++(int) {
        iterator tmp(*this);
        m_node = m_node->next;
        return tmp;
    }
    iterator& operator--() {
        m_node = m_node->prev;
        return *this;
    }
    iterator operator--(int) {
        iterator temp(*this);
        m_node = m_node->prev;
        return temp;
    }
    bool operator==(const iterator& o) const { return m_node == o.m_node; }
    bool operator!=(const iterator& o) const { return m_node != o.m_node; }
private:
    Node* m_node;
};

template <typename T>
class MyList<T>::const_iterator {
    friend class MyList<T>;
public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using reference = const T&;
    using pointer = const T*;
    using iterator_category = std::bidirectional_iterator_tag;

    const_iterator() : m_node(nullptr) {}
    explicit const_iterator(Node* node) : m_node(node) {}
    const_iterator(const const_iterator& o) : m_node(o.m_node) {}
    const_iterator(const iterator& o) : m_node(o.m_node) {}

    const_iterator& operator=(const const_iterator& o) {
        m_node = o.m_node;
        return *this;
    }
    reference operator*() const { return m_node->data; }
    pointer operator->() const { return &m_node->data; }
    const_iterator& operator++() {
        m_node = m_node->next;
        return *this;
    }
    const_iterator operator++(int) {
        const_iterator tmp(*this);
        m_node = m_node->next;
        return tmp;
    }
    const_iterator& operator--() {
        m_node = m_node->prev;
        return *this;
    }
    const_iterator operator--(int) {
        const_iterator temp(*this);
        m_node = m_node->prev;
        return temp;
    }
    bool operator==(const const_iterator& o) const { return m_node == o.m_node; }
    bool operator!=(const const_iterator& o) const { return m_node != o.m_node; }
private:
    Node* m_node;
};
#endif // MY_LIST_H