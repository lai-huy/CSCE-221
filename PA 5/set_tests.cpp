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
	assert(set.is_empty());

	END_TEST;
}

bool test_insert_pair() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	pair<Set_iterator<int>, bool> p(set.insert(7));
	{
		assert(set.size() == 1);
		assert(p.first->value() == 7);
		assert(*p.first == 7);
		assert(p.second);
	}

	p = set.insert(3);
	{
		assert(set.size() == 2);
		assert(p.first->value() == 3);
		assert(*p.first == 3);
		assert(p.second);
	}

	p = set.insert(11);
	{
		assert(set.size() == 3);
		assert(p.first->value() == 11);
		assert(*p.first == 11);
		assert(p.second);
	}

	p = set.insert(1);
	{
		assert(set.size() == 4);
		assert(p.first->value() == 1);
		assert(*p.first == 1);
		assert(p.second);
	}

	p = set.insert(5);
	{
		assert(set.size() == 5);
		assert(p.first->value() == 5);
		assert(*p.first == 5);
		assert(p.second);
	}

	p = set.insert(9);
	{
		assert(set.size() == 6);
		assert(p.first->value() == 9);
		assert(*p.first == 9);
		assert(p.second);
	}

	p = set.insert(13);
	{
		assert(set.size() == 7);
		assert(p.first->value() == 13);
		assert(*p.first == 13);
		assert(p.second);
	}

	p = set.insert(0);
	{
		assert(set.size() == 8);
		assert(p.first->value() == 0);
		assert(*p.first == 0);
		assert(p.second);
	}

	p = set.insert(2);
	{
		assert(set.size() == 9);
		assert(p.first->value() == 2);
		assert(*p.first == 2);
		assert(p.second);
	}

	p = set.insert(4);
	{
		assert(set.size() == 10);
		assert(p.first->value() == 4);
		assert(*p.first == 4);
		assert(p.second);
	}

	p = set.insert(6);
	{
		assert(set.size() == 11);
		assert(p.first->value() == 6);
		assert(*p.first == 6);
		assert(p.second);
	}

	p = set.insert(8);
	{
		assert(set.size() == 12);
		assert(p.first->value() == 8);
		assert(*p.first == 8);
		assert(p.second);
	}

	p = set.insert(10);
	{
		assert(set.size() == 13);
		assert(p.first->value() == 10);
		assert(*p.first == 10);
		assert(p.second);
	}

	p = set.insert(12);
	{
		assert(set.size() == 14);
		assert(p.first->value() == 12);
		assert(*p.first == 12);
		assert(p.second);
	}

	p = set.insert(14);
	{
		assert(set.size() == 15);
		assert(p.first->value() == 14);
		assert(*p.first == 14);
		assert(p.second);
	}

	END_TEST;
}

bool test_insert_right() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	set.insert(set.end(), 0);
	set.insert(set.end(), 1);
	set.insert(set.end(), 2);
	set.insert(set.end(), 3);
	set.insert(set.end(), 4);
	set.insert(set.end(), 5);
	set.insert(set.end(), 6);
	set.insert(set.end(), 7);
	set.insert(set.end(), 8);
	set.insert(set.end(), 9);
	set.insert(set.end(), 10);
	set.insert(set.end(), 11);
	set.insert(set.end(), 12);
	set.insert(set.end(), 13);
	Set_iterator<int> iter(set.insert(set.end(), 14));
	assert(set.size() == 15);
	assert(iter->value() == 14);
	assert(*iter == 14);

	END_TEST;
}

bool test_insert_left() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	set.insert(set.end(), 14);
	set.insert(set.end(), 13);
	set.insert(set.end(), 12);
	set.insert(set.end(), 11);
	set.insert(set.end(), 10);
	set.insert(set.end(), 9);
	set.insert(set.end(), 8);
	set.insert(set.end(), 7);
	set.insert(set.end(), 6);
	set.insert(set.end(), 5);
	set.insert(set.end(), 4);
	set.insert(set.end(), 3);
	set.insert(set.end(), 2);
	set.insert(set.end(), 1);
	Set_iterator<int> iter(set.insert(set.end(), 0));
	assert(set.size() == 15);
	assert(iter->value() == 0);
	assert(*iter == 0);
	END_TEST;
}

bool test_insert_rl() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	expect_no_throw(set.insert(set.end(), 0));
	expect_no_throw(set.insert(set.end(), 2));
	expect_no_throw(set.insert(set.end(), 1));
	assert(set.size() == 3);

	END_TEST;
}

bool test_insert_lr() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	expect_no_throw(set.insert(set.end(), 2));
	expect_no_throw(set.insert(set.end(), 0));
	expect_no_throw(set.insert(set.end(), 1));
	assert(set.size() == 3);

	END_TEST;
}

bool test_insert_iter() {
	Set<int> set;
	assert(set.size() == 0);

	set.insert(7);
	set.insert(3);
	set.insert(11);
	set.insert(1);
	set.insert(5);
	set.insert(9);
	set.insert(13);
	set.insert(2);
	set.insert(4);
	set.insert(6);
	set.insert(8);
	set.insert(10);
	set.insert(12);
	set.insert(14);
	assert(set.size() == 14);

	expect_no_throw(set.insert(set.begin(), 0));
	assert(set.size() == 15);

	END_TEST;
}

bool test_insert_dup_pair() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	Set_const_iterator begin(set.begin());
	assert(set.size() == 15);

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
	Set_const_iterator b(set.begin());
	assert(set.size() == 15);
	assert(begin == b);

	END_TEST;
}

bool test_insert_dup_iter() {
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
	assert(set.size() == 15);

	set.insert(set.end(), 7);
	set.insert(set.end(), 3);
	set.insert(set.end(), 11);
	set.insert(set.end(), 1);
	set.insert(set.end(), 5);
	set.insert(set.end(), 9);
	set.insert(set.end(), 13);
	set.insert(set.end(), 0);
	set.insert(set.end(), 2);
	set.insert(set.end(), 4);
	set.insert(set.end(), 6);
	set.insert(set.end(), 8);
	set.insert(set.end(), 10);
	set.insert(set.end(), 12);
	set.insert(set.end(), 14);
	assert(set.size() == 15);

	END_TEST;
}

bool test_remove_empty() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	assert(set.remove(0) == 0);
	assert(set.size() == 0);
	assert(set.is_empty());

	END_TEST;
}

bool test_remove_invalid() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);

	assert(set.remove(15) == 0);
	assert(set.size() == 15);

	END_TEST;
}

bool test_remove_leaf() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);

	assert(set.remove(14));
	assert(set.remove(12));
	assert(set.remove(10));
	assert(set.remove(8));
	assert(set.remove(6));
	assert(set.remove(4));
	assert(set.remove(2));
	assert(set.remove(0));
	assert(set.remove(13));
	assert(set.remove(9));
	assert(set.remove(5));
	assert(set.remove(1));
	assert(set.remove(11));
	assert(set.remove(3));
	assert(set.remove(7));
	assert(set.size() == 0);
	assert(set.is_empty());

	END_TEST;
}

bool test_remove_middle() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);

	assert(set.remove(13));
	assert(set.remove(14));
	assert(set.remove(8));
	assert(set.remove(9));
	assert(set.size() == 11);

	END_TEST;
}

bool test_remove_root() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);

	assert(set.remove(7));
	assert(set.remove(8));
	assert(set.remove(9));
	assert(set.remove(10));
	assert(set.remove(11));
	assert(set.remove(12));
	assert(set.remove(5));
	assert(set.remove(6));
	assert(set.remove(3));
	assert(set.remove(4));
	assert(set.remove(13));
	assert(set.remove(2));
	assert(set.remove(1));
	assert(set.remove(14));
	assert(set.remove(0));
	assert(set.size() == 0);
	assert(set.is_empty());

	END_TEST;
}

bool test_find() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	assert(set.find(0) != set.end());
	assert(set.find(1) != set.end());
	assert(set.find(2) != set.end());
	assert(set.find(3) != set.end());
	assert(set.find(4) != set.end());
	assert(set.find(5) != set.end());
	assert(set.find(6) != set.end());
	assert(set.find(7) != set.end());
	assert(set.find(8) != set.end());
	assert(set.find(9) != set.end());
	assert(set.find(10) != set.end());
	assert(set.find(11) != set.end());
	assert(set.find(12) != set.end());
	assert(set.find(13) != set.end());
	assert(set.find(14) != set.end());

	END_TEST;
}

bool test_iter_end() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_iterator<int> end(set.end());
	expect_throw(*end, runtime_error);
	expect_no_throw(++end);
	expect_throw(*end, runtime_error);
	expect_no_throw(--end);
	expect_throw(*end, runtime_error);

	END_TEST;
}

bool test_iter_forward() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_iterator<int> iter(set.find(0));
	for (size_t i = 0; i < set.size(); ++i)
		expect_no_throw(++iter);

	END_TEST;
}

bool test_iter_reverse() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_iterator<int> iter(set.find(14));
	for (size_t i = 0; i < set.size(); ++i)
		expect_no_throw(--iter);

	iter = set.find(14);
	for (size_t i = 0; i < set.size(); ++i)
		expect_no_throw(iter--);

	END_TEST;
}

bool test_iter_string() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_iterator<int> iter(set.begin());
	stringstream ss(iter.to_string());
	assert(ss.str() == "<Set::iterator → [0]>");

	ss.clear();
	ss.str("");

	iter = set.end();
	ss << iter.to_string();
	assert(ss.str() == "<Set::iterator → [nullptr]>");

	END_TEST;
}

bool test_const_iter_forward() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_const_iterator<int> iter(set.begin());
	for (size_t i = 0; i < set.size(); ++i)
		expect_no_throw(++iter);

	END_TEST;
}

bool test_const_iter_reverse() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_const_iterator<int> iter(set.find(14));
	for (size_t i = 0; i < set.size() - 1; ++i)
		expect_no_throw(--iter);

	END_TEST;
}

bool test_const_iter_end() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_const_iterator<int> end(set.end());
	expect_throw(*end, runtime_error);
	expect_no_throw(++end);
	expect_throw(*end, runtime_error);
	expect_no_throw(--end);
	expect_throw(*end, runtime_error);

	END_TEST;
}

bool test_const_iter_string() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	Set_const_iterator<int> iter(set.begin());
	stringstream ss(iter.to_string());
	assert(ss.str() == "<Set::const_iterator → [0]>");

	ss.clear();
	ss.str("");

	iter = set.end();
	ss << iter.to_string();
	assert(ss.str() == "<Set::const_iterator → [nullptr]>");

	END_TEST;
}

bool test_print_set() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	stringstream ss;
	expect_no_throw(set.print_set(ss));
	assert(ss.str() == "{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}");

	END_TEST;
}

bool test_print_tree() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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

	stringstream ss;
	expect_no_throw(set.print_tree(ss));
	assert(ss.str() == "      14\n    13\n      12\n  11\n      10\n    9\n      8\n7\n      6\n    5\n      4\n  3\n      2\n    1\n      0\n");

	END_TEST;
}

bool test_print_empty() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	stringstream ss;
	expect_no_throw(set.print_set(ss));
	assert(ss.str() == "<empty>");

	ss.str("");
	ss.clear();
	expect_no_throw(set.print_tree(ss));
	assert(ss.str() == "<empty>");
	END_TEST;
}

bool test_copy() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);

	Set<int> a(set);
	assert(a.size() == 15);

	END_TEST;
}

bool test_copy_empty() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	Set<int> a(set);
	assert(set.size() == 0);
	assert(a.is_empty());

	END_TEST;
}

bool test_copy_oper() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);

	Set<int> a;
	assert(a.size() == 0);
	assert(a.is_empty());

	a.insert(6);
	a.insert(2);
	a.insert(10);
	a.insert(0);
	a.insert(4);
	a.insert(8);
	a.insert(12);
	a.insert(-1);
	a.insert(1);
	a.insert(3);
	a.insert(5);
	a.insert(7);
	a.insert(9);
	a.insert(11);
	a.insert(13);
	{
		Set_const_iterator<int> begin(set.begin()), b(a.begin());
		assert(a.size() == 15);
		assert(begin != b);
		assert(*begin != *b);
	}

	a = set;
	{
		Set_const_iterator<int> begin(set.begin()), b(a.begin());
		assert(a.size() == set.size());
		assert(begin == b);
		assert(*begin == *b);
	}

	END_TEST;
}

bool test_copy_oper_empty() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	Set<int> a;
	assert(a.size() == 0);
	assert(a.is_empty());

	a.insert(6);
	a.insert(2);
	a.insert(10);
	a.insert(0);
	a.insert(4);
	a.insert(8);
	a.insert(12);
	a.insert(-1);
	a.insert(1);
	a.insert(3);
	a.insert(5);
	a.insert(7);
	a.insert(9);
	a.insert(11);
	a.insert(13);
	assert(a.size() == 15);

	a = set;
	{
		assert(a.size() == set.size());
		assert(a.is_empty());
		assert(a.begin() == a.end());
	}

	END_TEST;
}

bool test_self_assignment() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

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
	assert(set.size() == 15);
	Set_const_iterator<int> begin(set.begin());

	set = set;
	{
		Set_const_iterator<int> b(set.begin());
		assert(set.size() == 15);
		assert(begin == b);
		assert(*begin == *b);
	}

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(insert_pair);
	test(insert_right);
	test(insert_left);
	test(insert_lr);
	test(insert_rl);
	test(insert_iter);
	test(insert_dup_pair);
	test(insert_dup_iter);
	test(remove_empty);
	test(remove_invalid);
	test(remove_leaf);
	test(remove_middle);
	test(remove_root);
	test(find);
	test(iter_end);
	test(iter_forward);
	test(iter_reverse);
	test(iter_string);
	test(const_iter_end);
	test(const_iter_forward);
	test(const_iter_reverse);
	test(const_iter_string);
	test(print_set);
	test(print_tree);
	test(print_empty);
	test(copy);
	test(copy_empty);
	test(copy_oper);
	test(copy_oper_empty);
	test(self_assignment);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
