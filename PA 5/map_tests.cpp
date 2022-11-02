#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <tuple>
#include "my_map.h"

using std::cout;
using std::string, std::pair;
using std::runtime_error;

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

bool test_insert_in2out() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	for (int i = 64; i > -1; --i) {
		int num = i % 2 ? -i : i;
		map.insert({std::to_string(num), num >> 1});
	}

	END_TEST;
}

bool test_insert_out2in() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	for (int i = 0; i <= 64; ++i) {
		int num = i % 2 ? -i : i;
		map.insert({std::to_string(num), num >> 1});
	}

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

bool test_insert_iter_left() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	Map_const_iterator<string, int> end = map.end();
	map.insert(end, {"00", 0});
	map.insert(end, {"01", 1});
	map.insert(end, {"02", 2});
	map.insert(end, {"03", 3});
	map.insert(end, {"04", 4});
	map.insert(end, {"05", 5});
	map.insert(end, {"06", 6});
	map.insert(end, {"07", 7});
	map.insert(end, {"08", 8});
	map.insert(end, {"09", 9});
	map.insert(end, {"10", 10});
	map.insert(end, {"11", 11});
	map.insert(end, {"12", 12});
	map.insert(end, {"13", 13});
	map.insert(end, {"14", 14});
	assert(map.size() == 15);

	END_TEST;
}

bool test_insert_iter_right() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	Map_const_iterator<string, int> end = map.end();
	map.insert(end, {"14", 14});
	map.insert(end, {"13", 13});
	map.insert(end, {"12", 12});
	map.insert(end, {"11", 11});
	map.insert(end, {"10", 10});
	map.insert(end, {"09", 9});
	map.insert(end, {"08", 8});
	map.insert(end, {"07", 7});
	map.insert(end, {"06", 6});
	map.insert(end, {"05", 5});
	map.insert(end, {"04", 4});
	map.insert(end, {"03", 3});
	map.insert(end, {"02", 2});
	map.insert(end, {"01", 1});
	map.insert(end, {"00", 0});
	assert(map.size() == 15);

	END_TEST;
}

bool test_insert_random() {
	int nums[256] = {244, 63, 164, 66, 95, 33, 248, 214, 20, 35, 183, 197, 134, 73, 36, 19, 30, 109, 195, 151, 162, 240, 59, 215, 119, 145, 209, 12, 78, 106, 221, 238, 208, 135, 26, 139, 219, 232, 181, 108, 144, 251, 180, 98, 117, 255, 83, 87, 62, 234, 68, 43, 233, 196, 142, 75, 182, 88, 204, 32, 47, 254, 122, 173, 184, 86, 242, 125, 79, 93, 150, 163, 16, 31, 253, 69, 76, 100, 148, 192, 25, 82, 247, 72, 94, 141, 6, 53, 157, 48, 4, 74, 237, 131, 202, 186, 50, 27, 46, 80, 39, 8, 246, 193, 77, 45, 116, 200, 13, 218, 3, 191, 171, 55, 166, 216, 137, 107, 37, 231, 210, 91, 158, 90, 224, 2, 174, 172, 65, 136, 124, 211, 199, 160, 146, 0, 54, 189, 14, 149, 56, 1, 112, 228, 126, 24, 168, 102, 21, 153, 140, 10, 67, 132, 118, 104, 155, 89, 11, 178, 177, 190, 99, 167, 194, 105, 222, 7, 143, 236, 212, 111, 128, 249, 185, 71, 176, 243, 250, 138, 245, 15, 121, 179, 187, 18, 52, 130, 113, 42, 207, 188, 44, 114, 230, 223, 133, 22, 34, 129, 170, 203, 226, 201, 92, 101, 85, 51, 61, 115, 64, 220, 97, 217, 154, 70, 96, 110, 120, 206, 60, 29, 175, 213, 241, 17, 23, 161, 152, 103, 38, 156, 9, 41, 147, 235, 40, 252, 5, 58, 229, 169, 127, 225, 81, 205, 165, 198, 123, 28, 49, 239, 57, 159, 84, 227};
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	for (const int& num : nums)
		map.insert({std::to_string(num), num >> 1});

	for (const int& num : nums)
		map.remove(std::to_string(num));

	END_TEST;
}

bool test_remove_empty() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	assert(map.remove("00") == 0);
	assert(map.size() == 0);
	assert(map.is_empty());

	END_TEST;
}

bool test_remove_invalid() {
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

	assert(map.remove("15") == 0);
	assert(map.size() == 15);

	END_TEST;
}

bool test_remove_leaf() {
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

	assert(map.remove("14"));
	assert(map.remove("12"));
	assert(map.remove("10"));
	assert(map.remove("08"));
	assert(map.remove("06"));
	assert(map.remove("04"));
	assert(map.remove("02"));
	assert(map.remove("00"));
	assert(map.remove("13"));
	assert(map.remove("09"));
	assert(map.remove("05"));
	assert(map.remove("01"));
	assert(map.remove("11"));
	assert(map.remove("03"));
	assert(map.remove("07"));
	assert(map.size() == 0);
	assert(map.is_empty());

	END_TEST;
}

bool test_remove_middle() {
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

	assert(map.remove("13"));
	assert(map.remove("14"));
	assert(map.remove("08"));
	assert(map.remove("09"));
	assert(map.size() == 11);

	END_TEST;
}

bool test_remove_root() {
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

	assert(map.remove("07"));
	assert(map.remove("08"));
	assert(map.remove("09"));
	assert(map.remove("10"));
	assert(map.remove("11"));
	assert(map.remove("12"));
	assert(map.remove("03"));
	assert(map.remove("04"));
	assert(map.remove("05"));
	assert(map.remove("06"));
	assert(map.remove("13"));
	assert(map.remove("02"));
	assert(map.remove("01"));
	assert(map.remove("14"));
	assert(map.remove("00"));
	assert(map.size() == 0);
	assert(map.is_empty());

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

bool test_find_const() {
	Map<string, int> m;
	assert(m.size() == 0);
	assert(m.is_empty());

	m.insert({"07", 7});
	m.insert({"03", 3});
	m.insert({"11", 11});
	m.insert({"01", 1});
	m.insert({"05", 5});
	m.insert({"09", 9});
	m.insert({"13", 13});
	m.insert({"00", 0});
	m.insert({"02", 2});
	m.insert({"04", 4});
	m.insert({"06", 6});
	m.insert({"08", 8});
	m.insert({"10", 10});
	m.insert({"12", 12});
	m.insert({"14", 14});
	assert(m.size() == 15);

	const Map<string, int> map(m);
	Map_const_iterator end = map.end();
	assert(map.find("00") != end);
	assert(map.find("01") != end);
	assert(map.find("02") != end);
	assert(map.find("03") != end);
	assert(map.find("04") != end);
	assert(map.find("05") != end);
	assert(map.find("06") != end);
	assert(map.find("07") != end);
	assert(map.find("08") != end);
	assert(map.find("09") != end);
	assert(map.find("10") != end);
	assert(map.find("11") != end);
	assert(map.find("12") != end);
	assert(map.find("13") != end);
	assert(map.find("14") != end);

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
	ss.clear();
	ss.str("");
	iter = map.end();
	ss << iter.to_string();

	END_TEST;
}

bool test_iter_empty() {
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

	Map_iterator<string, int> iter(map.find("07"));
	map.make_empty();
	iter = map.begin();
	expect_throw(*iter, runtime_error);

	END_TEST;
}

bool test_iter_remove_leaf() {
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

	Map_const_iterator<string, int> index = map.find("14");
	Map_iterator<string, int> iter = map.remove(index);
	expect_throw(*iter, runtime_error);
	expect_throw(iter->first, runtime_error);
	expect_throw(iter->second, runtime_error);

	index = map.find("12");
	iter = map.remove(index);
	assert(iter->first == "13");
	assert(iter->second == 13);

	index = map.find("10");
	iter = map.remove(index);
	assert(iter->first == "11");
	assert(iter->second == 11);

	index = map.find("08");
	iter = map.remove(index);
	assert(iter->first == "09");
	assert(iter->second == 9);

	index = map.find("06");
	iter = map.remove(index);
	assert(iter->first == "07");
	assert(iter->second == 7);

	index = map.find("04");
	iter = map.remove(index);
	assert(iter->first == "05");
	assert(iter->second == 5);

	index = map.find("02");
	iter = map.remove(index);
	assert(iter->first == "03");
	assert(iter->second == 3);

	index = map.find("00");
	iter = map.remove(index);
	assert(iter->first == "01");
	assert(iter->second == 1);

	index = map.find("13");
	iter = map.remove(index);
	expect_throw(*iter, runtime_error);
	expect_throw(iter->first, runtime_error);
	expect_throw(iter->second, runtime_error);

	index = map.find("09");
	iter = map.remove(index);
	assert(iter->first == "11");
	assert(iter->second == 11);

	index = map.find("05");
	iter = map.remove(index);
	assert(iter->first == "07");
	assert(iter->second == 7);

	index = map.find("01");
	iter = map.remove(index);
	assert(iter->first == "03");
	assert(iter->second == 3);

	index = map.find("11");
	iter = map.remove(index);
	expect_throw(*iter, runtime_error);
	expect_throw(iter->first, runtime_error);
	expect_throw(iter->second, runtime_error);

	index = map.find("03");
	iter = map.remove(index);
	assert(iter->first == "07");
	assert(iter->second == 7);

	index = map.find("07");
	iter = map.remove(index);
	expect_throw(*iter, runtime_error);
	expect_throw(iter->first, runtime_error);
	expect_throw(iter->second, runtime_error);

	END_TEST;
}

bool test_iter_remove_middle() {
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

	Map_const_iterator<string, int> index = map.find("13");
	Map_iterator<string, int> iter = map.remove(index);
	assert(iter->first == "14");
	assert(iter->second == 14);

	index = map.find("12");
	iter = map.remove(index);
	assert(iter->first == "14");
	assert(iter->second == 14);

	assert(map.remove("08"));
	index = map.find("09");
	iter = map.remove(index);
	assert(iter->first == "10");
	assert(iter->second == 10);

	assert(map.size() == 11);

	END_TEST;
}

bool test_iter_remove_root() {
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

	Map_const_iterator<string, int> index = map.find("07");
	Map_iterator<string, int> iter = map.remove(index);
	assert(iter->first == "08");
	assert(iter->second == 8);

	index = map.find("08");
	iter = map.remove(index);
	assert(iter->first == "09");
	assert(iter->second == 9);

	index = map.find("09");
	iter = map.remove(index);
	assert(iter->first == "10");
	assert(iter->second == 10);

	index = map.find("10");
	iter = map.remove(index);
	assert(iter->first == "11");
	assert(iter->second == 11);

	index = map.find("11");
	iter = map.remove(index);
	assert(iter->first == "12");
	assert(iter->second == 12);

	index = map.find("12");
	iter = map.remove(index);
	assert(iter->first == "13");
	assert(iter->second == 13);

	index = map.find("05");
	iter = map.remove(index);
	assert(iter->first == "06");
	assert(iter->second == 6);

	index = map.find("06");
	iter = map.remove(index);
	assert(iter->first == "13");
	assert(iter->second == 13);

	index = map.find("03");
	iter = map.remove(index);
	assert(iter->first == "04");
	assert(iter->second == 4);

	index = map.find("04");
	iter = map.remove(index);
	assert(iter->first == "13");
	assert(iter->second == 13);

	index = map.find("13");
	iter = map.remove(index);
	assert(iter->first == "14");
	assert(iter->second == 14);

	index = map.find("02");
	iter = map.remove(index);
	assert(iter->first == "14");
	assert(iter->second == 14);

	index = map.find("01");
	iter = map.remove(index);
	assert(iter->first == "14");
	assert(iter->second == 14);

	index = map.find("14");
	iter = map.remove(index);
	expect_throw(*iter, runtime_error);
	expect_throw(iter->first, runtime_error);
	expect_throw(iter->second, runtime_error);

	index = map.find("00");
	iter = map.remove(index);
	expect_throw(*iter, runtime_error);
	expect_throw(iter->first, runtime_error);
	expect_throw(iter->second, runtime_error);

	assert(map.size() == 0);
	assert(map.is_empty());


	END_TEST;
}

bool test_iter_remove_empty() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	Map_const_iterator<string, int> index = map.end();
	Map_iterator<string, int> iter = map.remove(index);
	expect_throw(*iter, runtime_error);

	index = map.begin();
	iter = map.remove(index);
	expect_throw(*iter, runtime_error);

	END_TEST;
}

bool test_iter_remove_invalid() {
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

	Map_const_iterator<string, int> index = map.end();
	expect_throw(map.remove(index), invalid_argument);

	Map_Node<string, int> node({"15", 15}, Color::RED);
	index = &node;
	expect_throw(map.remove(index), invalid_argument);

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
	cout << ss.str() << "\n";

	ss.clear();
	ss.str("");

	iter = map.end();
	ss << iter.to_string();
	cout << ss.str() << "\n";

	END_TEST;
}

bool test_at() {
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

	assert(map.at("00") == 0);
	assert(map.at("01") == 1);
	assert(map.at("02") == 2);
	assert(map.at("03") == 3);
	assert(map.at("04") == 4);
	assert(map.at("05") == 5);
	assert(map.at("06") == 6);
	assert(map.at("07") == 7);
	assert(map.at("08") == 8);
	assert(map.at("09") == 9);
	assert(map.at("10") == 10);
	assert(map.at("11") == 11);
	assert(map.at("12") == 12);
	assert(map.at("13") == 13);
	assert(map.at("14") == 14);

	END_TEST;
}

bool test_at_invalid() {
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

	expect_throw(map.at("15"), out_of_range);

	END_TEST;
}

bool test_at_set() {
	Map<string, int> map;
	assert(map.size() == 0);
	assert(map.is_empty());

	map.insert({"07", 0});
	map.insert({"03", 0});
	map.insert({"11", 0});
	map.insert({"01", 0});
	map.insert({"05", 0});
	map.insert({"09", 0});
	map.insert({"13", 0});
	map.insert({"00", 0});
	map.insert({"02", 0});
	map.insert({"04", 0});
	map.insert({"06", 0});
	map.insert({"08", 0});
	map.insert({"10", 0});
	map.insert({"12", 0});
	map.insert({"14", 0});

	expect_no_throw(map.at("00") = 0);
	expect_no_throw(map.at("01") = 1);
	expect_no_throw(map.at("02") = 2);
	expect_no_throw(map.at("03") = 3);
	expect_no_throw(map.at("04") = 4);
	expect_no_throw(map.at("05") = 5);
	expect_no_throw(map.at("06") = 6);
	expect_no_throw(map.at("07") = 7);
	expect_no_throw(map.at("08") = 8);
	expect_no_throw(map.at("09") = 9);
	expect_no_throw(map.at("10") = 10);
	expect_no_throw(map.at("11") = 11);
	expect_no_throw(map.at("12") = 12);
	expect_no_throw(map.at("13") = 13);
	expect_no_throw(map.at("14") = 14);

	assert(map.at("00") == 0);
	assert(map.at("01") == 1);
	assert(map.at("02") == 2);
	assert(map.at("03") == 3);
	assert(map.at("04") == 4);
	assert(map.at("05") == 5);
	assert(map.at("06") == 6);
	assert(map.at("07") == 7);
	assert(map.at("08") == 8);
	assert(map.at("09") == 9);
	assert(map.at("10") == 10);
	assert(map.at("11") == 11);
	assert(map.at("12") == 12);
	assert(map.at("13") == 13);
	assert(map.at("14") == 14);

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
	cout << ss.str() << "\n";

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
	cout << ss.str() << "\n";
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

bool test_node() {
	Map_Node<string, int> node({"Hello", INT32_MAX}, static_cast<Color>(4));
	assert(node.sibling() == nullptr);

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
	test(at);
	test(at_invalid);
	test(at_set);
	test(print_map);
	test(print_tree);
	test(print_empty);
	test(copy);
	test(copy_empty);
	test(copy_oper);
	test(copy_oper_empty);
	test(self_assignment);
	test(node);

	cout << "\n";
	cout << magenta << "summary:" << remap << "\n";
	cout << green << pass_cnt << " tests passing." << remap << "\n";
	cout << red << fail_cnt << " tests failing." << remap << "\n";
	cout << yellow << skip_cnt << " tests skipped." << remap << "\n";

	return 0;
}
