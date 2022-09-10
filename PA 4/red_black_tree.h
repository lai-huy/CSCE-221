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

    void rotateLeft(Node<Comparable>*& root, Node<Comparable>*& pt) {
        Node<Comparable>* pt_right = pt->right;

        pt->right = pt_right->left;

        if (pt->right != NULL)
            pt->right->parent = pt;

        pt_right->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_right;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;

        else
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node<Comparable>*& root, Node<Comparable>*& pt) {
        Node<Comparable>* pt_left = pt->left;

        pt->left = pt_left->right;

        if (pt->left != NULL)
            pt->left->parent = pt;

        pt_left->parent = pt->parent;

        if (pt->parent == NULL)
            root = pt_left;

        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;

        else
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(Node<Comparable>*& root, Node<Comparable>*& pt) {
        Node<Comparable>* parent_pt = NULL;
        Node<Comparable>* grand_parent_pt = NULL;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {

            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            /*  Case : A
                Parent of pt is left child
                of Grand-parent of pt */
            if (parent_pt == grand_parent_pt->left) {

                Node<Comparable>* uncle_pt = grand_parent_pt->right;

                /* Case : 1
                   The uncle of pt is also red
                   Only Recoloring required */
                if (uncle_pt != NULL && uncle_pt->color ==
                                                       RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                }

                else {
                    /* Case : 2
                       pt is right child of its parent
                       Left-rotation required */
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3
                       pt is left child of its parent
                       Right-rotation required */
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color,
                               grand_parent_pt->color);
                    pt = parent_pt;
                }
            }

            /* Case : B
               Parent of pt is right child
               of Grand-parent of pt */
            else {
                Node<Comparable>* uncle_pt = grand_parent_pt->left;

                /*  Case : 1
                    The uncle of pt is also red
                    Only Recoloring required */
                if ((uncle_pt != NULL) && (uncle_pt->color ==
                    RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    /* Case : 2
                       pt is left child of its parent
                       Right-rotation required */
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    /* Case : 3
                       pt is right child of its parent
                       Left-rotation required */
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }

        root->color = BLACK;
    }

    Node<Comparable>* insert(Node<Comparable>* root, Node<Comparable>* pt) {
        /* If the tree is empty, return a new node */
        if (!root)
            return pt;

        /* Otherwise, recur down the tree */
        if (pt->value < root->value) {
            root->left = this->insert(root->left, pt);
            root->left->parent = root;
        } else if (pt->value > root->value) {
            root->right = this->insert(root->right, pt);
            root->right->parent = root;
        }

        /* return the (unchanged) node pointer */
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