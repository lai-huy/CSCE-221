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

    struct Node {
        Comparable value;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Comparable& value) : value{Comparable(value)}, color{Color::RED}, left{nullptr}, right{nullptr}, parent{nullptr} {}
        Node(const Comparable& value, const Color& color) : value{Comparable(value)}, color{color}, left{nullptr}, right{nullptr}, parent{nullptr} {}

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

        friend ostream& operator<<(ostream& os, const Node& node) {
            os << node.colorToString() << ":" << node.value;
            return os;
        }

        bool isLeaf() const { return !this->left && !this->right; }

        bool isLeft() const { return this->parent ? this == this->parent->left : false; }

        bool isRight() const { return this->parent ? this == this->parent->right : false; }

        bool hasRedChild() { return (this->left && this->left->color == Color::RED) || (this->right && this->right->color == Color::RED); }

        bool isBlack() const { return this->color == Color::BLACK; }

        Node* sibling() const {
            if (!this->parent)
                return nullptr;
            return this->isLeft() ? this->parent->right : this->parent->left;
        }

        Node* uncle() const {
            if (!this->parent)
                return nullptr;
            return this->parent->sibling();
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
    Node* root;

    void rotateLeft(Node* node) {
        Node* right = node->right;
        node->right = right->left;
        if (right->left)
            right->left->parent = node;

        right->parent = node->parent;
        if (!node->parent)
            this->root = right;
        else if (node->isLeft())
            node->parent->left = right;
        else
            node->parent->right = right;

        right->left = node;
        node->parent = right;
    }

    void rotateRight(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        if (left->right)
            left->right->parent = node;

        left->parent = node->parent;
        if (!node->parent)
            this->root = left;
        else if (node->isRight())
            node->parent->right = left;
        else
            node->parent->left = left;

        left->right = node;
        node->parent = left;
    }

    void fixInsert(Node*& node) {
        Node* uncle = node->uncle();
        while (node->parent && node->parent->color == Color::RED) {
            if (!uncle || uncle->color == Color::BLACK) {
                if (node->parent->isLeft()) {
                    if (node->isRight()) {
                        node = node->parent;
                        this->rotateLeft(node);
                    }

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    this->rotateRight(node->parent->parent);
                } else {
                    if (node->isLeft()) {
                        node = node->parent;
                        this->rotateRight(node);
                    }

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    this->rotateLeft(node->parent->parent);
                }
            } else {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            }

            if (node == this->root)
                break;
        }

        this->root->color = Color::BLACK;
    }

    void transplant(Node*& u, Node*& v) {
        if (!u->parent)
            this->root = v;
        else if (u->isLeft())
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void fixRemove(Node* x) {
        Node* s = x->uncle();
        while (x != this->root && x->color == Color::RED) {
            if (x->isLeft()) {
                if (s->color == Color::BLACK) {
                    s->color = Color::RED;
                    x->parent->color = Color::BLACK;
                    this->rotateLeft(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == Color::RED && s->right->color == Color::RED) {
                    s->color = Color::BLACK;
                    x = x->parent;
                } else {
                    if (s->right->color == Color::RED) {
                        s->left->color = Color::RED;
                        s->color = Color::BLACK;
                        this->rotateRight(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = Color::RED;
                    s->right->color = Color::RED;
                    this->rotateLeft(x->parent);
                    x = root;
                }
            } else {
                if (s->color == Color::BLACK) {
                    s->color = Color::RED;
                    x->parent->color = Color::BLACK;
                    this->rotateRight(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == Color::RED && s->right->color == Color::RED) {
                    s->color = Color::BLACK;
                    x = x->parent;
                } else {
                    if (s->left->color == Color::RED) {
                        s->right->color = Color::RED;
                        s->color = Color::BLACK;
                        this->rotateLeft(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = Color::RED;
                    s->left->color = Color::RED;
                    this->rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = Color::RED;
    }

    Node* search(Node* root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->value == value)
            return root;
        return root->value < value ? this->search(root->right, value) : this->search(root->left, value);
    }

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

    Node* clear(Node*& root) {
        if (root) {
            root->left = this->clear(root->left);
            root->right = this->clear(root->right);
            delete root;
        }

        root = nullptr;
        return nullptr;
    }

    Node* copy(const Node* root) {
        if (!root)
            return nullptr;

        Node* node = new Node(root->value, root->color);
        node->left = this->copy(root->left);
        node->right = this->copy(root->right);
        return node;
    }

    Node* replace(Node*& root) const {
        switch (root->countChildren()) {
        case 1:
            return root->right ? root->right : root->left;
        case 2:
            return this->find_min(root->right);
        default:
            return nullptr;
        }
    }

    Node* find_min(Node* root) const {
        Node* node = root;
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* find_max(Node* root) const {
        Node* node = root;
        while (node && node->right)
            node = node->right;
        return node;
    }

    void print_tree(const Node* root, ostream& os, size_t trace) const {
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

        Node* z = new Node(value);
        this->root = this->insert(this->root, z);
        this->fixInsert(z);
    }

    void remove(const Comparable& value) {
        if (!this->root)
            return;

        Node* z = this->search(this->root, value);
        if (!z)
            return;

        Node* x = nullptr;
        Node* y = z;
        Color y_orig_color = y->color;

        switch (z->countChildren()) {
        case 0:
            if (z->isLeft())
                z->parent->left = nullptr;
            else
                z->parent->right = nullptr;
            break;
        case 1:
            if (z->right) {
                x = z->left;
                this->transplant(z, z->left);
            } else {
                x = z->right;
                this->transplant(z, z->right);
            }
            break;
        case 2:
            y = this->find_min(z->right);
            y_orig_color = y->color;
            x = y->right;
            if (y->parent == z)
                x->parent = y;
            else {
                this->transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            this->transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
            break;
        }

        delete z;
        if (y_orig_color == Color::BLACK)
            this->fixRemove(x);
    }

    bool contains(const Comparable& value) const { return this->search(this->root, value); }

    const Comparable& find_min() const {
        if (!this->root)
            throw invalid_argument("Red Black Tree is empty");

        return this->find_min(this->root)->value;
    }

    const Comparable& find_max() const {
        if (!this->root)
            throw invalid_argument("Red Black Tree is empty");

        return this->find_max(this->root)->value;
    }

    int color(const Node* node) const { return node ? node->color : Color::BLACK; }

    const Node* get_root() const { return this->root; }

    // ----------------------- Optional ----------------------- //
    // RedBlackTree(RedBlackTree&& rhs) : root{nullptr} {
    //     swap(this->root, rhs.root);
    // }

    // RedBlackTree& operator=(RedBlackTree&& rhs) {
    //     if (this != &rhs) {
    //         this->root = this->clear(this->root);
    //         swap(this->root, rhs.root);
    //     }

    //     return *this;
    // }

    // void insert(Comparable&& value) {
    //     if (this->contains(value))
    //         return;

    //     Comparable v = Comparable();
    //     swap(v, value);
    //     Node* z = new Node(v);
    //     this->root = this->insert(this->root, z);
    //     this->fixInsert(z);
    // }

    bool is_empty() const { return !this->root; }

    void make_empty() { this->root = this->clear(this->root); }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->root, os, i);
    }
};