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

/**
 * @brief Node class for set
 *
 * @tparam Comparable date type that will overload the comparison operators
 */
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

    /**
     * @brief Resets all attributes to their default values
     */
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

    /**
     * @brief Determine if this node is a left child
     *
     * @return true if this node is a left child
     * @return false otherwise
     */
    bool isLeft() const { return this->_parent ? this == this->_parent->_left : false; }

    /**
     * @brief Determine if this node if a right child
     *
     * @return true if this node is a right child
     * @return false otherwise
     */
    bool isRight() const { return this->_parent ? this == this->_parent->_right : false; }
};

/**
 * @brief Const iterator for Set
 *
 * @tparam Comparable data type that will overload the comparison operators
 */
template <class Comparable>
class Set_const_iterator {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;

protected:
    /**
     * @brief Current node of the iterator
     */
    const Node* _node;
public:
    /**
     * @brief Construct a new Set_const_iterator object
     */
    Set_const_iterator() : _node{nullptr} {}

    /**
     * @brief Construct a new Set_const_iterator object
     *
     * @param node Set_Node to point to
     */
    Set_const_iterator(const Node* const& node) : _node{node} {}

    /**
     * @brief Construct a new Set_const_iterator object
     *
     * @param rhs iterator to copy from
     */
    Set_const_iterator(const Set_const_iterator& rhs) : Set_const_iterator(rhs._node) {}

    /**
     * @brief Copy assignment operator
     *
     * @param rhs iterator to copy from
     * @return Set_const_iterator& *this
     */
    Set_const_iterator& operator=(const Set_const_iterator& rhs) {
        if (this != &rhs)
            this->_node = rhs._node;
        return *this;
    }

    /**
     * @brief Destroy the Set_const_iterator object
     */
    virtual ~Set_const_iterator() { this->_node = nullptr; }

    /**
     * @brief Indirection operator
     *
     * @return const Comparable& value stored in the node
     */
    const Comparable& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return this->_node->_value;
    }

    /**
     * @brief Member access
     *
     * @return const Comparable* pointer to the value stored in the node
     */
    const Comparable* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return &this->_node->_value;
    }

    /**
     * @brief Pre-increment this iterator
     *
     * @return Set_const_iterator& this iterator after incrementing
     */
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

    /**
     * @brief Post-increement this iterator
     *
     * @return Set_const_iterator this iterator before incrementing
     */
    Set_const_iterator operator++(int) {
        Set_const_iterator iter = *this;
        ++(*this);
        return iter;
    }

    /**
     * @brief Lexicographically compares two iterators
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if the two iterators point to the same node
     * @return false otherwise
     */
    friend bool operator==(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs._node == rhs._node; }

    /**
     * @brief Lexicographically compares a iterator to a node
     *
     * @param lhs iterator
     * @param rhs Node*
     * @return true if the iterator points to the same node as the node*
     * @return false otherwise
     */
    friend bool operator==(const Set_const_iterator& lhs, Node* const& rhs) { return lhs._node == rhs; }

    /**
     * @brief Lexicographically compares two iterators
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if the two iterators do not point to the same node
     * @return false otherwise
     */
    friend bool operator!=(const Set_const_iterator& lhs, const Set_const_iterator& rhs) { return lhs._node != rhs._node; }

    /**
     * @brief Converts this iterator into a std::string
     *
     * @return string printable version of the iterator
     */
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

/**
 * @brief Iterator for Set
 *
 * @tparam Comparable data type that will overload the comparison operators
 */
template <class Comparable>
class Set_iterator : public Set_const_iterator<Comparable> {
    friend class Set<Comparable>;
    typedef Set_Node<Comparable> Node;
    typedef Set_const_iterator<Comparable> const_iterator;
public:
    /**
     * @brief Construct a new Set_iterator object
     */
    Set_iterator() : Set_const_iterator<Comparable>() {}

    /**
     * @brief Construct a new Set_iterator object
     *
     * @param rhs iterator to copy from
     */
    Set_iterator(const Set_iterator<Comparable>& rhs) : Set_const_iterator<Comparable>(rhs._node) {}

    /**
     * @brief Construct a new Set_iterator object
     *
     * @param node Node* to copy from
     */
    Set_iterator(const Node* const& node) : Set_const_iterator<Comparable>(node) {}

    /**
     * @brief Destroy the Set_iterator object
     */
    virtual ~Set_iterator() { this->_node = nullptr; }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs iterator to copy from
     * @return Set_iterator& *this
     */
    Set_iterator& operator=(const Set_iterator& rhs) {
        if (this != &rhs)
            this->_node = rhs._node;

        return *this;
    }

    /**
     * @brief Indirection operator
     *
     * @return Comparable value stored in the node this points to.
     */
    Comparable& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return this->_node->_value;
    }

    /**
     * @brief Member access operator
     *
     * @return Comparable* pointer to the value stored in the node this points to.
     */
    Comparable* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return &this->_node->_value;
    }

    /**
     * @brief Pre-increment
     *
     * @return Set_iterator& the iterator after incrementing
     */
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

    /**
     * @brief Post-increment
     *
     * @return Set_iterator the iterator after incrementing
     */
    Set_iterator operator++(int) {
        Set_iterator iter = *this;
        ++(*this);
        return iter;
    }

    /**
     * @brief Lexicographically compares two iterators
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if the two iterators point to the same node
     * @return false otherwise
     */
    friend bool operator==(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs._node == rhs._node; }

    /**
     * @brief Lexicographically compares two iterators
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if the two iterators do not point to the same node
     * @return false otherwise
     */
    friend bool operator!=(const Set_iterator& lhs, const Set_iterator& rhs) { return lhs._node != rhs._node; }

    /**
     * @brief Converts this iterator into a std::string
     *
     * @return string printable version of the iterator
     */
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
    /**
     * @brief Root of the tree
     */
    Node* _root;

    /**
     * @brief Size of the set
     */
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
    /**
     * @brief Construct a new Set object
     */
    Set() : _root{nullptr}, _size{0} {}

    /**
     * @brief Construct a new Set object
     *
     * @param rhs Set to copy from
     */
    Set(const Set& rhs) : _root{this->copy(rhs._root)}, _size{rhs._size} {}

    /**
     * @brief Destroy the Set object
     *
     */
    ~Set() { this->make_empty(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs Set to copy from
     * @return Set& *this
     */
    Set& operator=(const Set& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs._root);
            this->_size = rhs._size;
        }

        return *this;
    }

    /**
     * @brief Gets an iterator to the first element in the set
     *
     * @return iterator to the first element in the set
     */
    iterator begin() { return iterator(this->find_min(this->_root)); }

    /**
     * @brief Gets a const iterator to the first element in the list
     *
     * @return const_iterator to the first element in the set
     */
    const_iterator begin() const { return const_iterator(this->find_min(this->_root)); }

    /**
     * @brief Gets an iterator to nullptr
     *
     * @return iterator to nullptr
     */
    iterator end() { return iterator(nullptr); }

    /**
     * @brief Gets a const iterator to nullptr
     *
     * @return const_iterator to nullptr
     */
    const_iterator end() const { return const_iterator(nullptr); }

    /**
     * @brief Determine if the set is empty
     *
     * @return true if the set is empty
     * @return false otherwise
     */
    bool is_empty() const { return !this->_root; }

    /**
     * @brief Determine the size of the set
     *
     * @return size_t size of the set
     */
    size_t size() const { return this->_size; }

    /**
     * @brief
     *
     */
    void make_empty() { this->_size = 0; this->_root = this->clear(this->_root); }

    /**
     * @brief Insert a value into the set
     *
     * @param value value to insert
     * @return pair<iterator, bool> iterator to the inserted value, if insertion was successful
     */
    pair<iterator, bool> insert(const Comparable& value) {
        const Node* node = this->search(this->_root, value);
        if (node)
            return pair(iterator(node), false);

        this->_root = this->insert(this->_root, value);
        ++this->_size;
        return pair(this->find(value), true);
    }

    /**
     * @brief Insert a value into the set at a specified location
     *
     * @param hint const_iterator to the a specifed location in the set
     * @param value value to insert
     * @return iterator to the value inserted
     */
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
        return this->find(value);
    }

    /**
     * @brief Remove a value from the set
     *
     * @param value value to remove
     * @return size_t the number of elementes removed
     */
    size_t remove(const Comparable& value) {
        if (!this->contains(value))
            return 0;
        this->_root = this->remove(this->_root, value);
        --this->_size;
        return 1;
    }

    /**
     * @brief Remove a value from the set
     *
     * @param index const_iterator to the value to remove
     * @return iterator to the next value in the set
     */
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

    /**
     * @brief Determine if a value is in the set
     *
     * @param value value to search for
     * @return true if the value exists in the set
     * @return false otherwise
     */
    bool contains(const Comparable& value) const { return this->search(this->_root, value); }

    /**
     * @brief Determine the location of a value in the set
     *
     * @param key value to search for
     * @return iterator location of the value
     */
    iterator find(const Comparable& key) { return iterator(this->search(this->_root, key)); }

    /**
     * @brief Determine the location of a value in the set
     *
     * @param key value to search for
     * @return const_iterator location of the value
     */
    const_iterator find(const Comparable& key) const { return const_iterator(this->search(this->_root, key)); }

    /**
     * @brief Prints the set to an ostream, cout by default
     *
     * @param os ostream to print to.
     */
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
    /**
     * @brief Construct a new Set object
     *
     * @param rhs set to copy from
     */
    Set(Set&& rhs) : _root{nullptr}, _size{0} {
        swap(this->_root, rhs._root);
        swap(this->_size, rhs._size);
    }

    /**
     * @brief move assignment operator
     *
     * @param rhs set to copy from
     * @return Set& *this
     */
    Set& operator=(Set&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs._root);
            swap(this->_size, rhs._size);
        }

        return *this;
    }

    /**
     * @brief Move insert a value into the set
     *
     * @param value value to insert
     * @return pair<iterator, bool> iterator to the inserted value, if insertion was successful
     */
    pair<iterator, bool> insert(Comparable&& value) {
        Comparable v = Comparable();
        swap(v, value);
        return this->insert(v);
    }

    /**
     * @brief Move insert a specified value into the set at a specified location
     *
     * @param hint
     * @param value
     * @return iterator
     */
    iterator insert(const_iterator hint, Comparable&& value) {
        Comparable v = Comparable();
        swap(v, value);
        return this->insert(hint, v);
    }

    /**
     * @brief Prints the underlying tree of the set
     *
     * @param os ostream to print to
     */
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