#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::pair, std::swap;
using std::cout, std::ostream, std::stringstream;
using std::runtime_error, std::invalid_argument, std::out_of_range;
using std::string;

template <class K, class V> class Map;
template <class K, class V> class Map_const_iterator;
template <class K, class V> class Map_iterator;

/**
 * @brief Node class for map
 *
 * @tparam Key key type of the node
 * @tparam Value value type of the node
 */
template <class Key, class Value>
class Map_Node {
    friend class Map<Key, Value>;
    friend class Map_const_iterator<Key, Value>;
    friend class Map_iterator<Key, Value>;
private:
    /**
     * @brief Value stored in this node
     */
    pair<const Key, Value>* _pair;

    /**
     * @brief Largets distance to a leaf node
     */
    size_t _height;

    /**
     * @brief A pointer to the left node
     */
    Map_Node* _left;

    /**
     * @brief A pointer to the right node
     */
    Map_Node* _right;

    /**
     * @brief A pointer to the parent of this node
     */
    Map_Node* _parent;
public:
    /**
     * @brief Construct a new Node object
     *
     * @param value value to put in this node
     */
    Map_Node(const pair<const Key, Value> p) : _pair{new pair<const Key, Value>(p)}, _height{1}, _left{nullptr}, _right{nullptr}, _parent{nullptr} {}

    /**
     * @brief Construct a new Map_Node object
     *
     * @param rhs Node to copy from
     */
    Map_Node(const Map_Node& rhs) : Map_Node(*rhs._pair) {}

    /**
     * @brief Copy assignment operator
     *
     * @param rhs node to copy from
     * @return Map_Node& *this
     */
    Map_Node& operator=(const Map_Node& rhs) {
        if (this != &rhs) {
            this->clear();
            this->_pair = new pair<const Key, Value>(*rhs._pair);
        }

        return *this;
    }

    /**
     * @brief Destroy the Map_Node object
     */
    ~Map_Node() { this->clear(); }

    /**
     * @brief Reset the attributes to their default values
     */
    void clear() {
        if (this->_pair)
            delete this->_pair;
        this->_parent = nullptr;
        this->_pair = nullptr;
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
     * @brief Determine if this node is a right child
     *
     * @return true if this node is a right child
     * @return false otherwise
     */
    bool isRight() const { return this->_parent ? this == this->_parent->_right : false; }

    /**
     * @brief insertion operator
     *
     * @param os ostream to print to
     * @param node node to print
     * @return ostream& ostream to print to
     */
    friend ostream& operator<<(ostream& os, const Map_Node& node) { return os << node._pair->first << ": " << node._pair->second; }
};

/**
 * @brief Const iterator for map
 *
 * @tparam Key key type
 * @tparam Value value type
 */
template <class Key, class Value>
class Map_const_iterator {
private:
    friend class Map<Key, Value>;
    typedef Map_Node<Key, Value> Node;
    typedef pair<const Key, Value> value_type;
protected:
    /**
     * @brief current Node of the iterator
     */
    const Node* _node;
public:
    /**
     * @brief Construct a new Map_const_iterator object
     */
    Map_const_iterator() : Map_const_iterator(nullptr) {};

    /**
     * @brief Construct a new Map_const_iterator object
     *
     * @param node node to point to
     */
    Map_const_iterator(const Node* node) : _node{node} {}

    /**
     * @brief Construct a new Map_const_iterator object
     *
     * @param rhs const iterator to copy from
     */
    Map_const_iterator(const Map_const_iterator& rhs) : Map_const_iterator(rhs._node) {}

    /**
     * @brief Copy assignment operator
     *
     * @param rhs const iterator to copy from
     * @return Map_const_iterator& *this
     */
    Map_const_iterator& operator=(const Map_const_iterator& rhs) {
        if (this != &rhs)
            this->_node = rhs._node;
        return *this;
    }

    /**
     * @brief Destroy the Map_const_iterator object
     */
    virtual ~Map_const_iterator() { this->_node = nullptr; }

    /**
     * @brief Indirection operator
     *
     * @return const value_type& value stored in the node of this iterator
     */
    const value_type& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return *this->_node->_pair;
    }

    /**
     * @brief Structure Dereference operator
     *
     * @return const value_type* pointer to the value stored in the node of this iterator
     */
    const value_type* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentaion Fault");
        return this->_node->_pair;
    }

    /**
     * @brief Prefix Increment operator
     *
     * @return Map_const_iterator& *this
     */
    Map_const_iterator& operator++() {
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
     * @brief Postfix Increment operator
     *
     * @return Map_const_iterator iterator before incrementing
     */
    Map_const_iterator operator++(int) {
        Map_const_iterator iter(*this);
        ++(*this);
        return iter;
    }

    /**
     * @brief equality operator
     *
     * @param lhs first const iterator
     * @param rhs second const iterator
     * @return true if the two iterators point to the same node
     * @return false otherwise
     */
    friend bool operator==(const Map_const_iterator& lhs, const Map_const_iterator& rhs) { return lhs._node == rhs._node; }

    /**
     * @brief negated equality operator
     *
     * @param lhs first const iterator
     * @param rhs second const iterator
     * @return true if the two iteratos point to different nodes
     * @return false otherwise
     */
    friend bool operator!=(const Map_const_iterator& lhs, const Map_const_iterator& rhs) { return lhs._node != rhs._node; }

    /**
     * @brief Convert this iterator to a std::string
     *
     * @return string printable version of this
     */
    virtual string to_string() const {
        stringstream ss;
        ss << "<Map::const_iterator -> [";
        if (this->_node)
            ss << *(this->_node);
        else
            ss << "nullptr";
        ss << "]>";
        return ss.str();
    }
};

/**
 * @brief Iterator for map
 *
 * @tparam Key key type
 * @tparam Value value type
 */
template <class Key, class Value>
class Map_iterator : public Map_const_iterator<Key, Value> {
private:
    friend class Map<Key, Value>;
    typedef Map_Node<Key, Value> Node;
    typedef pair<const Key, Value> value_type;
    typedef Map_const_iterator<Key, Value> const_iterator;
public:
    /**
     * @brief Construct a new Map_iterator object
     */
    Map_iterator() : Map_const_iterator<Key, Value>() {}

    /**
     * @brief Construct a new Map_iterator object
     *
     * @param node node to point to
     */
    Map_iterator(const Node* node) : Map_const_iterator<Key, Value>(node) {}

    /**
     * @brief Construct a new Map_iterator object
     *
     * @param rhs const iterator to copy from
     */
    Map_iterator(const Map_const_iterator<Key, Value>& rhs) : Map_const_iterator<Key, Value>(rhs) {}

    /**
     * @brief
     *
     * @return value_type
     */
    value_type& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return *this->_node->_pair;
    }

    /**
     * @brief
     *
     * @return value_type*
     */
    value_type* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentaion Fault");
        return &*this->_node->_pair;
    }

    /**
     * @brief Prefix increment operator
     *
     * @return Map_iterator& iterator after incrementing
     */
    Map_iterator& operator++() {
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
     * @brief Postfix increment operator
     *
     * @return Map_iterator iterator before incrementing
     */
    Map_iterator operator++(int) {
        Map_iterator iter(*this);
        ++(*this);
        return iter;
    }

    /**
     * @brief equality operator
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if the two iteratos point to the same node
     * @return false otherwise
     */
    friend bool operator==(const Map_iterator& lhs, const Map_iterator& rhs) { return lhs._node == rhs._node; }

    /**
     * @brief negated equality operator
     *
     * @param lhs first iterator
     * @param rhs second iterator
     * @return true if the two iteratos point to different nodes
     * @return false otherwise
     */
    friend bool operator!=(const Map_iterator& lhs, const Map_iterator& rhs) { return lhs._node != rhs._node; }

    /**
     * @brief Converts this iterator to a std::string
     *
     * @return string printable version of this
     */
    string to_string() const override {
        stringstream ss;
        ss << "<Map::iterator -> [";
        if (this->_node)
            ss << *(this->_node);
        else
            ss << "nullptr";
        ss << "]>";
        return ss.str();
    }
};

template <class Key, class Value>
class Map {
private:
    typedef Map_Node<Key, Value> Node;

    /**
     * @brief root of the tree
     */
    Node* _root;

    /**
     * @brief Number of nodes in the tree
     */
    size_t _size;

    template <typename Type>
    Type max(const Type& a, const Type& b) const { return a > b ? a : b; }

    long height(Node* const& root) const { return !root ? 0l : root->_height; }

    long balace_factor(Node* const& root) const {
        return !root ?
            0l :
            this->height(root->_left) - this->height(root->_right);
    }

    size_t calcHeight(Node* const& root) const {
        return 1 + this->max<long>(this->height(root->_left), this->height(root->_right));
    }

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

        Node* node = new Node(*root->_pair);
        node->_left = this->copy(root->_left);
        if (node->_left)
            node->_left->_parent = node;
        node->_right = this->copy(root->_right);
        if (node->_right)
            node->_right->_parent = node;
        return node;
    }

    Node* balance(Node*& root) {
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
        if (root->_right)
            root->_right->_parent = root;
        temp->_left = root;
        if (temp->_left)
            temp->_left->_parent = temp;

        root->_height = this->calcHeight(root);
        temp->_height = this->calcHeight(temp);

        return temp;
    }

    Node* ll_rotate(Node*& root) {
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
        Node* temp = root->_left;
        root->_left = this->rr_rotate(temp);
        root->_left->_parent = root;
        return this->ll_rotate(root);
    }

    Node* rl_rotate(Node*& root) {
        Node* temp = root->_right;
        root->_right = this->ll_rotate(temp);
        root->_right->_parent = root;
        return this->rr_rotate(root);
    }

    Node* insert(Node*& root, const pair<const Key, Value>& _pair) {
        if (!root)
            return new Node(_pair);
        if (_pair.first < root->_pair->first) {
            root->_left = this->insert(root->_left, _pair);
            root->_left->_parent = root;
        } else if (_pair.first > root->_pair->first) {
            root->_right = this->insert(root->_right, _pair);
            root->_right->_parent = root;
        }

        root = this->balance(root);
        return root;
    }

    Node* remove(Node*& root, const Key& _key) {
        if (_key < root->_pair->first) {
            root->_left = this->remove(root->_left, _key);
            if (root->_left)
                root->_left->_parent = root;
        } else if (_key > root->_pair->first) {
            root->_right = this->remove(root->_right, _key);
            if (root->_right)
                root->_right->_parent = root;
        } else {
            Node* temp = nullptr;
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
                swap(root->_pair, temp->_pair);
                root->_right = this->remove(root->_right, temp->_pair->first);
                if (root->_right)
                    root->_right->_parent = root;
            }
        }

        root = this->balance(root);
        return root;
    }

    Node* search(Node* const& root, const Key& _key) const {
        if (!root)
            return nullptr;
        if (root->_pair->first == _key)
            return root;
        return this->search(_key < root->_pair->first ? root->_left : root->_right, _key);
    }

    Node* find_min(Node* const& root) const {
        Node* node = root;
        while (node && node->_left)
            node = node->_left;
        return node;
    }

    void print_tree(Node* const& root, ostream& os, size_t trace) const {
        if (root->_right)
            this->print_tree(root->_right, os, trace + 1);
        os << string(trace * 2, ' ') << *root << "\n";
        if (root->_left)
            this->print_tree(root->_left, os, trace + 1);
    }
public:
    typedef Map_const_iterator<Key, Value> const_iterator;
    typedef Map_iterator<Key, Value> iterator;

    /**
     * @brief Construct a new Map object
     */
    Map() : _root{nullptr}, _size{0} {}

    /**
     * @brief Construct a new Map object
     *
     * @param rhs map to copy from
     */
    Map(const Map& rhs) : _root{this->copy(rhs._root)}, _size{rhs._size} {}

    /**
     * @brief Destroy the Map object
     */
    ~Map() { this->make_empty(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs
     * @return Map&
     */
    Map& operator=(const Map& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs._root);
            this->_size = rhs._size;
        }

        return *this;
    }

    /**
     * @brief
     *
     * @param key
     * @return Value&
     */
    Value& at(const Key& key) {
        const Node* node = this->search(this->_root, key);
        if (node)
            return node->_pair->second;
        stringstream ss;
        ss << key << " is not in the map.";
        throw out_of_range(ss.str());
    }

    /**
     * @brief
     *
     * @param key
     * @return const Value&
     */
    const Value& at(const Key& key) const {
        const Node* node = this->_size(this->_root, key);
        if (node)
            return node->_pair->second;
        stringstream ss;
        ss << key;
        ss << " is not in the map.";
        throw out_of_range(ss.str());
    }

    /**
     * @brief
     *
     * @param key
     * @return Value&
     */
    Value& operator[](const Key& key) {
        const_iterator index = this->find(key);
        if (index._node)
            return this->at(key);
        else {
            iterator it = this->insert(index, {key, Value()});
            return this->at(key);
        }
    }

    /**
     * @brief
     *
     * @param key
     * @return const Value&
     */
    const Value& operator[](const Key& key) const {
        Node* node = this->search(this->_root, key);
        if (node)
            return this->at(key);
        else {
            pair<iterator, bool> p(this->insert({key, Value()}));
            return this->at(key);
        }
    }

    /**
     * @brief
     *
     * @return iterator
     */
    iterator begin() { return iterator(this->find_min(this->_root)); }

    /**
     * @brief
     *
     * @return const_iterator
     */
    const_iterator begin() const { return const_iterator(this->find_min(this->_root)); }

    /**
     * @brief
     *
     * @return iterator
     */
    iterator end() { return iterator(nullptr); }

    /**
     * @brief
     *
     * @return const_iterator
     */
    const_iterator end() const { return const_iterator(nullptr); }

    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_empty() const { return !this->_size; }

    /**
     * @brief
     *
     * @return size_t
     */
    size_t size() const { return this->_size; }

    /**
     * @brief Prevents memory leaks by deallocating the map
     */
    void make_empty() {
        this->_root = this->clear(this->_root);
        this->_size = 0;
    }

    /**
     * @brief
     *
     * @param _pair
     * @return pair<iterator, bool>
     */
    pair<iterator, bool> insert(const pair<const Key, Value>& _pair) {
        const Node* node = this->search(this->_root, _pair.first);
        if (node)
            return pair(iterator(node), false);

        this->_root = this->insert(this->_root, _pair);
        ++this->_size;
        return pair(this->find(_pair.first), true);
    }

    /**
     * @brief
     *
     * @param hint
     * @param _pair
     * @return iterator
     */
    iterator insert(const_iterator hint, const pair<const Key, Value>& _pair) {
        const Node* node = this->search(this->_root, _pair.first);
        if (node)
            return iterator(node);

        const Node* location = hint._node;
        if (!this->_root || !location)
            this->_root = this->insert(this->_root, _pair);
        else
            this->insert(const_cast<Node*&>(location), _pair);
        ++this->_size;
        return this->find(_pair.first);
    }

    /**
     * @brief
     *
     * @param key
     * @return size_t
     */
    size_t remove(const Key& key) {
        if (!this->contains(key))
            return 0;
        this->_root = this->remove(this->_root, key);
        --this->_size;
        return 1;
    }

    /**
     * @brief
     *
     * @param index
     * @return iterator
     */
    iterator remove(const_iterator index) {
        if (!this->_root)
            return iterator(nullptr);
        if (!index._node)
            throw invalid_argument("Iterator does not point anywhere");

        const_iterator temp = index;
        iterator it = (++temp)._node;
        Key value;
        try {
            value = temp->first;
        } catch (const runtime_error& err) {
            it = nullptr;
        }
        this->_root = this->remove(this->_root, index->first);
        if (this->_root)
            this->_root->_parent = nullptr;
        --this->_size;
        return it._node ? this->find(value) : it;
    }

    /**
     * @brief
     *
     * @param key
     * @return true
     * @return false
     */
    bool contains(const Key& key) const { return this->search(this->_root, key); }

    /**
     * @brief
     *
     * @param key
     * @return iterator
     */
    iterator find(const Key& key) { return iterator(this->search(this->_root, key)); }

    /**
     * @brief
     *
     * @param key
     * @return const_iterator
     */
    const_iterator find(const Key& key) const { return const_iterator(this->search(this->_root, key)); }

    /**
     * @brief
     *
     * @param os
     */
    void print_map(ostream& os = cout) const {
        if (this->_size) {
            os << "{";
            const_iterator iter(this->begin());
            for (size_t i = 0; i < this->_size; ++i) {
                os << iter->first << ": " << iter->second;
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
     * @brief Construct a new Map object
     *
     * @param rhs map to move from
     */
    Map(Map&& rhs) : Map() { swap(this->_root, rhs._root); swap(this->_size, rhs._size); }

    /**
     * @brief Move assignment operator
     *
     * @param rhs map to move from
     * @return Map& *this
     */
    Map& operator=(Map&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs._root);
            swap(this->_root, rhs._size);
        }

        return *this;
    }

    // pair<iterator, bool> insert(pair<const Key, Value>&& pair);
    // iterator insert(const_iterator hint, pair<const Key, Value>&& pair);
    /**
     * @brief print the internal tree
     *
     * @param os ostream to print to
     */
    void print_tree(ostream& os = cout) const {
        if (this->_size)
            this->print_tree(this->_root, os, 0);
        else
            os << "<empty>";
    }
};

template <class Key, class Value>
ostream& operator<<(ostream& os, const Map_const_iterator<Key, Value>& iter) { return os << iter.to_string(); }
