#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
#include <stack>

using std::pair, std::swap;
using std::cout, std::ostream, std::stringstream;
using std::runtime_error, std::invalid_argument;
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

    /**
     * @brief A pointer to the parent of this node
     */
    Set_Node* _parent;
public:
    /**
     * @brief Construct a new Node object
     *
     * @param value value to put in this node
     */
    Set_Node(const Comparable& value) : _value{Comparable(value)}, _height{1}, _left{nullptr}, _right{nullptr}, _parent{nullptr} {}

    const Comparable& value() const { return this->_value; }

    Comparable value() { return this->_value; }

    /**
     * @brief Determine if this node is a leaf.
     *
     * @return true if this node is a leaf
     * @return false otherwise
     */
    bool isLeaf() const { return !this->_left && !this->_right; }

    bool isLeft() const { return this->_parent ? this == this->_parent->_left : false; }
    bool isRight() const { return this->_parent ? this == this->_parent->_right : false; }
};

template <class Comparable>
class Set_const_iterator {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;

protected:
    const Node* _node;
public:
    Set_const_iterator() : _node{nullptr} {}
    Set_const_iterator(const Node* node) : _node{node} {}

    Set_const_iterator(const Set_const_iterator& rhs) = default;
    Set_const_iterator& operator=(const Set_const_iterator& rhs) = default;
    virtual ~Set_const_iterator() = default;

    const Comparable& operator*() const { return *this->_node; }

    const Node* operator->() const { return this->_node; }

    Set_const_iterator& operator++() {
        if (!this->_node)
            return *this;
        if (this->_node->_right) {
            this->_node = this->_node->_right;
            while (this->_node->_left)
                this->_node = this->_node->_left;
        } else {
            Node* parent = this->_node->_parent;
            while (parent && this->_node->isRight()) {
                this->_node = parent;
                parent = parent->_parent;
            }

            this->_node = parent;
        }

        return *this;
    }

    Set_const_iterator operator++(int) {
        Set_const_iterator iter = *this;
        ++(*this);
        return iter;
    }

    Set_const_iterator& operator--() {
        if (!this->_node)
            return *this;
        if (this->_node->_left) {
            this->_node = this->_node->_left;
            while (this->_node->_right)
                this->_node = this->_node->_right;
        } else {
            Node* parent = this->_node->_parent;
            while (parent && this->_node->isLeft()) {
                this->_node = parent;
                parent = parent->_parent;
            }

            this->_node = parent;
        }

        return *this;
    }

    Set_const_iterator operator--(int) {
        Set_const_iterator iter = *this;
        --(*this);
        return iter;
    }

    friend bool operator==(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs->value() == rhs->value(); }

    friend bool operator!=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs->value() != rhs->value(); }

    friend bool operator<(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs->value() < rhs->value(); }

    friend bool operator<=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs->value() <= rhs->value(); }

    friend bool operator>(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs->value() > rhs->value(); }

    friend bool operator>=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs->value() < rhs->value(); }

    virtual std::string to_string() const {
        stringstream ss;
        ss << this->top();
        return "<Set::const_iterator -> [" + ss.str() + "]";
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
    Set_iterator(const Set_iterator& rhs) : Set_const_iterator<Comparable>() { this->_location = rhs._location; }
    Set_iterator(Node* node) : Set_const_iterator<Comparable>(node) {}
    ~Set_iterator() = default;

    Set_iterator& operator=(const Set_iterator& rhs) {
        if (this != &rhs)
            this->_location = rhs._location;

        return *this;
    }

    Node& operator*() {
        if (this->_location.empty())
            throw runtime_error("stack is empty");
        return *(this->_location.top());
    }

    Node* operator->() {
        if (this->_location.empty())
            throw runtime_error("stack is empty");
        return this->_location.top();
    }

    Comparable top() const {
        if (this->_location.empty())
            throw runtime_error("stack is empty");
        return this->_location.top()->_value;
    }

    Set_iterator& operator++() {
        Node* node = this->_location.top();
        if (node->_right)
            this->_location.push(node->_right);
        else if (this->_location.size() == 1)
            throw runtime_error("Cannot increment the end iterator");
        else
            this->_location.pop();
        return *this;
    }

    Set_iterator operator++(int) {
        Set_iterator iter = *this;
        ++(*this);
        return iter;
    }

    Set_iterator& operator--() {
        Node* node = this->_location.top();
        if (node->_left)
            this->_location.push(node->_left);
        else if (this->_location.size() == 1)
            throw runtime_error("Cannot decrement the begin iterator");
        else
            this->_location.pop();
        return *this;
    }

    Set_iterator operator--(int) {
        Set_iterator iter = *this;
        --(*this);
        return iter;
    }

    friend bool operator==(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs->value() == rhs->value(); }

    friend bool operator!=(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs->value() != rhs->value(); }

    friend bool operator<(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs->value() < rhs->value(); }

    friend bool operator<=(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs->value() <= rhs->value(); }

    friend bool operator>(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs->value() > rhs->value(); }

    friend bool operator>=(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs->value() < rhs->value(); }

    std::string to_string() const override {
        // make a string that represents the state of the iterator
        //   e.g. "<Set::iterator -> [value]>"
        stringstream ss;
        ss << this->top();
        return "<Set::iterator -> [" + ss.str() + "]";
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

    Node* search(const Node* root, const Comparable& value) const {
        if (!root)
            return nullptr;
        return this->search(value < root->_value ? root->_left : root->_right, value);
    }

    iterator search(iterator& iter, Node*& root, const Comparable& value) const {
        if (!root)
            return iter;
        iter.push(root);
        this->search(iter, value < root->_value ? root->_left : root->_right, value);
        return iter;
    }

    Node* insert(Node*& root, const Comparable& value) {
        if (!root)
            return value;
        if (value < root->value) {
            root->left = this->insert(root->left, value);
            root->left->parent = root;
        } else if (value > root->value) {
            root->right = this->insert(root->right, value);
            root->right->parent = root;
        }

        return root;
    }

    Node* remove(Node* root, const Comparable& value) {
        if (!root)
            return nullptr;
        if (value < root->_value)
            root->_left = this->remove(root->_left, value);
        else if (value > root->_value)
            root->_right = this->remove(root->_right, value);
        else {
            if (root->is_leaf()) {
                delete root;
                return nullptr;
            } else if (!root->_left) {
                Node* temp = root->_right;
                delete root;
                root = nullptr;
                return temp;
            } else if (!root->_right) {
                Node* temp = root->_left;
                delete root;
                root = nullptr;
                return temp;
            } else {
                const Node* temp = this->find_min(root->_right);
                root->_value = temp->_value;
                root->_right = this->remove(root->_right, temp->_value);
            }
        }

        root = this->balance(root);
        return root;
    }

    void print_tree(const Node* root, ostream& os, size_t trace) const {
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

    iterator end() { return iterator(nullptr); }

    const_iterator end() const { return const_iterator(nullptr); }

    bool is_empty() const { return !this->_root; }

    size_t size() const { return this->_size; }

    void make_empty() { this->_root = this->clear(this->_root); }

    pair<iterator, bool> insert(const Comparable& value) {
        iterator it;
        it = this->search(it, this->_root, value);

        if (it._location.empty()) {
            this->_root = new Node(value);
            it.push(this->_root);
        } else if (it._location.top()->_value == value)
            return pair(it, false);
        else
            this->insert(it, this->_root, value);

        ++this->_size;
        return pair(it, true);
    }

    iterator insert(const_iterator iter, const Comparable& value) {
        iterator it(iter);
        it = this->search(it, this->_root, value);

        if (it._location.empty()) {
            this->_root = new Node(value);
            it.push(this->_root);
        } else if (it._location.top()->_value == value)
            return it;
        else
            this->insert(it, this->_root, value);

        ++this->_size;
        return it;
    }

    size_t remove(const Comparable& value) {
        if (!this->contains(value))
            return 0;
        this->_root = this->remove(this->_root, value);
        return 1;
    }

    iterator remove(const_iterator iter) {
        if (!this->_root)
            throw invalid_argument("Set is empty");
        if (iter._location.empty())
            throw invalid_argument("Iterator does not point anywhere");
        return iterator(iter);
    }

    bool contains(const Comparable& value) const { return this->search(this->_root, value); }

    iterator find(const Comparable& key) {
        iterator it;
        it = this->search(it, this->_root, key);
        return it;
    }

    const_iterator find(const Comparable& key) const {
        Node* node = this->search(this->_root, key);
        return node ? const_iterator(node) : this->end();
    }

    void print_set(ostream& os = cout) const {
        os << "{ ";
        for (Set_const_iterator iter = this->begin(), end = this->end(); iter < end; ++iter) {
            os << iter.top();
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
