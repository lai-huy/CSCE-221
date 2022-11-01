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
 * @brief Color of each node
 */
enum Color { RED, BLACK };

/**
 * @brief Node class for map
 *
 * @tparam Key key type of the node
 * @tparam Value key type of the node
 */
template <class Key, class Value>
class Map_Node {
    friend class Map<Key, Value>;
    friend class Map_const_iterator<Key, Value>;
    friend class Map_iterator<Key, Value>;
    typedef Map_Node<Key, Value> Node;

    /**
     * @brief pointer to a Key, Value pair stored in the node
     */
    pair<const Key, Value>* _pair;

    /**
     * @brief Color of this node
     */
    Color _color;

    /**
     * @brief a pointer to the left child of this node
     */
    Node* _left;

    /**
     * @brief a pointer to the right child of this node
     *
     */
    Node* _right;

    /**
     * @brief a pointer to the parent of this node
     */
    Node* _parent;
public:
    /**
     * @brief Construct a new Node object
     *
     * @param rhs comparable to set as the key
    */
    Map_Node(const pair<const Key, Value>& rhs) : Map_Node(rhs, Color::RED) {}

    /**
     * @brief Construct a new Node object
     *
     * @param rhs comparable to set as the key
     * @param color Color to set as the color
     */
    Map_Node(const pair<const Key, Value>& rhs, const Color& color) : _pair{new pair<const Key, Value>(rhs)}, _color{color}, _left{nullptr}, _right{nullptr}, _parent{nullptr} {}

    /**
     * @brief Determines the sibling of this node
     *
     * @return Node* a pointer to the sibling of this node
     */
    Node* sibling() const {
        if (!this->_parent)
            return nullptr;
        return this->isRight() ? this->_parent->_left : this->_parent->_right;
    }

    /**
     * @brief Determine if both children are a specified color
     *
     * @param color the color of both children
     * @return true if both children are a specified color
     * @return false otherwise
     */
    bool hasColorChildren(const Color& color) const {
        return (!this->_left && !this->_right && color == Color::BLACK) ||
            ((this->_left && this->_left->_color == color) && (this->_right && this->_right->_color == color));
    }

    /**
     * @brief Determines if the left nibling is red
     *
     * @return true if left nibling is red
     * @return false otherwise
     */
    bool leftNiblingRed() const {
        Node* sibling = this->sibling();
        return sibling && sibling->_left && sibling->_left->_color == Color::RED;
    }

    /**
     * @brief Determines if the right nibling if red
     *
     * @return true if the right nibling if red
     * @return false otherwise
     */
    bool rightNiblingRed() const {
        Node* sibling = this->sibling();
        return sibling && sibling->_right && sibling->_right->_color == Color::RED;
    }

    /**
     * @brief Determine if this is a left child
     *
     * @return true if this is a left child
     * @return false otherwise
     */
    bool isLeft() const { return this->_parent ? this == this->_parent->_left : false; }

    /**
     * @brief Determine if this is a right child
     *
     * @return true if this is a right child
     * @return false otherwise
     */
    bool isRight() const { return this->_parent ? this == this->_parent->_right : false; }

    /**
     * @brief Counts the number of children this node has
     *
     * @return size_t the number of children this node has
     */
    size_t countChildren() const {
        size_t count = 0;
        if (this->_left)
            ++count;
        if (this->_right)
            ++count;
        return count;
    }

    /**
     * @brief Converts this node to a std::string
     *
     * @return string printable version of this
     */
    string to_string() const {
        stringstream ss;
        switch (this->_color) {
        case Color::RED:
            ss << "🟥 ";
            break;
        default:
            ss << "⬛ ";
            break;
        }
        ss << this->_pair->first << ": " << this->_pair->second;
        return ss.str();
    }

    /**
     * @brief Insertion operator
     *
     * @param os ostream to insert to
     * @param node node to print
     * @return ostream& ostream to insert to
     */
    friend ostream& operator<<(ostream& os, const Node& node) { return os << node.to_string(); }
};

/**
 * @brief Const iterator for map
 *
 * @tparam Key key type
 * @tparam Value key type
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
    Node* _node;
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
    Map_const_iterator(Node* const& node) : _node{node} {}

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
     * @return const value_type& key stored in the node of this iterator
     */
    const value_type& operator*() const {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return *this->_node->_pair;
    }

    /**
     * @brief Structure Dereference operator
     *
     * @return const value_type* pointer to the key stored in the node of this iterator
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
 * @tparam Value key type
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
    Map_iterator(Node* const& node) : Map_const_iterator<Key, Value>(node) {}

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
        return this->_node->_pair;
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
public:
    typedef Map_Node<Key, Value> Node;
    typedef Map_const_iterator<Key, Value> const_iterator;
    typedef Map_iterator<Key, Value> iterator;
    typedef pair<const Key, Value> value_type;

private:
private:
    /**
     * @brief Root of the 🟥⬛🌲
     */
    Node* _root;

    /**
     * @brief size of the set
     */
    size_t _size;

    /**
     * @brief Determine if a subtree contains a key
     *
     * @param root subtree's root
     * @param key key to search for
     * @return true if the subtree contains the key
     * @return false otherwise
     */
    bool contains(Node* const& root, const Key& key) {
        if (!root)
            return false;
        if (root->_pair->first == key)
            return true;
        return this->contains(root->_pair->first > key ? root->_left : root->_right, key);
    }

    /**
     * @brief Inserts a key into a subtree
     *
     * @param node subtree's root
     * @param pair key to insert
     */
    void insert(Node* node, const value_type& pair) {
        if (!node) {
            node = new Node(pair);
            if (!this->_root)
                this->_root = node;
            return;
        }

        if (node->_pair->first == pair.first)
            return;

        if (node->_pair->first > pair.first) {
            if (!node->_left) {
                node->_left = new Node(pair);
                node->_left->_parent = node;

                if (node->_color == Color::BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isLeft()) {
                        node = this->rotateRight(node->_parent);
                        node->_color = Color::BLACK;
                        node->_left->_color = node->_right->_color = Color::RED;
                        return;
                    } else {
                        node = this->rotateRight(node);
                        node = this->rotateLeft(node->_parent);
                        node->_color = Color::BLACK;
                        node->_left->_color = node->_right->_color = Color::RED;
                        return;
                    }
                }
            }
        } else if (node->_pair->first < pair.first) {
            if (!node->_right) {
                node->_right = new Node(pair);
                node->_right->_parent = node;
                if (node->_color == Color::BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isRight()) {
                        node = this->rotateLeft(node->_parent);
                        node->_color = Color::BLACK;
                        node->_right->_color = node->_left->_color = Color::RED;
                        return;
                    } else {
                        node = this->rotateLeft(node);
                        node = this->rotateRight(node->_parent);
                        node->_color = Color::BLACK;
                        node->_right->_color = node->_left->_color = Color::RED;
                        return;
                    }
                }
            }
        }

        if (node->hasColorChildren(Color::RED)) {
            node->_color = Color::RED;
            node->_right->_color = node->_left->_color = Color::BLACK;

            if (node->_parent && node->_parent->_color == Color::RED) {
                if (node->isLeft() && node->_parent->isLeft()) {
                    node = this->rotateRight(node->_parent->_parent);
                    node->_color = Color::BLACK;
                    node->_left->_color = node->_right->_color = Color::RED;
                    this->insert(node, pair);
                    return;
                }
                if (node->isRight() && node->_parent->isRight()) {
                    node = this->rotateLeft(node->_parent->_parent);
                    node->_color = Color::BLACK;
                    node->_left->_color = node->_right->_color = Color::RED;
                    this->insert(node, pair);
                    return;
                }
                if (node->isRight() && node->_parent->isLeft()) {
                    node = this->rotateLeft(node->_parent);
                    node = this->rotateRight(node->_parent);
                    node->_color = Color::BLACK;
                    node->_left->_color = node->_right->_color = Color::RED;
                    this->insert(node, pair);
                    return;
                }
                if (node->isLeft() && node->_parent->isRight()) {
                    node = this->rotateRight(node->_parent);
                    node = this->rotateLeft(node->_parent);
                    node->_color = Color::BLACK;
                    node->_left->_color = node->_right->_color = Color::RED;
                    this->insert(node, pair);
                    return;
                }
            }
        }
        this->insert(node->_pair->first > pair.first ? node->_left : node->_right, pair);
    }

    /**
     * @brief Remove a key from a subtree
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void remove(Node* node, const Key& key) {
        if (node == this->_root && node->_pair->first == key && !node->countChildren()) {
            delete node;
            node = this->_root = nullptr;
        } else if (node && node->hasColorChildren(Color::BLACK) && node == this->_root) {
            this->_root->_color = Color::RED;
            this->decideDelete(this->_root, key);
        } else
            this->setUpRemoval(node, key);
        if (this->_root)
            this->_root->_color = Color::BLACK;
    }

    /**
     * @brief Determine which direction to traverse when deleting
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void decideDelete(Node* node, const Key& key) {
        if (!node)
            return;
        if (node->_pair->first > key && !node->_left)
            return;
        if (node->_pair->first < key && !node->_right)
            return;
        if (node->_pair->first == key)
            this->removeNode(node);
        else
            this->setUpRedLeaf(node->_pair->first > key ? node->_left : node->_right, key);
    }

    /**
     * @brief Set up Red Leaf for removal
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void setUpRedLeaf(Node* node, const Key& key) {
        if (!node) return;
        if (node->hasColorChildren(Color::BLACK))
            this->setUpRotations(node, key);
        else
            this->setUpRemoval(node, key);
    }

    /**
     * @brief Set up rotations on the way down
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void setUpRotations(Node* node, const Key& key) {
        Node* sibling = node->sibling();
        if (sibling && sibling->hasColorChildren(Color::BLACK)) {
            this->recolorChildren(node, key);
        } else if ((node->isLeft() && node->leftNiblingRed()) || (node->isRight() && node->rightNiblingRed())) {
            this->rotateNiblingRed(node, key);
        } else
            this->rotateNiblingBlack(node, key);
    }

    /**
     * @brief Recolor node and its sibling to RED
     *
     * @param node node to recolor
     * @param key key to remove
     */
    void recolorChildren(Node* node, const Key& key) {
        node->_color = node->sibling()->_color = Color::RED;
        if (node->_parent)
            node->_parent->_color = Color::BLACK;
        this->decideDelete(node, key);
    }

    /**
     * @brief Rotates if the node's nibling is red
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void rotateNiblingRed(Node* node, const Key& key) {
        if (node->isLeft()) {
            node = this->rotateRight(node->sibling());
            node = this->rotateLeft(node->_parent);
            node->_left->_color = Color::BLACK;
            node->_left->_left->_color = Color::RED;
            node = node->_left->_left;
        } else {
            node = this->rotateLeft(node->sibling());
            node = this->rotateRight(node->_parent);
            node->_right->_color = Color::BLACK;
            node->_right->_right->_color = Color::RED;
            node = node->_right->_right;
        }
        this->decideDelete(node, key);
    }

    /**
     * @brief Rotates if the node's nibling is black
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void rotateNiblingBlack(Node* node, const Key& key) {
        if (node->isLeft()) {
            node = this->rotateLeft(node->_parent);
            node->_color = Color::RED;
            node->_right->_color = node->_left->_color = Color::BLACK;
            node = node->_left->_left;
        } else {
            node = this->rotateRight(node->_parent);
            node->_color = Color::RED;
            node->_right->_color = node->_left->_color = Color::BLACK;
            node = node->_right->_right;
        }
        node->_color = Color::RED;
        this->decideDelete(node, key);
    }

    /**
     * @brief Set
     *
     * @param node
     * @param key
     */
    void setUpRemoval(Node* node, const Key& key) {
        if (key == node->_pair->first)
            this->removeNode(node);
        else {
            node = node->_pair->first > key ? node->_left : node->_right;
            if (!node) return;
            else if (node->_color == Color::RED)
                this->decideDelete(node, key);
            else
                this->rotateRemoval(node, key);
        }
    }

    /**
     * @brief Rotate on the way down
     *
     * @param node subtree's root
     * @param key key to remove
     */
    void rotateRemoval(Node* node, const Key& key) {
        if (node->isLeft()) {
            node = this->rotateLeft(node->_parent);
            node->_left->_color = Color::RED;
            node->_color = Color::BLACK;
            node = node->_left->_left;
        } else {
            node = this->rotateRight(node->_parent);
            node->_right->_color = Color::RED;
            node->_color = Color::BLACK;
            node = node->_right->_right;
        }
        this->setUpRedLeaf(node, key);
    }

    /**
     * @brief Removes the node from the tree
     *
     * @param node a pointer to the node to remove
     */
    void removeNode(Node* node) {
        if (!node)
            return;
        switch (node->countChildren()) {
        case 0:
            if (node->isLeft())
                node->_parent->_left = nullptr;
            if (node->isRight())
                node->_parent->_right = nullptr;
            if (node != this->_root) {
                delete node;
                node = nullptr;
            }
            return;
        case 1:
            if (node->isLeft()) {
                if (node->_left) {
                    node->_parent->_left = node->_left;
                    node->_left->_parent = node->_parent;
                    node->_left->_color = Color::BLACK;
                } else if (node->_right) {
                    node->_parent->_left = node->_right;
                    node->_right->_parent = node->_parent;
                    node->_right->_color = Color::BLACK;
                }
            } else if (node->isRight()) {
                if (node->_right) {
                    node->_parent->_right = node->_right;
                    node->_right->_parent = node->_parent;
                    node->_right->_color = Color::BLACK;
                } else if (node->_left) {
                    node->_parent->_right = node->_left;
                    node->_left->_parent = node->_parent;
                    node->_left->_color = Color::BLACK;
                }
            } else if (node == this->_root)
                this->_root = node->_left ? node->_left : node->_right;
            delete node;
            node = nullptr;
            return;
        default:
            Node* temp = this->find_min(node->_right);
            value_type* key = temp->_pair;
            if (node->_color == Color::RED) {
                node->_pair = temp->_pair;
                this->setUpRedLeaf(node->_right, node->_pair->first);
            } else {
                this->setUpRemoval(node, temp->_pair->first);
                node->_pair = key;
            }
            return;
        }
    }

    /**
     * @brief print a subtree to an ostream
     *
     * @param root subtree's root
     * @param os ostream to print to
     * @param lvl depth of root
     */
    void print_tree(const Node* const& root, ostream& os, size_t lvl) const {
        if (root->_right)
            this->print_tree(root->_right, os, lvl + 1);
        os << string(lvl << 2, ' ') << *root << "\n";
        if (root->_left)
            this->print_tree(root->_left, os, lvl + 1);
    }

    /**
     * @brief Rotate left arround a node
     *
     * @param root node to rotate arround
     * @return Node* a pointer to the replacement node
     */
    Node* rotateLeft(Node* root) {
        Node* temp = root->_right;
        root->_right = temp->_left;
        if (temp->_left)
            temp->_left->_parent = root;
        temp->_parent = root->_parent;
        if (!root->_parent)
            this->_root = temp;
        else if (root->isRight())
            root->_parent->_right = temp;
        else if (root->isLeft())
            root->_parent->_left = temp;
        temp->_left = root;
        root->_parent = temp;
        return temp;
    }

    /**
     * @brief Rotate right arround a node
     *
     * @param root node to rotate arround
     * @return Node* a pointer to the replacement node
     */
    Node* rotateRight(Node* root) {
        Node* temp = root->_left;
        root->_left = temp->_right;
        if (temp->_right)
            temp->_right->_parent = root;
        temp->_parent = root->_parent;
        if (!root->_parent)
            this->_root = temp;
        else if (root->isLeft())
            root->_parent->_left = temp;
        else if (root->isRight())
            root->_parent->_right = temp;
        temp->_right = root;
        root->_parent = temp;
        return temp;
    }

    /**
     * @brief Prevents memory leaks by dellocating
     *
     * @param root current subtree being cleared
     * @return Node* nullptr
     */
    Node* clear(Node*& root) {
        if (root) {
            root->_left = this->clear(root->_left);
            root->_right = this->clear(root->_right);
            root->_parent = nullptr;
            delete root;
        }

        return root = nullptr;
    }

    /**
     * @brief Copy a subtree into this tree's subtree
     *
     * @param root subtree to copy from
     * @return Node* new subtree
     */
    Node* copy(const Node* const& root) {
        if (!root)
            return nullptr;
        Node* node = new Node(*root->_pair, root->_color);
        node->_left = this->copy(root->_left);
        if (node->_left)
            node->_left->_parent = node;
        node->_right = this->copy(root->_right);
        if (node->_right)
            node->_right->_parent = node;
        return node;
    }

    /**
     * @brief Finds the minimum node of a subtree
     *
     * @param node subtree's root
     * @return Node* a pointer to the node with the minimum key
     */
    Node* find_min(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->_left)
            temp = temp->_left;
        return temp;
    }

    /**
     * @brief Finds the maximum node of a subtree
     *
     * @param node subtree's root
     * @return Node* a poitner to the node with the maximum key
     */
    Node* find_max(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->_right)
            temp = temp->_right;
        return temp;
    }

    Node* search(Node* const& root, const Key& key) const {
        if (!root)
            return nullptr;
        if (root->_pair->first == key)
            return root;
        return this->search(root->_pair->first < key ? root->_right : root->_left, key);
    }

public:
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
        Node* node = this->search(this->_root, key);
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
        Node* node = this->_size(this->_root, key);
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
        Node* node = this->search(this->_root, _pair.first);
        if (node)
            return pair(iterator(node), false);

        this->insert(this->_root, _pair);
        this->_root->_color = Color::BLACK;
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
        Node* node = this->search(this->_root, _pair.first);
        if (node)
            return iterator(node);

        const Node* location = hint._node;
        if (!this->_root || !location)
            this->insert(this->_root, _pair);
        else
            this->insert(const_cast<Node*&>(location), _pair);
        this->_root->_color = Color::BLACK;
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
        this->remove(this->_root, key);
        if (this->_root) {
            this->_root->_parent = nullptr;
            this->_root->_color = Color::BLACK;
        }
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
        Key key;
        try {
            key = temp->first;
        } catch (const runtime_error& err) {
            it = nullptr;
        }
        this->remove(this->_root, index->first);
        if (this->_root) {
            this->_root->_parent = nullptr;
            this->_root->_color = Color::BLACK;
        }
        --this->_size;
        return it._node ? this->find(key) : it;
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
