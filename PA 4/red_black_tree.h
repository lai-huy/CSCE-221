#pragma once
#include <iostream>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::ostream, std::cout, std::stringstream;
using std::invalid_argument;
using std::string, std::swap;

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

        Node(const Comparable& rhs) : Node(rhs, Color::RED) {}

        Node(const Comparable& rhs, const Color& color) : value{rhs}, color{color}, left{nullptr}, right{nullptr}, parent{nullptr} {}

        Node* uncle() const {
            if (!this->parent)
                return nullptr;
            return this->parent->sibling();
        }

        Node* sibling() const {
            if (this->isRight())
                return this->parent->left;
            if (this->isLeft())
                return this->parent->right;
            return nullptr;
        }

        bool hasColorChildren(const Color& color) const {
            return (!this->left && !this->right && color == Color::BLACK) ||
                ((this->left && this->left->color == color) && (this->right && this->right->color == color));
        }

        bool leftNiblingRed() const {
            Node* sibling = this->sibling();
            return sibling && sibling->left && sibling->left->color == Color::RED;
        }

        bool rightNiblingRed() const {
            Node* sibling = this->sibling();
            return sibling && sibling->right && sibling->right->color == Color::RED;
        }

        bool isLeft() const { return this->parent ? this == this->parent->left : false; }

        bool isRight() const { return this->parent ? this == this->parent->right : false; }

        size_t countChildren() const {
            size_t count = 0;
            if (this->right)
                ++count;
            if (this->left)
                ++count;
            return count;
        }

        string to_string() const {
            stringstream ss;
            switch (this->color) {
            case RED:
                ss << "🟥 ";
                break;
            default:
                ss << "⬛ ";
                break;
            }
            ss << this->value;
            return ss.str();
        }

        friend ostream& operator<<(ostream& os, const Node& node) { return os << node.to_string(); }
    };
private:
    Node* _root;

    Node* rotateLeft(Node* root) {
        Node* temp = root->right;
        root->right = temp->left;
        if (temp->left)
            temp->left->parent = root;
        temp->parent = root->parent;
        if (!root->parent)
            this->_root = temp;
        else if (root->isRight())
            root->parent->right = temp;
        else if (root->isLeft())
            root->parent->left = temp;
        temp->left = root;
        root->parent = temp;
        return temp;
    }

    Node* rotateRight(Node* root) {
        Node* temp = root->left;
        root->left = temp->right;
        if (temp->right)
            temp->right->parent = root;
        temp->parent = root->parent;
        if (!root->parent)
            this->_root = temp;
        else if (root->isLeft())
            root->parent->left = temp;
        else if (root->isRight())
            root->parent->right = temp;
        temp->right = root;
        root->parent = temp;
        return temp;
    }

    Node* copy(const Node* root) {
        if (!root)
            return nullptr;
        Node* node = new Node(root->value, root->color);
        node->left = this->copy(root->left);
        if (node->left)
            node->left->parent = node;
        node->right = this->copy(root->right);
        if (node->right)
            node->right->parent = node;
        return node;
    }

    Node* clear(Node*& root) {
        if (root) {
            root->left = this->clear(root->left);
            root->right = this->clear(root->right);
            delete root;
        }

        return root = nullptr;
    }

    Node* find_min(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->left)
            temp = temp->left;
        return temp;
    }

    Node* find_max(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->right)
            temp = temp->right;
        return temp;
    }

    void insert(Node* node, const Comparable& value) {
        if (!node) {
            node = new Node(value);
            if (!this->_root)
                this->_root = node;
        }

        if (node->value == value)
            return;
        if (node->value > value) {
            if (!node->left) {
                node->left = new Node(value);
                node->left->parent = node;
                if (node->color == BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isLeft()) {
                        node = this->rotateRight(node->parent);
                        node->color = BLACK;
                        node->right->color = node->left->color = RED;
                        return;
                    } else {
                        node = this->rotateRight(node);
                        node = this->rotateLeft(node->parent);
                        node->color = BLACK;
                        node->left->color = node->right->color = RED;
                        return;
                    }
                }
            }
        } else if (node->value < value) {
            if (!node->right) {
                node->right = new Node(value);
                node->right->parent = node;
                if (node->color == BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isRight()) {
                        node = this->rotateLeft(node->parent);
                        node->color = BLACK;
                        node->right->color = node->left->color = RED;
                        return;
                    } else {
                        node = this->rotateLeft(node);
                        node = this->rotateRight(node->parent);
                        node->color = BLACK;
                        node->right->color = node->left->color = RED;
                        return;
                    }
                }
            }
        }

        if (node->hasColorChildren(Color::RED)) {
            node->color = RED;
            node->right->color = node->left->color = BLACK;
            if (node->parent && node->parent->color == RED) {
                if (node->isLeft() && node->parent->isLeft()) {
                    node = this->rotateRight(node->parent->parent);
                    node->color = BLACK;
                    node->left->color = node->right->color = RED;
                    this->insert(node, value);
                    return;
                }
                if (node->isRight() && node->parent->isRight()) {
                    node = this->rotateLeft(node->parent->parent);
                    node->color = BLACK;
                    node->left->color = node->right->color = RED;
                    this->insert(node, value);
                    return;
                }
                if (node->isRight() && node->parent->isLeft()) {
                    node = this->rotateLeft(node->parent);
                    node = this->rotateRight(node->parent);
                    node->color = BLACK;
                    node->left->color = node->right->color = RED;
                    this->insert(node, value);
                    return;
                }
                if (node->isLeft() && node->parent->isRight()) {
                    node = this->rotateRight(node->parent);
                    node = this->rotateLeft(node->parent);
                    node->color = BLACK;
                    node->left->color = node->right->color = RED;
                    this->insert(node, value);
                    return;
                }
            }
        }
        this->insert(node->value > value ? node->left : node->right, value);
    }

    void remove(Node* node, const Comparable& value) {
        if (node == this->_root && node->value == value && !node->countChildren()) {
            delete node;
            node = this->_root = nullptr;
        } else if (node && node->hasColorChildren(BLACK) && node == this->_root) {
            this->_root->color = Color::RED;
            this->decideDelete(this->_root, value);
        } else
            this->step2B(node, value);
        if (this->_root)
            this->_root->color = Color::BLACK;
    }

    void decideDelete(Node* node, const Comparable& value) {
        if (!node)
            return;
        if (node->value > value && !node->left)
            return;
        if (node->value < value && !node->right)
            return;
        if (node->value == value)
            this->step3(node);
        else step2(node->value > value ? node->left : node->right, value);
    }

    void step2(Node* node, const Comparable& value) {
        if (!node) return;
        if (node->hasColorChildren(BLACK))
            this->step2A(node, value);
        else
            this->step2B(node, value);
    }

    void step2A(Node* node, const Comparable& value) {
        if (node->sibling() && node->sibling()->hasColorChildren(BLACK)) {
            step2A1(node, value);
        } else if ((node->isLeft() && node->leftNiblingRed()) || (node->isRight() && node->rightNiblingRed())) {
            step2A2(node, value);
        } else step2A3(node, value);
    }

    void step2A1(Node* node, const Comparable& value) {
        node->color = node->sibling()->color = Color::RED;
        if (node->parent) node->parent->color = Color::BLACK;
        decideDelete(node, value);
    }

    void step2A2(Node* node, const Comparable& value) {
        if (node->isLeft()) {
            node = this->rotateRight(node->sibling());
            node = this->rotateLeft(node->parent);
            node->left->color = Color::BLACK;
            node->left->left->color = Color::RED;
            node = node->left->left;
        } else {
            node = this->rotateLeft(node->sibling());
            node = this->rotateRight(node->parent);
            node->right->color = Color::BLACK;
            node->right->right->color = Color::RED;
            node = node->right->right;
        }
        this->decideDelete(node, value);
    }

    void step2A3(Node* node, const Comparable& value) {

        if (node->isLeft()) {
            node = rotateLeft(node->parent);
            node->color = Color::RED;
            node->right->color = node->left->color = Color::BLACK;
            node = node->left->left;
        } else {
            node = rotateRight(node->parent);
            node->color = Color::RED;
            node->right->color = node->left->color = Color::BLACK;
            node = node->right->right;
        }
        node->color = Color::RED;
        this->decideDelete(node, value);
    }

    void step2B(Node* node, const Comparable& value) {
        if (value == node->value)
            step3(node);
        else {
            node = node->value > value ? node->left : node->right;
            if (!node) return;
            else if (node->color == Color::RED)
                this->decideDelete(node, value);
            else
                step2B2(node, value);
        }
    }

    void step2B2(Node* node, const Comparable& value) {
        if (node->isLeft()) {
            node = this->rotateLeft(node->parent);
            node->left->color = Color::RED;
            node->color = Color::BLACK;
            node = node->left->left;
        } else {
            node = this->rotateRight(node->parent);
            node->right->color = Color::RED;
            node->color = Color::BLACK;
            node = node->right->right;
        }
        step2(node, value);
    }

    void step3(Node* node) {
        if (!node)
            return;
        switch (node->countChildren()) {
        case 0:
            if (node->isLeft())
                node->parent->left = nullptr;
            if (node->isRight())
                node->parent->right = nullptr;
            if (node == this->_root) {
                delete this->_root;
                node = this->_root = nullptr;
            } else {
                delete node;
                node = nullptr;
            }
            return;
        case 1:
            if (node->isLeft()) {
                if (node->left) {
                    node->parent->left = node->left;
                    node->left->parent = node->parent;
                    node->left->color = Color::BLACK;
                } else if (node->right) {
                    node->parent->left = node->right;
                    node->right->parent = node->parent;
                    node->right->color = Color::BLACK;
                }
            } else if (node->isRight()) {
                if (node->right) {
                    node->parent->right = node->right;
                    node->right->parent = node->parent;
                    node->right->color = Color::BLACK;
                } else if (node->left) {
                    node->parent->right = node->left;
                    node->left->parent = node->parent;
                    node->left->color = Color::BLACK;
                }
            } else if (node == this->_root)
                this->_root = node->left ? node->left : node->right;
            delete node;
            node = nullptr;
            return;
        case 2:
            Node * temp = this->find_min(node->right);
            Comparable value = temp->value;
            if (node->color == Color::RED) {
                node->value = temp->value;
                this->step2(node->right, node->value);
            } else {
                this->step2B(node, temp->value);
                node->value = value;
            }
            return;
        }
    }

    void print_tree(const Node* root, ostream& os, size_t lvl) const {
        if (root->right)
            this->print_tree(root->right, os, lvl + 1);
        os << string(lvl * 2, ' ') << *root << "\n";
        if (root->left)
            this->print_tree(root->left, os, lvl + 1);

    }

    bool followsRules(Node* const& root) const {
        if (this->doubleRed(root)) {
            cout << "Double Red\n";
            return false;
        }

        if (this->blackHeight(root->left) != this->blackHeight(root->right)) {
            cout << "Invalid Black Height\n";
            return false;
        }

        return true;
    }

    bool doubleRed(Node* const& root) const {
        if (!root)
            return false;
        if (root->color == Color::RED && !root->hasColorChildren(Color::BLACK))
            return true;
        return this->doubleRed(root->left) || this->doubleRed(root->right);
    }

    bool contains(Node* const& root, const Comparable& value) {
        if (!root)
            return false;
        if (root->value == value)
            return true;
        return this->contains(root->value > value ? root->left : root->right, value);
    }

    size_t blackHeight(Node* const& root) const {
        if (!root)
            return 1;
        size_t height = this->blackHeight(root->left);
        return height + (root->color == Color::BLACK ? 1 : 0);
    }
public:
    RedBlackTree() : _root{nullptr} {};

    RedBlackTree(const RedBlackTree& rbt) : _root{this->copy(rbt._root)} {};

    ~RedBlackTree() { this->make_empty(); }

    const RedBlackTree& operator=(const RedBlackTree& rbt) {
        if (&rbt != this) {
            this->clear(this->_root);
            this->_root = this->copy(rbt._root);
        }
        return *this;
    }

    void insert(const Comparable& value) {
        this->insert(this->_root, value);
        this->_root->color = Color::BLACK;
        return;
    }

    void remove(const Comparable& value) {
        if (!this->_root)
            return;
        this->remove(this->_root, value);
    }

    bool contains(const Comparable& value) { return this->contains(this->_root, value); }

    const Comparable& find_min() {
        if (!_root)
            throw invalid_argument("🟥⬛🌲 is empty.");
        return this->find_min(this->_root)->value;
    }

    const Comparable& find_max() {
        if (!this->_root)
            throw invalid_argument("🟥⬛🌲 is empty.");
        return this->find_max(this->_root)->value;
    }

    int color(const Node* node) const { return node ? node->color : Color::BLACK; }

    const Node* get_root() const { return this->_root; }

    bool followsRules() const { return this->_root ? this->followsRules(this->_root) : true; }

    // ----------------------- Optional ----------------------- //
    RedBlackTree(RedBlackTree&& rhs) : _root{nullptr} { swap(this->_root, rhs._root); }
    RedBlackTree& operator=(RedBlackTree&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs._root);
        }
    }

    bool is_empty() { return !this->_root; }

    void insert(Comparable&& value) {
        Comparable v;
        swap(v, value);
        this->insert(v);
    }

    void make_empty() { this->_root = this->clear(_root); }

    void print_tree(std::ostream& os = std::cout) const {
        if (this->_root)
            this->print_tree(this->_root, os, 0);
        os << "<empty>";
    }
};