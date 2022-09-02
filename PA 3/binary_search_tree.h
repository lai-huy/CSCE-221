#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ostream, std::cout;
using std::invalid_argument;

/**
 * @brief An Individual node of the LinkedList
 * 
 * @tparam Comparable a data type that overloads operator==, operator<, and operator>
 */
template <typename Comparable>
struct Node {
    Comparable _value;
    Node<Comparable>* _left;
    Node<Comparable>* _right;

    Node() : _value{Comparable()}, _left{nullptr}, _right{nullptr} {}
    Node(Comparable val) : _value{val}, _left{nullptr}, _right{nullptr} {}

    bool is_leaf() const {
        return !this->_left && !this->_right;
    }
};

/**
 * @brief A Binary Search Tree
 * 
 * @tparam Comparable a data type that overloads operator==, operator<, and operator>
 */
template <typename Comparable>
class BinarySearchTree {
private:
    Node<Comparable>* _root;

    bool contains(const Node<Comparable>* root, const Comparable& val) const {
        if (!root)
            return false;
        if (root->_value == val)
            return true;
        if (root->_value < val)
            return this->contains(root->_right, val);
        return this->contains(root->_left, val);
    }

    Node<Comparable>* clear(Node<Comparable>* node) {
        if (node) {
            node->_left = this->clear(node->_left);
            node->_right = this->clear(node->_right);
            delete node;
        }

        return nullptr;
    }

    void copy(const BinarySearchTree& rhs) {
        this->_root = this->copy(rhs.root());
    }

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

    Node<Comparable>* copy(const Node<Comparable>* root) {
        if (!root)
            return nullptr;

        Node<Comparable>* new_root = new Node<Comparable>(root->_value);
        new_root->_left = this->copy(root->_left);
        new_root->_right = this->copy(root->_right);
        return new_root;
    }

    Node<Comparable>* insert(Node<Comparable>* node, const Comparable& val) {
        if (!node)
            return new Node<Comparable>(val);
        if (node->_value <= val)
            node->_right = this->insert(node->_right, val);
        else
            node->_left = this->insert(node->_left, val);
        return node;
    }

    Node<Comparable>* remove(Node<Comparable>* root, const Comparable& val) {
        if (!root)
            return nullptr;

        if (val < root->_value)
            root->_left = this->remove(root->_left, val);
        else if (val > root->_value)
            root->_right = this->remove(root->_right, val);
        else {
            if (root->is_leaf()) {
                delete root;
                return nullptr;
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

    const Node<Comparable>* find_min(const Node<Comparable>* root) const {
        const Node<Comparable>* curr = root;
        while (curr && curr->_left)
            curr = curr->_left;

        return curr;
    }

public:
    BinarySearchTree() : _root{nullptr} {}

    BinarySearchTree(const BinarySearchTree& rhs) : _root{nullptr} {
        this->copy(rhs);
    }

    ~BinarySearchTree() {
        this->make_empty();
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->copy(rhs);
        }

        return *this;
    }

    bool contains(const Comparable& val) {
        return this->contains(this->_root, val);
    }

    void insert(const Comparable& val) {
        // cout << "bst.insert(" << std::to_string(val) << ");\n";
        this->_root = this->insert(this->_root, val);
    }

    void remove(const Comparable& val) {
        // cout << "bst.remove(" << std::to_string(val) << ");\n";
        this->_root = this->remove(this->_root, val);
    }

    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("Binary Search Tree is empty");

        Node<Comparable>* curr = this->_root;
        while (curr->_left)
            curr = curr->_left;

        return curr->_value;
    }

    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("Binary Search Tree is empty");

        Node<Comparable>* curr = this->_root;
        while (curr->_right)
            curr = curr->_right;

        return curr->_value;
    }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->_root, os, i);
    }

    const Node<Comparable>* root() const {
        return this->_root;
    }

    // Optional
    // BinarySearchTree(BinarySearchTree&& rhs);
    // BinarySearchTree& operator=(BinarySearchTree&&);

    bool is_empty() const {
        return !this->_root;
    }

    // void insert(Comparable&&);
    void make_empty() {
        this->_root = this->clear(this->_root);
    }
};
