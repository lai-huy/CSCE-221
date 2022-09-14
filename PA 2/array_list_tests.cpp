#include <iostream>
#include <stdexcept>
#include "array_list.h"

using std::cout;
using std::out_of_range;

// ----------------------------- From Dr. Ritchey ----------------------------- //

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

// ----------------------------- END ----------------------------- //

bool test_create() {
	ArrayList<int> list;

	assert(list.size() == 0);
	assert(list.capacity() == 1);

	END_TEST;
}

bool test_create_size() {
	ArrayList<int> list(10);
	assert(list.size() == 10);

	END_TEST;
}

bool test_insert_head() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 2);
	list.insert(0, 1);
	list.insert(0, 0);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	END_TEST;
}

bool test_insert_tail() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	END_TEST;
}

bool test_insert_middle() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 2);
	list.insert(1, 1);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	END_TEST;
}

bool test_insert_invalid() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	expect_throw(list.insert(5, 5), out_of_range);

	END_TEST;
}

bool test_at_invalid() {
	ArrayList<int> list;
	assert(list.size() == 0);
	assert(list.capacity() == 1);
	assert(list.data() == nullptr);

	expect_throw(list[10] = 0, out_of_range);

	END_TEST;
}

bool test_remove_head() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	list.remove(0);
	assert(list.size() == 2);
	assert(list[0] == 1);
	assert(list[1] == 2);
	expect_throw(list[2], out_of_range);

	list.remove(0);
	assert(list.size() == 1);
	assert(list[0] == 2);
	expect_throw(list[1], out_of_range);

	list.remove(0);
	assert(list.size() == 0);
	expect_throw(list[0], out_of_range);

	END_TEST;
}

bool test_remove_tail() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	list.remove(2);
	assert(list.size() == 2);
	assert(list[0] == 0);
	assert(list[1] == 1);
	expect_throw(list[2], out_of_range);

	list.remove(1);
	assert(list.size() == 1);
	assert(list[0] == 0);
	expect_throw(list[1], out_of_range);

	list.remove(0);
	assert(list.size() == 0);
	expect_throw(list[0], out_of_range);

	END_TEST;
}

bool test_remove_middle() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	list.remove(1);
	assert(list.size() == 2);
	assert(list[0] == 0);
	assert(list[1] == 2);

	END_TEST;
}

bool test_remove_invalid() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	expect_throw(list.remove(5), out_of_range);

	END_TEST;
}

bool test_copy() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	ArrayList<int> a(list);
	assert(a.size() == list.size());
	assert(a[0] == list[0]);
	assert(a[1] == list[1]);
	assert(a[2] == list[2]);

	END_TEST;
}

bool test_copy_empty() {
	ArrayList<int> list;
	assert(list.size() == 0);
	assert(list.capacity() == 1);
	assert(list.data() == nullptr);

	ArrayList<int> a(list);
	assert(a.size() == 0);
	assert(a.capacity() == 1);
	assert(a.data() == nullptr);

	END_TEST;
}

bool test_assignment() {
	ArrayList<int> list;
	assert(list.size() == 0);

	list.insert(0, 0);
	list.insert(1, 1);
	list.insert(2, 2);
	assert(list.size() == 3);
	assert(list[0] == 0);
	assert(list[1] == 1);
	assert(list[2] == 2);

	ArrayList<int> a;
	a.insert(0, 3);
	a.insert(1, 4);
	a.insert(2, 5);
	a.insert(3, 6);
	assert(a.size() == 4);
	assert(a[0] == 3);
	assert(a[1] == 4);
	assert(a[2] == 5);
	assert(a[3] == 6);

	a = list;
	assert(a.size() == list.size());
	assert(a[0] == list[0]);
	assert(a[1] == list[1]);
	assert(a[2] == list[2]);

	END_TEST;
}

bool test_assignment_empty() {
	ArrayList<int> list;
	assert(list.size() == 0);
	assert(list.capacity() == 1);
	assert(list.data() == nullptr);

	ArrayList<int> a;
	assert(a.size() == 0);
	assert(a.capacity() == 1);
	assert(a.data() == nullptr);
	a.insert(0, 3);
	a.insert(1, 4);
	a.insert(2, 5);
	a.insert(3, 6);
	assert(a.size() == 4);
	assert(a[0] == 3);
	assert(a[1] == 4);
	assert(a[2] == 5);
	assert(a[3] == 6);

	a = list;
	assert(a.size() == 0);
	assert(a.capacity() == 1);
	assert(a.data() == nullptr);

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(create_size);
	test(insert_head);
	test(insert_tail);
	test(insert_middle);
	test(insert_invalid);
	test(at_invalid);
	test(remove_head);
	test(remove_tail);
	test(remove_middle);
	test(remove_invalid);
	test(copy);
	test(copy_empty);
	test(assignment);
	test(assignment_empty);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
