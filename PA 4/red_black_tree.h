#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::cout, std::ostream;
using std::invalid_argument;
using std::string, std::wstring;
using std::swap;

/**
 * @brief A self-balancing Binary Search Tree.
 *
 * @tparam Comparable a data type that overloads the comparison operators
 */
template <typename Comparable>
class RedBlackTree {
public:
    /**
     * @brief An Extra bit that is used to ensure that the tree remains balanced during insertions and deletions.
     */
    enum Color { RED = 0, BLACK = 1 };

    /**
     * @brief Internal Node structure
     */
    struct Node {
        /**
         * @brief value stored in the node
         */
        Comparable value;

        /**
         * @brief The Color of the node
         */
        Color color;

        /**
         * @brief A pointer to the left child
         */
        Node* left;

        /**
         * @brief A pointer to the right child
         */
        Node* right;

        /**
         * @brief A pointer to the parent
         */
        Node* parent;

        /**
         * @brief Construct a new Node object
         *
         * @param value value to store in the node
         */
        Node(const Comparable& value) : Node(value, Color::RED) {}

        /**
         * @brief Construct a new Node object
         *
         * @param value value to store in the node
         * @param color Color of the node
         */
        Node(const Comparable& value, const Color& color) : value{Comparable(value)}, color{color}, left{nullptr}, right{nullptr}, parent{nullptr} {}

        /**
         * @brief Converts the color of the node to a string
         *
         * @return string string representation of the color of the node
         */
        string colorToString() const {
            switch (this->color) {
            case Color::RED:
                return "⬜";
            case Color::BLACK:
                return "⬛";
            default:
                return "?";
            }
        }

        /**
         * @brief flushed this node to an ostream
         *
         * @param os ostream to flush to
         * @param node node to flush
         * @return ostream& ostream to flush to
         */
        friend ostream& operator<<(ostream& os, const Node& node) {
            os << node.colorToString() << ":" << node.value;
            return os;
        }

        /**
         * @brief Determines if this node is the left child of its parrent
         *
         * @return true if this node is the left child of its parrent
         * @return false otherwise
         */
        bool isLeft() const { return this->parent ? this == this->parent->left : false; }

        /**
         * @brief Determines if the node is the right child of its parrent
         *
         * @return true if this node it the right child of its parrent
         * @return false otherwise
         */
        bool isRight() const { return this->parent ? this == this->parent->right : false; }

        /**
         * @brief Gets the sibling of this node
         *
         * @return Node* pointer to the sibling of this node
         */
        Node* sibling() const {
            if (!this->parent)
                return nullptr;
            return this->isLeft() ? this->parent->right : this->parent->left;
        }

        /**
         * @brief Gets the uncle of this node
         *
         * @return Node* pointer to the uncle of this node
         */
        Node* uncle() const {
            if (!this->parent)
                return nullptr;
            return this->parent->sibling();
        }

        /**
         * @brief Counts the number of children this node has
         *
         * @return size_t the number of children this node has
         */
        size_t countChildren() {
            size_t count = 0;
            if (this->left)
                ++count;
            if (this->right)
                ++count;
            return count;
        }
    };

private:
    /**
     * @brief a pointer to the root of the 🟥⬛ Tree
     */
    Node* _root;

    /**
     * @brief Rotate leftwards arround an inputed node
     *
     * @param node a pointer to the root to rotate arround
     */
    void rotateLeft(Node* node) {
        Node* y = node->right;
        node->right = y->left;
        if (y->left)
            y->left->parent = node;
        y->parent = node->parent;
        if (!node->parent)
            this->_root = y;
        else if (node->isLeft())
            node->parent->left = y;
        else
            node->parent->right = y;
        y->left = node;
        node->parent = y;
    }

    /**
     * @brief Rotate rightwards arround an inputed node
     *
     * @param node a pointer to the root to rotates arround
     */
    void rotateRight(Node* node) {
        Node* y = node->left;
        node->left = y->right;
        if (y->right)
            y->right->parent = node;
        y->parent = node->parent;
        if (!node->parent)
            this->_root = y;
        else if (node->isRight())
            node->parent->right = y;
        else
            node->parent->left = y;
        y->right = node;
        node->parent = y;
    }

    /**
     * @brief Fix violations incured by the insert
     *
     * @param node a pointer to the inserted node
     */
    void fixInsert(Node*& node) {
        this->_root->color = Color::BLACK;
        if (node == this->_root) return;

        Node* uncle;
        while (node->parent->color == Color::RED) {
            uncle = node->uncle();
            if (uncle && uncle->color == Color::RED) {
                uncle->color = Color::BLACK;
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else if (node->parent->isRight()) {
                if (node->isLeft()) {
                    node = node->parent;
                    this->rotateRight(node);
                }
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                this->rotateLeft(node->parent->parent);
            } else {
                if (node->isRight()) {
                    node = node->parent;
                    this->rotateLeft(node);
                }
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                this->rotateRight(node->parent->parent);
            }

            if (node == this->_root) break;
        }

        this->_root->color = Color::BLACK;
    }

    /**
     * @brief Fix violation incurred by the remove
     *
     * @param x a pointer to the node removed
     */
    void fixRemove(Node*& x) {
        if (!x)
            return;

        Node* sibling = x->sibling();
        if (!sibling) {
            x->color = Color::BLACK;
            return;
        }

        while (x != this->_root && x->color == Color::BLACK) {
            if (x->isLeft()) {
                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    this->rotateLeft(x->parent);
                    sibling = x->parent->right;
                }

                if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
                    sibling->color = Color::RED;
                    x = x->parent;
                } else {
                    if (sibling->right->color == Color::BLACK) {
                        sibling->left->color = Color::BLACK;
                        sibling->color = Color::RED;
                        this->rotateRight(sibling);
                        sibling = x->parent->right;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    sibling->right->color = Color::BLACK;
                    this->rotateLeft(x->parent);
                    x = this->_root;
                }
            } else {
                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    x->parent->color = Color::RED;
                    this->rotateRight(x->parent);
                    sibling = x->parent->left;
                }

                if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) {
                    sibling->color = Color::RED;
                    x = x->parent;
                } else {
                    if (sibling->left->color == Color::RED) {
                        sibling->right->color = Color::BLACK;
                        sibling->color = Color::RED;
                        this->rotateLeft(sibling);
                        sibling = x->parent->left;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = Color::BLACK;
                    sibling->left->color = Color::BLACK;
                    this->rotateRight(x->parent);
                    x = this->_root;
                }
            }
        }

        x->color = Color::BLACK;
    }

    /**
     * @brief Tranplant into the tree
     *
     * @param u a pointer to the node to tranplant into
     * @param v a pointer to the node being transplanted
     */
    void transplant(Node*& u, Node*& v) {
        if (!u->parent)
            this->_root = v;
        else if (u->isLeft())
            u->parent->left = v;
        else
            u->parent->right = v;
        if (v)
            v->parent = u->parent;
    }

    /**
     * @brief Remove a node from the Tree
     *
     * @param z a pointer to the node being removed
     */
    void remove(Node*& node) {
        Node* x = nullptr;
        Node* y = node;
        Color color = y->color;
        switch (node->countChildren()) {
        case 0:
            if (node->isLeft())
                node->parent->left = nullptr;
            else if (node->isRight())
                node->parent->right = nullptr;
            break;
        case 1:
            if (!node->left) {
                x = node->right;
                this->transplant(node, node->right);
            } else if (!node->right) {
                x = node->left;
                this->transplant(node, node->left);
            }
            break;
        case 2:
            y = this->find_min(node->right);
            color = y->color;
            x = y->right;
            if (y->parent == node) {
                if (x)
                    x->parent = node;
            } else {
                this->transplant(y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }

            this->transplant(node, y);
            y->left = node->left;
            if (y->left)
                y->left->parent = y;
            y->color = node->color;
            break;
        }

        if (node == this->_root)
            this->_root = nullptr;
        delete node;
        node = nullptr;
        if (color == Color::BLACK)
            this->fixRemove(x);
    }

    /**
     * @brief Search for a node in a subtree
     *
     * @param root current subtree being searched
     * @param value value to search for
     * @return Node* a pointer to the node with the value found. Or nullptr if value is not found.
     */
    Node* search(Node* root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->value == value)
            return root;
        return root->value < value ? this->search(root->right, value) : this->search(root->left, value);
    }

    /**
     * @brief Insert a node into the tree
     *
     * @param root a pointer to the current subtree to insert into
     * @param value a pointer to the node being inserted
     * @return Node* a pointer to the current subtree to insert into
     */
    Node* insert(Node*& root, Node*& value) {
        if (!root)
            return value;
        if (value->value < root->value) {
            root->left = this->insert(root->left, value);
            root->left->parent = root;
        } else if (value->value > root->value) {
            root->right = this->insert(root->right, value);
            root->right->parent = root;
        }

        return root;
    }

    /**
     * @brief Prevents memory leaks by deallocated a subtree
     *
     * @param root subtree currently being deallocated
     * @return Node* nullptr
     */
    Node* clear(Node*& root) {
        if (root) {
            root->left = this->clear(root->left);
            root->right = this->clear(root->right);
            delete root;
        }

        root = nullptr;
        return nullptr;
    }

    /**
     * @brief Makes a copy of a subtree
     *
     * @param root subtree being coppied from
     * @return Node* new subtree created.
     */
    Node* copy(const Node* root) {
        if (!root)
            return nullptr;

        Node* node = new Node(root->value, root->color);
        node->left = this->copy(root->left);
        node->right = this->copy(root->right);
        return node;
    }

    /**
     * @brief Searched for the node with the smallest value in a subtree
     *
     * @param root subtree to search through
     * @return Node* a pointer to the node with the smallest value
     */
    Node* find_min(Node* root) const {
        Node* node = root;
        while (node && node->left)
            node = node->left;
        return node;
    }

    /**
     * @brief Prints a subtree so an ostream
     *
     * @param root current subtree being flushed
     * @param os ostream to flush to
     * @param trace how much to indent each line
     */
    void print_tree(const Node* root, ostream& os, size_t trace) const {
        if (root->right)
            this->print_tree(root->right, os, trace + 1);
        os << string(trace * 2, ' ') << *root << "\n";
        if (root->left)
            this->print_tree(root->left, os, trace + 1);
    }

public:
    /**
     * @brief Construct a new Red Black Tree object
     */
    RedBlackTree() : _root{nullptr} {}

    /**
     * @brief Construct a new Red Black Tree object
     *
     * @param rhs RedBlackTree to copy from
     */
    RedBlackTree(const RedBlackTree& rhs) : _root{this->copy(rhs.get_root())} {}

    /**
     * @brief Destroy the Red Black Tree object
     */
    ~RedBlackTree() { this->make_empty(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs Red Black Tree to copy from
     * @return RedBlackTree& *this
     */
    RedBlackTree& operator=(const RedBlackTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs.get_root());
        }

        return *this;
    }

    /**
     * @brief Insert a value into the tree
     *
     * @param value Comparable to insert
     */
    void insert(const Comparable& value) {
        if (this->contains(value))
            return;

        Node* node = new Node(value);
        this->_root = this->insert(this->_root, node);
        this->fixInsert(node);
    }

    /**
     * @brief Remove a value from the tree
     *
     * @param value Comparable to remove
     */
    void remove(const Comparable& value) {
        if (!this->_root)
            return;

        Node* node = this->search(this->_root, value);
        if (!node)
            return;

        this->remove(node);
    }

    /**
     * @brief Determine if this tree contains a value
     *
     * @param value Comparable to search for
     * @return true if the tree contains the value
     * @return false otherwise
     */
    bool contains(const Comparable& value) const { return this->search(this->_root, value); }

    /**
     * @brief Determines the smallest value in the tree
     *
     * @return const Comparable& the smallest value in the tree
     */
    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("Red Black Tree is empty");

        return this->find_min(this->_root)->value;
    }

    /**
     * @brief Determines the largest value in the tree
     *
     * @return const Comparable& the largest value in the tree
     */
    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("Red Black Tree is empty");

        Node* node = this->_root;
        while (node->right)
            node = node->right;

        return node->value;
    }

    /**
     * @brief Determine the Color of a node
     *
     * @param node a pointer to a node to determine the color of
     * @return int Color of the node
     */
    int color(const Node* node) const { return node ? node->color : Color::BLACK; }

    /**
     * @brief Get the root object
     *
     * @return const Node* a pointer the the root of the tree
     */
    const Node* get_root() const { return this->_root; }

    // ----------------------- Optional ----------------------- //
    RedBlackTree(RedBlackTree&& rhs) : _root{nullptr} { swap(this->_root, rhs.root); }

    RedBlackTree& operator=(RedBlackTree&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs.root);
        }

        return *this;
    }

    void insert(Comparable&& value) {
        Comparable v;
        swap(v, value);
        this->insert(v);
    }

    /**
     * @brief Determine if the tree is empty
     *
     * @return true if the tree is empty
     * @return false otherwise
     */
    bool is_empty() const { return !this->_root; }

    /**
     * @brief Prevents memory leaks by deallocating the entire tree
     */
    void make_empty() { this->_root = this->clear(this->_root); }

    /**
     * @brief Flushes the entire tree to an ostream
     *
     * @param os ostream to flush to, cout by default
     */
    void print_tree(ostream& os = cout) const {
        if (this->_root)
            this->print_tree(this->_root, os, 0);
        else
            os << "<empty>";
    }
};