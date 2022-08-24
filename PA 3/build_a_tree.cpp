#include <iostream>
#include "binary_search_tree.h"
#include "avl_tree.h"

using std::cout, std::endl, std::cin;

int main() {
    // build a tree of ints
    BinarySearchTree<int> bst;
    AVLTree<int> avl;
    bool isAVL = false;
    char choice;
    cout << "(B)ST or (A)VL? ";
    cin >> choice;
    if (tolower(choice) == 'a') {
        isAVL = true;
    } else if (tolower(choice) != 'b') {
        cout << choice << " is invalid, defaulting to BST." << endl;
    }
    cout << "enter whitespace-separated values, end with 0 or any non-integer value." << endl;
    cout << "positive integer value := insert(|value|)" << endl;
    cout << "negative integer value := remove(|value|)" << endl;
    cout << "-----" << endl;
    if (isAVL) {
        avl.print_tree();
    } else {
        bst.print_tree();
    }
    cout << "-----" << endl;
    while(1) {
        int value = 0;
        cin >> value;
        if (cin.fail() || value == 0) { break; }
        cout << "-----" << endl;
        if (isAVL) {
            if (value > 0) {
                avl.insert(value);
            } else {
                avl.remove(-value);
            }
            avl.print_tree();
        } else {
            if (value > 0) {
                bst.insert(value);
            } else {
                bst.remove(-value);
            }
            bst.print_tree();
        }
        cout << "-----" << endl;
    }
}
