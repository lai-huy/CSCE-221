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
 * @brief Color of each node
 */
enum Color { RED, BLACK };

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
    typedef Set_Node<Comparable> Node;

    /**
     * @brief Comparable stored in the node
     */
    Comparable _value;

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
     * @param rhs comparable to set as the value
    */
    Set_Node(const Comparable& rhs) : Set_Node(rhs, Color::RED) {}

    /**
     * @brief Construct a new Node object
     *
     * @param rhs comparable to set as the value
     * @param color Color to set as the color
     */
    Set_Node(const Comparable& rhs, const Color& color) : _value{rhs}, _color{color}, _left{nullptr}, _right{nullptr}, _parent{nullptr} {}

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
        case Color::BLACK:
            ss << "⬛ ";
            break;
        default:
            ss << "🟦 ";
            break;
        }
        ss << this->_value;
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
    Node* _node;
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
    Set_const_iterator(Node* const& node) : _node{node} {}

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
     * @param lhs iterator const iterator
     * @param rhs Node* a pointer to a node.
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
        stringstream ss{};
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
    Set_iterator(Node* const& node) : Set_const_iterator<Comparable>(node) {}

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
    Comparable& operator*() {
        if (!this->_node)
            throw runtime_error("Segmentation Fault");
        return this->_node->_value;
    }

    /**
     * @brief Member access operator
     *
     * @return Comparable* pointer to the value stored in the node this points to.
     */
    Comparable* operator->() {
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
        stringstream ss{};
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
public:
    typedef Set_Node<Comparable> Node;
    typedef Set_const_iterator<Comparable> const_iterator;
    typedef Set_iterator<Comparable> iterator;

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
     * @brief Inserts a value into a subtree
     *
     * @param node subtree's root
     * @param value value to insert
     */
    void insert(Node* node, const Comparable& value) {
        if (!node) {
            node = new Node(value);
            if (!this->_root)
                this->_root = node;
            return;
        }

        if (node->_value > value) {
            if (!node->_left) {
                node->_left = new Node(value);
                node->_left->_parent = node;

                if (node->_color == Color::BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isLeft())
                        node = this->rotateRight(node->_parent);
                    else {
                        node = this->rotateRight(node);
                        node = this->rotateLeft(node->_parent);
                    }

                    node->_color = Color::BLACK;
                    node->_left->_color = node->_right->_color = Color::RED;
                    return;
                }
            }
        } else if (node->_value < value) {
            if (!node->_right) {
                node->_right = new Node(value);
                node->_right->_parent = node;
                if (node->_color == Color::BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isRight())
                        node = this->rotateLeft(node->_parent);
                    else {
                        node = this->rotateLeft(node);
                        node = this->rotateRight(node->_parent);
                    }

                    node->_color = Color::BLACK;
                    node->_right->_color = node->_left->_color = Color::RED;
                    return;
                }
            }
        }

        if (node->hasColorChildren(Color::RED)) {
            node->_color = Color::RED;
            node->_right->_color = node->_left->_color = Color::BLACK;

            if (node->_parent && node->_parent->_color == Color::RED) {
                if (node->isLeft() && node->_parent->isLeft())
                    node = this->rotateRight(node->_parent->_parent);
                else if (node->isRight() && node->_parent->isRight())
                    node = this->rotateLeft(node->_parent->_parent);
                else if (node->isRight() && node->_parent->isLeft()) {
                    node = this->rotateLeft(node->_parent);
                    node = this->rotateRight(node->_parent);
                } else if (node->isLeft() && node->_parent->isRight()) {
                    node = this->rotateRight(node->_parent);
                    node = this->rotateLeft(node->_parent);
                }

                node->_color = Color::BLACK;
                node->_left->_color = node->_right->_color = Color::RED;
                this->insert(node, value);
                return;
            }
        }
        this->insert(node->_value > value ? node->_left : node->_right, value);
    }

    /**
     * @brief Remove a value from a subtree
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void remove(Node* node, const Comparable& value) {
        if (node == this->_root && node->_value == value && !node->countChildren()) {
            delete node;
            node = this->_root = nullptr;
        } else if (node && node->hasColorChildren(Color::BLACK) && node == this->_root) {
            this->_root->_color = Color::RED;
            this->decideDelete(this->_root, value);
        } else
            this->setUpRemoval(node, value);
        if (this->_root)
            this->_root->_color = Color::BLACK;
    }

    /**
     * @brief Determine which direction to traverse when deleting
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void decideDelete(Node* node, const Comparable& value) {
        if (node->_value == value)
            this->removeNode(node);
        else
            this->setUpRedLeaf(node->_value > value ? node->_left : node->_right, value);
    }

    /**
     * @brief Set up Red Leaf for removal
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void setUpRedLeaf(Node* node, const Comparable& value) {
        if (!node)
            return;
        if (node->hasColorChildren(Color::BLACK))
            this->setUpRotations(node, value);
        else
            this->setUpRemoval(node, value);
    }

    /**
     * @brief Set up rotations on the way down
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void setUpRotations(Node* node, const Comparable& value) {
        Node* sibling = node->sibling();
        if (sibling && sibling->hasColorChildren(Color::BLACK))
            this->recolorChildren(node, value);
        else if ((node->isLeft() && node->leftNiblingRed()) || (node->isRight() && node->rightNiblingRed()))
            this->rotateNiblingRed(node, value);
        else
            this->rotateNiblingBlack(node, value);
    }

    /**
     * @brief Recolor node and its sibling to RED
     *
     * @param node node to recolor
     * @param value value to remove
     */
    void recolorChildren(Node* node, const Comparable& value) {
        node->_color = node->sibling()->_color = Color::RED;
        if (node->_parent)
            node->_parent->_color = Color::BLACK;
        this->decideDelete(node, value);
    }

    /**
     * @brief Rotates if the node's nibling is red
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void rotateNiblingRed(Node* node, const Comparable& value) {
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
        this->decideDelete(node, value);
    }

    /**
     * @brief Rotates if the node's nibling is black
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void rotateNiblingBlack(Node* node, const Comparable& value) {
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
        this->decideDelete(node, value);
    }

    /**
     * @brief Set
     *
     * @param node
     * @param value
     */
    void setUpRemoval(Node* node, const Comparable& value) {
        if (value == node->_value)
            this->removeNode(node);
        else {
            node = node->_value > value ? node->_left : node->_right;
            if (!node)
                return;
            else if (node->_color == Color::RED)
                this->decideDelete(node, value);
            else
                this->rotateRemoval(node, value);
        }
    }

    /**
     * @brief Rotate on the way down
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void rotateRemoval(Node* node, const Comparable& value) {
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
        this->setUpRedLeaf(node, value);
    }

    /**
     * @brief Removes the node from the tree
     *
     * @param node a pointer to the node to remove
     */
    void removeNode(Node* node) {
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
            Comparable value = temp->_value;
            if (node->_color == Color::RED) {
                node->_value = temp->_value;
                this->setUpRedLeaf(node->_right, node->_value);
            } else {
                this->setUpRemoval(node, temp->_value);
                node->_value = value;
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
    void print_tree(Node* const& root, ostream& os, size_t lvl) const {
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
        Node* node = new Node(root->_value, root->_color);
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
     * @return Node* a pointer to the node with the minimum value
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
     * @return Node* a poitner to the node with the maximum value
     */
    Node* find_max(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->_right)
            temp = temp->_right;
        return temp;
    }

    Node* search(Node* const& root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->_value == value)
            return root;
        return this->search(root->_value < value ? root->_right : root->_left, value);
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
        Node* node = this->search(this->_root, value);
        if (node)
            return pair(iterator(node), false);

        this->insert(this->_root, value);
        ++this->_size;
        this->_root->_color = Color::BLACK;
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
        Node* node = this->search(this->_root, value);
        if (node)
            return iterator(node);

        if (!this->_root || !hint._node)
            this->insert(this->_root, value);
        else if (hint._node == this->_root)
            this->insert(this->_root, value);
        else {
            Node* location = hint._node;
            Node* min = this->find_min(this->_root);
            Node* max = this->find_max(this->_root);

            if (!(value < min->_value && location == min) && !(value > max->_value && location == max))
                // go up the tree until 🥪
                while ((value < location->_value && value < location->_parent->_value) || (value > location->_value && value > location->_parent->_value)) {
                    location = location->_parent;
                    if (location == this->_root)
                        break;
                }

            // go up the tree until balance condition
            if (location != this->_root) {
                Node* sibling = location->sibling();
                bool balance = sibling && location->_color == Color::RED && sibling->_color == Color::RED && location->_parent->_color == Color::BLACK;
                while (!balance) {
                    location = location->_parent;
                    if (location == this->_root)
                        break;
                    balance = sibling && location->_color == Color::RED && sibling->_color == Color::RED && location->_parent->_color == Color::BLACK;
                }
            }

            this->insert(location->_parent ? location->_parent : location, value);
        }
        ++this->_size;
        this->_root->_color = Color::BLACK;
        return this->find(value);
    }

    /**
     * @brief Remove a value from the set
     *
     * @param value value to remove
     * @return size_t the number of elementes removed
     */
    size_t remove(const Comparable& value) {
        if (!this->search(this->_root, value))
            return 0;
        this->remove(this->_root, value);
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
        if (!index._node)
            throw invalid_argument("Iterator does not point anywhere");
        if (!this->search(this->_root, *index))
            throw invalid_argument("Iterator does not point to a value in the set");

        const_iterator temp = index;
        iterator it = (++temp)._node;
        Comparable value;
        try {
            value = *temp;
        } catch (const runtime_error& err) {
            it = nullptr;
        }
        this->remove(this->_root, *index);
        if (this->_root) {
            this->_root->_parent = nullptr;
            this->_root->_color = Color::BLACK;
        }
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
    Set(Set&& rhs) : Set() {
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
        Comparable v{};
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
        Comparable v{};
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