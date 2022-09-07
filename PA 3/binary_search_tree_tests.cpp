#include <iostream>
#include "binary_search_tree.h"

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
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	END_TEST;
}

bool test_insert() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.insert(7);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(0));
		assert(bst.contains(1));
		assert(bst.contains(2));
		assert(bst.contains(3));
		assert(bst.contains(4));
		assert(bst.contains(5));
		assert(bst.contains(6));
		assert(bst.contains(7));
		assert(bst.contains(8));
		assert(bst.contains(9));
		assert(bst.contains(10));
		assert(bst.contains(11));
		assert(bst.contains(12));
		assert(bst.contains(13));
		assert(bst.contains(14));
		assert(!bst.contains(15));
	}

	END_TEST;
}

bool test_remove_leaf() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(12);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(13);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(10);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(8);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(9);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(11);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(6);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(4);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(5);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(2);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(0);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(1);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
		assert(root != nullptr);
		assert(root->_value == 7);
		assert(root->_left != nullptr);
		assert(root->_left->_value == 3);
		assert(root->_left->_left == nullptr);
		assert(root->_left->_right == nullptr);
		assert(root->_right == nullptr);
	}

	bst.remove(3);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
		assert(root != nullptr);
		assert(root->_value == 7);
		assert(root->_left == nullptr);
		assert(root->_right == nullptr);
	}

	bst.remove(7);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
		assert(root == nullptr);
	}

	END_TEST;
}

bool test_remove_middle() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(13);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	std::cout << "\n\n";

	bst.remove(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(8);
	bst.remove(9);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

bool test_remove_root() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.remove(7);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
		assert(root != nullptr);
		assert(root->_value == 8);
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

bool test_remove_empty() {
	BinarySearchTree<int> bst;

	assert(bst.root() == nullptr);

	bst.remove(0);
	assert(bst.root() == nullptr);

	END_TEST;
}

bool test_remove_invalid() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(8);
	bst.insert(4);
	bst.insert(12);
	bst.insert(2);
	bst.insert(6);
	bst.insert(10);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}

	bst.remove(0);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}

	END_TEST;
}

bool test_find_min() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(8);
	bst.insert(4);
	bst.insert(12);
	bst.insert(2);
	bst.insert(6);
	bst.insert(10);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}
	assert(bst.find_min() == 2);

	END_TEST;
}

bool test_find_min_empty() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);
	expect_throw(bst.find_min(), invalid_argument);

	END_TEST;
}

bool test_find_max() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(8);
	bst.insert(4);
	bst.insert(12);
	bst.insert(2);
	bst.insert(6);
	bst.insert(10);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}
	assert(bst.find_max() == 14);

	END_TEST;
}

bool test_find_max_empty() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);
	expect_throw(bst.find_max(), invalid_argument);

	END_TEST;
}

bool test_print_empty() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.print_tree();

	END_TEST;
}

bool test_print() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(7);
	bst.insert(3);
	bst.insert(11);
	bst.insert(1);
	bst.insert(5);
	bst.insert(9);
	bst.insert(13);
	bst.insert(0);
	bst.insert(2);
	bst.insert(4);
	bst.insert(6);
	bst.insert(8);
	bst.insert(10);
	bst.insert(12);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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

	bst.print_tree();
	END_TEST;
}

bool test_copy() {
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(8);
	bst.insert(4);
	bst.insert(12);
	bst.insert(2);
	bst.insert(6);
	bst.insert(10);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}

	BinarySearchTree<int> a(bst);
	{
		const BinarySearchTree<int>::Node<int>* root = a.root(), * rooot = bst.root();
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
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(8);
	bst.insert(4);
	bst.insert(12);
	bst.insert(2);
	bst.insert(6);
	bst.insert(10);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}

	BinarySearchTree<int> a;
	assert(a.root() == nullptr);

	a.insert(6);
	a.insert(2);
	a.insert(10);
	a.insert(0);
	a.insert(4);
	a.insert(8);
	a.insert(12);
	{
		const BinarySearchTree<int>::Node<int>* root = a.root();
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
		const BinarySearchTree<int>::Node<int>* root = a.root(), * rooot = bst.root();
		assert(root != rooot);
		assert(root->_value != rooot->_value);
	}

	a = bst;
	{
		const BinarySearchTree<int>::Node<int>* root = a.root();
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
	BinarySearchTree<int> bst;
	assert(bst.root() == nullptr);

	bst.insert(8);
	bst.insert(4);
	bst.insert(12);
	bst.insert(2);
	bst.insert(6);
	bst.insert(10);
	bst.insert(14);
	{
		const BinarySearchTree<int>::Node<int>* root = bst.root();
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
		assert(bst.contains(8));
		assert(bst.contains(4));
		assert(bst.contains(12));
		assert(bst.contains(2));
		assert(bst.contains(6));
		assert(bst.contains(10));
		assert(bst.contains(14));
	}

	bst.make_empty();
	assert(bst.root() == nullptr);

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
	test(remove_root);
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
