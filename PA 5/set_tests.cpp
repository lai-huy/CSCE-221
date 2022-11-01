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

	pair<Set<int>::iterator, bool> p = set.insert(7);
	{
		assert(set.size() == 1);
		assert(*p.first == 7);
		assert(p.second);
	}

	p = set.insert(3);
	{
		assert(set.size() == 2);
		assert(*p.first == 3);
		assert(p.second);
	}

	p = set.insert(11);
	{
		assert(set.size() == 3);
		assert(*p.first == 11);
		assert(p.second);
	}

	p = set.insert(1);
	{
		assert(set.size() == 4);
		assert(*p.first == 1);
		assert(p.second);
	}

	p = set.insert(5);
	{
		assert(set.size() == 5);
		assert(*p.first == 5);
		assert(p.second);
	}

	p = set.insert(9);
	{
		assert(set.size() == 6);
		assert(*p.first == 9);
		assert(p.second);
	}

	p = set.insert(13);
	{
		assert(set.size() == 7);
		assert(*p.first == 13);
		assert(p.second);
	}

	p = set.insert(0);
	{
		assert(set.size() == 8);
		assert(*p.first == 0);
		assert(p.second);
	}

	p = set.insert(2);
	{
		assert(set.size() == 9);
		assert(*p.first == 2);
		assert(p.second);
	}

	p = set.insert(4);
	{
		assert(set.size() == 10);
		assert(*p.first == 4);
		assert(p.second);
	}

	p = set.insert(6);
	{
		assert(set.size() == 11);
		assert(*p.first == 6);
		assert(p.second);
	}

	p = set.insert(8);
	{
		assert(set.size() == 12);
		assert(*p.first == 8);
		assert(p.second);
	}

	p = set.insert(10);
	{
		assert(set.size() == 13);
		assert(*p.first == 10);
		assert(p.second);
	}

	p = set.insert(12);
	{
		assert(set.size() == 14);
		assert(*p.first == 12);
		assert(p.second);
	}

	p = set.insert(14);
	{
		assert(set.size() == 15);
		assert(*p.first == 14);
		assert(p.second);
	}

	END_TEST;
}

bool test_insert_right() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	set.insert(0);
	set.insert(1);
	set.insert(2);
	set.insert(3);
	set.insert(4);
	set.insert(5);
	set.insert(6);
	set.insert(7);
	set.insert(8);
	set.insert(9);
	set.insert(10);
	set.insert(11);
	set.insert(12);
	set.insert(13);
	set.insert(14);
	assert(set.size() == 15);

	END_TEST;
}

bool test_insert_left() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	set.insert(14);
	set.insert(13);
	set.insert(12);
	set.insert(11);
	set.insert(10);
	set.insert(9);
	set.insert(8);
	set.insert(7);
	set.insert(6);
	set.insert(5);
	set.insert(4);
	set.insert(3);
	set.insert(2);
	set.insert(1);
	set.insert(0);
	Set_iterator<int> iter(set.find(0));
	assert(set.size() == 15);
	assert(*iter == 0);
	END_TEST;
}

bool test_insert_in2out() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	for (int i = 0; i <= 64; ++i) {
		int num = i % 2 ? -i : i;
		set.insert(num);
	}

	END_TEST;
}

bool test_insert_out2in() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	for (int i = 64; i > -1; --i) {
		int num = i % 2 ? -i : i;
		set.insert(num);
	}

	END_TEST;
}

bool test_insert_random() {
	int nums[256] = {244, 63, 164, 66, 95, 33, 248, 214, 20, 35, 183, 197, 134, 73, 36, 19, 30, 109, 195, 151, 162, 240, 59, 215, 119, 145, 209, 12, 78, 106, 221, 238, 208, 135, 26, 139, 219, 232, 181, 108, 144, 251, 180, 98, 117, 255, 83, 87, 62, 234, 68, 43, 233, 196, 142, 75, 182, 88, 204, 32, 47, 254, 122, 173, 184, 86, 242, 125, 79, 93, 150, 163, 16, 31, 253, 69, 76, 100, 148, 192, 25, 82, 247, 72, 94, 141, 6, 53, 157, 48, 4, 74, 237, 131, 202, 186, 50, 27, 46, 80, 39, 8, 246, 193, 77, 45, 116, 200, 13, 218, 3, 191, 171, 55, 166, 216, 137, 107, 37, 231, 210, 91, 158, 90, 224, 2, 174, 172, 65, 136, 124, 211, 199, 160, 146, 0, 54, 189, 14, 149, 56, 1, 112, 228, 126, 24, 168, 102, 21, 153, 140, 10, 67, 132, 118, 104, 155, 89, 11, 178, 177, 190, 99, 167, 194, 105, 222, 7, 143, 236, 212, 111, 128, 249, 185, 71, 176, 243, 250, 138, 245, 15, 121, 179, 187, 18, 52, 130, 113, 42, 207, 188, 44, 114, 230, 223, 133, 22, 34, 129, 170, 203, 226, 201, 92, 101, 85, 51, 61, 115, 64, 220, 97, 217, 154, 70, 96, 110, 120, 206, 60, 29, 175, 213, 241, 17, 23, 161, 152, 103, 38, 156, 9, 41, 147, 235, 40, 252, 5, 58, 229, 169, 127, 225, 81, 205, 165, 198, 123, 28, 49, 239, 57, 159, 84, 227};
	Set<int> set;

	for (const int& num : nums)
		set.insert(num);

	for (const int& num : nums)
		set.remove(num);

	END_TEST;
}

bool test_insert_iter() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	Set<int>::const_iterator hint = set.end();
	Set<int>::iterator iter = set.insert(hint, 7);
	assert(*iter == 7);
	assert(set.size() == 1);

	hint = set.find(7);
	iter = set.insert(hint, 3);
	assert(*iter == 3);
	assert(set.size() == 2);

	hint = set.find(7);
	iter = set.insert(hint, 11);
	assert(*iter == 11);
	assert(set.size() == 3);

	hint = set.find(3);
	iter = set.insert(hint, 1);
	assert(*iter == 1);
	assert(set.size() == 4);

	hint = set.find(3);
	iter = set.insert(hint, 5);
	assert(*iter == 5);
	assert(set.size() == 5);

	hint = set.find(11);
	iter = set.insert(hint, 9);
	assert(*iter == 9);
	assert(set.size() == 6);

	hint = set.find(11);
	iter = set.insert(hint, 13);
	assert(*iter == 13);
	assert(set.size() == 7);

	hint = set.find(3);
	iter = set.insert(hint, 0);
	assert(*iter == 0);
	assert(set.size() == 8);

	hint = set.find(3);
	iter = set.insert(hint, 2);
	assert(*iter == 2);
	assert(set.size() == 9);

	hint = set.find(3);
	iter = set.insert(hint, 4);
	assert(*iter == 4);
	assert(set.size() == 10);

	hint = set.find(3);
	iter = set.insert(hint, 6);
	assert(*iter == 6);
	assert(set.size() == 11);

	hint = set.find(11);
	iter = set.insert(hint, 8);
	assert(*iter == 8);
	assert(set.size() == 12);

	hint = set.find(11);
	iter = set.insert(hint, 10);
	assert(*iter == 10);
	assert(set.size() == 13);

	hint = set.find(11);
	iter = set.insert(hint, 12);
	assert(*iter == 12);
	assert(set.size() == 14);

	hint = set.find(11);
	iter = set.insert(hint, 14);
	assert(*iter == 14);
	assert(set.size() == 15);

	END_TEST;
}

bool test_insert_iter_right() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	Set_const_iterator<int> end = set.end();
	set.insert(end, 0);
	set.insert(end, 1);
	set.insert(end, 2);
	set.insert(end, 3);
	set.insert(end, 4);
	set.insert(end, 5);
	set.insert(end, 6);
	set.insert(end, 7);
	set.insert(end, 8);
	set.insert(end, 9);
	set.insert(end, 10);
	set.insert(end, 11);
	set.insert(end, 12);
	set.insert(end, 13);
	set.insert(end, 14);
	assert(set.size() == 15);

	END_TEST;
}

bool test_insert_iter_left() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	Set_const_iterator<int> end = set.end();
	set.insert(end, 14);
	set.insert(end, 13);
	set.insert(end, 12);
	set.insert(end, 11);
	set.insert(end, 10);
	set.insert(end, 9);
	set.insert(end, 8);
	set.insert(end, 7);
	set.insert(end, 6);
	set.insert(end, 5);
	set.insert(end, 4);
	set.insert(end, 3);
	set.insert(end, 2);
	set.insert(end, 1);
	set.insert(end, 0);
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

	Set_iterator end(set.end());
	assert(set.find(0) != end);
	assert(set.find(1) != end);
	assert(set.find(2) != end);
	assert(set.find(3) != end);
	assert(set.find(4) != end);
	assert(set.find(5) != end);
	assert(set.find(6) != end);
	assert(set.find(7) != end);
	assert(set.find(8) != end);
	assert(set.find(9) != end);
	assert(set.find(10) != end);
	assert(set.find(11) != end);
	assert(set.find(12) != end);
	assert(set.find(13) != end);
	assert(set.find(14) != end);

	END_TEST;
}

bool test_find_const() {
	Set<int> a;
	assert(a.size() == 0);
	assert(a.is_empty());

	a.insert(7);
	a.insert(3);
	a.insert(11);
	a.insert(1);
	a.insert(5);
	a.insert(9);
	a.insert(13);
	a.insert(0);
	a.insert(2);
	a.insert(4);
	a.insert(6);
	a.insert(8);
	a.insert(10);
	a.insert(12);
	a.insert(14);

	const Set<int> set(a);
	const Set_const_iterator<int> end(set.end());
	assert(set.find(0) != end);
	assert(set.find(1) != end);
	assert(set.find(2) != end);
	assert(set.find(3) != end);
	assert(set.find(4) != end);
	assert(set.find(5) != end);
	assert(set.find(6) != end);
	assert(set.find(7) != end);
	assert(set.find(8) != end);
	assert(set.find(9) != end);
	assert(set.find(10) != end);
	assert(set.find(11) != end);
	assert(set.find(12) != end);
	assert(set.find(13) != end);
	assert(set.find(14) != end);

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
	set.insert(15);

	Set_iterator<int> iter(set.find(15)), end(set.end());
	expect_no_throw(++iter);
	assert(iter == end);

	expect_throw(*end, runtime_error);
	expect_no_throw(++end);
	expect_throw(*end, runtime_error);
	expect_no_throw(end++);
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
	assert(ss.str() == "<Set::iterator -> [0]>");

	ss.clear();
	ss.str("");

	iter = set.end();
	ss << iter.to_string();
	assert(ss.str() == "<Set::iterator -> [nullptr]>");

	END_TEST;
}

bool test_iter_empty() {
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

	Set_iterator<int> iter(set.find(7));
	set.make_empty();
	iter = set.begin();
	expect_throw(*iter, runtime_error);

	END_TEST;
}

bool test_iter_remove_leaf() {
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

	Set_const_iterator<int> index = set.find(14);
	Set_iterator<int> iter = set.remove(index);
	expect_throw(*iter, runtime_error);

	index = set.find(12);
	iter = set.remove(index);
	assert(*iter == 13);

	index = set.find(10);
	iter = set.remove(index);
	assert(*iter == 11);

	index = set.find(8);
	iter = set.remove(index);
	assert(*iter == 9);

	index = set.find(6);
	iter = set.remove(index);
	assert(*iter == 7);

	index = set.find(4);
	iter = set.remove(index);
	assert(*iter == 5);

	index = set.find(2);
	iter = set.remove(index);
	assert(*iter == 3);

	index = set.find(0);
	iter = set.remove(index);
	assert(*iter == 1);

	index = set.find(13);
	iter = set.remove(index);
	expect_throw(*iter, runtime_error);

	index = set.find(9);
	iter = set.remove(index);
	assert(*iter == 11);

	index = set.find(5);
	iter = set.remove(index);
	assert(*iter == 7);

	index = set.find(1);
	iter = set.remove(index);
	assert(*iter == 3);

	index = set.find(11);
	iter = set.remove(index);
	expect_throw(*iter, runtime_error);

	index = set.find(3);
	iter = set.remove(index);
	assert(*iter == 7);

	index = set.find(7);
	iter = set.remove(index);
	expect_throw(*iter, runtime_error);

	END_TEST;
}

bool test_iter_remove_middle() {
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

	Set_const_iterator<int> index = set.find(13);
	Set_iterator<int> iter = set.remove(index);
	assert(*iter == 14);

	index = set.find(12);
	iter = set.remove(index);
	assert(*iter == 14);

	assert(set.remove(8));
	index = set.find(9);
	iter = set.remove(index);
	assert(*iter == 10);

	assert(set.size() == 11);

	END_TEST;
}

bool test_iter_remove_root() {
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

	Set_const_iterator<int> index = set.find(7);
	Set_iterator<int> iter = set.remove(index);
	assert(*iter == 8);

	index = set.find(8);
	iter = set.remove(index);
	assert(*iter == 9);

	index = set.find(9);
	iter = set.remove(index);
	assert(*iter == 10);

	index = set.find(10);
	iter = set.remove(index);
	assert(*iter == 11);

	index = set.find(11);
	iter = set.remove(index);
	assert(*iter == 12);

	index = set.find(12);
	iter = set.remove(index);
	assert(*iter == 13);

	index = set.find(5);
	iter = set.remove(index);
	assert(*iter == 6);

	index = set.find(6);
	iter = set.remove(index);
	assert(*iter == 13);

	index = set.find(3);
	iter = set.remove(index);
	assert(*iter == 4);

	index = set.find(4);
	iter = set.remove(index);
	assert(*iter == 13);

	index = set.find(13);
	iter = set.remove(index);
	assert(*iter == 14);

	index = set.find(2);
	iter = set.remove(index);
	assert(*iter == 14);

	index = set.find(1);
	iter = set.remove(index);
	assert(*iter == 14);

	index = set.find(14);
	iter = set.remove(index);
	expect_throw(*iter, runtime_error);

	index = set.find(0);
	iter = set.remove(index);
	expect_throw(*iter, runtime_error);
	assert(set.is_empty());

	END_TEST;
}

bool test_iter_remove_invalid() {
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

	Set_const_iterator<int> end = set.end();
	expect_throw(set.remove(end), invalid_argument);
	set.make_empty();
	assert(set.remove(end) == end);

	END_TEST;
}

bool test_iter_remove_empty() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	expect_no_throw(set.remove(set.end()));

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

bool test_const_iter_end() {
	Set<int> set;
	assert(set.size() == 0);
	assert(set.is_empty());

	for (int i = 0; i < 21; ++i)
		set.insert(i);

	Set_const_iterator<int> iter(set.find(20)), end(set.end());
	expect_no_throw(++iter);
	assert(iter == end);

	expect_throw(*end, runtime_error);
	expect_no_throw(++end);
	expect_throw(*end, runtime_error);
	expect_no_throw(end++);
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
	assert(ss.str() == "<Set::const_iterator -> [0]>");

	ss.clear();
	ss.str("");

	iter = set.end();
	ss << iter.to_string();
	assert(ss.str() == "<Set::const_iterator -> [nullptr]>");

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
	cout << ss.str() << "\n";

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
		assert(begin != b);
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
	test(insert_dup_pair);
	test(insert_dup_iter);
	test(insert_right);
	test(insert_left);
	test(insert_in2out);
	test(insert_out2in);
	test(insert_random);
	test(insert_iter);
	test(insert_iter_right);
	test(insert_iter_left);
	test(find);
	test(find_const);
	test(remove_empty);
	test(remove_invalid);
	test(remove_leaf);
	test(remove_middle);
	test(remove_root);
	test(iter_end);
	test(iter_forward);
	test(iter_string);
	test(iter_empty);
	test(iter_remove_leaf);
	test(iter_remove_middle);
	test(iter_remove_root);
	test(iter_remove_empty);
	test(iter_remove_invalid);
	test(const_iter_end);
	test(const_iter_forward);
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
