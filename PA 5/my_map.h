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

// forward declarations
template <class K, class V> class Map;
template <class K, class V> class Map_const_iterator;
template <class K, class V> class Map_iterator;

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
    Map_Node(const pair<const Key, Value> pair) : _pair{new std::pair<const Key, Value>{pair}}, _height{1}, _left{nullptr}, _right{nullptr}, _parent{nullptr} {}
    Map_Node(const Map_Node& rhs) = default;

    ~Map_Node() {
        if (this->_pair)
            delete this->_pair;
    }

    Map_Node& operator=(const Map_Node& rhs) = default;

    const pair<const Key, Value>& data() const { return *this->_pair; }
    pair<const Key, Value> data() { return *this->_pair; }

    /**
     * @brief Determine if this node is a leaf.
     *
     * @return true if this node is a leaf
     * @return false otherwise
     */
    bool isLeaf() const { return !this->_left && !this->_right; }

    bool isLeft() const { return this->_parent ? this == this->_parent->_left : false; }

    bool isRight() const { return this->_parent ? this == this->_parent->_right : false; }

    friend ostream& operator<<(ostream& os, const Map_Node& node) {
        os << node._pair->first << ": " << node._pair->second;
        return os;
    }
};

// TODO(stduent): implement this
template <class Key, class Value>
class Map_const_iterator {
private:
    friend class Map<Key, Value>;
    typedef Map_Node<Key, Value> Node;
    typedef pair<const Key, Value> value_type;
protected:
    const Node* _node;
public:
    Map_const_iterator() : _node{nullptr} {};
    Map_const_iterator(const Node* node) : _node{node} {}
    Map_const_iterator(const Map_const_iterator& rhs) : _node{rhs._node} {}

    Map_const_iterator& operator=(const Map_const_iterator& rhs) {
        if (this != &rhs)
            this->_node = rhs._node;
        return *this;
    }

    virtual ~Map_const_iterator() { this->_node = nullptr; }

    const value_type& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return *this->_node->_pair;
    }

    const value_type* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentaion Fault");
        return this->_node->_pair;
    }

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

    Map_const_iterator operator++(int) {
        Map_const_iterator iter(*this);
        ++(*this);
        return iter;
    }

    friend bool operator==(const Map_const_iterator& lhs, const Map_const_iterator& rhs) { return lhs._node == rhs._node; }

    friend bool operator!=(const Map_const_iterator& lhs, const Map_const_iterator& rhs) { return lhs._node != rhs._node; }

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

// TODO(stduent): implement this
template <class Key, class Value>
class Map_iterator : public Map_const_iterator<Key, Value> {
private:
    friend class Map<Key, Value>;
    typedef Map_Node<Key, Value> Node;
    typedef pair<const Key, Value> value_type;
    typedef Map_const_iterator<Key, Value> const_iterator;
public:
    Map_iterator() : Map_const_iterator<Key, Value>() {}
    Map_iterator(const Node* node) : Map_const_iterator<Key, Value>(node) {}
    Map_iterator(const Map_const_iterator<Key, Value>& rhs) : Map_const_iterator<Key, Value>(rhs) {}

    value_type operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return *this->_node->_pair;
    }

    const value_type* operator->() const {
        if (!this->_node)
            throw runtime_error("Segmentaion Fault");
        return this->_node->_pair;
    }

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

    Map_iterator operator++(int) {
        Map_iterator iter(*this);
        ++(*this);
        return iter;
    }

    friend bool operator==(const Map_iterator& lhs, const Map_iterator& rhs) { return lhs._node == rhs._node; }

    friend bool operator!=(const Map_iterator& lhs, const Map_iterator& rhs) { return lhs._node != rhs._node; }

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

// TODO(stduent): implement this
template <class Key, class Value>
class Map {
private:
    typedef Map_Node<Key, Value> Node;

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
            node->_parent = nullptr;
            delete node;
        }

        node = nullptr;
        return node;
    }

    Node* copy(const Node* root) {
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
        if (_key < root->_pair->first)
            root->_left = this->remove(root->_left, _key);
        else if (_key > root->_pair->first)
            root->_right = this->remove(root->_right, _key);
        else {
            if (root->isLeaf()) {
                delete root;
                root = nullptr;
                return root;
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
                Node* temp = this->find_min(root->_right);
                swap(root->_pair, temp->_pair);
                root->_right = this->remove(root->_right, temp->_pair->first);
            }
        }

        root = this->balance(root);
        return root;
    }

    const Node* search(const Node* root, const Key& _key) const {
        if (!root)
            return nullptr;
        if (root->_pair->first == _key)
            return root;
        return this->search(_key < root->_pair->first ? root->_left : root->_right, _key);
    }

    Node* find_min(Node* root) const {
        while (root && root->_left)
            root = root->_left;
        return root;
    }

    void print_tree(const Node* root, ostream& os, size_t trace) const {
        if (root->_right)
            this->print_tree(root->_right, os, trace + 1);
        os << string(trace * 2, ' ') << *root << "\n";
        if (root->_left)
            this->print_tree(root->_left, os, trace + 1);
    }
public:
    typedef Map_const_iterator<Key, Value> const_iterator;
    typedef Map_iterator<Key, Value> iterator;

    Map() : _root{nullptr}, _size{0} {}
    Map(const Map& rhs) : _root{this->copy(rhs._root)}, _size{rhs._size} {}
    ~Map() { this->make_empty(); }
    Map& operator=(const Map& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs._root);
            this->_size = rhs._size;
        }

        return *this;
    }

    Value& at(const Key& key) {
        const Node* node = this->search(this->_root, key);
        if (node)
            return node->_pair->second;
        stringstream ss;
        ss << key;
        ss << " is not in the map.";
        throw out_of_range(ss.str());
    }

    const Value& at(const Key& key) const {
        const Node* node = this->_size(this->_root, key);
        if (node)
            return node->_pair->second;
        stringstream ss;
        ss << key;
        ss << " is not in the map.";
        throw out_of_range(ss.str());
    }

    Value& operator[](const Key& key) { return this->search(this->_root, key)->_pair->second; }
    const Value& operator[](const Key& key) const { return this->search(this->_root, key)->_pair->second; }

    iterator begin() { return iterator(this->find_min(this->_root)); }
    const_iterator begin() const { return const_iterator(this->find_min(this->_root)); }
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return const_iterator(nullptr); }

    bool is_empty() const { return !this->_size; }
    size_t size() const { return this->_size; }

    void make_empty() {
        this->_root = this->clear(this->_root);
        this->_size = 0;
    }

    pair<iterator, bool> insert(const pair<const Key, Value>& _pair) {
        const Node* node = this->search(this->_root, _pair.first);
        if (node)
            return pair(iterator(node), false);

        this->_root = this->insert(this->_root, _pair);
        ++this->_size;
        return pair(iterator(this->search(this->_root, _pair.first)), true);
    }

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
        return iterator(this->search(this->_root, _pair.first));
    }

    size_t remove(const Key& key) {
        if (!this->contains(key))
            return 0;
        this->_root = this->remove(this->_root, key);
        --this->_size;
        return 1;
    }

    iterator remove(const_iterator iter) {
        if (!this->_root)
            throw invalid_argument("Set is empty");
        const_iterator end(this->end());
        if (iter == end)
            throw invalid_argument("Iterator does not point anywhere");
        const Key& key = iter->first;
        iterator it(++iter);
        this->_root = this->remove(this->_root, key);
        --this->_size;
        return it;
    }

    bool contains(const Key& key) const { return this->search(this->_root, key); }

    iterator find(const Key& key) { return iterator(this->search(this->_root, key)); }

    const_iterator find(const Key& key) const { return const_iterator(this->search(this->_root, key)); }

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
    // Map(Map&& rhs);
    // Map& operator=(Map&& rhs);
    // pair<iterator, bool> insert(pair<const Key, Value>&& pair);
    // iterator insert(const_iterator hint, pair<const Key, Value>&& pair);
    void print_tree(ostream& os = cout) const {
        if (this->_size)
            this->print_tree(this->_root, os, 0);
        else
            os << "<empty>";
    }
};

template <class Key, class Value>
ostream& operator<<(ostream& os, const Map_const_iterator<Key, Value>& iter) {
    return os << iter.to_string();
}
