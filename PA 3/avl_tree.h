#pragma once

template <typename Comparable>
class AVLTree {
public:
    AVLTree();
    AVLTree(const AVLTree& rhs);
    ~AVLTree();
    AVLTree& operator=(const AVLTree& rhs);

    bool contains(const Comparable& val);
    void insert(const Comparable& val);
    void remove(const Comparable& val);
    const Comparable& find_min() const;
    const Comparable& find_max() const;
    void print_tree(ostream&=cout) const;

    // OPTIONAL
    // AVLTree(AVLTree&&);
    // AVLTree& operator=(AVLTree&&);
    // bool is_empty() const;
    // void insert(Comparable&&);
    // void make_empty();
};
