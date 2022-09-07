#include <iostream>
#include "red_black_tree.h"

using std::cout, std::endl;

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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
    }

    rbt.insert(7);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
    }

    rbt.remove(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right == nullptr);
    }

    rbt.remove(12);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
    }

    rbt.remove(13);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right == nullptr);
    }

    rbt.remove(10);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right == nullptr);
    }

    rbt.remove(8);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right == nullptr);
    }

    rbt.remove(9);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left == nullptr);
        assert(root->_right->_right == nullptr);
    }

    rbt.remove(11);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right == nullptr);
    }

    rbt.remove(6);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right == nullptr);
    }

    rbt.remove(4);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
    }

    rbt.remove(5);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right == nullptr);
    }

    rbt.remove(2);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_right == nullptr);
    }

    rbt.remove(0);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_right == nullptr);
    }

    rbt.remove(1);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left == nullptr);
        assert(root->_left->_right == nullptr);
        assert(root->_right == nullptr);
    }

    rbt.remove(3);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left == nullptr);
        assert(root->_right == nullptr);
    }

    rbt.remove(7);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root == nullptr);
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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
    }

    rbt.remove(13);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right == nullptr);
    }

    rbt.remove(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 12);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr)
    }

    rbt.remove(8);
    rbt.remove(9);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
    }
    END_TEST;
}

bool test_remove_get_root() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    rbt.remove(8);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 10);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(!rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    END_TEST;
}

bool test_remove_empty() {
    RedBlackTree<int> rbt;

    assert(rbt.get_root() == nullptr);

    rbt.remove(0);
    assert(rbt.get_root() == nullptr);

    END_TEST;
}

bool test_remove_invalid() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    rbt.remove(0);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    END_TEST;
}

bool test_find_min() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }
    assert(rbt.find_min() == 2);

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

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
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

bool test_print_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.print_tree();

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
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 7);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 3);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 1);
        assert(root->_left->_left->_left != nullptr);
        assert(root->_left->_left->_left->_value == 0);
        assert(root->_left->_left->_left->_left == nullptr);
        assert(root->_left->_left->_left->_right == nullptr);
        assert(root->_left->_left->_right != nullptr);
        assert(root->_left->_left->_right->_value == 2);
        assert(root->_left->_left->_right->_left == nullptr);
        assert(root->_left->_left->_right->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 5);
        assert(root->_left->_right->_left != nullptr);
        assert(root->_left->_right->_left->_value == 4);
        assert(root->_left->_right->_left->_left == nullptr);
        assert(root->_left->_right->_left->_right == nullptr);
        assert(root->_left->_right->_right != nullptr);
        assert(root->_left->_right->_right->_value == 6);
        assert(root->_left->_right->_right->_left == nullptr);
        assert(root->_left->_right->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 11);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 9);
        assert(root->_right->_left->_left != nullptr);
        assert(root->_right->_left->_left->_value == 8);
        assert(root->_right->_left->_left->_left == nullptr);
        assert(root->_right->_left->_left->_right == nullptr);
        assert(root->_right->_left->_right != nullptr);
        assert(root->_right->_left->_right->_value == 10);
        assert(root->_right->_left->_right->_left == nullptr);
        assert(root->_right->_left->_right->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 13);
        assert(root->_right->_right->_left != nullptr);
        assert(root->_right->_right->_left->_value == 12);
        assert(root->_right->_right->_left->_left == nullptr);
        assert(root->_right->_right->_left->_right == nullptr);
        assert(root->_right->_right->_right != nullptr);
        assert(root->_right->_right->_right->_value == 14);
        assert(root->_right->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right->_right == nullptr);
    }

    rbt.print_tree();
    END_TEST;
}

bool test_copy() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    RedBlackTree<int> a(rbt);
    {
        const RedBlackTree<int>::Node<int>* root = a.get_root(), * rooot = rbt.get_root();
        assert(root != nullptr);
        assert(root != rooot);
        assert(root->_value == 8);
        assert(root->_value == rooot->_value);
        assert(root->_left != nullptr);
        assert(root->_left != rooot->_left);
        assert(root->_left->_value == 4);
        assert(root->_left->_value == rooot->_left->_value)
            assert(root->_left->_left != nullptr);
        assert(root->_left->_left != rooot->_left->_left);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_value == rooot->_left->_left->_value);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(a.contains(8));
        assert(a.contains(4));
        assert(a.contains(12));
        assert(a.contains(2));
        assert(a.contains(6));
        assert(a.contains(10));
        assert(a.contains(14));
    }

    END_TEST;
}

bool test_copy_oper() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    RedBlackTree<int> a;
    assert(a.get_root() == nullptr);

    a.insert(6);
    a.insert(2);
    a.insert(10);
    a.insert(0);
    a.insert(4);
    a.insert(8);
    a.insert(12);
    {
        const RedBlackTree<int>::Node<int>* root = a.get_root();
        assert(root != nullptr);
        assert(root->_value == 6);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 2);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 0);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 4);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 10);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 8);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 12);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(a.contains(6));
        assert(a.contains(2));
        assert(a.contains(10));
        assert(a.contains(0));
        assert(a.contains(4));
        assert(a.contains(8));
        assert(a.contains(12));
    }

    {
        const RedBlackTree<int>::Node<int>* root = a.get_root(), * rooot = rbt.get_root();
        assert(root != rooot);
        assert(root->_value != rooot->_value);
    }

    a = rbt;
    {
        const RedBlackTree<int>::Node<int>* root = a.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(a.contains(8));
        assert(a.contains(4));
        assert(a.contains(12));
        assert(a.contains(2));
        assert(a.contains(6));
        assert(a.contains(10));
        assert(a.contains(14));
    }

    END_TEST;
}

bool test_make_empty() {
    RedBlackTree<int> rbt;
    assert(rbt.get_root() == nullptr);

    rbt.insert(8);
    rbt.insert(4);
    rbt.insert(12);
    rbt.insert(2);
    rbt.insert(6);
    rbt.insert(10);
    rbt.insert(14);
    {
        const RedBlackTree<int>::Node<int>* root = rbt.get_root();
        assert(root != nullptr);
        assert(root->_value == 8);
        assert(root->_left != nullptr);
        assert(root->_left->_value == 4);
        assert(root->_left->_left != nullptr);
        assert(root->_left->_left->_value == 2);
        assert(root->_left->_left->_left == nullptr);
        assert(root->_left->_left->_right == nullptr);
        assert(root->_left->_right != nullptr);
        assert(root->_left->_right->_value == 6);
        assert(root->_left->_right->_left == nullptr);
        assert(root->_left->_right->_right == nullptr);
        assert(root->_right != nullptr);
        assert(root->_right->_value == 12);
        assert(root->_right->_left != nullptr);
        assert(root->_right->_left->_value == 10);
        assert(root->_right->_left->_left == nullptr);
        assert(root->_right->_left->_right == nullptr);
        assert(root->_right->_right != nullptr);
        assert(root->_right->_right->_value == 14);
        assert(root->_right->_right->_left == nullptr);
        assert(root->_right->_right->_right == nullptr);
        assert(rbt.contains(8));
        assert(rbt.contains(4));
        assert(rbt.contains(12));
        assert(rbt.contains(2));
        assert(rbt.contains(6));
        assert(rbt.contains(10));
        assert(rbt.contains(14));
    }

    rbt.make_empty();
    assert(rbt.get_root() == nullptr);

    END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(create);
    test(insert);
    test(insert_duplicate);
    test(insert_dup_many);
    test(contains);
    test(remove_leaf);
    test(remove_middle);
    test(remove_empty);
    test(remove_invalid);
    test(find_min);
    test(find_min_empty);
    test(find_max);
    test(find_max_empty);
    test(print_empty);
    test(print);
    test(make_empty);

    test(copy);
    test(copy_oper);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
