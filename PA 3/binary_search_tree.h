#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ostream, std::cout;
using std::invalid_argument;
using std::string;
using std::swap;

/**
 * @brief A Binary Search Tree
 *
 * @tparam Comparable a data type that overloads the comparison operators
 */
template <typename Comparable>
class BinarySearchTree {
public:
    /**
     * @brief An internal node struct
     *
     * @tparam T a data type that overloads the comparison operators
     */
    struct Node {
        /**
         * @brief the value stored by this node
         */
        Comparable _value;

        /**
         * @brief a pointer to the left subtree
         */
        Node* _left;

        /**
         * @brief a pointer to the right subtree
         */
        Node* _right;

        /**
         * @brief Construct a new Node object
         */
        Node() : _value{Comparable()}, _left{nullptr}, _right{nullptr} {}

        /**
         * @brief Construct a new Node object
         *
         * @param val value stored in the node
         */
        Node(const Comparable& val) : _value{Comparable(val)}, _left{nullptr}, _right{nullptr} {}

        /**
         * @brief Determine if both subtree pointers are nullptr
         *
         * @return true is both _left and _right are nullptr
         * @return false otherwise
         */
        bool isLeaf() const { return !this->_left && !this->_right; }
    };

private:
    /**
     * @brief a pointer to the root of the tree
     */
    Node* _root;

    /**
     * @brief Determine if this tree contains a specified value
     *
     * @param root current subtree being searched
     * @param val value to find
     * @return true if the value is found
     * @return false otherwise
     */
    bool contains(const Node* root, const Comparable& val) const {
        if (!root)
            return false;
        if (root->_value == val)
            return true;
        return this->contains(root->_value < val ? root->_right : root->_left, val);
    }

    /**
     * @brief pushed this tree to an ostream
     *
     * @param root current subtree being pushed
     * @param os ostream to push to
     * @param trace how much to indent each line
     */
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

    /**
     * @brief Prevents memory leaks by deallocating subtrees
     *
     * @param root current subtree being cleared
     * @return Node* nullptr
     */
    Node* clear(Node*& root) {
        if (root) {
            root->_left = this->clear(root->_left);
            root->_right = this->clear(root->_right);
            delete root;
        }

        return nullptr;
    }

    /**
     * @brief Copy a subtree into the current subtree
     *
     * @param root current subtree to copy into
     * @return Node* a new subtree
     */
    Node* copy(const Node* root) {
        if (!root)
            return nullptr;

        Node* node = new Node(root->_value);
        node->_left = this->copy(root->_left);
        node->_right = this->copy(root->_right);
        return node;
    }

    /**
     * @brief Insert a value into a subtree
     *
     * @param node current subtree being inserted into
     * @param val value to insert
     * @return Node* new subtree
     */
    Node* insert(Node*& node, const Comparable& val) {
        if (!node)
            return new Node(val);
        if (node->_value < val)
            node->_right = this->insert(node->_right, val);
        else if (node->_value > val)
            node->_left = this->insert(node->_left, val);
        return node;
    }

    /**
     * @brief Remove a value from a subtree
     *
     * @param root current subtree being removed from
     * @param val value to remove
     * @return Node* the right subtree of the node removed
     */
    Node* remove(Node* root, const Comparable& val) {
        if (!root)
            return nullptr;

        if (val < root->_value)
            root->_left = this->remove(root->_left, val);
        else if (val > root->_value)
            root->_right = this->remove(root->_right, val);
        else if (val == root->_value) {
            if (root->isLeaf()) {
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

        return root;
    }

    /**
     * @brief Find the node whose value is the smallets in the subtree
     *
     * @param root subtree to search through
     * @return const Node* a pointer to the smallest node
     */
    const Node* find_min(Node* const& root) const {
        Node* curr = root;
        while (curr && curr->_left)
            curr = curr->_left;

        return curr;
    }

    const Node* find_max(Node* const& root) const {
        Node* curr = root;
        while (curr && curr->_right)
            curr = curr->_right;
        return curr;
    }

public:
    /**
     * @brief Construct a new Binary Search Tree object
     */
    BinarySearchTree() : _root{nullptr} {}

    /**
     * @brief Construct a new Binary Search Tree object
     *
     * @param rhs BinarySearchTree to copy from
     */
    BinarySearchTree(const BinarySearchTree& rhs) : _root{this->copy(rhs.root())} {}

    /**
     * @brief Destroy the Binary Search Tree object
     */
    ~BinarySearchTree() { this->make_empty(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rhs BinarySearchTree to copy from
     * @return BinarySearchTree& *this
     */
    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs.root());
        }

        return *this;
    }

    /**
     * @brief Determine if this tree contains a specified value
     *
     * @param val value to search for
     * @return true if this tree contains the value
     * @return false otherwise
     */
    bool contains(const Comparable& val) { return this->contains(this->_root, val); }

    /**
     * @brief Insert a value into the tree
     *
     * @param val value to insert
     */
    void insert(const Comparable& val) { this->_root = this->insert(this->_root, val); }

    /**
     * @brief Remove a value from the tree
     *
     * @param val value to remove
     */
    void remove(const Comparable& val) { this->_root = this->remove(this->_root, val); }

    /**
     * @brief find the smallest value in the tree
     *
     * @return const Comparable& smallest value
     */
    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("Binary Search Tree is empty");
        return this->find_min(this->_root)->_value;
    }

    /**
     * @brief find the largets value in the tree
     *
     * @return const Comparable& largest value
     */
    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("Binary Search Tree is empty");
        return this->find_max(this->_root)->_value;
    }

    /**
     * @brief Pushes this tree to a ostream
     *
     * @param os ostream to push to
     */
    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->_root, os, i);
    }

    /**
     * @brief Return the root of the tree
     *
     * @return const Node* this->_root
     */
    const Node* root() const { return this->_root; }

    // ----------------------- Optional ----------------------- //

    BinarySearchTree(BinarySearchTree&& rhs) : _root{nullptr} { swap(this->_root, rhs._root); }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs._root);
        }

        return *this;
    }

    void insert(Comparable&& val) {
        Comparable v;
        swap(v, val);
        this->_root = this->insert(this->_root, v);
    }

    /**
     * @brief Determine if this tree is empty
     *
     * @return true if the tree is empty
     * @return false otherwise
     */
    bool is_empty() const { return !this->_root; }

    /**
     * @brief Prevents memory leaks by dellocating the entire tree
     */
    void make_empty() { this->_root = this->clear(this->_root); }
};
