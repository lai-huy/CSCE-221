#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
#include "my_set.h"

using std::pair;
using std::out_of_range, std::invalid_argument;
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
		cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << "\n";\
		test_passed = false;\
	}\
} catch(...) {\
	cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << "\n";\
	test_passed = false;\
}

#define assert(X) try {\
	if (!(X)) {\
		cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << "\n";\
		test_passed = false;\
		END_TEST;\
	}\
} catch(...) {\
	cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << "\n";\
	test_passed = false;\
	END_TEST;\
}

#define expect_throw(X,E) {\
	bool threw_expected_exception = false;\
	try { X; }\
	catch(const E& err) {\
		threw_expected_exception = true;\
	} catch(...) {\
		cout << blue << "  [help] " << #X << " threw an incorrect exception." << reset << "\n";\
	}\
	if (!threw_expected_exception) {\
		cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<"\n";\
		test_passed = false;\
	}\
}

#define expect_no_throw(X) {\
	try { X; }\
	catch(...) {\
		cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << reset << "\n";\
		test_passed = false;\
	}\
}

#define test(x) if (test_##x()) { cout << green << "[PASS] "; pass_cnt++; }\
else { cout << red << "[FAIL] "; fail_cnt++; }\
cout << #x << reset << "\n";
#define skip(x) cout << yellow << "[SKIP] " << #x << reset << "\n"; skip_cnt++;

namespace {
	bool test_passed = true;
}

bool test_create() {
	Set<int> set;
	assert(set.size() == 0);

	END_TEST;
}

bool test_insert_pair() {
	Set<int> set;
	assert(set.size() == 0);

	pair<Set_iterator<int>, bool> p(set.insert(7));
	{
		assert(set.size() == 1);
		assert(p.first->value() == 7);
		assert(p.second);
	}

	p = set.insert(3);
	{
		assert(set.size() == 2);
		assert(p.first->value() == 3);
		assert(p.second);
	}

	p = set.insert(11);
	{
		assert(set.size() == 3);
		assert(p.first->value() == 11);
		assert(p.second);
	}

	p = set.insert(1);
	{
		assert(set.size() == 4);
		assert(p.first->value() == 1);
		assert(p.second);
	}

	p = set.insert(5);
	{
		assert(set.size() == 5);
		assert(p.first->value() == 5);
		assert(p.second);
	}

	p = set.insert(9);
	{
		assert(set.size() == 6);
		assert(p.first->value() == 9);
		assert(p.second);
	}

	p = set.insert(13);
	{
		assert(set.size() == 7);
		assert(p.first->value() == 13);
		assert(p.second);
	}

	p = set.insert(0);
	{
		assert(set.size() == 8);
		assert(p.first->value() == 0);
		assert(p.second);
	}

	p = set.insert(2);
	{
		assert(set.size() == 9);
		assert(p.first->value() == 2);
		assert(p.second);
	}

	p = set.insert(4);
	{
		assert(set.size() == 10);
		assert(p.first->value() == 4);
		assert(p.second);
	}

	p = set.insert(6);
	{
		assert(set.size() == 11);
		assert(p.first->value() == 6);
		assert(p.second);
	}

	p = set.insert(8);
	{
		assert(set.size() == 12);
		assert(p.first->value() == 8);
		assert(p.second);
	}

	p = set.insert(10);
	{
		assert(set.size() == 13);
		assert(p.first->value() == 10);
		assert(p.second);
	}

	p = set.insert(12);
	{
		assert(set.size() == 14);
		assert(p.first->value() == 12);
		assert(p.second);
	}

	p = set.insert(14);
	{
		assert(set.size() == 15);
		assert(p.first->value() == 14);
		assert(p.second);
	}

	END_TEST;
}

bool test_insert_iter() {
	Set<int> set;
	assert(set.size() == 0);

	Set_iterator<int> iter = set.insert(set.begin(), 7);
	assert(set.size() == 1);
	assert(iter->value() == 7);
	expect_throw(++iter, runtime_error);
	expect_throw(--iter, runtime_error);

	iter = set.insert(iter, 3);
	assert(set.size() == 2);
	assert(iter->value() == 3);

	END_TEST;
}

bool test_print_set() {
	Set<int> set;
	assert(set.size() == 0);

	set.insert(7);
	set.insert(3);
	set.insert(11);
	set.insert(1);
	set.insert(5);
	set.insert(9);
	set.insert(13);
	set.insert(0);
	set.insert(2);
	set.insert(4);
	set.insert(6);
	set.insert(8);
	set.insert(10);
	set.insert(12);
	set.insert(14);

	set.print_set();

	END_TEST;
}

bool test_print_tree() {
	Set<int> set;
	assert(set.size() == 0);

	set.insert(7);
	set.insert(3);
	set.insert(11);
	set.insert(1);
	set.insert(5);
	set.insert(9);
	set.insert(13);
	set.insert(0);
	set.insert(2);
	set.insert(4);
	set.insert(6);
	set.insert(8);
	set.insert(10);
	set.insert(12);
	set.insert(14);

	set.print_tree();

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(insert_pair);
	// test(insert_iter);
	test(print_set);
	test(print_tree);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
