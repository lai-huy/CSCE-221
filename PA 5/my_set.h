#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::pair;
using std::cout, std::ostream;
using std::runtime_error, std::out_of_range;

// forward declarations
template <class T> class Set;
template <class T> class Set_const_iterator;
template <class T> class Set_iterator;

template <class Comparable>
class Set_Node {
    friend class Set<Comparable>;
    friend class Set_const_iterator<Comparable>;
    friend class Set_iterator<Comparable>;

    /**
     * @brief Value stored in this node
     */
    Comparable _value;

    /**
     * @brief Largets distance to a leaf node
     */
    size_t _height;

    /**
     * @brief A pointer to the left node
     */
    Set_Node* _left;

    /**
     * @brief A pointer to the right node
     */
    Set_Node* _right;

    /**
     * @brief Construct a new Node object
     *
     * @param value value to put in this node
     */
    Set_Node(const Comparable& value) : _value{Comparable(value)}, _height{1}, _left{nullptr}, _right{nullptr} {}

    /**
     * @brief Determine if this node is a leaf.
     *
     * @return true if this node is a leaf
     * @return false otherwise
     */
    bool is_leaf() const {
        return !this->_left && !this->_right;
    }
};

template <class Comparable>
class Stack {
    friend class Set<Comparable>;
public:
    struct Node {
        Comparable _value;
        Node* _next;
        Node* _prev;

        Node() : _value{Comparable()}, _next{nullptr}, _prev{nullptr} {}
        Node(const Node& rhs) : _value{rhs._value}, _next{nullptr}, _prev{nullptr} {}
        Node(const Comparable& value) : _value{Comparable(value)}, _next{nullptr}, _prev{nullptr} {}
    };

private:
    Stack<Comparable>::Node* _head;
    Stack<Comparable>::Node* _tail;

    void clear() {
        if (this->_head) {
            Node* node = this->_head;
            while (node->_next) {
                node = node->_next;
                delete node->_prev;
            }

            delete this->_tail;
        }

        this->_size = 0;
        this->_head = nullptr;
        this->_tail = nullptr;
    }

public:
    Stack() : _head{nullptr}, _tail{nullptr} {}
    ~Stack() { this->clear(); }

    void push(const Comparable& value) {
        Stack<Comparable>::Node* head = this->_head;
        this->_head = new Stack<Comparable>::Node(value);
        this->_head->_next = head;
        if (head)
            head->_prev = this->_head;
    }

    void pop() {
        if (!this->_head)
            throw out_of_range("Stack underflow");
        this->_head = this->_head->_next;
        delete this->_head->_prev;
    }

    const Comparable& top() const {
        if (!this->_head)
            throw out_of_range("Stack is empty");
        return this->_head->_value;
    }
};

template <class Comparable>
class Set_const_iterator {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;

    Node* _root;

public:
    Set_const_iterator() : _root{nullptr} {}
    // Set_const_iterator(const Set_const_iterator& rhs) : _root{*rhs} {}
    // ~Set_const_iterator() { if (this->_root) delete this->_root }
    // Set_const_iterator& operator==(const Set_const_iterator& rhs) {
    //     if (this->_root)
    //         delete this->_root;

    //     this->_root = *rhs;
    // }

    Set_const_iterator(const Node*& node) : _root{node} {}

    const Node& operator*() const {
        return *(this->_root);
    }

    const Node* operator->() {
        return this->_root;
    }

    Set_const_iterator& operator++() {
        this->_root = this->_root->_right;
        return *this;
    }

    Set_const_iterator operator++(int) {
        Set_const_iterator iter = *this;
        ++(*this);
        return iter;
    }

    Set_const_iterator& operator--() {
        this->_root = this->_root->_left;
        return *this;
    }

    Set_const_iterator operator--(int) {
        Set_const_iterator iter = *this;
        --(*this);
        return iter;
    }

    friend bool operator==(const Set_const_iterator& lhs, const Set_const_iterator& rhs) {
        return (*lhs)._value == (*rhs)._value;
    }

    friend bool operator!=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) {
        return (*lhs)._value != (*rhs)._value;
    }

    friend bool operator<(const Set_const_iterator& lhs, const Set_const_iterator& rhs) {
        return (*lhs)._value < (*rhs)._value;
    }

    friend bool operator<=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) {
        return (*lhs)._value <= (*rhs)._value;
    }

    friend bool operator>(const Set_const_iterator& lhs, const Set_const_iterator& rhs) {
        return (*lhs)._value > (*rhs)._value;
    }

    friend bool operator>=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) {
        return (*lhs)._value < (*rhs)._value;
    }

    virtual std::string to_string() const {
        // make a string that represents the state of the iterator
        //   e.g. "<Set::const_iterator -> [value]>"
        return "<Set::const_iterator -> [" + this->_root->_value + "]";
    }
};

template <class Comparable>
class Set_iterator : public Set_const_iterator<Comparable> {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;
    typedef Set_const_iterator<Comparable> const_iterator;

    Stack<Set_Node<Comparable>*> _stack;
public:
    Set_iterator() : _stack{Stack<Set_Node<Comparable>*>()} {}
    Set_iterator(Set_Node<Comparable>* node) : _stack{Stack<Set_Node<Comparable>*>()} { this->_stack.push(node); }

    Node& operator*() const {
        return *(this->_stack.top());
    }

    Node* operator->() {
        return this->_stack.top();
    }

    Set_iterator& operator++() {
        Node* node = this->_stack.top();
        if (node->_right)
            this->_stack.push(node->_right);
        else
            this->_stack.pop();
        return *this;
    }

    Set_iterator operator++(int) {
        Set_iterator iter = *this;
        ++(*this);
        return iter;
    }

    Set_iterator& operator--() {
        Node* node = this->_stack.top();
        if (node->_left)
            this->_stack.push(node->_left);
        else
            this->_stack.pop();
        return *this;
    }

    Set_iterator operator--(int) {
        Set_iterator iter = *this;
        --(*this);
        return iter;
    }

    friend bool operator==(const Set_iterator& lhs, const Set_iterator& rhs) {
        return lhs->_stack == rhs->_stack;
    }

    friend bool operator!=(const Set_iterator& lhs, const Set_iterator& rhs) {
        return (*lhs) == (*rhs);
    }

    friend bool operator<(const Set_iterator& lhs, const Set_iterator& rhs) {
        return (*lhs)._value < (*rhs)._value;
    }

    friend bool operator<=(const Set_iterator& lhs, const Set_iterator& rhs) {
        return (*lhs)._value <= (*rhs)._value;
    }

    friend bool operator>(const Set_iterator& lhs, const Set_iterator& rhs) {
        return (*lhs)._value > (*rhs)._value;
    }

    friend bool operator>=(const Set_iterator& lhs, const Set_iterator& rhs) {
        return (*lhs)._value < (*rhs)._value;
    }

    std::string to_string() const override {
        // make a string that represents the state of the iterator
        //   e.g. "<Set::iterator -> [value]>"
        return "<Set::iterator -> [" + this->_root->_value + "]";
    }
};

template <class Comparable>
class Set {
    typedef Set_Node<Comparable> Node;

    Node* _root;
    size_t _size;

    Node*& clear(Node*& node) {
        if (node) {
            node->_left = this->clear(node->_left);
            node->_right = this->clear(node->_right);
            delete node;
        }

        node = nullptr;
        return node;
    }

    Node* copy(const Node*& root) {
        if (!root)
            return nullptr;

        Node* new_root = new Node(root->_value);
        new_root->_left = this->copy(root->_left);
        new_root->_right = this->copy(root->_right);
        return new_root;
    }

    Node* search(const Node*& root, const Comparable& value) {
        if (!root)
            return nullptr;
        if (root->_value == value)
            return root;
        return this->search(root->_value < value ? root->_right : root->_left, value);
    }

    Node* insert(Node* node, const Comparable& value) {
        if (!node)
            return new Node(value);
        else if (value == node->_value)
            return node;
        else if (value < node->_value)
            node->_left = this->insert(node->_left, value);
        else if (value > node->_value)
            node->_right = this->insert(node->_right, value);

        node = this->balance(node);
        return node;
    }

public:
    typedef Set_const_iterator<Comparable> const_iterator;
    typedef Set_iterator<Comparable> iterator;

    Set() : _root{nullptr}, _size{0} {}
    Set(const Set& rhs) : _root{this->copy(rhs._root)}, _size{rhs._size} {}
    ~Set() { this->make_empty(); }
    Set& operator=(const Set& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->copy(rhs._root);
        }
    }

    iterator begin() {
        Node* node = this->_root;
        while (node && node->_left) {
            node = node->_left;
        }

        return iterator(node);
    }

    const_iterator begin() const {
        Node* node = this->_root;
        while (node && node->_left) {
            node = node->_left;
        }

        return const_iterator(node);
    }

    iterator end() {
        Node* node = this->_root;
        while (node && node->_right) {
            node = node->_right;
        }

        return iterator(node);
    }

    const_iterator end() const {
        Node* node = this->_root;
        while (node && node->_right) {
            node = node->_right;
        }

        return const_iterator(node);
    }

    bool is_empty() const {
        return !this->_root;
    }

    size_t size() const {
        return this->_size;
    }

    void make_empty() {
        this->_root = this->clear(this->_root);
    }

    pair<iterator, bool> insert(const Comparable& value) {
        return std::make_pair(iterator(this->insert(value)), this->contains(value));
    }

    iterator insert(const_iterator iter, const Comparable& value) {

    }

    size_t remove(const Comparable& value);
    iterator remove(const_iterator iter);

    bool contains(const Comparable& value) const {
        return this->search(this->_root, value);
    }

    iterator find(const Comparable& key) {
        Node* node = this->search(this->_root, key);
        return node ? iterator(node) : this->end();
    }

    const_iterator find(const Comparable& key) const {
        Node* node = this->search(this->_root, key);
        return node ? const_iterator(node) : this->end();
    }

    void print_set(ostream os = cout) {
        os << "{ ";
        for (Set_const_iterator iter = this->begin(), end = this->end(); iter < end; ++iter) {
            os << iter->_value;
            if (iter != end)
                os << ", ";
        }
        os << "}";
    }

    // ----------------------- Optional ----------------------- //
    // Set(Set&& set);
    // Set& operator=(Set&& set);
    // pair<iterator, bool> insert(Comparable&& value);
    // iterator insert(const_iterator, Comparable&& value) const;
    // void print_tree(ostream os = cout);
};

template <class Comparable>
std::ostream& operator<<(std::ostream& os, const Set_const_iterator<Comparable>& iter) {
    return os << iter.to_string();
}
