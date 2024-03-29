#include <stdexcept>
#include <iostream>
#include "collection.h"

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
	Collection<int> list;

	assert(list.is_empty());
	assert(list.size() is 0);

	END_TEST;
}

bool test_insert() {
	Collection<int> list;

	assert(list.is_empty());
	assert(list.size() is 0);

	list.insert(0);
	{
		assert(!list.is_empty());
		assert(list.size() is 1);
	}

	list.insert(1);
	{
		assert(!list.is_empty());
		assert(list.size() is 2);
	}

	list.insert(2);
	{
		assert(!list.is_empty());
		assert(list.size() is 3);
	}

	list.insert(3);
	{
		assert(!list.is_empty());
		assert(list.size() is 4);
	}

	list.insert(4);
	{
		assert(!list.is_empty());
		assert(list.size() is 5);
	}

	list.insert(5);
	{
		assert(!list.is_empty());
		assert(list.size() is 6);
	}

	list.insert(6);
	{
		assert(!list.is_empty());
		assert(list.size() is 7);
	}

	END_TEST;
}

bool test_contains() {
	Collection<int> list;
	assert(list.is_empty());
	assert(list.size() is 0);
	assert(!list.contains(0));

	list.insert(0);
	assert(list.contains(0));

	END_TEST;
}

bool test_remove() {
	Collection<int> list;
	assert(list.is_empty());
	assert(list.size() is 0);

	list.remove(0);
	assert(list.is_empty());
	assert(list.size() is 0);

	list.insert(0);
	assert(!list.is_empty());
	assert(list.size() is 1);

	list.remove(0);
	{
		assert(list.is_empty());
		assert(list.size() is 0);
	}

	list.insert(1);
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.insert(5);
	{
		assert(!list.is_empty());
		assert(list.size() is 5);
	}

	list.remove(1);
	{
		assert(!list.is_empty());
		assert(list.size() is 4);
	}

	END_TEST;
}

bool test_copy_const() {
	Collection<int> a;
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);

	Collection<int> b(a);
	assert(b.size() is a.size());
	assert(b.is_empty() == a.is_empty());

	END_TEST;
}

bool test_copy_oper() {
	Collection<int> a;
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);

	Collection<int> b;
	b.insert(5);
	b.insert(6);
	b.insert(7);
	b.insert(8);
	b.insert(9);
	{
		assert(b.size() is 5);
	}

	b = a;
	{
		assert(b.size() is 4);
		assert(b.size() is a.size());
	}

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(insert);
	test(contains);
	test(remove);
	test(copy_const);
	test(copy_oper);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}