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
        Color color;
        Node<T>* left;
        Node<T>* right;
        Node<T>* parent;

        Node(T value) : value{value}, color{Color::RED}, left{nullptr}, right{nullptr}, parent{nullptr} {}
    };

private:
    Node<Comparable>* root;

    void rotateLeft(Node<Comparable>*& root, Node<Comparable>*& parent) {
        Node<Comparable>* right = parent->right;
        parent->right = right->left;

        if (parent->right)
            parent->right->parent = parent;
        right->parent = parent->parent;
        if (!parent->parent)
            root = right;
        else if (parent == parent->parent->left)
            parent->parent->left = right;
        else
            parent->parent->right = right;

        right->left = parent;
        parent->parent = right;
    }

    void rotateRight(Node<Comparable>*& root, Node<Comparable>*& parent) {
        Node<Comparable>* left = parent->left;
        parent->left = left->right;

        if (parent->left)
            parent->left->parent = parent;
        left->parent = parent->parent;
        if (!parent->parent)
            root = left;
        else if (parent == parent->parent->left)
            parent->parent->left = left;
        else
            parent->parent->right = left;

        left->right = parent;
        parent->parent = left;
    }

    void fixViolation(Node<Comparable>*& root, Node<Comparable>*& parent) {
        Node<Comparable>* p_ptr = nullptr;
        Node<Comparable>* gp_ptr = nullptr;

        while ((parent != root) && (parent->color != Color::BLACK) && (parent->parent->color == Color::RED)) {
            p_ptr = parent->parent;
            gp_ptr = parent->parent->parent;
            Node<Comparable>* uncle = p_ptr == gp_ptr->left ? gp_ptr->right : gp_ptr->left;

            if (!uncle)
                break;

            if (p_ptr == gp_ptr->left) { // parent is left child of Grand parent of parent
                if (uncle->color == Color::RED) { // The Uncle of pointer is also red. Only recoloring required
                    gp_ptr->color = Color::RED;
                    p_ptr->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    parent = gp_ptr;
                } else { // parent is right child. Left rotation
                    if (parent == p_ptr->right) {
                        rotateLeft(root, p_ptr);
                        parent = p_ptr;
                        p_ptr = parent->parent;
                    }

                    // parent is left child of its Parent. Right rotation required
                    this->rotateRight(root, gp_ptr);
                    swap(p_ptr->color, gp_ptr->color);
                    parent = p_ptr;
                }
            } else { // Parent of parent is right child of Grand-parent of pointer
                if (uncle->color == Color::RED) { // The Uncle of parent is also red. Only Recoloring Required
                    gp_ptr->color = Color::RED;
                    p_ptr->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    parent = gp_ptr;
                } else { // Parent is left child of its parent. Right rotation required
                    if (parent == p_ptr->left) {
                        rotateRight(root, p_ptr);
                        parent = p_ptr;
                        p_ptr = parent->parent;
                    }

                    // parent is right child of its parent. Left rotation required
                    rotateLeft(root, gp_ptr);
                    swap(p_ptr->color, gp_ptr->color);
                    parent = p_ptr;
                }
            }
        }

        root->color = Color::BLACK;
    }

    Node<Comparable>* insert(Node<Comparable>* root, Node<Comparable>* pt) {
        // If the tree is empty, return a new node
        if (!root)
            return pt;

        // Otherwise, recur down the tree
        if (pt->value < root->value) {
            root->left = this->insert(root->left, pt);
            root->left->parent = root;
        } else if (pt->value > root->value) {
            root->right = this->insert(root->right, pt);
            root->right->parent = root;
        }

        // return the (unchanged) node pointer
        return root;
    }

    Node<Comparable>* clear(Node<Comparable>* root) {
        if (root) {
            root->left = this->clear(root->left);
            root->right = this->clear(root->right);
            delete root;
        }

        root = nullptr;
        return nullptr;
    }

    Node<Comparable>* copy(const Node<Comparable>* root) {
        if (!root)
            return nullptr;

        Node<Comparable>* node = new Node<Comparable>(root->value);
        node->left = this->copy(root->left);
        node->right = this->copy(root->right);
        return node;
    }

    bool contains(const Node<Comparable>* root, const Comparable& value) const {
        if (!root)
            return false;
        if (root->value == value)
            return true;
        return root->value < value ? this->contains(root->right, value) : this->contains(root->left, value);
    }

    void print_tree(const Node<Comparable>* root, ostream& os, size_t trace) const {
        if (!root) {
            os << "<empty>\n";
            return;
        }

        if (root->right)
            this->print_tree(root->right, os, trace + 1);
        os << string(trace * 2, ' ') << root->_value << "\n";
        if (root->_left)
            this->print_tree(root->left, os, trace + 1);
    }

public:
    RedBlackTree() : root{nullptr} {}

    RedBlackTree(const RedBlackTree& rhs) : root{nullptr} {
        cout << &rhs << "\n";
    }

    ~RedBlackTree() {
        this->make_empty();
    }

    RedBlackTree& operator=(const RedBlackTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->root = this->copy(rhs.get_root());
        }

        return *this;
    }

    void insert(const Comparable& value) {
        if (this->contains(value))
            return;

        Node<Comparable>* pt = new Node(value);
        this->root = this->insert(this->root, pt);
        this->fixViolation(this->root, pt);
    }

    void remove(const Comparable& value) {
        cout << &value << "\n";
    }

    bool contains(const Comparable& value) const {
        return this->contains(this->root, value);
    }

    const Comparable& find_min() const {
        if (!this->root)
            throw invalid_argument("Red Black Tree is empty");

        Node<Comparable>* node = this->root;
        while (node->left)
            node = node->left;

        return node->value;
    }

    const Comparable& find_max() const {
        if (!this->root)
            throw invalid_argument("Red Black Tree is empty");

        Node<Comparable>* node = this->root;
        while (node->right)
            node = node->right;

        return node->value;
    }

    int color(const Node<Comparable>* node) const {
        return node ? node->color : Color::BLACK;
    }

    const Node<Comparable>* get_root() const {
        return this->root;
    }

    // OPTIONAL
    // RedBlackTree(RedBlackTree&&);
    // RedBlackTree& operator=(RedBlackTree&&);
    // void insert(Comparable&&);

    bool is_empty() const {
        return !this->root;
    }

    void make_empty() {
        this->root = this->clear(this->root);
    }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->root, os, i);
    }
};