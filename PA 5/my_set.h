#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::pair, std::swap;
using std::cout, std::ostream, std::stringstream;
using std::runtime_error, std::invalid_argument;
using std::string;

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

    void clear() {
        this->_parent = nullptr;
        this->_height = 0;
    }

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
    Set_const_iterator(const Set_const_iterator& rhs) : Set_const_iterator(rhs._node) {}

    Set_const_iterator& operator=(const Set_const_iterator& rhs) {
        if (this != &rhs)
            this->_node = rhs._node;
        return *this;
    }

    virtual ~Set_const_iterator() { this->_node = nullptr; }

    const Comparable& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return this->_node->_value;
    }

    const Comparable* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return &this->_node->_value;
    }

    Set_const_iterator& operator++() {
        if (!this->_node)
            return *this;
        Comparable value = this->_node->_value;
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

        if (this->_node && value > this->_node->_value)
            this->_node = nullptr;

        return *this;
    }

    Set_const_iterator operator++(int) {
        Set_const_iterator iter = *this;
        ++(*this);
        return iter;
    }

    friend bool operator==(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs._node == rhs._node; }

    friend bool operator==(const Set_const_iterator& lhs, Node* const& rhs) { return lhs._node == rhs; }

    friend bool operator!=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs._node != rhs._node; }

    virtual string to_string() const {
        stringstream ss;
        ss << "<Set::const_iterator -> [";
        if (this->_node)
            ss << this->_node->_value;
        else
            ss << "nullptr";
        ss << "]>";
        return ss.str();
    }
};

template <class Comparable>
class Set_iterator : public Set_const_iterator<Comparable> {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;
    typedef Set_const_iterator<Comparable> const_iterator;
public:
    Set_iterator() : Set_const_iterator<Comparable>() {}
    Set_iterator(const Set_iterator<Comparable>& rhs) : Set_const_iterator<Comparable>(rhs._node) {}
    Set_iterator(const Node* node) : Set_const_iterator<Comparable>(node) {}
    virtual ~Set_iterator() { this->_node = nullptr; }

    Set_iterator& operator=(const Set_iterator& rhs) {
        if (this != &rhs)
            this->_node = rhs._node;

        return *this;
    }

    Comparable operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return this->_node->_value;
    }

    Comparable* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return &this->_node->_value;
    }

    Set_iterator& operator++() {
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

    Set_iterator operator++(int) {
        Set_iterator iter = *this;
        ++(*this);
        return iter;
    }

    friend bool operator==(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs._node == rhs._node; }

    friend bool operator!=(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs._node != rhs._node; }

    string to_string() const override {
        stringstream ss;
        ss << "<Set::iterator -> [";
        if (this->_node)
            ss << this->_node->_value;
        else
            ss << "nullptr";
        ss << "]>";
        return ss.str();
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

    long height(Node* const& root) const { return root ? root->_height : 0l; }

    long balace_factor(Node* const& root) const { return root ? this->height(root->_left) - this->height(root->_right) : 0l; }

    size_t calcHeight(Node* const& root) const { return 1 + this->max(this->height(root->_left), this->height(root->_right)); }

    Node*& clear(Node*& node) {
        if (node) {
            node->_left = this->clear(node->_left);
            node->_right = this->clear(node->_right);
            node->clear();
            delete node;
        }

        node = nullptr;
        return node;
    }

    Node* copy(Node* const& root) {
        if (!root)
            return nullptr;

        Node* node = new Node(root->_value);
        node->_left = this->copy(root->_left);
        if (node->_left)
            node->_left->_parent = node;
        node->_right = this->copy(root->_right);
        if (node->_right)
            node->_right->_parent = node;
        return node;
    }

    Node* balance(Node*& root) {
        root->_height = this->calcHeight(root);
        long bf = this->balace_factor(root);
        if (bf > 1)
            root = this->balace_factor(root->_left) > 0 ? this->right_rotate(root) : this->lr_rotate(root);
        else if (bf < -1)
            root = this->balace_factor(root->_right) > 0 ? this->rl_rotate(root) : this->left_rotate(root);
        return root;
    }

    Node* left_rotate(Node*& root) {
        Node* temp = root->_right;
        root->_right = temp->_left;
        if (root->_right)
            root->_right->_parent = root;
        temp->_left = root;
        if (temp->_left)
            temp->_left->_parent = temp;

        root->_height = this->calcHeight(root);
        temp->_height = this->calcHeight(temp);

        return temp;
    }

    Node* right_rotate(Node*& root) {
        Node* temp = root->_left;
        root->_left = temp->_right;
        if (root->_left)
            root->_left->_parent = root;
        temp->_right = root;
        if (temp->_right)
            temp->_right->_parent = temp;

        root->_height = this->calcHeight(root);
        temp->_height = this->calcHeight(temp);

        return temp;
    }

    Node* lr_rotate(Node*& root) {
        root->_left = this->left_rotate(root->_left);
        root->_left->_parent = root;
        return this->right_rotate(root);
    }

    Node* rl_rotate(Node*& root) {
        root->_right = this->right_rotate(root->_right);
        root->_right->_parent = root;
        return this->left_rotate(root);
    }

    Node* insert(Node*& root, const Comparable& value) {
        if (!root)
            return new Node(value);
        if (value < root->_value) {
            root->_left = this->insert(root->_left, value);
            root->_left->_parent = root;
        } else if (value > root->_value) {
            root->_right = this->insert(root->_right, value);
            root->_right->_parent = root;
        }

        root = this->balance(root);
        return root;
    }

    Node* remove(Node*& root, const Comparable& value) {
        if (value < root->_value) {
            root->_left = this->remove(root->_left, value);
            if (root->_left) root->_left->_parent = root;
        } else if (value > root->_value) {
            root->_right = this->remove(root->_right, value);
            if (root->_right) root->_right->_parent = root;
        } else {
            Node* temp;
            if (root->isLeaf()) {
                root->clear();
                delete root;
                root = nullptr;
                return root;
            } else if (!root->_left) {
                temp = root->_right;
                root->clear();
                delete root;
                root = nullptr;
                return temp;
            } else if (!root->_right) {
                temp = root->_left;
                root->clear();
                delete root;
                root = nullptr;
                return temp;
            } else {
                temp = this->find_min(root->_right);
                swap(root->_value, temp->_value);
                root->_right = this->remove(root->_right, temp->_value);
                if (root->_right) root->_right->_parent = root;
            }
        }

        root = this->balance(root);
        return root;
    }

    const Node* search(Node* const& root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->_value == value)
            return root;
        return this->search(value < root->_value ? root->_left : root->_right, value);
    }

    /**
     * @brief Find the smallest node in the avl tree
     *
     * @param root current subtree being searched
     * @return Node* pointer to the smallest node
     */
    Node* find_min(Node* const& root) const {
        Node* node = root;
        while (node && node->_left)
            node = node->_left;
        return node;
    }

    Node* find_max(Node* const& root) const {
        Node* node = root;
        while (node && node->_right)
            node = node->_right;
        return node;
    }

    void print_tree(Node* const& root, ostream& os, size_t trace) const {
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
            this->_root = this->copy(rhs._root);
            this->_size = rhs._size;
        }

        return *this;
    }

    iterator begin() { return iterator(this->find_min(this->_root)); }

    const_iterator begin() const { return const_iterator(this->find_min(this->_root)); }

    iterator end() { return iterator(nullptr); }

    const_iterator end() const { return const_iterator(nullptr); }

    bool is_empty() const { return !this->_root; }

    size_t size() const { return this->_size; }

    void make_empty() { this->_size = 0; this->_root = this->clear(this->_root); }

    pair<iterator, bool> insert(const Comparable& value) {
        const Node* node = this->search(this->_root, value);
        if (node)
            return pair(iterator(node), false);

        this->_root = this->insert(this->_root, value);
        ++this->_size;
        return pair(iterator(this->search(this->_root, value)), true);
    }

    iterator insert(const_iterator hint, const Comparable& value) {
        const Node* node = this->search(this->_root, value);
        if (node)
            return iterator(node);

        const Node* location = hint._node;
        if (!this->_root || !location)
            this->_root = this->insert(this->_root, value);
        else
            this->insert(const_cast<Node*&>(location), value);
        ++this->_size;
        return iterator(this->search(this->_root, value));
    }

    size_t remove(const Comparable& value) {
        if (!this->contains(value))
            return 0;
        this->_root = this->remove(this->_root, value);
        --this->_size;
        return 1;
    }

    iterator remove(const_iterator index) {
        if (!this->_root)
            return iterator(nullptr);
        if (!index._node)
            throw invalid_argument("Iterator does not point anywhere");

        const_iterator temp = index;
        iterator it = (++temp)._node;
        Comparable value;
        try {
            value = *temp;
        } catch (const runtime_error& err) {
            it = nullptr;
        }
        this->_root = this->remove(this->_root, *index);
        if (this->_root)
            this->_root->_parent = nullptr;
        --this->_size;
        return it._node ? this->find(value) : it;
    }

    bool contains(const Comparable& value) const { return this->search(this->_root, value); }

    iterator find(const Comparable& key) { return iterator(this->search(this->_root, key)); }

    const_iterator find(const Comparable& key) const { return const_iterator(this->search(this->_root, key)); }

    void print_set(ostream& os = cout) const {
        if (this->_size) {
            os << "{";
            const_iterator iter(this->begin());
            for (size_t i = 0; i < this->_size; ++i) {
                os << *iter;
                if (i != this->_size - 1)
                    os << ", ";
                ++iter;
            }
            os << "}";
        } else
            os << "<empty>";
    }

    // ----------------------- Optional ----------------------- //
    Set(Set&& rhs) : _root{nullptr}, _size{0} {
        swap(this->_root, rhs._root);
        swap(this->_size, rhs._size);
    }

    Set& operator=(Set&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs._root);
            swap(this->_size, rhs._size);
        }
    }

    pair<iterator, bool> insert(Comparable&& value) {
        Comparable v = Comparable();
        swap(v, value);
        return this->insert(v);
    }

    iterator insert(const_iterator iter, Comparable&& value) {
        Comparable v = Comparable();
        swap(v, value);
        return this->insert(iter, v);
    }

    void print_tree(ostream& os = cout) const {
        if (this->_size)
            this->print_tree(this->_root, os, 0);
        else
            os << "<empty>";
        return;
    }
};

template <class Comparable>
ostream& operator<<(ostream& os, const Set_const_iterator<Comparable>& iter) { return os << iter.to_string(); }