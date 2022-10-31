#pragma once
#include <iostream>
#include <cstddef>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>

using std::ostream, std::cout, std::stringstream;
using std::invalid_argument;
using std::string;
using std::swap;

/**
 * @brief 🟥⬛🌲
 *
 * @tparam Comparable value type that overloads the comparison operators
 */
template <typename Comparable>
class RedBlackTree {
public:
    /**
     * @brief Color of each node
     */
    enum Color { RED, BLACK };

    /**
     * @brief Internal node structure of the tree
     */
    struct Node {
        /**
         * @brief Comparable stored in the node
         */
        Comparable value;

        /**
         * @brief Color of this node
         */
        Color color;

        /**
         * @brief a pointer to the left child of this node
         */
        Node* left;

        /**
         * @brief a pointer to the right child of this node
         *
         */
        Node* right;

        /**
         * @brief a pointer to the parent of this node
         */
        Node* parent;

        /**
         * @brief Construct a new Node object
         *
         * @param rhs comparable to set as the value
         */
        Node(const Comparable& rhs) : Node(rhs, Color::RED) {}

        /**
         * @brief Construct a new Node object
         *
         * @param rhs comparable to set as the value
         * @param color Color to set as the color
         */
        Node(const Comparable& rhs, const Color& color) : value{rhs}, color{color}, left{nullptr}, right{nullptr}, parent{nullptr} {}

        /**
         * @brief Determines the sibling of this node
         *
         * @return Node* a pointer to the sibling of this node
         */
        Node* sibling() const {
            if (!this->parent)
                return nullptr;
            return this->isRight() ? this->parent->left : this->parent->right;
        }

        /**
         * @brief Determine if both children are a specified color
         *
         * @param color the color of both children
         * @return true if both children are a specified color
         * @return false otherwise
         */
        bool hasColorChildren(const Color& color) const {
            return (!this->left && !this->right && color == Color::BLACK) ||
                ((this->left && this->left->color == color) && (this->right && this->right->color == color));
        }

        /**
         * @brief Determines if the left nibling is red
         *
         * @return true if left nibling is red
         * @return false otherwise
         */
        bool leftNiblingRed() const {
            Node* sibling = this->sibling();
            return sibling && sibling->left && sibling->left->color == Color::RED;
        }

        /**
         * @brief Determines if the right nibling if red
         *
         * @return true if the right nibling if red
         * @return false otherwise
         */
        bool rightNiblingRed() const {
            Node* sibling = this->sibling();
            return sibling && sibling->right && sibling->right->color == Color::RED;
        }

        /**
         * @brief Determine if this is a left child
         *
         * @return true if this is a left child
         * @return false otherwise
         */
        bool isLeft() const { return this->parent ? this == this->parent->left : false; }

        /**
         * @brief Determine if this is a right child
         *
         * @return true if this is a right child
         * @return false otherwise
         */
        bool isRight() const { return this->parent ? this == this->parent->right : false; }

        /**
         * @brief Counts the number of children this node has
         *
         * @return size_t the number of children this node has
         */
        size_t countChildren() const {
            size_t count = 0;
            if (this->left)
                ++count;
            if (this->right)
                ++count;
            return count;
        }

        /**
         * @brief Converts this node to a std::string
         *
         * @return string printable version of this
         */
        string to_string() const {
            stringstream ss;
            switch (this->color) {
            case Color::RED:
                ss << "🟥 ";
                break;
            default:
                ss << "⬛ ";
                break;
            }
            ss << this->value;
            return ss.str();
        }

        /**
         * @brief Insertion operator
         *
         * @param os ostream to insert to
         * @param node node to print
         * @return ostream& ostream to insert to
         */
        friend ostream& operator<<(ostream& os, const Node& node) { return os << node.to_string(); }
    };
private:
    /**
     * @brief Root of the 🟥⬛🌲
     */
    Node* _root;

    /**
     * @brief Determine if a subtree contains a value
     *
     * @param root subtree's root
     * @param value value to search for
     * @return true if the subtree contains the value
     * @return false otherwise
     */
    bool contains(Node* const& root, const Comparable& value) {
        if (!root)
            return false;
        if (root->value == value)
            return true;
        return this->contains(root->value > value ? root->left : root->right, value);
    }

    /**
     * @brief Inserts a value into a subtree
     *
     * @param node subtree's root
     * @param value value to insert
     */
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

                if (node->color == Color::BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isLeft()) {
                        node = this->rotateRight(node->parent);
                        node->color = Color::BLACK;
                        node->left->color = node->right->color = Color::RED;
                        return;
                    } else {
                        node = this->rotateRight(node);
                        node = this->rotateLeft(node->parent);
                        node->color = Color::BLACK;
                        node->left->color = node->right->color = Color::RED;
                        return;
                    }
                }
            }
        } else if (node->value < value) {
            if (!node->right) {
                node->right = new Node(value);
                node->right->parent = node;
                if (node->color == Color::BLACK)
                    return;
                if (!node->sibling()) {
                    if (node->isRight()) {
                        node = this->rotateLeft(node->parent);
                        node->color = Color::BLACK;
                        node->right->color = node->left->color = Color::RED;
                        return;
                    } else {
                        node = this->rotateLeft(node);
                        node = this->rotateRight(node->parent);
                        node->color = Color::BLACK;
                        node->right->color = node->left->color = Color::RED;
                        return;
                    }
                }
            }
        }

        if (node->hasColorChildren(Color::RED)) {
            node->color = Color::RED;
            node->right->color = node->left->color = Color::BLACK;

            if (node->parent && node->parent->color == Color::RED) {
                if (node->isLeft() && node->parent->isLeft()) {
                    node = this->rotateRight(node->parent->parent);
                    node->color = Color::BLACK;
                    node->left->color = node->right->color = Color::RED;
                    this->insert(node, value);
                    return;
                }
                if (node->isRight() && node->parent->isRight()) {
                    node = this->rotateLeft(node->parent->parent);
                    node->color = Color::BLACK;
                    node->left->color = node->right->color = Color::RED;
                    this->insert(node, value);
                    return;
                }
                if (node->isRight() && node->parent->isLeft()) {
                    node = this->rotateLeft(node->parent);
                    node = this->rotateRight(node->parent);
                    node->color = Color::BLACK;
                    node->left->color = node->right->color = Color::RED;
                    this->insert(node, value);
                    return;
                }
                if (node->isLeft() && node->parent->isRight()) {
                    node = this->rotateRight(node->parent);
                    node = this->rotateLeft(node->parent);
                    node->color = Color::BLACK;
                    node->left->color = node->right->color = Color::RED;
                    this->insert(node, value);
                    return;
                }
            }
        }
        this->insert(node->value > value ? node->left : node->right, value);
    }

    /**
     * @brief Remove a value from a subtree
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void remove(Node* node, const Comparable& value) {
        if (node == this->_root && node->value == value && !node->countChildren()) {
            delete node;
            node = this->_root = nullptr;
        } else if (node && node->hasColorChildren(Color::BLACK) && node == this->_root) {
            this->_root->color = Color::RED;
            this->decideDelete(this->_root, value);
        } else
            this->setUpRemoval(node, value);
        if (this->_root)
            this->_root->color = Color::BLACK;
    }

    /**
     * @brief Determine which direction to traverse when deleting
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void decideDelete(Node* node, const Comparable& value) {
        if (!node)
            return;
        if (node->value > value && !node->left)
            return;
        if (node->value < value && !node->right)
            return;
        if (node->value == value)
            this->removeNode(node);
        else
            this->setUpRedLeaf(node->value > value ? node->left : node->right, value);
    }

    /**
     * @brief Set up Red Leaf for removal
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void setUpRedLeaf(Node* node, const Comparable& value) {
        if (!node) return;
        if (node->hasColorChildren(Color::BLACK))
            this->setUpRotations(node, value);
        else
            this->setUpRemoval(node, value);
    }

    /**
     * @brief Set up rotations on the way down
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void setUpRotations(Node* node, const Comparable& value) {
        Node* sibling = node->sibling();
        if (sibling && sibling->hasColorChildren(Color::BLACK)) {
            this->recolorChildren(node, value);
        } else if ((node->isLeft() && node->leftNiblingRed()) || (node->isRight() && node->rightNiblingRed())) {
            this->rotateNiblingRed(node, value);
        } else
            this->rotateNiblingBlack(node, value);
    }

    /**
     * @brief Recolor node and its sibling to RED
     *
     * @param node node to recolor
     * @param value value to remove
     */
    void recolorChildren(Node* node, const Comparable& value) {
        node->color = node->sibling()->color = Color::RED;
        if (node->parent)
            node->parent->color = Color::BLACK;
        this->decideDelete(node, value);
    }

    /**
     * @brief Rotates if the node's nibling is red
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void rotateNiblingRed(Node* node, const Comparable& value) {
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

    /**
     * @brief Rotates if the node's nibling is black
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void rotateNiblingBlack(Node* node, const Comparable& value) {
        if (node->isLeft()) {
            node = this->rotateLeft(node->parent);
            node->color = Color::RED;
            node->right->color = node->left->color = Color::BLACK;
            node = node->left->left;
        } else {
            node = this->rotateRight(node->parent);
            node->color = Color::RED;
            node->right->color = node->left->color = Color::BLACK;
            node = node->right->right;
        }
        node->color = Color::RED;
        this->decideDelete(node, value);
    }

    /**
     * @brief Set
     *
     * @param node
     * @param value
     */
    void setUpRemoval(Node* node, const Comparable& value) {
        if (value == node->value)
            this->removeNode(node);
        else {
            node = node->value > value ? node->left : node->right;
            if (!node) return;
            else if (node->color == Color::RED)
                this->decideDelete(node, value);
            else
                this->rotateRemoval(node, value);
        }
    }

    /**
     * @brief Rotate on the way down
     *
     * @param node subtree's root
     * @param value value to remove
     */
    void rotateRemoval(Node* node, const Comparable& value) {
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
        this->setUpRedLeaf(node, value);
    }

    /**
     * @brief Removes the node from the tree
     *
     * @param node a pointer to the node to remove
     */
    void removeNode(Node* node) {
        if (!node)
            return;
        switch (node->countChildren()) {
        case 0:
            if (node->isLeft())
                node->parent->left = nullptr;
            if (node->isRight())
                node->parent->right = nullptr;
            if (node != this->_root) {
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
        default:
            Node* temp = this->find_min(node->right);
            Comparable value = temp->value;
            if (node->color == Color::RED) {
                node->value = temp->value;
                this->setUpRedLeaf(node->right, node->value);
            } else {
                this->setUpRemoval(node, temp->value);
                node->value = value;
            }
            return;
        }
    }

    /**
     * @brief print a subtree to an ostream
     *
     * @param root subtree's root
     * @param os ostream to print to
     * @param lvl depth of root
     */
    void print_tree(const Node* const& root, ostream& os, size_t lvl) const {
        if (root->right)
            this->print_tree(root->right, os, lvl + 1);
        os << string(lvl << 2, ' ') << *root << "\n";
        if (root->left)
            this->print_tree(root->left, os, lvl + 1);
    }

    /**
     * @brief Rotate left arround a node
     *
     * @param root node to rotate arround
     * @return Node* a pointer to the replacement node
     */
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

    /**
     * @brief Rotate right arround a node
     *
     * @param root node to rotate arround
     * @return Node* a pointer to the replacement node
     */
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

    /**
     * @brief Prevents memory leaks by dellocating
     *
     * @param root current subtree being cleared
     * @return Node* nullptr
     */
    Node* clear(Node*& root) {
        if (root) {
            root->left = this->clear(root->left);
            root->right = this->clear(root->right);
            root->parent = nullptr;
            delete root;
        }

        return root = nullptr;
    }

    /**
     * @brief Copy a subtree into this tree's subtree
     *
     * @param root subtree to copy from
     * @return Node* new subtree
     */
    Node* copy(const Node* const& root) {
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

    /**
     * @brief Finds the minimum node of a subtree
     *
     * @param node subtree's root
     * @return Node* a pointer to the node with the minimum value
     */
    Node* find_min(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->left)
            temp = temp->left;
        return temp;
    }

    /**
     * @brief Finds the maximum node of a subtree
     *
     * @param node subtree's root
     * @return Node* a poitner to the node with the maximum value
     */
    Node* find_max(Node* const& node) const {
        Node* temp = node;
        while (temp && temp->right)
            temp = temp->right;
        return temp;
    }

public:
    /**
     * @brief Construct a new Red Black Tree object
     */
    RedBlackTree() : _root{nullptr} {};

    /**
     * @brief Construct a new Red Black Tree object
     *
     * @param rhs 🟥⬛🌲 to copy from
     */
    RedBlackTree(const RedBlackTree& rhs) : _root{this->copy(rhs._root)} {};

    /**
     * @brief Destroy the Red Black Tree object
     */
    ~RedBlackTree() { this->make_empty(); }

    /**
     * @brief Copy assignment operator
     *
     * @param rbt 🟥⬛🌲 to copy from
     * @return RedBlackTree& *this
     */
    RedBlackTree& operator=(const RedBlackTree& rbt) {
        if (&rbt != this) {
            this->clear(this->_root);
            this->_root = this->copy(rbt._root);
        }
        return *this;
    }

    /**
     * @brief insert a value into the tree
     *
     * @param value value to insert
     */
    void insert(const Comparable& value) {
        this->insert(this->_root, value);
        this->_root->color = Color::BLACK;
        return;
    }

    /**
     * @brief Removes a value from the tree
     *
     * @param value value to remove
     */
    void remove(const Comparable& value) {
        if (!this->_root)
            return;
        this->remove(this->_root, value);
    }

    /**
     * @brief Determines if a value is in the tree
     *
     * @param value value to search for
     * @return true if the value is in the tree
     * @return false otherwise
     */
    bool contains(const Comparable& value) { return this->contains(this->_root, value); }

    /**
     * @brief Finds the minimum value of the tree
     *
     * @return const Comparable& smallest value in the tree
     */
    const Comparable& find_min() const {
        if (!this->_root)
            throw invalid_argument("Empty 🟥⬛🌲");
        return this->find_min(this->_root)->value;
    }

    /**
     * @brief Finds the maximum value of the tree
     *
     * @return const Comparable& largest value in the tree
     */
    const Comparable& find_max() const {
        if (!this->_root)
            throw invalid_argument("Empty 🟥⬛🌲");
        return this->find_max(this->_root)->value;
    }

    /**
     * @brief Determines the color of a specified node
     *
     * @param node a pointer to the node
     * @return int Color of the node
     */
    int color(const Node* node) const { return node ? node->color : Color::BLACK; }

    /**
     * @brief Get the root of the tree
     *
     * @return const Node* this->_root
     */
    const Node* get_root() const { return this->_root; }

    // ----------------------- Optional ----------------------- //
    /**
     * @brief Construct a new Red Black Tree object
     *
     * @param rhs 🟥⬛🌲 to move from
     */
    RedBlackTree(RedBlackTree&& rhs) : RedBlackTree() { swap(this->_root, rhs._root); }

    /**
     * @brief Move assignment operator
     *
     * @param rhs 🟥⬛🌲 to move from
     * @return RedBlackTree& *this
     */
    RedBlackTree& operator=(RedBlackTree&& rhs) {
        if (this != &rhs) {
            this->make_empty();
            swap(this->_root, rhs._root);
        }

        return *this;
    }

    /**
     * @brief Determine if this tree is empty
     *
     * @return true if the tree is empty
     * @return false otherwise
     */
    bool is_empty() const { return !this->_root; }

    /**
     * @brief Move insert a value into the tree
     *
     * @param value value to insert
     */
    void insert(Comparable&& value) {
        Comparable v{};
        swap(v, value);
        this->insert(v);
    }

    /**
     * @brief Prevents memory errors be deallocating the entire tree
     */
    void make_empty() { this->_root = this->clear(this->_root); }

    /**
     * @brief prints this tree to an ostream
     *
     * @param os ostream to print to
     */
    void print_tree(ostream& os = cout) const {
        if (this->_root)
            this->print_tree(this->_root, os, 0);
        else
            os << "<empty>\n";
    }
};