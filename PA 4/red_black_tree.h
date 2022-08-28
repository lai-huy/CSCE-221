#pragma once

template <typename Comparable>
class RedBlackTree {
public:
    enum Color { RED, BLACK };

    // Constructor & Rule of Three
    RedBlackTree();
    RedBlackTree(const RedBlackTree& rhs);
    ~RedBlackTree();
    RedBlackTree& operator=(const RedBlackTree&);

    // modifiers
    void insert(const Comparable& rhs);
    void remove(const Comparable& rhs);

    // look up
    bool contains(const Comparable&) const;
    const Comparable& find_min() const;
    const Comparable& find_max() const;

    // For Testing
    int color(const Node* node) const;
    const Node* get_root() const;

    // OPTIONAL
    // RedBlackTree(RedBlackTree&& rhs);
    // RedBlackTree& operator=(RedBlackTree&& rhs);
    // bool is_empty() const;
    // void insert(Comparable&& val);
    // void make_empty();
    // void print_tree(std::ostream&=std::cout) const;
};
