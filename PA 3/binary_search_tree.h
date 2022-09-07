#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ostream, std::cout;
using std::invalid_argument;

/**
 * @brief A Binary Search Tree
 *
 * @tparam Comparable a data type that overloads the comparison operators
 */
template <typename Comparable>
class BinarySearchTree {
public:
    /**
     * @brief Internal Node struct
     *
     * @tparam T a data type that overloads the comparison operators
     */
    template <typename T>
    struct Node {
        /**
         * @brief The value stored in the node
         */
        T _value;

        /**
         * @brief A pointer to the left node
         */
        Node<T>* _left;

        /**
         * @brief A pointer to the right node
         */
        Node<T>* _right;

        /**
         * @brief Construct a new Node object
         */
        Node() : _value{T()}, _left{nullptr}, _right{nullptr} {}

        /**
         * @brief Construct a new Node object
         *
         * @param val a specified value
         */
        Node(T val) : _value{val}, _left{nullptr}, _right{nullptr} {}

        /**
         * @brief Determine if both _left and _right are nullptr
         *
         * @return true if both _left and _right are nullptr
         * @return false otherwise
         */
        bool is_leaf() const {
            return !this->_left && !this->_right;
        }
    };

private:
    /**
     * @brief A pointer to the root of the Binary Search Tree
     */
    Node<Comparable>* _root;

    /**
     * @brief Determine if this tree contains a specified value
     *
     * @param root a pointer to the root of the sub tree currently being searched
     * @param val the value to find
     * @return true if the value is found
     * @return false otherwise
     */
    bool contains(const Node<Comparable>* root, const Comparable& val) const {
        if (!root)
            return false;
        if (root->_value == val)
            return true;
        if (root->_value < val)
            return this->contains(root->_right, val);
        return this->contains(root->_left, val);
    }

    /**
     * @brief Prevents memory leaks by dellocated the entire binary search tree
     *
     * @param node the current subtree being dellocated
     * @return Node<Comparable>* nullptr
     */
    Node<Comparable>* clear(Node<Comparable>* node) {
        if (node) {
            node->_left = this->clear(node->_left);
            node->_right = this->clear(node->_right);
            delete node;
        }

        return nullptr;
    }

    /**
     * @brief Pushes the elements of this tree into a supplied ostream
     *
     * @param root current subtree being pushed
     * @param os    ostream to push to
     * @param trace how much to indent each line
     */
    void print_tree(const Node<Comparable>* root, ostream& os, size_t trace) const {
        if (!root) {
            os << "<empty>\n";
            return;
        }

        if (root->_right)
            this->print_tree(root->_right, os, trace + 1);
        os << std::string(trace * 2, ' ') << root->_value << "\n";
        if (root->_left)
            this->print_tree(root->_left, os, trace + 1);
    }

    /**
     * @brief Copies a tree into this tree
     *
     * @param root current subtree being coppied
     * @return Node<Comparable>* a new pointer to Node
     */
    Node<Comparable>* copy(const Node<Comparable>* root) {
        if (!root)
            return nullptr;

        Node<Comparable>* new_root = new Node<Comparable>(root->_value);
        new_root->_left = this->copy(root->_left);
        new_root->_right = this->copy(root->_right);
        return new_root;
    }

    /**
     * @brief Insert a new value into the tree
     *
     * @param node current subtree being inserted into
     * @param val value
     * @return Node<Comparable>* node inserted
     */
    Node<Comparable>* insert(Node<Comparable>*& root, const Comparable& val) {
        if (!root)
            return new Node<Comparable>(val);
        if (root->_value < val)
            root->_right = this->insert(root->_right, val);
        else
            root->_left = this->insert(root->_left, val);
        return root;
    }

    /**
     * @brief Remove a value from the tree
     *
     * @param root current subtree being removed from
     * @param val value to remove
     * @return Node<Comparable>* a pointer to any subtree that the original value might have had
     */
    Node<Comparable>* remove(Node<Comparable>* root, const Comparable& val) {
        if (!root)
            return root;

        if (val < root->_value)
            root->_left = this->remove(root->_left, val);
        else if (val > root->_value)
            root->_right = this->remove(root->_right, val);
        else {
            if (root->is_leaf()) {
                delete root;
                root = nullptr;
                return root;
            } else if (!root->_left) {
                Node<Comparable>* temp = root->_right;
                delete root;
                root = nullptr;
                return temp;
            } else if (!root->_right) {
                Node<Comparable>* temp = root->_left;
                delete root;
                root = nullptr;
                return temp;
            } else {
                const Node<Comparable>* temp = this->find_min(root->_right);
                root->_value = temp->_value;
                root->_right = this->remove(root->_right, temp->_value);
            }
        }

        return root;
    }

    /**
     * @brief Find the Node with the smallest value within a subtree
     *
     * @param root the current subtree being searched
     * @return const Node<Comparable>*& a pointer to the smallest node in the subtree
     */
    const Node<Comparable>*& find_min(const Node<Comparable>* root) const {
        const Node<Comparable>*& curr = root;
        while (curr && curr->_left)
            curr = curr->_left;

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
    ~BinarySearchTree() {
        this->make_empty();
    }

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
     * @param val value to look for
     * @return true if this tree contains the value
     * @return false otherwise
     */
    bool contains(const Comparable& val) {
        return this->contains(this->_root, val);
    }

    /**
     * @brief Insert a value into the tree.
     *
     * @param val value to insert
     */
    void insert(const Comparable& val) {
        // cout << "bst.insert(" << std::to_string(val) << ");\n";
        if (this->contains(val))
            return;

        this->_root = this->insert(this->_root, val);
    }

    /**
     * @brief Remove a value from the tree
     *
     * @param val value to remove
     */
    void remove(const Comparable& val) {
        // cout << "bst.remove(" << std::to_string(val) << ");\n";
        this->_root = this->remove(this->_root, val);
    }

    /**
     * @brief Find the smallest value in the tree
     *
     * @return const Comparable& the smallest value
     */
    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("Binary Search Tree is empty");

        Node<Comparable>* curr = this->_root;
        while (curr->_left)
            curr = curr->_left;

        return curr->_value;
    }

    /**
     * @brief Find the largest value in the tree
     *
     * @return const Comparable& the largest value
     */
    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("Binary Search Tree is empty");

        Node<Comparable>* curr = this->_root;
        while (curr->_right)
            curr = curr->_right;

        return curr->_value;
    }

    /**
     * @brief Pushed this tree to a ostream
     *
     * @param os ostream to push this tree to
     */
    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->_root, os, i);
    }

    /**
     * @brief return this root of the tree
     *
     * @return const Node<Comparable>* this->_root
     */
    const Node<Comparable>* root() const {
        return this->_root;
    }

    // Optional
    // BinarySearchTree(BinarySearchTree&& rhs) : _root{rhs.root()} {
    //     rhs._root = nullptr; 
    // }

    // BinarySearchTree& operator=(BinarySearchTree&& rhs) {
    //     if (this != &rhs) {
    //         this->make_empty();
    //         this->_root = rhs.root();
    //         rhs._root = nullptr;
    //     }

    //     return *this;
    // }

    // void insert(Comparable&& val) {
    //     this->_root = this->insert(this->_root, val);
    //     val = nullptr;
    // }

    /**
     * @brief Determine if this tree is empty
     *
     * @return true if this->_root == nullptr
     * @return false otherwise
     */
    bool is_empty() const {
        return !this->_root;
    }

    /**
     * @brief Prevents memory leaks by deallocated the entire tree
     */
    void make_empty() {
        this->_root = this->clear(this->_root);
    }
};
