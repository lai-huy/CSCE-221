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

namespace {
	bool test_passed = true;
}

bool test_create() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	END_TEST;
}

bool test_insert_head() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 3);
	list.insert(0, 2);
	list.insert(0, 1);
	list.insert(0, 0);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	END_TEST;
}

bool test_insert_tail() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	END_TEST;
}

bool test_insert_middle() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 3);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	END_TEST;
}

bool test_insert_invalid() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	expect_throw(list.insert(1, 1), out_of_range);

	END_TEST;
}

bool test_remove_head() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	list.remove(0);
	assert(list.size() == 3);
	assert(list.head() != nullptr);

	list.remove(0);
	assert(list.size() == 2);
	assert(list.head() != nullptr);

	list.remove(0);
	assert(list.size() == 1);
	assert(list.head() != nullptr);

	list.remove(0);
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	END_TEST;
}

bool test_remove_tail() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	list.remove(list.size() - 1);
	assert(list.size() == 3);
	assert(list.head() != nullptr);

	list.remove(list.size() - 1);
	assert(list.size() == 2);
	assert(list.head() != nullptr);

	list.remove(list.size() - 1);
	assert(list.size() == 1);
	assert(list.head() != nullptr);

	list.remove(list.size() - 1);
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	END_TEST;
}

bool test_remove_middle() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	list.remove(1);
	assert(list.size() == 3);
	assert(list.head() != nullptr);

	list.remove(1);
	assert(list.size() == 2);
	assert(list.head() != nullptr);

	END_TEST;
}

bool test_remove_invalid() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	assert(list.size() == 4);
	assert(list.head() != nullptr);

	expect_throw(list.remove(6), out_of_range);

	END_TEST;
}

bool test_oper_sq() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	list.insert(4, 4);
	list.insert(5, 5);
	assert(list.size() == 6);
	assert(list.head() != nullptr);

	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);
	assert(list[3] == 3);
	assert(list[4] == 4);
	assert(list[5] == 5);
	expect_throw(list[6], out_of_range);

	END_TEST;
}

bool test_copy() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	list.insert(4, 4);
	list.insert(5, 5);
	assert(list.size() == 6);
	assert(list.head() != nullptr);

	DoublyLinkedList<int> a(list);
	assert(a.size() == list.size());
	assert(a.head() != list.head());
	assert(a.head()->_value == list.head()->_value);

	END_TEST;
}

bool test_copy_empty() {
	DoublyLinkedList<int> list;
	assert(list.head() == nullptr);
	assert(list.tail() == nullptr);
	assert(list.size() == 0);

	DoublyLinkedList<int> a(list);

	END_TEST;
}

bool test_copy_oper() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	list.insert(4, 4);
	list.insert(5, 5);
	assert(list.size() == 6);
	assert(list.head() != nullptr);

	DoublyLinkedList<int> a;
	a.insert(0, 6);
	a.insert(0, 7);
	a.insert(0, 8);
	a.insert(0, 9);
	assert(a.size() == 4);
	assert(a.head() != nullptr);

	a = list;
	assert(a.size() == list.size());
	assert(a.head() != list.head());
	assert(a.head()->_value == list.head()->_value);

	END_TEST;
}

bool test_copy_oper_empty() {
	DoublyLinkedList<int> list;
	assert(list.size() == 0);
	assert(list.head() == nullptr);
	assert(list.tail() == nullptr);

	DoublyLinkedList<int> a;
	assert(a.size() == 0);
	assert(a.head() == nullptr);
	assert(a.tail() == nullptr);

	a.insert(0, 0);
	a.insert(1, 1);
	a.insert(2, 2);
	a.insert(3, 3);
	a.insert(4, 4);
	a.insert(5, 5);
	assert(a.size() == 6);
	assert(a.head() != nullptr);
	assert(a.tail() != nullptr);

	a = list;

	END_TEST;
}

bool test_iter() {
	DoublyLinkedList<int> list;
	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	list.insert(3, 3);
	list.insert(4, 4);
	list.insert(5, 5);

	size_t i = 0;
	for (DoublyLinkedList<int>::iterator it = list.begin(); it != list.end(); ++it) {
		assert(*it == list[i]);
		++i;
	}

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(insert_head);
	test(insert_tail);
	test(insert_middle);
	test(insert_invalid);
	test(remove_head);
	test(remove_tail);
	test(remove_middle);
	test(remove_invalid);
	test(oper_sq);
	test(copy);
	test(copy_empty);
	test(copy_oper);
	test(copy_oper_empty);
	test(iter);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}