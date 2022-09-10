#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::cout, std::ostream;
using std::invalid_argument;
using std::string;
using std::swap;

template <typename Comparable>
class RedBlackTree {
public:
    enum Color { RED, BLACK };

    template <typename T>
    struct Node {
        T value;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;
        Color color;

        Node() : value{T()}, left{nullptr}, right{nullptr}, parent{nullptr}, color{Color::RED} {}
        Node(const T& val) : value{T(val)}, left{nullptr}, right{nullptr}, parent{nullptr}, color{Color::RED} {}

        bool is_leaf() {
            return !this->left && !this->right;
        }

        bool operator==(const Node<T>& rhs) {
            if (this == &rhs)
                return true;
            if (this->value != rhs.value)
                return false;
            if (this->left != rhs.left)
                return false;
            if (this->right != rhs.right)
                return false;
            if (this->parent != rhs.parent)
                return false;
            if (this->color != rhs.color)
                return false;
            return true;
        }
    };

    typedef Node<Comparable>* nodeptr;

private:
    nodeptr _root;

    /**
     * @brief Determine if this tree contains a specified value
     *
     * @param root current subtree being searched
     * @param val value to find
     * @return true if the value is found
     * @return false otherwise
     */
    bool contains(const Node<Comparable>* root, const Comparable& val) const {
        if (!root)
            return false;
        if (root->value == val)
            return true;
        if (root->value < val)
            return this->contains(root->right, val);
        return this->contains(root->left, val);
    }

    /**
     * @brief Prevents memory leaks by deallocating subtrees
     *
     * @param root current subtree being cleared
     * @return Node<Comparable>* nullptr
     */
    Node<Comparable>* clear(Node<Comparable>* root) {
        if (root) {
            root->left = this->clear(root->left);
            root->right = this->clear(root->right);
            delete root;
        }

        return nullptr;
    }

    /**
     * @brief Copy a subtree into the current subtree
     *
     * @param root current subtree to copy into
     * @return Node<Comparable>* a new subtree
     */
    Node<Comparable>* copy(const Node<Comparable>* root) {
        if (!root)
            return nullptr;

        Node<Comparable>* new_root = new Node<Comparable>(root->value);
        new_root->left = this->copy(root->left);
        new_root->right = this->copy(root->right);
        return new_root;
    }

    /**
     * @brief Insert a value into a subtree
     *
     * @param node current subtree being inserted into
     * @param val value to insert
     * @return Node<Comparable>* new subtree
     */
    Node<Comparable>* insert(Node<Comparable>*& node, const Comparable& val) {
        if (!node)
            return new Node<Comparable>(val);
        if (node->value < val)
            node->right = this->insert(node->right, val);
        else if (node->value > val)
            node->left = this->insert(node->left, val);
        return node;
    }

    /**
     * @brief Remove a value from a subtree
     *
     * @param root current subtree being removed from
     * @param val value to remove
     * @return Node<Comparable>* the right subtree of the node removed
     */
    Node<Comparable>* remove(Node<Comparable>* root, const Comparable& val) {
        if (!root)
            return nullptr;

        if (val < root->value)
            root->left = this->remove(root->left, val);
        else if (val > root->value)
            root->right = this->remove(root->right, val);
        else if (val == root->value) {
            if (root->is_leaf()) {
                delete root;
                return nullptr;
            } else if (!root->left) {
                Node<Comparable>* temp = root->right;
                delete root;
                root = nullptr;
                return temp;
            } else if (!root->right) {
                Node<Comparable>* temp = root->left;
                delete root;
                root = nullptr;
                return temp;
            } else {
                const Node<Comparable>* temp = this->find_min(root->right);
                root->value = temp->value;
                root->right = this->remove(root->right, temp->value);
            }
        }

        return root;
    }

    /**
     * @brief Find the node whose value is the smallets in the subtree
     *
     * @param root subtree to search through
     * @return const Node<Comparable>* a pointer to the smallest node
     */
    const Node<Comparable>* find_min(const Node<Comparable>* root) const {
        const Node<Comparable>* curr = root;
        while (curr && curr->left)
            curr = curr->left;

        return curr;
    }

public:
    RedBlackTree() : _root{nullptr} {}
    RedBlackTree(const RedBlackTree& rhs) : _root{this->copy(const_cast<Node<Comparable>*>(rhs.get_root()))} {}
    ~RedBlackTree() {
        this->make_empty();
    }

    RedBlackTree& operator=(const RedBlackTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(const_cast<Node<Comparable>*>(rhs.get_root()));
        }

        return *this;
    }

    void insert(const Comparable& value) {
        // cout << std::to_string(value) << "\n";
        this->_root = this->insert(this->_root, value);
    }

    void remove(const Comparable& value) {
        // cout << std::to_string(value) << "\n";
        this->_root = this->remove(this->_root, value);
    }

    bool contains(const Comparable& value) const {
        return this->contains(const_cast<const Node<Comparable>*&>(this->_root), value);
    }

    const Comparable& find_min() const {
        nodeptr node = this->_root;
        while (node && node->left)
            node = node->left;

        return node->value;
    }

    const Comparable& find_max() const {
        nodeptr node = this->_root;
        while (node && node->right)
            node = node->right;

        return node->value;
    }

    int color(const nodeptr node) const {
        return node ? node->color : Color::BLACK;
    }

    const Node<Comparable>* get_root() const {
        return const_cast<const nodeptr>(this->_root);
    }

    // OPTIONAL
    // RedBlackTree(RedBlackTree&& rhs);
    // RedBlackTree& operator=(RedBlackTree&& rhs);

    bool is_empty() const {
        return !this->_root;
    }

    // void insert(Comparable&& value);
    void make_empty() {
        this->_root = this->clear(this->_root);
    }

    // void print_tree(ostream& os=cout) const;
};
