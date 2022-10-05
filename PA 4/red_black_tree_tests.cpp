#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
// #include "rbt.h"
#include "red_black_tree.h"

using std::cout, std::endl;
using std::invalid_argument;

#define black   "\033[30m"
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define reset   "\033[m"

#define END_TEST bool this_test_passed = test_passed;\
test_passed = true;\
return this_test_passed;

#define expect(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << "\n";\
    test_passed = false;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
}

#define assert(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << "\n";\
    test_passed = false;\
    END_TEST;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
  END_TEST;\
}

#define expect_throw(X,E) {\
  bool threw_expected_exception = false;\
  try { X; }\
  catch(const E& err) {\
    threw_expected_exception = true;\
  } catch(...) {\
    std::cout << blue << "  [help] " << #X << " threw an incorrect exception." << reset << "\n";\
  }\
  if (!threw_expected_exception) {\
    std::cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<"\n";\
    test_passed = false;\
  }\
}

#define expect_no_throw(X) {\
  try { X; }\
  catch(...) {\
    std::cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << reset << "\n";\
    test_passed = false;\
  }\
}

#define test(x) if (test_##x()) { std::cout << green << "[PASS] "; pass_cnt++; }\
else { std::cout << red << "[FAIL] "; fail_cnt++; }\
std::cout << #x << reset << "\n";
#define skip(x) std::cout << yellow << "[SKIP] " << #x << reset << "\n"; skip_cnt++;

namespace {
    bool test_passed = true;
}

bool test_create() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    END_TEST;
}

bool test_insert() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_insert_duplicate() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.insert(7);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_insert_dup_many() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_insert_right() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(0);
    rbt.insert(1);
    rbt.insert(2);
    rbt.insert(3);
    rbt.insert(4);
    rbt.insert(5);
    rbt.insert(6);
    rbt.insert(7);
    rbt.insert(8);
    rbt.insert(9);
    rbt.insert(10);
    rbt.insert(11);
    rbt.insert(12);
    rbt.insert(13);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 3);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 1);
        assert(root->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 0);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left == nullptr);
        assert(root->left->left->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 2);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 7);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 5);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 4);
        assert(root->right->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 6);
        assert(root->right->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 9);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 8);
        assert(root->right->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 11);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left != nullptr);
        assert(root->right->right->right->left->value == 10);
        assert(root->right->right->right->left->left == nullptr);
        assert(root->right->right->right->left->right == nullptr);
        assert(root->right->right->right->right != nullptr);
        assert(root->right->right->right->right->value == 13);
        assert(root->right->right->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->right->right->left != nullptr);
        assert(root->right->right->right->right->left->value == 12);
        assert(root->right->right->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->right->left->left == nullptr);
        assert(root->right->right->right->right->left->right == nullptr);
        assert(root->right->right->right->right->right != nullptr);
        assert(root->right->right->right->right->right->value == 14);
        assert(root->right->right->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->right->right->left == nullptr);
        assert(root->right->right->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_insert_left() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(14);
    rbt.insert(13);
    rbt.insert(12);
    rbt.insert(11);
    rbt.insert(10);
    rbt.insert(9);
    rbt.insert(8);
    rbt.insert(7);
    rbt.insert(6);
    rbt.insert(5);
    rbt.insert(4);
    rbt.insert(3);
    rbt.insert(2);
    rbt.insert(1);
    rbt.insert(0);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 11);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 7);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 5);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 3);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left != nullptr);
        assert(root->left->left->left->left->value == 1);
        assert(root->left->left->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left->left->left != nullptr);
        assert(root->left->left->left->left->left->value == 0);
        assert(root->left->left->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left->left->left == nullptr);
        assert(root->left->left->left->left->left->right == nullptr);
        assert(root->left->left->left->left->right != nullptr);
        assert(root->left->left->left->left->right->value == 2);
        assert(root->left->left->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left->right->left == nullptr);
        assert(root->left->left->left->left->right->right == nullptr);
        assert(root->left->left->left->right != nullptr);
        assert(root->left->left->left->right->value == 4);
        assert(root->left->left->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left->right->left == nullptr);
        assert(root->left->left->left->right->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 6);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 9);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 8);
        assert(root->left->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 10);
        assert(root->left->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 13);
        assert(root->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 12);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 14);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_insert_rl() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(1);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 1);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 0);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left == nullptr);
        assert(root->left->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 2);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right == nullptr);
    }

    END_TEST;
}

bool test_insert_lr() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(2);
    rbt.insert(0);
    rbt.insert(1);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 1);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 0);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left == nullptr);
        assert(root->left->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 2);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right == nullptr);
    }

    END_TEST;
}

bool test_contains() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    {
        assert(rbt.contains(0));
        assert(rbt.contains(1));
        assert(rbt.contains(2));
        assert(rbt.contains(3));
        assert(rbt.contains(4));
        assert(rbt.contains(5));
        assert(rbt.contains(6));
        assert(rbt.contains(7));
        assert(rbt.contains(8));
        assert(rbt.contains(9));
        assert(rbt.contains(10));
        assert(rbt.contains(11));
        assert(rbt.contains(12));
        assert(rbt.contains(13));
        assert(rbt.contains(14));
        assert(!rbt.contains(15));
    }

    END_TEST;
}

bool test_remove_leaf() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.remove(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(12);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(10);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(8);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(6);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(4);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(2);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(0);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left == nullptr);
        assert(root->left->left->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(13);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left == nullptr);
        assert(root->left->left->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right == nullptr);
    }

    rbt.remove(9);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left == nullptr);
        assert(root->left->left->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left == nullptr);
        assert(root->left->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right == nullptr);
    }

    rbt.remove(5);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left == nullptr);
        assert(root->left->left->right == nullptr);
        assert(root->left->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right == nullptr);
    }

    rbt.remove(1);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left == nullptr);
        assert(root->left->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right == nullptr);
    }

    rbt.remove(11);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left == nullptr);
        assert(root->left->right == nullptr);
        assert(root->right == nullptr);
    }

    rbt.remove(3);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left == nullptr);
        assert(root->right == nullptr);
    }

    rbt.remove(7);
    {
        assert(rbt.get_root() == nullptr);
    }

    END_TEST;
}

bool test_remove_middle() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.remove(13);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 14);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right == nullptr);
    }

    rbt.remove(14);
    rbt.print_tree();
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 12);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr)
    }

    rbt.remove(8);
    rbt.remove(9);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 10);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 12);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left == nullptr);
        assert(root->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_remove_root() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.remove(7);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 8);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.remove(8);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 9);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 10);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left == nullptr);
        assert(root->right->left->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.remove(9);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 10);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_remove_root_l() {
    RedBlackTree<int> rbt;

    rbt.insert(1);
    rbt.insert(0);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 1);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 0);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left == nullptr);
        assert(root->left->right == nullptr);
        assert(root->right == nullptr);
    }

    rbt.remove(1);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 0);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left == nullptr);
        assert(root->right == nullptr);
    }

    END_TEST;
}

bool test_remove_root_r() {
    RedBlackTree<int> rbt;

    rbt.insert(0);
    rbt.insert(1);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 0);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 1);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left == nullptr);
        assert(root->right->right == nullptr);
    }

    rbt.remove(0);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 1);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left == nullptr);
        assert(root->right == nullptr);
    }

    END_TEST;
}

bool test_remove_empty() {
    RedBlackTree<int> rbt;

    assert(rbt.get_root() == nullptr);

    expect_no_throw(rbt.remove(0));
    assert(rbt.get_root() == nullptr);

    END_TEST;
}

bool test_remove_invalid() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    expect_no_throw(rbt.remove(100));
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_find_min() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }
    assert(rbt.find_min() == 0);

    END_TEST;
}

bool test_find_min_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);
    expect_throw(rbt.find_min(), invalid_argument);

    END_TEST;
}

bool test_find_max() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }
    assert(rbt.find_max() == 14);

    END_TEST;
}

bool test_find_max_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);
    expect_throw(rbt.find_max(), invalid_argument);

    END_TEST;
}

bool test_copy() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    RedBlackTree<int> a(rbt);
    {
        const RedBlackTree<int>::Node* root = a.get_root();
        assert(root != rbt.get_root());
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_copy_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    RedBlackTree<int> a(rbt);
    assert(a.get_root() == nullptr);

    END_TEST;
}

bool test_copy_oper() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    RedBlackTree<int> a;
    assert(a.get_root() == nullptr);

    a.insert(6);
    a.insert(2);
    a.insert(10);
    a.insert(0);
    a.insert(5);
    a.insert(8);
    a.insert(12);
    a.insert(-1);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(7);
    a.insert(9);
    a.insert(11);
    a.insert(13);
    {
        const RedBlackTree<int>::Node* root = a.get_root();
        assert(root != nullptr);
        assert(root->value == 6);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 2);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 0);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == -1);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 1);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 4);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 3);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 5);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 10);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 8);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 7);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 9);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 12);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 11);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 13);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    {
        const RedBlackTree<int>::Node* root = a.get_root(), * rooot = rbt.get_root();
        assert(root != rooot);
        assert(root->value != rooot->value);
    }

    a = rbt;
    {
        const RedBlackTree<int>::Node* root = a.get_root();
        assert(root != nullptr);
        assert(root != rbt.get_root());
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_copy_oper_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    RedBlackTree<int> a;
    assert(a.get_root() == nullptr);

    a.insert(6);
    a.insert(2);
    a.insert(10);
    a.insert(0);
    a.insert(5);
    a.insert(8);
    a.insert(12);
    a.insert(-1);
    a.insert(1);
    a.insert(3);
    a.insert(4);
    a.insert(7);
    a.insert(9);
    a.insert(11);
    a.insert(13);
    {
        const RedBlackTree<int>::Node* root = a.get_root();
        assert(root != nullptr);
        assert(root->value == 6);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 2);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 0);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == -1);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 1);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 4);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 3);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 5);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 10);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 8);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 7);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 9);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 12);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 11);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 13);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    a = rbt;
    assert(a.get_root() == nullptr);

    END_TEST;
}

bool test_self_assignment() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    const RedBlackTree<int>::Node* old_root = rbt.get_root();
    rbt = rbt;
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root == old_root);
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    END_TEST;
}

bool test_node() {
    RedBlackTree<int>::Node node = RedBlackTree<int>::Node(INT32_MAX, static_cast<RedBlackTree<int>::Color>(4));
    assert(node.sibling() == nullptr);
    assert(node.uncle() == nullptr);
    cout << node << "\n";

    END_TEST;
}

bool test_print() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(11);
    rbt.insert(1);
    rbt.insert(5);
    rbt.insert(9);
    rbt.insert(13);
    rbt.insert(0);
    rbt.insert(2);
    rbt.insert(4);
    rbt.insert(6);
    rbt.insert(8);
    rbt.insert(10);
    rbt.insert(12);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->value == 7);
        assert(root->color == RedBlackTree<int>::BLACK);
        assert(root->left != nullptr);
        assert(root->left->value == 3);
        assert(root->left->color == RedBlackTree<int>::RED);
        assert(root->left->left != nullptr);
        assert(root->left->left->value == 1);
        assert(root->left->left->color == RedBlackTree<int>::BLACK);
        assert(root->left->left->left != nullptr);
        assert(root->left->left->left->value == 0);
        assert(root->left->left->left->color == RedBlackTree<int>::RED);
        assert(root->left->left->left->left == nullptr);
        assert(root->left->left->left->right == nullptr);
        assert(root->left->left->right != nullptr);
        assert(root->left->left->right->value == 2);
        assert(root->left->left->right->color == RedBlackTree<int>::RED);
        assert(root->left->left->right->left == nullptr);
        assert(root->left->left->right->right == nullptr);
        assert(root->left->right != nullptr);
        assert(root->left->right->value == 5);
        assert(root->left->right->color == RedBlackTree<int>::BLACK);
        assert(root->left->right->left != nullptr);
        assert(root->left->right->left->value == 4);
        assert(root->left->right->left->color == RedBlackTree<int>::RED);
        assert(root->left->right->left->left == nullptr);
        assert(root->left->right->left->right == nullptr);
        assert(root->left->right->right != nullptr);
        assert(root->left->right->right->value == 6);
        assert(root->left->right->right->color == RedBlackTree<int>::RED);
        assert(root->left->right->right->left == nullptr);
        assert(root->left->right->right->right == nullptr);
        assert(root->right != nullptr);
        assert(root->right->value == 11);
        assert(root->right->color == RedBlackTree<int>::RED);
        assert(root->right->left != nullptr);
        assert(root->right->left->value == 9);
        assert(root->right->left->color == RedBlackTree<int>::BLACK);
        assert(root->right->left->left != nullptr);
        assert(root->right->left->left->value == 8);
        assert(root->right->left->left->color == RedBlackTree<int>::RED);
        assert(root->right->left->left->left == nullptr);
        assert(root->right->left->left->right == nullptr);
        assert(root->right->left->right != nullptr);
        assert(root->right->left->right->value == 10);
        assert(root->right->left->right->color == RedBlackTree<int>::RED);
        assert(root->right->left->right->left == nullptr);
        assert(root->right->left->right->right == nullptr);
        assert(root->right->right != nullptr);
        assert(root->right->right->value == 13);
        assert(root->right->right->color == RedBlackTree<int>::BLACK);
        assert(root->right->right->left != nullptr);
        assert(root->right->right->left->value == 12);
        assert(root->right->right->left->color == RedBlackTree<int>::RED);
        assert(root->right->right->left->left == nullptr);
        assert(root->right->right->left->right == nullptr);
        assert(root->right->right->right != nullptr);
        assert(root->right->right->right->value == 14);
        assert(root->right->right->right->color == RedBlackTree<int>::RED);
        assert(root->right->right->right->left == nullptr);
        assert(root->right->right->right->right == nullptr);
    }

    rbt.print_tree();

    END_TEST;
}

bool test_print_empty() {
    RedBlackTree<int> rbt;
    rbt.print_tree();

    END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(create);
    test(insert);
    test(insert_duplicate);
    test(insert_dup_many);
    test(insert_right);
    test(insert_left);
    test(insert_rl);
    test(insert_lr);
    test(contains);
    test(remove_leaf);
    test(remove_middle);
    test(remove_root);
    test(remove_root_l);
    test(remove_root_r);
    test(remove_empty);
    test(remove_invalid);
    test(find_min);
    test(find_min_empty);
    test(find_max);
    test(find_max_empty);
    test(copy);
    test(copy_empty);
    test(copy_oper);
    test(copy_oper_empty);
    test(self_assignment);
    test(node);
    test(print);
    test(print_empty);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
