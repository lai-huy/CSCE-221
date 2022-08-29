#pragma once

#include <iostream>

using std::ostream, std::cout;

template <typename Comparable>
class AVLTree {
public:
    AVLTree() {

    }

    AVLTree(const AVLTree& rhs) {

    }
    
    ~AVLTree() {

    }

    AVLTree& operator=(const AVLTree& rhs) {
        cout << &rhs << "\n";
        return *this;
    }

    bool contains(const Comparable& val) {
        cout << "avl.contains(" << std::to_string(val) << ");\n";
        return false;
    }

    void insert(const Comparable& val) {
        cout << "avl.insert(" << std::to_string(val) << ");\n";
    }

    void remove(const Comparable& val) {
        cout << "avl.remove(" << std::to_string(val) << ");\n";
    }

    const Comparable& find_min() const {
        cout << "avl.find_min();\n";
        return Comparable();
    }

    const Comparable& find_max() const {
        cout << "avl.find_max();\n";
        return Comparable();
    }

    void print_tree(ostream& os = cout) const {
        cout << "avl.print_tree();\n";
    }

    // OPTIONAL
    // AVLTree(AVLTree&&);
    // AVLTree& operator=(AVLTree&&);
    // bool is_empty() const;
    // void insert(Comparable&&);
    // void make_empty();
};
