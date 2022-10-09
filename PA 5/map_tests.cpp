#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
#include "my_map.h"

using std::cout;
using std::string, std::pair;

#define black   "\033[30m"
#define red     "\033[31m"
#define green   "\033[32m"
#define yellow  "\033[33m"
#define blue    "\033[34m"
#define magenta "\033[35m"
#define cyan    "\033[36m"
#define white   "\033[37m"
#define remap   "\033[m"

#define END_TEST bool this_test_passed = test_passed;\
test_passed = true;\
return this_test_passed;

#define expect(X) try {\
	if (!(X)) {\
		cout << red "  [fail]" remap " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << remap << "\n";\
		test_passed = false;\
	}\
} catch(...) {\
	cout << red "  [fail]" remap " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << remap << "\n";\
	test_passed = false;\
}

#define assert(X) try {\
	if (!(X)) {\
		cout << red "  [fail]" remap " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << remap << "\n";\
		test_passed = false;\
		END_TEST;\
	}\
} catch(...) {\
	cout << red "  [fail]" remap " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << remap << "\n";\
	test_passed = false;\
	END_TEST;\
}

#define expect_throw(X,E) {\
	bool threw_expected_exception = false;\
	try { X; }\
	catch(const E& err) {\
		threw_expected_exception = true;\
	} catch(...) {\
		cout << blue << "  [help] " << #X << " threw an incorrect exception." << remap << "\n";\
	}\
	if (!threw_expected_exception) {\
		cout << red <<"  [fail]" << remap << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << remap <<"\n";\
		test_passed = false;\
	}\
}

#define expect_no_throw(X) {\
	try { X; }\
	catch(...) {\
		cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << remap << "\n";\
		test_passed = false;\
	}\
}

#define test(x) if (test_##x()) { cout << green << "[PASS] "; pass_cnt++; }\
else { cout << red << "[FAIL] "; fail_cnt++; }\
cout << #x << remap << "\n";
#define skip(x) cout << yellow << "[SKIP] " << #x << remap << "\n"; skip_cnt++;

namespace {
	bool test_passed = true;
}

bool test_create() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	END_TEST;
}

bool test_insert_pair() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	pair<Map_iterator<string, int>, bool> p(map.insert({"07", 7}));
	{
		assert(map.size() == 1);
		assert(p.first->first == "07");
		assert((*(p.first)).first == "07");
		assert(p.first->second == 7);
		assert((*(p.first)).second == 7);
		assert(p.second);
	}

	p = map.insert({"03", 3});
	{
		assert(map.size() == 2);
		assert(p.first->first == "03");
		assert((*(p.first)).first == "03");
		assert(p.first->second == 3);
		assert((*(p.first)).second == 3);
		assert(p.second);
	}

	p = map.insert({"11", 11});
	{
		assert(map.size() == 3);
		assert(p.first->first == "11");
		assert((*(p.first)).first == "11");
		assert(p.first->second == 11);
		assert((*(p.first)).second == 11);
		assert(p.second);
	}

	p = map.insert({"01", 1});
	{
		assert(map.size() == 4);
		assert(p.first->first == "01");
		assert((*(p.first)).first == "01");
		assert(p.first->second == 1);
		assert((*(p.first)).second == 1);
		assert(p.second);
	}

	p = map.insert({"05", 5});
	{
		assert(map.size() == 5);
		assert(p.first->first == "05");
		assert((*(p.first)).first == "05");
		assert(p.first->second == 5);
		assert((*(p.first)).second == 5);
		assert(p.second);
	}

	p = map.insert({"09", 9});
	{
		assert(map.size() == 6);
		assert(p.first->first == "09");
		assert((*(p.first)).first == "09");
		assert(p.first->second == 9);
		assert((*(p.first)).second == 9);
		assert(p.second);
	}

	p = map.insert({"13", 13});
	{
		assert(map.size() == 7);
		assert(p.first->first == "13");
		assert((*(p.first)).first == "13");
		assert(p.first->second == 13);
		assert((*(p.first)).second == 13);
		assert(p.second);
	}

	p = map.insert({"00", 0});
	{
		assert(map.size() == 8);
		assert(p.first->first == "00");
		assert((*(p.first)).first == "00");
		assert(p.first->second == 0);
		assert((*(p.first)).second == 0);
		assert(p.second);
	}

	p = map.insert({"02", 2});
	{
		assert(map.size() == 9);
		assert(p.first->first == "02");
		assert((*(p.first)).first == "02");
		assert(p.first->second == 2);
		assert((*(p.first)).second == 2);
		assert(p.second);
	}

	p = map.insert({"04", 4});
	{
		assert(map.size() == 10);
		assert(p.first->first == "04");
		assert((*(p.first)).first == "04");
		assert(p.first->second == 4);
		assert((*(p.first)).second == 4);
		assert(p.second);
	}

	p = map.insert({"06", 6});
	{
		assert(map.size() == 11);
		assert(p.first->first == "06");
		assert((*(p.first)).first == "06");
		assert(p.first->second == 6);
		assert((*(p.first)).second == 6);
		assert(p.second);
	}

	p = map.insert({"08", 8});
	{
		assert(map.size() == 12);
		assert(p.first->first == "08");
		assert((*(p.first)).first == "08");
		assert(p.first->second == 8);
		assert((*(p.first)).second == 8);
		assert(p.second);
	}

	p = map.insert({"10", 10});
	{
		assert(map.size() == 13);
		assert(p.first->first == "10");
		assert((*(p.first)).first == "10");
		assert(p.first->second == 10);
		assert((*(p.first)).second == 10);
		assert(p.second);
	}

	p = map.insert({"12", 12});
	{
		assert(map.size() == 14);
		assert(p.first->first == "12");
		assert((*(p.first)).first == "12");
		assert(p.first->second == 12);
		assert((*(p.first)).second == 12);
		assert(p.second);
	}

	p = map.insert({"14", 14});
	{
		assert(map.size() == 15);
		assert(p.first->first == "14");
		assert((*(p.first)).first == "14");
		assert(p.first->second == 14);
		assert((*(p.first)).second == 14);
		assert(p.second);
	}

	END_TEST;
}

bool test_insert_right() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"00", 0});
	map.insert({"01", 1});
	map.insert({"02", 2});
	map.insert({"03", 3});
	map.insert({"04", 4});
	map.insert({"05", 5});
	map.insert({"06", 6});
	map.insert({"07", 7});
	map.insert({"08", 8});
	map.insert({"09", 9});
	map.insert({"10", 10});
	map.insert({"11", 11});
	map.insert({"12", 12});
	map.insert({"13", 13});
	map.insert({"14", 14});

	assert(map.size() == 15);

	END_TEST;
}

bool test_insert_left() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"14", 14});
	map.insert({"13", 13});
	map.insert({"12", 12});
	map.insert({"11", 11});
	map.insert({"10", 10});
	map.insert({"09", 9});
	map.insert({"08", 8});
	map.insert({"07", 7});
	map.insert({"06", 6});
	map.insert({"05", 5});
	map.insert({"04", 4});
	map.insert({"03", 3});
	map.insert({"02", 2});
	map.insert({"01", 1});
	map.insert({"00", 0});

	assert(map.size() == 15);

	END_TEST;
}

bool test_insert_lr() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"01", 1});

	END_TEST;
}

bool test_insert_rl() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"02", 2});
	map.insert({"00", 0});
	map.insert({"01", 1});

	END_TEST;
}

bool test_insert_iter() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert(map.end(), {"01", 1});
	map.insert(map.end(), {"02", 2});
	map.insert(map.end(), {"03", 3});
	map.insert(map.end(), {"04", 4});
	map.insert(map.end(), {"05", 5});
	map.insert(map.end(), {"06", 6});
	map.insert(map.end(), {"07", 7});
	map.insert(map.end(), {"08", 8});
	map.insert(map.end(), {"09", 9});
	map.insert(map.end(), {"10", 10});
	map.insert(map.end(), {"11", 11});
	map.insert(map.end(), {"12", 12});
	map.insert(map.end(), {"13", 13});
	map.insert(map.end(), {"14", 14});
	assert(map.size() == 14);

	map.insert(map.begin(), {"00", 0});
	assert(map.size() == 15);

	END_TEST;
}

bool test_insert_dup_pair() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	END_TEST;
}

bool test_insert_dup_iter() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	map.insert(map.end(), {"00", 0});
	map.insert(map.end(), {"01", 1});
	map.insert(map.end(), {"02", 2});
	map.insert(map.end(), {"03", 3});
	map.insert(map.end(), {"04", 4});
	map.insert(map.end(), {"05", 5});
	map.insert(map.end(), {"06", 6});
	map.insert(map.end(), {"07", 7});
	map.insert(map.end(), {"08", 8});
	map.insert(map.end(), {"09", 9});
	map.insert(map.end(), {"10", 10});
	map.insert(map.end(), {"11", 11});
	map.insert(map.end(), {"12", 12});
	map.insert(map.end(), {"13", 13});
	map.insert(map.end(), {"14", 14});
	assert(map.size() == 15);

	END_TEST;
}

bool test_find() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	assert(map.find("00") != map.end());
	assert(map.find("01") != map.end());
	assert(map.find("02") != map.end());
	assert(map.find("03") != map.end());
	assert(map.find("04") != map.end());
	assert(map.find("05") != map.end());
	assert(map.find("06") != map.end());
	assert(map.find("07") != map.end());
	assert(map.find("08") != map.end());
	assert(map.find("09") != map.end());
	assert(map.find("10") != map.end());
	assert(map.find("11") != map.end());
	assert(map.find("12") != map.end());
	assert(map.find("13") != map.end());
	assert(map.find("14") != map.end());

	END_TEST;
}

bool test_iter_end() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_iterator end(map.end());
	expect_throw(*end, runtime_error);
	expect_throw(end->first, runtime_error);
	expect_no_throw(++end);
	expect_throw(*end, runtime_error);
	expect_throw(end->first, runtime_error);
	expect_no_throw(--end);
	expect_throw(*end, runtime_error);
	expect_throw(end->first, runtime_error);

	END_TEST;
}

bool test_iter_forward() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_iterator<string, int> iter(map.find("00"));
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(++iter);
		expect_no_throw(*iter);
	}

	iter = map.find("00");
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(iter++);
		expect_no_throw(*iter);
	}

	END_TEST;
}

bool test_iter_reverse() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_iterator<string, int> iter(map.find("14"));
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(--iter);
		expect_no_throw(*iter);
	}

	iter = map.find("14");
	for (size_t i = 0; i < map.size() - 1; ++i)
		expect_no_throw(iter--);

	END_TEST;
}

bool test_iter_string() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_iterator<string, int> iter(map.begin());
	stringstream ss(iter.to_string());
	assert(ss.str() == "<Map::iterator -> [00: 0]>");

	ss.clear();
	ss.str("");

	iter = map.end();
	ss << iter.to_string();
	assert(ss.str() == "<Map::iterator -> [nullptr]>");

	END_TEST;
}

bool test_const_iter_forward() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_const_iterator<string, int> iter(map.begin());
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(++iter);
		expect_no_throw(*iter);
	}

	iter = map.find("00");
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(iter++);
		expect_no_throw(*iter);
	}

	END_TEST;
}

bool test_const_iter_reverse() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_const_iterator<string, int> iter(map.find("14"));
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(--iter);
		expect_no_throw(*iter);
	}

	iter = map.find("14");
	for (size_t i = 0; i < map.size() - 1; ++i) {
		expect_no_throw(iter--);
		expect_no_throw(*iter);
	}

	END_TEST;
}

bool test_const_iter_end() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_const_iterator<string, int> end(map.end());
	expect_throw(*end, runtime_error);
	expect_throw(end->first, runtime_error);
	expect_no_throw(++end);
	expect_throw(*end, runtime_error);
	expect_throw(end->first, runtime_error);
	expect_no_throw(--end);
	expect_throw(*end, runtime_error);
	expect_throw(end->first, runtime_error);

	END_TEST;
}

bool test_const_iter_string() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map_const_iterator<string, int> iter(map.begin());
	stringstream ss(iter.to_string());
	assert(ss.str() == "<Map::const_iterator -> [00: 0]>");

	ss.clear();
	ss.str("");

	iter = map.end();
	ss << iter.to_string();
	assert(ss.str() == "<Map::const_iterator -> [nullptr]>");

	END_TEST;
}

bool test_print_map() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});

	stringstream ss;
	map.print_map(ss);
	assert(ss.str() == "{00: 0, 01: 1, 02: 2, 03: 3, 04: 4, 05: 5, 06: 6, 07: 7, 08: 8, 09: 9, 10: 10, 11: 11, 12: 12, 13: 13, 14: 14}");

	END_TEST;
}

bool test_print_tree() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});

	stringstream ss;
	map.print_tree(ss);
	assert(ss.str() == "      14: 14\n    13: 13\n      12: 12\n  11: 11\n      10: 10\n    09: 9\n      08: 8\n07: 7\n      06: 6\n    05: 5\n      04: 4\n  03: 3\n      02: 2\n    01: 1\n      00: 0\n");
	END_TEST;
}

bool test_print_empty() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	stringstream ss;
	map.print_map(ss);
	assert(ss.str() == "<empty>");
	ss.str("");
	map.print_tree(ss);
	assert(ss.str() == "<empty>");

	END_TEST;
}

bool test_copy() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map<string, int> a(map);
	assert(a.size() == map.size());

	END_TEST;
}

bool test_copy_empty() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	Map<string, int> a(map);
	assert(a.size() == 0);
	assert(a.is_empty());

	END_TEST;
}

bool test_copy_oper() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	Map<string, int> a;
	a.insert({"07", 6});
	a.insert({"03", 2});
	a.insert({"11", 10});
	a.insert({"01", 0});
	a.insert({"05", 4});
	a.insert({"09", 5});
	a.insert({"13", 12});
	a.insert({"00", -1});
	a.insert({"02", 1});
	a.insert({"04", 3});
	a.insert({"06", 5});
	a.insert({"08", 7});
	a.insert({"10", 9});
	a.insert({"12", 11});
	assert(a.size() == 14);

	a = map;
	assert(a.size() == map.size());

	END_TEST;
}

bool test_copy_oper_empty() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	Map<string, int> a;
	a.insert({"07", 6});
	a.insert({"03", 2});
	a.insert({"11", 10});
	a.insert({"01", 0});
	a.insert({"05", 4});
	a.insert({"09", 5});
	a.insert({"13", 12});
	a.insert({"00", -1});
	a.insert({"02", 1});
	a.insert({"04", 3});
	a.insert({"06", 5});
	a.insert({"08", 7});
	a.insert({"10", 9});
	a.insert({"12", 11});
	assert(a.size() == 14);

	a = map;
	assert(a.size() == 0);
	assert(a.is_empty());

	END_TEST;
}

bool test_self_assignment() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 7});
	map.insert({"03", 3});
	map.insert({"11", 11});
	map.insert({"01", 1});
	map.insert({"05", 5});
	map.insert({"09", 9});
	map.insert({"13", 13});
	map.insert({"00", 0});
	map.insert({"02", 2});
	map.insert({"04", 4});
	map.insert({"06", 6});
	map.insert({"08", 8});
	map.insert({"10", 10});
	map.insert({"12", 12});
	map.insert({"14", 14});
	assert(map.size() == 15);

	expect_no_throw(map = map);

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
	// test(remove_empty);
	// test(remove_invalid);
	// test(remove_leaf);
	// test(remove_middle);
	// test(remove_root);
	test(find);
	test(iter_end);
	test(iter_forward);
	test(iter_reverse);
	test(iter_string);
	test(const_iter_end);
	test(const_iter_forward);
	test(const_iter_reverse);
	test(const_iter_string);
	test(print_map);
	test(print_tree);
	test(print_empty);
	test(copy);
	test(copy_empty);
	test(copy_oper);
	test(copy_oper_empty);
	test(self_assignment);

	cout << "\n";
	cout << magenta << "summary:" << remap << "\n";
	cout << green << pass_cnt << " tests passing." << remap << "\n";
	cout << red << fail_cnt << " tests failing." << remap << "\n";
	cout << yellow << skip_cnt << " tests skipped." << remap << "\n";

	return 0;
}
