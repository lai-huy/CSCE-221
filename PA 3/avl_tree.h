#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ostream, std::cout;
using std::invalid_argument;
using std::string;

/**
 * @brief
 *
 * @tparam Comparable
 */
template <typename Comparable>
class AVLTree {
public:
    template <typename T>
    struct Node {
        T _value;
        size_t _height;
        Node<T>* _left;
        Node<T>* _right;

        Node(const T& val) : _value{T(val)}, _height{1}, _left{nullptr}, _right{nullptr} {}

        bool is_leaf() const {
            return !this->_left && !this->_right;
        }
    };

private:
    Node<Comparable>* _root;

    template <typename Type>
    Type max(const Type& a, const Type& b) const {
        return a > b ? a : b;
    }

    bool contains(Node<Comparable>*& root, const Comparable& val) const {
        if (!root)
            return false;
        if (root->_value == val)
            return true;
        if (root->_value < val)
            return this->contains(root->_right, val);
        return this->contains(root->_left, val);
    }

    Node<Comparable>*& clear(Node<Comparable>*& node) {
        if (node) {
            node->_left = this->clear(node->_left);
            node->_right = this->clear(node->_right);
            delete node;
        }

        node = nullptr;
        return node;
    }

    void print_tree(Node<Comparable>* root, ostream& os, size_t trace) const {
        if (!root) {
            os << "<empty>\n";
            return;
        }

        if (root->_right)
            this->print_tree(root->_right, os, trace + 1);
        os << string(trace * 2, ' ') << root->_value << "\n";
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
        else if (val == node->_value)
            return node;
        else if (val < node->_value)
            node->_left = this->insert(node->_left, val);
        else if (val > node->_value)
            node->_right = this->insert(node->_right, val);

        node = this->balance(node);
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

        root = this->balance(root);
        return root;
    }
    
    signed long height(const Node<Comparable>*& root) const {
        if (!root)
            return 0;

        return root->_height;
    }
    
    size_t calcHeight(const Node<Comparable>*& root) const {
        if (!root)
            return 0;
        return 1 + this->max(this->height(const_cast<const Node<Comparable>*&>(root->_left)), this->height(const_cast<const Node<Comparable>*&>(root->_right)));
    }

    signed long balace_factor(const Node<Comparable>*& root) const {
        return !root ?
            0l :
            this->height(const_cast<const Node<Comparable>*&>(root->_left)) - this->height(const_cast<const Node<Comparable>*&>(root->_right));
    }

    Node<Comparable>* rr_rotate(Node<Comparable>*& root) {
        Node<Comparable>* temp = root->_right;
        root->_right = temp->_left;
        temp->_left = root;

        // TODO fix height
        root->_height = this->calcHeight(const_cast<const Node<Comparable>*&>(root));
        temp->_height = this->calcHeight(const_cast<const Node<Comparable>*&>(temp));

        return temp;
    }

    Node<Comparable>* ll_rotate(Node<Comparable>*& root) {
        Node<Comparable>* temp = root->_left;
        root->_left = temp->_right;
        temp->_right = root;
        return temp;
    }

    Node<Comparable>* lr_rotate(Node<Comparable>*& root) {
        Node<Comparable>* temp = root->_left;
        root->_left = this->rr_rotate(temp);
        return this->ll_rotate(root);
    }

    Node<Comparable>* rl_rotate(Node<Comparable>*& root) {
        Node<Comparable>* temp = root->_right;
        root->_right = this->ll_rotate(temp);
        return this->rr_rotate(root);
    }

    Node<Comparable>* balance(Node<Comparable>* root) {
        const Node<Comparable>*& left = const_cast<const Node<Comparable>*&>(root->_left);
        const Node<Comparable>*& right = const_cast<const Node<Comparable>*&>(root->_right);

        root->_height = 1 + this->max(this->height(left), this->height(right));
        signed long bf = this->balace_factor(const_cast<const Node<Comparable>*&>(root));
        if (bf > 1)
            root = this->balace_factor(left) > 0 ? ll_rotate(root) : lr_rotate(root);
        else if (bf < -1)
            root = this->balace_factor(right) > 0 ? rl_rotate(root) : rr_rotate(root);
        return root;
    }

    Node<Comparable>* find_min(Node<Comparable>* root) {
        Node<Comparable>* node = root;
        while (node && node->_left)
            node = node->_left;

        return node;
    }

    void clearRoot() {
        this->_root = nullptr;
    }

public:
    AVLTree() : _root{nullptr} {}

    AVLTree(const AVLTree& rhs) : _root{this->copy(rhs.root())} {}

    ~AVLTree() {
        this->make_empty();
    }

    AVLTree& operator=(const AVLTree& rhs) {
        if (this != &rhs) {
            this->make_empty();
            this->_root = this->copy(rhs.root());
        }
        return *this;
    }

    bool contains(const Comparable& val) {
        return this->contains(this->_root, val);
    }

    void insert(const Comparable& val) {
        this->_root = this->insert(this->_root, val);
    }

    void remove(const Comparable& val) {
        this->_root = this->remove(this->_root, val);
    }

    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("AVL Tree is empty");

        Node<Comparable>* root = this->_root;

        while (root->_left)
            root = root->_left;

        return root->_value;
    }

    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("AVL Tree is empty");

        Node<Comparable>* root = this->_root;

        while (root->_right)
            root = root->_right;

        return root->_value;
    }

    void print_tree(ostream& os = cout) const {
        size_t i = 0;
        this->print_tree(this->_root, os, i);
    }

    const Node<Comparable>* root() const {
        return this->_root;
    }

    // OPTIONAL
    // AVLTree(AVLTree&& rhs) : _root{rhs.root()} { rhs.clearRoot() }
    // AVLTree& operator=(AVLTree&& rhs) {
    //     if (this != &rhs) {
    //         this->_root = rhs.root();
    //         rhs.clearRoot();
    //     }
    // }

    // void insert(Comparable&& value) {

    // }

    bool is_empty() const {
        return !this->_root;
    }

    void make_empty() {
        this->_root = this->clear(this->_root);
    }
};
