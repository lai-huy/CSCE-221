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

        bool isLeft() const { return this == parent->left; }

        bool hasRedChild() {
            return (this->left && this->left->color == Color::RED) || (this->right && this->right->color == Color::RED);
        }

        bool isLeaf() const { return !this->left && !this->right; }

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

    void rebalance(Node*& root, Node*& parent) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((parent != root) && (parent->color != Color::BLACK) && (parent->parent->color == Color::RED)) {
            parent_pt = parent->parent;
            grand_parent_pt = parent->parent->parent;
            Node* uncle;

            // Case : A Parent of pt is left child of Grand-parent of pt
            if (parent_pt == grand_parent_pt->left) {
                uncle = grand_parent_pt->right;

                // Case : 1 The uncle of pt is also red Only Recoloring required
                if (uncle && uncle->color == Color::RED) {
                    grand_parent_pt->color = Color::RED;
                    parent_pt->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    parent = grand_parent_pt;
                } else {
                    // Case : 2 pt is right child of its parent Left-rotation required
                    if (parent == parent_pt->right) {
                        this->rotateLeft(root, parent_pt);
                        parent = parent_pt;
                        parent_pt = parent->parent;
                    }

                    // Case : 3 pt is left child of its parent Right-rotation required
                    this->rotateRight(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    parent = parent_pt;
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
                    parent = grand_parent_pt;
                } else {
                    // Case : 2 pt is left child of its parent Right-rotation required
                    if (parent == parent_pt->left) {
                        this->rotateRight(root, parent_pt);
                        parent = parent_pt;
                        parent_pt = parent->parent;
                    }

                    // Case : 3 pt is right child of its parent Left-rotation required
                    this->rotateLeft(root, grand_parent_pt);
                    std::swap(parent_pt->color, grand_parent_pt->color);
                    parent = parent_pt;
                }
            }
        }

        root->color = Color::BLACK;
    }

    void fixDoubleBlack(Node*& node) {
        if (node == this->root)
            return;

        Node* sibling = node->sibling(), * parent = node->parent;
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
                    if (sibling->left != NULL && sibling->left->color == Color::RED) {
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
            }
        }
    }

    void remove(Node*& node) {
        Node* replace = this->replace(node);

        // True when replace and node are both black
        bool doubleBlack = node->isBlack() && (!replace || replace->isBlack());
        Node* parent = node->parent;

        switch (node->countChildren()) {
        case 0:
        {
            if (node == this->root) {   // Node being removed is the root of the tree
                this->root = nullptr;
            } else {
                if (doubleBlack) {
                    this->fixDoubleBlack(node);
                } else {
                    Node* sibling = node->sibling();
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
    */

    void rotateTriangle(Node*& child, Node*& parent) {
        Node* root = parent->parent;
        if (parent->isLeft()) {
            root->left = child;
            child->left = parent;
            parent->parent = child;
        } else {
            root->right = child;
            child->right = parent;
            parent->parent = child;
        }
    }

    void rotateLine(Node*& child, Node*& parent) {
        cout << child << "\n";
        cout << parent << "\n";
    }

    void fixViolation(Node*& root) {
        if (!root)
            return;

        if (root == this->root)
            this->root->color = Color::BLACK;
        else {
            Node* uncle = root->uncle();
            if (uncle)
                switch (uncle->color) {
                case Color::RED:
                    root->color = Color::RED;
                    root->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    root->parent->parent->color = Color::RED;
                    break;
                default:
                {
                    if (root->isLeft() ^ root->parent->isLeft())
                        this->rotateTriangle(root, root->parent);
                    else
                        cout << root->isLeft() << ", " << root->parent->isLeft() << "\n";
                    break;
                }
                }

            this->fixViolation(root->left);
            this->fixViolation(root->right);
        }
    }

    void recolor() {
        this->fixViolation(this->root->left);
        this->fixViolation(this->root->right);
        this->fixViolation(this->root);
    }

    Node* search(Node* root, const Comparable& value) const {
        if (!root)
            return nullptr;
        if (root->value == value)
            return root;
        return root->value < value ? this->search(root->right, value) : this->search(root->left, value);
    }

    Node* insert(Node*& root, const Comparable& value) {
        if (!root)
            return new Node(value);
        if (value < root->value) {
            root->left = this->insert(root->left, value);
            root->left->parent = root;
        } else if (value > root->value) {
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

        this->root = this->insert(this->root, value);
        this->recolor();
    }

    void remove(const Comparable& value) {
        if (!this->root)
            return;

        Node* node = this->search(this->root, value);
        if (!node)
            return;

        // this->remove(node);
    }

    bool contains(const Comparable& value) const {
        return this->search(this->root, value);
    }

    const Comparable& find_min() const {
        if (!this->root)
            throw invalid_argument("Red Black Tree is empty");

        Node* node = this->root;
        while (node->left)
            node = node->left;

        return node->value;
    }

    const Comparable& find_max() const {
        if (!this->root)
            throw invalid_argument("Red Black Tree is empty");

        Node* node = this->root;
        while (node->right)
            node = node->right;

        return node->value;
    }

    int color(const Node* node) const {
        return node ? node->color : Color::BLACK;
    }

    const Node* get_root() const {
        return this->root;
    }

    // ----------------------- Optional ----------------------- //
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