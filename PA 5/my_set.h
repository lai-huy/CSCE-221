#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
#include <stack>

using std::pair, std::swap;
using std::cout, std::ostream;
using std::runtime_error, std::out_of_range, std::underflow_error, std::overflow_error;
using std::string;
using std::stack;

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

public:
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

    const Comparable& value() const {
        return this->_value;
    }
};

/*
template <class Object>
class stack {
public:
    struct Node {
        Object _value;
        Node* _next;
        Node* _prev;

        Node() : _value{Object()}, _next{nullptr}, _prev{nullptr} {}
        Node(const Node& rhs) : _value{rhs._value}, _next{nullptr}, _prev{nullptr} {}
        Node(const Object& value) : _value{Object(value)}, _next{nullptr}, _prev{nullptr} {}
    };

private:
    stack<Object>::Node* _head;
    size_t _size;

public:
    stack() : _head{nullptr}, _size{size_t()} {}
    ~stack() { this->clear(); }
    stack(const stack& rhs) : _head{nullptr}, _size{size_t()} { this->copy(rhs); }
    stack& operator=(const stack& rhs) {
        if (this != &rhs) {
            this->clear();
            this->copy(rhs);
        }

        return *this;
    }

    void clear() {
        if (this->_head) {
            Node* node = this->_head;
            while (node->_next) {
                node = node->_next;
                delete node->_prev;
            }

            delete node;
        }

        this->_head = nullptr;
        this->_size = 0;
    }

    void copy(const stack& rhs) {
        const Node* head = rhs._head;
        if (!head)
            return;

        this->_head = new Node(head->_value);

        Node* curr = this->_head;
        Node* next = head->_next;
        Node* prev = this->_head;

        while (next) {
            curr->_next = new Node(next->_value);
            prev = curr;
            curr = curr->_next;
            curr->_prev = prev;
            next = next->_next;
        }

        this->_size = rhs._size;
    }

    void push(const Object& value) {
        ++this->_size;
        stack<Object>::Node* node = new stack<Object>::Node(value);
        if (this->_head) {
            this->_head->_prev = node;
            node->_next = this->_head;
            this->_head = this->_head->_prev;
        } else
            this->_head = node;
    }

    void pop() {
        --this->_size;
        this->_head = this->_head->_next;
        delete this->_head->_prev;
    }

    const Object& top() const { return this->_head->_value; }

    bool empty() const { return !this->_size; }

    size_t size() const { return this->_size; }
};*/

template <class Comparable>
class Set_const_iterator {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;

protected:
    stack<Node*> _stack;
public:
    Set_const_iterator() : _stack{stack<Node*>()} {}
    Set_const_iterator(const Set_const_iterator& rhs) : _stack{rhs._stack} {}
    Set_const_iterator(Node* node) : _stack{stack<Node*>()} {
        Node* curr = node;
        while (curr) {
            this->_stack.push(curr);
            curr = curr->_left;
        }
    }
    virtual ~Set_const_iterator() = default;

    Set_const_iterator& operator=(const Set_const_iterator& rhs) {
        if (this != &rhs)
            this->_stack = rhs._stack;

        return *this;
    }

    const Node& operator*() const {
        if (this->_stack.empty())
            throw underflow_error("stack is empty");
        return *(this->_stack.top());
    }

    const Node* operator->() const {
        if (this->_stack.empty())
            throw underflow_error("stack is empty");
        return this->_stack.top();
    }

    const Comparable& top() const {
        if (this->_stack.empty())
            throw underflow_error("stack is empty");
        return this->_stack.top()->_value;
    }

    Set_const_iterator& operator++() {
        Node* node = this->_stack.top();
        if (node->_right)
            this->_stack.push(node->_right);
        else if (this->_stack.size() == 1)
            throw overflow_error("Cannot increment the end iterator");
        else
            this->_stack.pop();
        return *this;
    }

    Set_const_iterator operator++(int) {
        Set_const_iterator iter = *this;
        ++(*this);
        return iter;
    }

    Set_const_iterator& operator--() {
        Node* node = this->_stack.top();
        if (node->_left)
            this->_stack.push(node->_left);
        else if (this->_stack.size() == 1)
            throw runtime_error("Cannot decrement the begin iterator");
        else
            this->_stack.pop();
        return *this;
    }

    Set_const_iterator operator--(int) {
        Set_const_iterator iter = *this;
        --(*this);
        return iter;
    }

    void push(Node*& node) { this->_stack.push(node); }

    friend bool operator==(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return (*lhs)._value == (*rhs)._value; }

    friend bool operator!=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return (*lhs)._value != (*rhs)._value; }

    friend bool operator<(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return (*lhs)._value < (*rhs)._value; }

    friend bool operator<=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return (*lhs)._value <= (*rhs)._value; }

    friend bool operator>(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return (*lhs)._value > (*rhs)._value; }

    friend bool operator>=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return (*lhs)._value < (*rhs)._value; }

    virtual std::string to_string() const {
        // make a string that represents the state of the iterator
        //   e.g. "<Set::const_iterator -> [value]>"
        return "<Set::const_iterator -> [" + std::to_string(this->operator*()._value) + "]";
    }
};

template <class Comparable>
class Set_iterator : public Set_const_iterator<Comparable> {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;
    typedef Set_const_iterator<Comparable> const_iterator;

public:
    Set_iterator() : Set_const_iterator<Comparable>() {}
    Set_iterator(const Set_const_iterator<Comparable>& rhs) : Set_const_iterator<Comparable>(rhs) {}
    Set_iterator(const Set_iterator& rhs) : Set_const_iterator<Comparable>() { this->_stack = rhs._stack; }
    Set_iterator(Node* node) : Set_const_iterator<Comparable>(node) {}
    ~Set_iterator() = default;

    Set_iterator& operator=(const Set_iterator& rhs) {
        if (this != &rhs)
            this->_stack = rhs._stack;

        return *this;
    }

    Node& operator*() {
        if (this->_stack.empty())
            throw runtime_error("stack is empty");
        return *(this->_stack.top());
    }

    Node* operator->() {
        if (this->_stack.empty())
            throw runtime_error("stack is empty");
        return this->_stack.top();
    }

    Comparable top() const {
        if (this->_stack.empty())
            throw runtime_error("stack is empty");
        return this->_stack.top()->_value;
    }

    Set_iterator& operator++() {
        Node* node = this->_stack.top();
        if (node->_right)
            this->_stack.push(node->_right);
        else if (this->_stack.size() == 1)
            throw runtime_error("Cannot increment the end iterator");
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
        else if (this->_stack.size() == 1)
            throw runtime_error("Cannot decrement the begin iterator");
        else
            this->_stack.pop();
        return *this;
    }

    Set_iterator operator--(int) {
        Set_iterator iter = *this;
        --(*this);
        return iter;
    }

    friend bool operator==(const Set_iterator& lhs, const Set_iterator& rhs) { return (*lhs)._value == (*rhs)._value; }

    friend bool operator!=(const Set_iterator& lhs, const Set_iterator& rhs) { return (*lhs)._value != (*rhs)._value; }

    friend bool operator<(const Set_iterator& lhs, const Set_iterator& rhs) { return (*lhs)._value < (*rhs)._value; }

    friend bool operator<=(const Set_iterator& lhs, const Set_iterator& rhs) { return (*lhs)._value <= (*rhs)._value; }

    friend bool operator>(const Set_iterator& lhs, const Set_iterator& rhs) { return (*lhs)._value > (*rhs)._value; }

    friend bool operator>=(const Set_iterator& lhs, const Set_iterator& rhs) { return (*lhs)._value < (*rhs)._value; }

    std::string to_string() const override {
        // make a string that represents the state of the iterator
        //   e.g. "<Set::iterator -> [value]>"
        return "<Set::iterator -> [" + std::to_string(this->top()) + "]";
    }
};

template <class Comparable>
class Set {
private:
    typedef Set_Node<Comparable> Node;
public:
    typedef Set_const_iterator<Comparable> const_iterator;
    typedef Set_iterator<Comparable> iterator;

private:
    Node* _root;
    size_t _size;

    template <typename Type>
    Type max(const Type& a, const Type& b) const { return a > b ? a : b; }

    long height(Node*& root) const { return !root ? 0l : root->_height; }

    long balace_factor(Node*& root) const {
        return !root ?
            0l :
            this->height(root->_left) - this->height(root->_right);
    }

    size_t calcHeight(Node*& root) const {
        return 1 + this->max<long>(this->height(root->_left), this->height(root->_right));
    }

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

    /*
    Node* search(Node* root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->_value == value)
            return root;
        return this->search(root->_value < value ? root->_right : root->_left, value);
    }*/

    iterator search(iterator& iter, Node*& root, const Comparable& value) const {
        if (!root)
            return iter;
        iter.push(root);
        this->search(iter, value < root->_value ? root->_left : root->_right, value);
        return iter;
    }

    Node* insert(iterator& iter, Node* node, const Comparable& value) {
        if (!node) {
            Node* new_node = new Node(value);
            iter.push(new_node);
            return new_node;
        } else if (value == node->_value)
            return node;
        else if (value < node->_value) {
            iter.push(node->_left);
            node->_left = this->insert(iter, node->_left, value);
        } else {
            iter.push(node->_right);
            node->_right = this->insert(iter, node->_right, value);
        }

        node = this->balance(node);
        iter.push(node);
        return node;
    }

    Node* balance(Node* root) {
        root->_height = 1 + this->max(this->height(root->_left), this->height(root->_right));
        long bf = this->balace_factor(root);
        if (bf > 1)
            root = this->balace_factor(root->_left) > 0 ? ll_rotate(root) : lr_rotate(root);
        else if (bf < -1)
            root = this->balace_factor(root->_right) > 0 ? rl_rotate(root) : rr_rotate(root);
        return root;
    }

    Node* rr_rotate(Node*& root) {
        Node* temp = root->_right;
        root->_right = temp->_left;
        temp->_left = root;

        root->_height = this->calcHeight(root);
        temp->_height = this->calcHeight(temp);

        return temp;
    }

    Node* ll_rotate(Node*& root) {
        Node* temp = root->_left;
        root->_left = temp->_right;
        temp->_right = root;

        root->_height = this->calcHeight(root);
        temp->_height = this->calcHeight(temp);

        return temp;
    }

    Node* lr_rotate(Node*& root) {
        Node* temp = root->_left;
        root->_left = this->rr_rotate(temp);
        return this->ll_rotate(root);
    }

    Node* rl_rotate(Node*& root) {
        Node* temp = root->_right;
        root->_right = this->ll_rotate(temp);
        return this->rr_rotate(root);
    }

    void print_tree(Node*& root, ostream& os, size_t trace) const {
        if (!root) {
            os << "<empty>\n";
            return;
        }

        if (root->_right)
            this->print_tree(root->_right, os, trace + 1);
        os << string(trace * 2, ' ') << root->_value << "\n";
        if (root->_left)
            this->print_tree(root->_left, os, trace + 1);
    }
public:

    Set() : _root{nullptr}, _size{0} {}
    Set(const Set& rhs) : _root{this->copy(rhs._root)}, _size{rhs._size} {}
    ~Set() { this->make_empty(); }
    Set& operator=(const Set& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->copy(rhs._root);
        }

        return *this;
    }

    iterator begin() {
        Node* node = this->_root;
        iterator iter(this->_root);
        while (node && node->_left) {
            node = node->_left;
            iter.push(node);
        }

        return iter;
    }

    const_iterator begin() const {
        Node* node = this->_root;
        const_iterator iter(this->_root);
        while (node && node->_left) {
            node = node->_left;
            iter.push(node);
        }

        return iter;
    }

    iterator end() {
        Node* node = this->_root;
        iterator iter(this->_root);
        while (node && node->_right) {
            node = node->_right;
            iter.push(node);
        }

        return iter;
    }

    const_iterator end() const {
        Node* node = this->_root;
        const_iterator iter(this->_root);
        while (node && node->_right) {
            node = node->_right;
            iter.push(node);
        }

        return iter;
    }

    bool is_empty() const { return !this->_root; }

    size_t size() const { return this->_size; }

    void make_empty() { this->_root = this->clear(this->_root); }

    /*
    pair<iterator, bool> insert(const Comparable& value) {
        Node* node = this->search(this->_root, value);
        if (node)
            return pair(iterator(node), false);

        iterator iter(this->_root);
        Node* inserted = this->insert(iter, this->_root, value);
        if (!this->_root)
            this->_root = inserted;

        ++this->_size;
        return pair(iter, !node);
    }*/

    pair<iterator, bool> insert(const Comparable& value) {
        iterator it;
        it = this->search(it, this->_root, value);

        if (it._stack.empty()) {
            this->_root = new Node(value);
            it.push(this->_root);
        } else if (it._stack.top()->_value == value)
            return pair(it, false);
        else
            this->insert(it, this->_root, value);

        ++this->_size;
        return pair(it, true);
    }

    iterator insert(const_iterator iter, const Comparable& value) {
        iterator it(iter);
        it = this->search(it, this->_root, value);

        ++this->_size;
        if (!this->_root) {
            this->_root = new Node(value);
            return iterator(this->_root);
        }

        // iterator it = iterator(iter);
        Node* inserted;
        try {
            inserted = this->insert(it, it._stack.top(), value);
        } catch (const runtime_error& err) {
            inserted = this->insert(it, this->_root, value);
        }
        it._stack.push(inserted);
        return it;
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

    void print_set(ostream& os = cout) const {
        os << "{ ";
        for (Set_const_iterator iter = this->begin(), end = this->end(); iter != end; ++iter) {
            os << (*iter)._value;
            if (iter != end)
                os << ", ";
        }
        os << "}\n";
    }

    // ----------------------- Optional ----------------------- //
    // Set(Set&& rhs) : _root{nullptr}, _size{0} {
    //     swap(this->_root, rhs._root);
    //     swap(this->_size, rhs._size);
    // }

    // Set& operator=(Set&& rhs) {
    //     if (this != &rhs) {
    //         this->clear();
    //         swap(this->_root, rhs._root);
    //         swap(this->_size, rhs._size);
    //     }
    // }

    // pair<iterator, bool> insert(Comparable&& value) {
    //     Comparable v = Comparable();
    //     swap(v, value);
    //     return this->insert(v);
    // }

    // iterator insert(const_iterator iter, Comparable&& value) const {
    //     Comparable v = Comparable();
    //     swap(v, value);
    //     return this->insert(iter, v);
    // }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->_root, os, i);
    }
};

template <class Comparable>
std::ostream& operator<<(std::ostream& os, const Set_const_iterator<Comparable>& iter) {
    return os << iter.to_string();
}
