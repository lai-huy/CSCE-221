#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "hashtable_separate_chaining.h"

using std::cout, std::stringstream;
using std::hash;
using std::invalid_argument;

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
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	END_TEST;
}

bool test_create_size() {
	HashTable<int, hash<int>> table(13);
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 13);

	END_TEST;
}

bool test_create_size_invalid() {
	try {
		HashTable<int, hash<int>> table(0);
	} catch (const invalid_argument& err) {
		assert(true);
	} catch (...) {
		assert(false);
	}
	END_TEST;
}

bool test_insert() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	assert(table.insert(0));
	assert(table.size() == 1);
	assert(table.bucket_count() == 11);

	assert(table.insert(1));
	assert(table.size() == 2);
	assert(table.bucket_count() == 11);

	assert(table.insert(2));
	assert(table.size() == 3);
	assert(table.bucket_count() == 11);

	assert(table.insert(3));
	assert(table.size() == 4);
	assert(table.bucket_count() == 11);

	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.bucket_count() == 11);

	assert(table.insert(5));
	assert(table.size() == 6);
	assert(table.bucket_count() == 11);

	assert(table.insert(6));
	assert(table.size() == 7);
	assert(table.bucket_count() == 11);

	assert(table.insert(7));
	assert(table.size() == 8);
	assert(table.bucket_count() == 11);

	assert(table.insert(8));
	assert(table.size() == 9);
	assert(table.bucket_count() == 11);

	assert(table.insert(9));
	assert(table.size() == 10);
	assert(table.bucket_count() == 11);

	assert(table.insert(10));
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	END_TEST;
}

bool test_insert_rehash() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	assert(table.insert(11));
	assert(table.size() == 12);
	assert(table.bucket_count() == 23);

	assert(table.insert(12));
	assert(table.size() == 13);
	assert(table.bucket_count() == 23);

	assert(table.insert(13));
	assert(table.size() == 14);
	assert(table.bucket_count() == 23);

	assert(table.insert(14));
	assert(table.size() == 15);
	assert(table.bucket_count() == 23);

	assert(table.insert(15));
	assert(table.size() == 16);
	assert(table.bucket_count() == 23);

	assert(table.insert(16));
	assert(table.size() == 17);
	assert(table.bucket_count() == 23);

	assert(table.insert(17));
	assert(table.size() == 18);
	assert(table.bucket_count() == 23);

	assert(table.insert(18));
	assert(table.size() == 19);
	assert(table.bucket_count() == 23);

	assert(table.insert(19));
	assert(table.size() == 20);
	assert(table.bucket_count() == 23);

	assert(table.insert(20));
	assert(table.size() == 21);
	assert(table.bucket_count() == 23);

	assert(table.insert(21));
	assert(table.size() == 22);
	assert(table.bucket_count() == 23);

	assert(table.insert(22));
	assert(table.size() == 23);
	assert(table.bucket_count() == 23);

	assert(table.insert(24));
	assert(table.size() == 24);
	assert(table.bucket_count() == 47);

	for (int i = 25; i < INT8_MAX; ++i)
		assert(table.insert(i));

	END_TEST;
}

bool test_insert_conflict_rehash() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	assert(table.insert(0));
	assert(table.insert(11));
	assert(table.insert(22));
	assert(table.insert(33));
	assert(table.insert(44));
	assert(table.insert(55));
	assert(table.insert(66));
	assert(table.insert(77));
	assert(table.insert(88));
	assert(table.insert(99));
	assert(table.insert(110));
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	assert(table.insert(121));
	assert(table.size() == 12);
	assert(table.bucket_count() == 23);


	END_TEST;
}

bool test_insert_dup() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	assert(!table.insert(0));

	END_TEST;
}

bool test_remove() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);

	assert(table.remove(0) == 1);

	END_TEST;
}

bool test_remove_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	assert(table.remove(0) == 0);

	END_TEST;
}

bool test_remove_invalid() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);

	assert(table.remove(11) == 0);

	END_TEST;
}

bool test_contains() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);

	assert(table.contains(0));
	assert(table.contains(1));
	assert(table.contains(2));
	assert(table.contains(3));
	assert(table.contains(4));
	assert(table.contains(5));
	assert(table.contains(6));
	assert(table.contains(7));
	assert(table.contains(8));
	assert(table.contains(9));
	assert(table.contains(10));
	assert(!table.contains(11));

	END_TEST;
}

bool test_load_factor() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(2);
	table.insert(4);
	table.insert(6);
	table.insert(8);
	table.insert(10);

	expect_no_throw(table.load_factor());

	END_TEST;
}

bool test_mlf() {
	HashTable<int, hash<int>> table;

	expect_no_throw(table.max_load_factor(1.0f));

	END_TEST;
}

bool test_mlf_invalid() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	expect_throw(table.max_load_factor(-1.0f), invalid_argument);
	expect_throw(table.max_load_factor(1 / 0.0f), invalid_argument);
	expect_throw(table.max_load_factor(1 / -0.0f), invalid_argument);
	expect_throw(table.max_load_factor(0.0f / 0.0f), invalid_argument);

	END_TEST;
}

bool test_mlf_rehash() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);
	table.max_load_factor(2.0f);

	for (int i = 0; i < 22; ++i)
		table.insert(i);
	assert(table.size() == 22);
	assert(table.bucket_count() == 11);

	expect_no_throw(table.max_load_factor(1.0f));
	assert(table.size() == 22);
	assert(table.bucket_count() == 23);

	END_TEST;
}

bool test_rehash_smaller() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	assert(table.insert(0));
	assert(table.insert(3));
	assert(table.insert(7));
	assert(table.size() == 3);
	assert(table.bucket_count() == 11);

	expect_no_throw(table.rehash(7));
	assert(table.size() == 3);
	assert(table.bucket_count() == 7);

	END_TEST;
}

bool test_rehash_smaller_mlf() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);
	expect_no_throw(table.max_load_factor(.5f));

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.bucket_count() == 11);
	assert(table.load_factor() < table.max_load_factor());

	expect_no_throw(table.rehash(5));
	assert(table.size() == 5);
	assert(table.bucket_count() == 11);

	END_TEST;
}

bool test_print() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(2);
	table.insert(4);
	table.insert(6);
	table.insert(8);
	table.insert(10);
	table.insert(11);

	table.print_table();

	END_TEST;
}

bool test_print_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	stringstream ss;
	table.print_table(ss);
	assert(ss.str() == "<empty>\n");

	END_TEST;
}

bool test_copy() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	HashTable<int, hash<int>> a(table);
	assert(a.size() == table.size());
	assert(a.bucket_count() == table.bucket_count());
	assert(a.max_load_factor() == table.max_load_factor());

	END_TEST;
}

bool test_copy_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	HashTable<int, hash<int>> a(table);
	assert(a.size() == table.size());
	assert(a.bucket_count() == table.bucket_count());
	assert(a.max_load_factor() == table.max_load_factor());
	assert(a.is_empty());

	END_TEST;
}

bool test_assignment() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	HashTable<int, hash<int>> a(7);
	a.max_load_factor(2.0f);
	assert(a.size() == 0);
	assert(a.is_empty());
	assert(a.bucket_count() == 7);

	a.insert(0);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(5);
	a.insert(6);
	a.insert(7);
	a.insert(8);
	a.insert(9);
	a.insert(10);
	a.insert(11);
	a.insert(12);
	a.insert(13);

	a = table;
	assert(a.size() == table.size());
	assert(a.bucket_count() == table.bucket_count());
	assert(a.max_load_factor() == table.max_load_factor());

	END_TEST;
}

bool test_assignment_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	HashTable<int, hash<int>> a(7);
	a.max_load_factor(2.0f);
	assert(a.size() == 0);
	assert(a.is_empty());
	assert(a.bucket_count() == 7);

	a.insert(0);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(5);
	a.insert(6);
	a.insert(7);
	a.insert(8);
	a.insert(9);
	a.insert(10);
	a.insert(11);
	a.insert(12);
	a.insert(13);

	a = table;
	assert(a.size() == table.size());
	assert(a.bucket_count() == table.bucket_count());
	assert(a.max_load_factor() == table.max_load_factor());

	END_TEST;
}

bool test_self_assignment() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.bucket_count() == 11);

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);
	table.insert(5);
	table.insert(6);
	table.insert(7);
	table.insert(8);
	table.insert(9);
	table.insert(10);
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	table = table;
	assert(table.size() == 11);
	assert(table.bucket_count() == 11);

	END_TEST;
}

/*
bool test_next_prime() {
	HashTable<int, hash<int>> table;
	size_t prime = 0;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < INT16_MAX; ++i) {
		table.insert(table.bucket_count() * i);
		if (table.bucket_count() != prime) {
			prime = table.bucket_count();
			cout << prime << "\n";
		}
	}
	auto end = high_resolution_clock::now();
	cout << "Time:\t" << duration_cast<milliseconds>(end - start).count() << "\n";

	END_TEST;
}*/

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(create_size);
	test(create_size_invalid);
	test(insert);
	test(insert_rehash);
	test(insert_dup);
	test(insert_conflict_rehash);
	test(remove);
	test(remove_empty);
	test(remove_invalid);
	test(contains);
	test(rehash_smaller);
	test(rehash_smaller_mlf);
	test(load_factor);
	test(mlf);
	test(mlf_invalid);
	test(mlf_rehash);
	test(print);
	test(print_empty);
	test(copy);
	test(copy_empty);
	test(assignment);
	test(assignment_empty);
	test(self_assignment);
	// test(next_prime);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
