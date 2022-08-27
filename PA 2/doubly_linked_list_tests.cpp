#include <iostream>
#include "doubly_linked_list.h"

using std::cout;

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

#define to_be ==
#define not_to_be !=
#define is to_be
#define is_not not_to_be

namespace {
	bool test_passed = true;
}

bool test_create() {
	DoublyLinkedList<int> list;
	assert(list.size() is 0);
	assert(list.head() is nullptr);

	END_TEST;
}

bool test_insert_head() {
	DoublyLinkedList<int> list;
	assert(list.size() is 0);
	assert(list.head() is nullptr);

	list.insert(0, 3);
	list.insert(0, 2);
	list.insert(0, 1);
	list.insert(0, 0);
	assert(list.size() is 4);
	assert(list.head() is_not nullptr);

	END_TEST;
}

bool test_insert_tail() {
	DoublyLinkedList<int> list;
	assert(list.size() is 0);
	assert(list.head() is nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	assert(list.size() is 4);
	assert(list.head() is_not nullptr);

	END_TEST;
}

bool test_insert_middle() {
	DoublyLinkedList<int> list;
	assert(list.size() is 0);
	assert(list.head() is nullptr);

	list.insert(0, 0);
	list.insert(1, 3);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() is 4);
	assert(list.head() is_not nullptr);

	END_TEST;
}

bool test_insert_invalid() {
	DoublyLinkedList<int> list;
	assert(list.size() is 0);
	assert(list.head() is nullptr);

	expect_throw(list.insert(1, 1), out_of_range);

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(insert_head);
	test(insert_tail);
	test(insert_middle);
	test(insert_invalid);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}