#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>

using std::ostream, std::cout;

template <typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();

    BinarySearchTree(const BinarySearchTree& rhs);
    ~BinarySearchTree();
    BinarySearchTree& operator=(const BinarySearchTree& rhs);

    bool contains(const Comparable& val);
    void insert(const Comparable& val);
    void remove(const Comparable& val);

    const Comparable& find_min() const;
    const Comparable& find_max() const;

    void print_tree(ostream&=cout) const;

    // Optional
    // BinarySearchTree(BinarySearchTree&& rhs);
    // BinarySearchTree& operator=(BinarySearchTree&&);
    // bool is_empty() const;
    // void insert(Comparable&&);
    // void make_empty();
};
