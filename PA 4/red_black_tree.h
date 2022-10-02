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
    enum Color { RED = 0, BLACK = 1 };

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
    Node* _root;

    /*
    void rotateLeft(Node*& root, Node*& parent) {
        Node* right = parent->right;
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

    void rotateRight(Node*& root, Node*& parent) {
        Node* left = parent->left;
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

    void fixInsert(Node*& root, Node*& node) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((node != this->_root) && (node->color != Color::BLACK) && (node->parent->color == Color::RED)) {
            parent_pt = node->parent;
            grand_parent_pt = node->parent->parent;
            Node* uncle;

            // Case : A Parent of pt is left child of Grand-parent of pt
            if (parent_pt == grand_parent_pt->left) {
                uncle = grand_parent_pt->right;

                // Case : 1 The uncle of pt is also red Only Recoloring required
                if (uncle && uncle->color == Color::RED) {
                    grand_parent_pt->color = Color::RED;
                    parent_pt->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node = grand_parent_pt;
                } else {
                    // Case : 2 pt is right child of its parent Left-rotation required
                    if (node == parent_pt->right) {
                        this->rotateLeft(root, parent_pt);
                        node = parent_pt;
                        parent_pt = node->parent;
                    }

                    // Case : 3 pt is left child of its parent Right-rotation required
                    this->rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    node = parent_pt;
                }
            }

            // Case : B Parent of pt is right child of Grand-parent of pt
            else {
                uncle = grand_parent_pt->left;

                //  Case : 1 The uncle of pt is also red Only Recoloring required
                if (uncle && uncle->color == Color::RED) {
                    grand_parent_pt->color = Color::RED;
                    parent_pt->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node = grand_parent_pt;
                } else {
                    // Case : 2 pt is left child of its parent Right-rotation required
                    if (node == parent_pt->left) {
                        this->rotateRight(root, parent_pt);
                        node = parent_pt;
                        parent_pt = node->parent;
                    }

                    // Case : 3 pt is right child of its parent Left-rotation required
                    this->rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    node = parent_pt;
                }
            }
        }

        this->_root->color = Color::BLACK;
    }*/

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            this->_root = y;
        else if (x->isLeft())
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right)
            y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent)
            this->_root = y;
        else if (x->isRight())
            x->parent->right = y;
        else
            x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

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

    void remove(Node*& z) {
        Node* x = nullptr;
        Node* y = z;
        Color y_og_color = y->color;
        switch (z->countChildren()) {
        case 0:
            break;
        case 1:
            if (!z->left) {
                x = z->right;
                this->transplant(z, z->right);
            } else if (!z->right) {
                x = z->left;
                this->transplant(z, z->left);
            }
            break;
        case 2:
            y = this->find_min(z->right);
            y_og_color = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x)
                    x->parent = z;
            } else {
                this->transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            this->transplant(z, y);
            y->left = z->left;
            if (y->left)
                y->left->parent = y;
            y->color = z->color;
            break;
        }

        if (z->isLeft())
            z->parent->left = nullptr;
        else
            z->parent->right = nullptr;
        delete z;
        z = nullptr;
        if (y_og_color == Color::RED)
            this->fixRemove(x);
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

    Node* find_min(Node*& root) const {
        Node* node = root;
        while (node && node->left)
            node = node->left;
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
    RedBlackTree() : _root{nullptr} {}

    RedBlackTree(const RedBlackTree& rhs) : _root{this->copy(rhs.get_root())} {}

    ~RedBlackTree() { this->make_empty(); }

    RedBlackTree& operator=(const RedBlackTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs.get_root());
        }

        return *this;
    }

    void insert(const Comparable& value) {
        if (this->contains(value))
            return;

        Node* z = new Node(value);
        this->_root = this->insert(this->_root, z);
        this->fixInsert(z);
    }

    void remove(const Comparable& value) {
        if (!this->_root)
            return;

        Node* node = this->search(this->_root, value);
        if (!node)
            return;

        this->remove(node);
    }

    bool contains(const Comparable& value) const { return this->search(this->_root, value); }

    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("Red Black Tree is empty");

        Node* node = this->_root;
        while (node->left)
            node = node->left;

        return node->value;
    }

    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("Red Black Tree is empty");

        Node* node = this->_root;
        while (node->right)
            node = node->right;

        return node->value;
    }

    int color(const Node* node) const { return node ? node->color : Color::BLACK; }

    const Node* get_root() const { return this->_root; }

    // ----------------------- Optional ----------------------- //
    // RedBlackTree(RedBlackTree&& rhs) : root{nullptr} { swap(this->_root, rhs.root); }

    // RedBlackTree& operator=(RedBlackTree&& rhs) {
    //     if (this != &rhs) {
    //         this->_root = this->clear(this->_root);
    //         swap(this->_root, rhs.root);
    //     }

    //     return *this;
    // }

    // void insert(Comparable&& value) {
    //     if (this->contains(value))
    //         return;

    //     Comparable v = Comparable();
    //     swap(v, value);
    //     Node* z = new Node(v);
    //     this->_root = this->insert(this->_root, z);
    //     this->fixInsert(this->_root, z);
    // }

    bool is_empty() const { return !this->_root; }

    void make_empty() { this->_root = this->clear(this->_root); }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->_root, os, i);
    }
};