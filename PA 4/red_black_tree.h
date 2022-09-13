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

        Node(const T& value) : value{T(value)}, color{Color::RED}, left{nullptr}, right{nullptr}, parent{nullptr} {}
        Node(const T& value, const Color& color) : value{T(value)}, color{color}, left{nullptr}, right{nullptr}, parent{nullptr} {}

        string colorToString() const {
            switch (this->color) {
            case RED:
                return "\u2B1C";
            case BLACK:
                return "\u2B1B";
            default:
                return "?";
            }
        }

        friend ostream& operator<<(ostream& os, const Node<T>& node) {
            os << node.colorToString() << ":" << node.value;
            return os;
        }

        bool isLeft() const { return this == parent->left; }

        bool hasRedChild() {
            return (this->left && left->color == Color::RED) || (this->right && right->color == Color::RED);
        }

        bool isLeaf() const { return !this->left && !this->right; }

        bool isBlack() const { return this->color == Color::BLACK; }

        Node<T>* sibling() const {
            if (!this->parent)
                return nullptr;
            return this->isLeft() ? this->parent->right : this->parent->left;
        }

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

    void rebalance(Node<Comparable>*& root, Node<Comparable>*& parent) {
        Node<Comparable>* parent_pt = nullptr;
        Node<Comparable>* grand_parent_pt = nullptr;

        while ((parent != root) && (parent->color != Color::BLACK) && (parent->parent->color == Color::RED)) {
            parent_pt = parent->parent;
            grand_parent_pt = parent->parent->parent;
            Node<Comparable>* uncle_pt;

            /*  Case : A
                Parent of pt is left child
                of Grand-parent of pt */
            if (parent_pt == grand_parent_pt->left) {
                uncle_pt = grand_parent_pt->right;

                /* Case : 1
                   The uncle of pt is also red
                   Only Recoloring required */
                if (uncle_pt && uncle_pt->color == Color::RED) {
                    grand_parent_pt->color = Color::RED;
                    parent_pt->color = Color::BLACK;
                    uncle_pt->color = Color::BLACK;
                    parent = grand_parent_pt;
                } else {
                    /* Case : 2
                       pt is right child of its parent
                       Left-rotation required */
                    if (parent == parent_pt->right) {
                        this->rotateLeft(root, parent_pt);
                        parent = parent_pt;
                        parent_pt = parent->parent;
                    }

                    /* Case : 3
                       pt is left child of its parent
                       Right-rotation required */
                    this->rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    parent = parent_pt;
                }
            }

            /* Case : B
               Parent of pt is right child
               of Grand-parent of pt */
            else {
                uncle_pt = grand_parent_pt->left;

                /*  Case : 1
                    The uncle of pt is also red
                    Only Recoloring required */
                if (uncle_pt && (uncle_pt->color == Color::RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    parent = grand_parent_pt;
                } else {
                    /* Case : 2
                       pt is left child of its parent
                       Right-rotation required */
                    if (parent == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        parent = parent_pt;
                        parent_pt = parent->parent;
                    }

                    /* Case : 3
                       pt is right child of its parent
                       Left-rotation required */
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    parent = parent_pt;
                }
            }
        }

        root->color = Color::BLACK;
    }

    void fixDoubleBlack(Node<Comparable>*& node) {
        if (node == this->root)
            return;

        Node<Comparable>* sibling = node->sibling(), * parent = node->parent;
        if (!sibling) // No sibiling, double black pushed up
            this->fixDoubleBlack(parent);
        else {
            switch (sibling->color) {
            case Color::RED:
            {
                parent->color = Color::RED;
                sibling->color = Color::BLACK;

                if (sibling->isLeft()) // left case
                    this->rotateRight(parent, parent->parent);
                else // right case
                    this->rotateLeft(parent, parent->parent);

                this->fixDoubleBlack(node);
                break;
            }
            case Color::BLACK:
            {
                if (sibling->hasRedChild()) {
                    // at least 1 red children
                    if (sibling->left != NULL and sibling->left->color == RED) {
                        if (sibling->isLeft()) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            this->rotateRight(parent, parent->parent);
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            this->rotateRight(sibling, sibling->parent);
                            this->rotateLeft(parent, parent->parent);
                        }
                    } else {
                        if (sibling->isLeft()) {
                            // left right
                            sibling->right->color = parent->color;
                            this->rotateLeft(sibling, sibling->parent);
                            this->rotateRight(parent, parent->parent);
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            this->rotateLeft(parent, parent->parent);
                        }
                    }
                    parent->color = Color::BLACK;
                } else {
                    // 2 black children
                    sibling->color = Color::RED;
                    if (parent->color == Color::BLACK)
                        this->fixDoubleBlack(parent);
                    else
                        parent->color = Color::BLACK;
                }
                break;
            }
            default:
            {
                throw std::runtime_error("Illegal Node Color:\t" + sibling->color);
            }
            }
        }
    }

    void remove(Node<Comparable>*& node) {
        Node<Comparable>* replace = this->find_min(node->right);

        // True when replace and node are both black
        bool doubleBlack = node->isBlack() && (!replace || replace->isBlack());
        Node<Comparable>* parent = node->parent;

        switch (node->countChildren()) {
        case 0:
        {
            if (node == this->root) {   // Node being removed is the root of the tree
                this->root = nullptr;
            } else {
                if (doubleBlack) {
                    this->fixDoubleBlack(node);
                } else {
                    Node<Comparable>* sibling = node->sibling();
                    if (sibling) // sibling is not null, make it red"
                        sibling->color = Color::RED;
                }

                // delete root from the tree
                if (node->isLeft())
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }

            delete node;
            return;
        }
        case 1:
        {
            if (node == this->root) { // Node being removed is the root of the tree, assign the value of replace to node, and delete replace
                node->value = replace->value;
                node->left = nullptr;
                node->right = nullptr;
                delete replace;
            } else {
                // Detach root from tree and move replace up
                if (node->isLeft()) {
                    parent->left = replace;
                } else {
                    parent->right = replace;
                }

                delete node;
                replace->parent = parent;
                if (doubleBlack) // replace and root both black, fix double black at replace
                    this->fixDoubleBlack(replace);
                else // replace or root red, color replace black
                    replace->color = Color::BLACK;
            }
            return;
        }
        case 2:
        {
            std::swap(replace->value, node->value);
            this->remove(replace);
        }
        }
    }

    Node<Comparable>* search(Node<Comparable>* root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->value == value)
            return root;
        return root->value < value ? this->search(root->right, value) : this->search(root->left, value);
    }

    Node<Comparable>* insert(Node<Comparable>*& root, Node<Comparable>*& parent) {
        if (!root)
            return parent;
        if (parent->value < root->value) {
            root->left = this->insert(root->left, parent);
            root->left->parent = root;
        } else if (parent->value > root->value) {
            root->right = this->insert(root->right, parent);
            root->right->parent = root;
        }

        return root;
    }

    Node<Comparable>* clear(Node<Comparable>*& root) {
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

        Node<Comparable>* node = new Node<Comparable>(root->value, root->color);
        node->left = this->copy(root->left);
        node->right = this->copy(root->right);
        return node;
    }

    Node<Comparable>* find_min(Node<Comparable>*& root) {
        Node<Comparable>* temp = root;
        while (temp && temp->left)
            temp = temp->left;
        return temp;
    }

    void print_tree(const Node<Comparable>* root, ostream& os, size_t trace) const {
        if (!root) {
            os << "<empty>\n";
            return;
        }

        if (root->right)
            this->print_tree(root->right, os, trace + 1);
        os << string(trace * 2, ' ') << *root << "\n";
        if (root->left)
            this->print_tree(root->left, os, trace + 1);
    }

public:
    RedBlackTree() : root{nullptr} {}

    RedBlackTree(const RedBlackTree& rhs) : root{this->copy(rhs.get_root())} {}

    ~RedBlackTree() { this->make_empty(); }

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

        Node<Comparable>* new_node = new Node(value);
        this->root = this->insert(this->root, new_node);
        this->rebalance(this->root, new_node);
    }

    void remove(const Comparable& value) {
        if (!this->root)
            return;

        Node<Comparable>* node = this->search(this->root, value);
        if (!node)
            return;

        this->remove(node);
    }

    bool contains(const Comparable& value) const {
        return this->search(this->root, value);
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

    bool is_empty() const { return !this->root; }

    void make_empty() { this->root = this->clear(this->root); }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->root, os, i);
    }
};