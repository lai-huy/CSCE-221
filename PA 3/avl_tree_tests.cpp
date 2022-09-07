#include <iostream>
#include <stdexcept>
#include "avl_tree.h"

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
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	END_TEST;
}

bool test_insert() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.insert(7);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

bool test_insert_right() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(1);
	avl.insert(2);
	avl.insert(3);
	avl.insert(4);
	avl.insert(5);
	avl.insert(6);
	avl.insert(7);
	avl.insert(8);
	avl.insert(9);
	avl.insert(10);

	{
		const AVLTree<int>::Node<int>* root = avl.root();
		assert(root != nullptr);
		assert(root->_value == 4);
		assert(root->_left != nullptr);
		assert(root->_left->_value == 2);
		assert(root->_left->_left != nullptr);
		assert(root->_left->_left->_value == 1);
		assert(root->_left->_left->_left == nullptr);
		assert(root->_left->_left->_right == nullptr);
		assert(root->_left->_right != nullptr);
		assert(root->_left->_right->_value == 3);
		assert(root->_left->_right->_left == nullptr);
		assert(root->_left->_right->_right == nullptr);
		assert(root->_right != nullptr);
		assert(root->_right->_value == 8);
		assert(root->_right->_left != nullptr);
		assert(root->_right->_left->_value == 6);
		assert(root->_right->_left->_left != nullptr);
		assert(root->_right->_left->_left->_value == 5);
		assert(root->_right->_left->_left->_left == nullptr);
		assert(root->_right->_left->_left->_right == nullptr);
		assert(root->_right->_left->_right != nullptr);
		assert(root->_right->_left->_right->_value == 7);
		assert(root->_right->_left->_right->_left == nullptr);
		assert(root->_right->_left->_right->_right == nullptr);
		assert(root->_right->_right != nullptr);
		assert(root->_right->_right->_value == 9);
		assert(root->_right->_right->_left == nullptr);
		assert(root->_right->_right->_right != nullptr);
		assert(root->_right->_right->_right->_value == 10);
		assert(root->_right->_right->_right->_left == nullptr);
		assert(root->_right->_right->_right->_right == nullptr);
	}

	END_TEST;
}

bool test_insert_left() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(10);
	avl.insert(9);
	avl.insert(8);
	avl.insert(7);
	avl.insert(6);
	avl.insert(5);
	avl.insert(4);
	avl.insert(3);
	avl.insert(2);
	avl.insert(1);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
		assert(root != nullptr);
		assert(root->_value == 7);
		assert(root->_left != nullptr);
		assert(root->_left->_value == 3);
		assert(root->_left->_left != nullptr);
		assert(root->_left->_left->_value == 2);
		assert(root->_left->_left->_left != nullptr);
		assert(root->_left->_left->_left->_value == 1);
		assert(root->_left->_left->_left->_left == nullptr);
		assert(root->_left->_left->_left->_right == nullptr);
		assert(root->_left->_left->_right == nullptr);
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
		assert(root->_right->_value == 9);
		assert(root->_right->_left != nullptr);
		assert(root->_right->_left->_value == 8);
		assert(root->_right->_left->_left == nullptr);
		assert(root->_right->_left->_right == nullptr);
		assert(root->_right->_right != nullptr);
		assert(root->_right->_right->_value == 10);
		assert(root->_right->_right->_left == nullptr);
		assert(root->_right->_right->_right == nullptr);
	}

	END_TEST;
}

bool test_insert_lr() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(2);
	avl.insert(0);
	avl.insert(1);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
		assert(root != nullptr);
		assert(root->_value == 1);
		assert(root->_left != nullptr);
		assert(root->_left->_value == 0);
		assert(root->_left->_left == nullptr);
		assert(root->_left->_right == nullptr);
		assert(root->_right != nullptr);
		assert(root->_right->_value == 2);
		assert(root->_right->_left == nullptr);
		assert(root->_right->_right == nullptr);
	}

	END_TEST;
}

bool test_insert_rl() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(0);
	avl.insert(2);
	avl.insert(1);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
		assert(root != nullptr);
		assert(root->_value == 1);
		assert(root->_left != nullptr);
		assert(root->_left->_value == 0);
		assert(root->_left->_left == nullptr);
		assert(root->_left->_right == nullptr);
		assert(root->_right != nullptr);
		assert(root->_right->_value == 2);
		assert(root->_right->_left == nullptr);
		assert(root->_right->_right == nullptr);
	}

	END_TEST;
}

bool test_remove_empty() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.remove(0);
	assert(avl.root() == nullptr);

	END_TEST;
}

bool test_remove_leaf() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.remove(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.remove(12);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	END_TEST;
}

bool test_remove_middle() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.remove(13);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.remove(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(root->_right->_right->_right == nullptr);
	}

	avl.remove(8);
	avl.remove(9);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(root->_right->_right->_value == 12);
		assert(root->_right->_right->_left == nullptr);
		assert(root->_right->_right->_right == nullptr);
	}

	END_TEST;
}

bool test_remove_root() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.remove(7);

	END_TEST;
}

bool test_contains() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(avl.contains(0));
		assert(avl.contains(1));
		assert(avl.contains(2));
		assert(avl.contains(3));
		assert(avl.contains(4));
		assert(avl.contains(5));
		assert(avl.contains(6));
		assert(avl.contains(7));
		assert(avl.contains(8));
		assert(avl.contains(9));
		assert(avl.contains(10));
		assert(avl.contains(11));
		assert(avl.contains(12));
		assert(avl.contains(13));
		assert(avl.contains(14));
		assert(!avl.contains(15));
	}

	END_TEST;
}

bool test_find_min() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(8);
	avl.insert(4);
	avl.insert(12);
	avl.insert(2);
	avl.insert(6);
	avl.insert(10);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(avl.contains(8));
		assert(avl.contains(4));
		assert(avl.contains(12));
		assert(avl.contains(2));
		assert(avl.contains(6));
		assert(avl.contains(10));
		assert(avl.contains(14));
	}
	assert(avl.find_min() == 2);

	END_TEST;
}

bool test_find_min_empty() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);
	expect_throw(avl.find_min(), invalid_argument);

	END_TEST;
}

bool test_find_max() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(8);
	avl.insert(4);
	avl.insert(12);
	avl.insert(2);
	avl.insert(6);
	avl.insert(10);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(avl.contains(8));
		assert(avl.contains(4));
		assert(avl.contains(12));
		assert(avl.contains(2));
		assert(avl.contains(6));
		assert(avl.contains(10));
		assert(avl.contains(14));
	}
	assert(avl.find_max() == 14);

	END_TEST;
}

bool test_find_max_empty() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);
	expect_throw(avl.find_max(), invalid_argument);

	END_TEST;
}

bool test_print_empty() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.print_tree();

	END_TEST;
}

bool test_print() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(7);
	avl.insert(3);
	avl.insert(11);
	avl.insert(1);
	avl.insert(5);
	avl.insert(9);
	avl.insert(13);
	avl.insert(0);
	avl.insert(2);
	avl.insert(4);
	avl.insert(6);
	avl.insert(8);
	avl.insert(10);
	avl.insert(12);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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

	avl.print_tree();
	END_TEST;
}

bool test_copy() {
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(8);
	avl.insert(4);
	avl.insert(12);
	avl.insert(2);
	avl.insert(6);
	avl.insert(10);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(avl.contains(8));
		assert(avl.contains(4));
		assert(avl.contains(12));
		assert(avl.contains(2));
		assert(avl.contains(6));
		assert(avl.contains(10));
		assert(avl.contains(14));
	}

	AVLTree<int> a(avl);
	{
		const AVLTree<int>::Node<int>* root = a.root(), * rooot = avl.root();
		assert(root != nullptr);
		assert(root != rooot);
		assert(root->_value == 8);
		assert(root->_value == rooot->_value);
		assert(root->_left != nullptr);
		assert(root->_left != rooot->_left);
		assert(root->_left->_value == 4);
		assert(root->_left->_value == rooot->_left->_value);
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
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(8);
	avl.insert(4);
	avl.insert(12);
	avl.insert(2);
	avl.insert(6);
	avl.insert(10);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(avl.contains(8));
		assert(avl.contains(4));
		assert(avl.contains(12));
		assert(avl.contains(2));
		assert(avl.contains(6));
		assert(avl.contains(10));
		assert(avl.contains(14));
	}

	AVLTree<int> a;
	assert(a.root() == nullptr);

	a.insert(6);
	a.insert(2);
	a.insert(10);
	a.insert(0);
	a.insert(4);
	a.insert(8);
	a.insert(12);
	{
		const AVLTree<int>::Node<int>* root = a.root();
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
		const AVLTree<int>::Node<int>* root = a.root(), * rooot = avl.root();
		assert(root != rooot);
		assert(root->_value != rooot->_value);
	}

	a = avl;
	{
		const AVLTree<int>::Node<int>* root = a.root();
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
	AVLTree<int> avl;
	assert(avl.root() == nullptr);

	avl.insert(8);
	avl.insert(4);
	avl.insert(12);
	avl.insert(2);
	avl.insert(6);
	avl.insert(10);
	avl.insert(14);
	{
		const AVLTree<int>::Node<int>* root = avl.root();
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
		assert(avl.contains(8));
		assert(avl.contains(4));
		assert(avl.contains(12));
		assert(avl.contains(2));
		assert(avl.contains(6));
		assert(avl.contains(10));
		assert(avl.contains(14));
	}

	avl.make_empty();
	assert(avl.root() == nullptr);

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
	test(insert_lr);
	test(insert_rl);
	test(remove_empty);
	test(remove_leaf);
	test(remove_middle);
	test(remove_root);
	test(contains);
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
