#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <chrono>
#include "hashtable_open_addressing.h"

using std::cout, std::stringstream;
using std::invalid_argument;
using namespace std::chrono;

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
	assert(table.table_size() == 11);

	END_TEST;
}

bool test_create_size() {
	HashTable<int, hash<int>> table(11);
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

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
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	END_TEST;
}

bool test_insert_rehash() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	assert(table.insert(5));
	assert(table.size() == 6);
	assert(table.table_size() == 23);

	for (int i = 6; i < 64; ++i)
		assert(table.insert(i));

	END_TEST;
}

bool test_insert_dup() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.insert(5));
	assert(table.insert(6));
	assert(table.insert(7));
	assert(table.insert(8));
	assert(table.insert(9));
	assert(table.insert(10));

	assert(!table.insert(0));
	assert(!table.insert(1));
	assert(!table.insert(2));
	assert(!table.insert(3));
	assert(!table.insert(4));
	assert(!table.insert(5));
	assert(!table.insert(6));
	assert(!table.insert(7));
	assert(!table.insert(8));
	assert(!table.insert(9));
	assert(!table.insert(10));

	END_TEST;
}

bool test_insert_conflict() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.size() == 1);
	assert(table.table_size() == 11);

	assert(table.insert(11));
	assert(table.size() == 2);
	assert(table.table_size() == 11);

	assert(table.insert(22));
	assert(table.size() == 3);
	assert(table.table_size() == 11);

	assert(table.insert(33));
	assert(table.size() == 4);
	assert(table.table_size() == 11);

	assert(table.insert(44));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	END_TEST;
}

bool test_insert_conflict_rehash() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.size() == 1);
	assert(table.table_size() == 11);

	assert(table.insert(11));
	assert(table.size() == 2);
	assert(table.table_size() == 11);

	assert(table.insert(22));
	assert(table.size() == 3);
	assert(table.table_size() == 11);

	assert(table.insert(33));
	assert(table.size() == 4);
	assert(table.table_size() == 11);

	assert(table.insert(44));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	assert(table.insert(55));
	assert(table.size() == 6);
	assert(table.table_size() == 23);

	END_TEST;
}

bool test_remove() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.insert(5));
	assert(table.insert(6));
	assert(table.insert(7));
	assert(table.insert(8));
	assert(table.insert(9));
	assert(table.insert(10));

	assert(table.remove(0));
	assert(table.remove(1));
	assert(table.remove(2));
	assert(table.remove(3));
	assert(table.remove(4));
	assert(table.remove(5));
	assert(table.remove(6));
	assert(table.remove(7));
	assert(table.remove(8));
	assert(table.remove(9));
	assert(table.remove(10));

	END_TEST;
}

bool test_remove_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(!table.remove(0));

	END_TEST;
}

bool test_remove_invalid() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.insert(5));
	assert(table.insert(6));
	assert(table.insert(7));
	assert(table.insert(8));
	assert(table.insert(9));
	assert(table.insert(10));

	assert(!table.remove(32));

	END_TEST;
}

bool test_remove_middle() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	table.insert(3);
	table.insert(14);
	table.insert(25);
	table.insert(36);
	table.insert(47);
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	table.remove(25);
	assert(table.size() == 4);
	assert(table.table_size() == 11);


	END_TEST;
}

bool test_undelete() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	assert(table.remove(0));
	assert(table.size() == 4);
	assert(table.table_size() == 11);

	assert(table.remove(1));
	assert(table.size() == 3);
	assert(table.table_size() == 11);

	assert(table.remove(2));
	assert(table.size() == 2);
	assert(table.table_size() == 11);

	assert(table.remove(3));
	assert(table.size() == 1);
	assert(table.table_size() == 11);

	assert(table.remove(4));
	assert(table.size() == 0);
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	END_TEST;
}

bool test_undelete_conflict() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.insert(11));
	assert(table.insert(22));
	assert(table.size() == 3);
	assert(table.table_size() == 11);

	assert(table.remove(0));
	assert(table.insert(33));
	assert(!table.contains(0));
	assert(table.contains(11));
	assert(table.contains(22));
	assert(table.contains(33));

	END_TEST;
}

bool test_contains() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	assert(table.contains(0));
	assert(table.contains(1));
	assert(table.contains(2));
	assert(table.contains(3));
	assert(table.contains(4));
	assert(!table.contains(5));

	END_TEST;
}

bool test_position_undelete() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	assert(table.position(0) == 0);
	table.insert(0);
	assert(table.size() == 1);
	assert(table.table_size() == 11);

	assert(table.position(11) == 1);
	table.insert(11);
	assert(table.size() == 2);
	assert(table.table_size() == 11);

	table.remove(0);
	assert(table.size() == 1);
	assert(table.table_size() == 11);

	assert(table.position(22) == 2);
	table.insert(22);
	assert(table.size() == 2);
	assert(table.table_size() == 11);

	table.remove(11);
	assert(table.size() == 1);
	assert(table.table_size() == 11);

	assert(table.position(33) == 3);
	table.insert(33);
	assert(table.size() == 2);
	assert(table.table_size() == 11);

	assert(table.position(0) == 0);
	table.insert(0);
	assert(table.size() == 3);
	assert(table.table_size() == 11);

	assert(table.position(11) == 1);
	table.insert(11);
	assert(table.size() == 4);
	assert(table.table_size() == 11);

	assert(table.position(44) == 4);
	table.insert(44);
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	assert(table.position(0) == 0);

	END_TEST;
}

bool test_print() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());

	assert(table.insert(0));
	assert(table.insert(1));
	assert(table.insert(2));
	assert(table.insert(3));
	assert(table.insert(4));
	assert(table.size() == 5);
	assert(table.table_size() == 11);

	expect_no_throw(table.print_table());

	END_TEST;
}

bool test_print_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());

	stringstream ss;
	table.print_table(ss);
	assert(ss.str() == "<empty>\n");

	END_TEST;
}

bool test_copy() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.table_size() == 11);
	assert(table.is_empty());

	table.insert(0);
	table.insert(1);
	table.insert(2);
	table.insert(3);
	table.insert(4);

	HashTable<int, hash<int>> a(table);
	assert(a.size() == table.size());
	assert(a.table_size() == table.table_size());

	END_TEST;
}

bool test_copy_empty() {
	HashTable<int, hash<int>> table;
	assert(table.size() == 0);
	assert(table.is_empty());
	assert(table.table_size() == 11);

	HashTable<int, hash<int>> a(table);
	assert(a.size() == table.size());
	assert(a.is_empty() == table.is_empty());
	assert(a.table_size() == table.table_size());

	END_TEST;
}

bool test_next_prime() {
	HashTable<int, hash<int>> table;
	size_t prime = 0;
	auto start = high_resolution_clock::now();
	for (int i = 0; i < INT16_MAX; ++i) {
		table.insert(table.table_size() * i);
		if (table.table_size() != prime) {
			prime = table.table_size();
			cout << prime << "\n";
		}
	}
	auto end = high_resolution_clock::now();
	cout << "Time:\t" << duration_cast<microseconds>(end - start).count() << "\n";

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	// test(create);
	// test(create_size);
	// test(create_size_invalid);
	// test(insert);
	// test(insert_rehash);
	// test(insert_dup);
	// test(insert_conflict);
	// test(insert_conflict_rehash);
	// test(remove);
	// test(remove_empty);
	// test(remove_invalid);
	// test(remove_middle);
	// test(undelete);
	// test(undelete_conflict);
	// test(position_undelete);
	// test(contains);
	// test(print);
	// test(print_empty);
	// test(copy);
	// test(copy_empty);
	test(next_prime);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}