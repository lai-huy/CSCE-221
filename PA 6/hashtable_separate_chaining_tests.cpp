#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "hashtable_separate_chaining.h"

using std::cout, std::stringstream;
using std::hash;

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

	cout << table.load_factor() << "\n";

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
	assert(ss.str() == "<empty>");

	END_TEST;
}

bool test_example() {
	cout << "make an empty hash table with 11 buckets for strings\n";
	HashTable<std::string> table(11);
	cout << "initial size is " << table.size() << "\n";
	cout << "initial bucket count is " << table.bucket_count() << "\n";
	cout << "initial load factor is " << table.load_factor() << "\n";
	cout << "initial max load factor is " << table.max_load_factor() << "\n";
	cout << "insert several strings\n";
	table.insert("And them who hold High Places");
	table.insert("Must be the ones to start");
	table.insert("To mold a new Reality");
	table.insert("Closer to the Heart");
	table.insert("The Blacksmith and the Artist");
	table.insert("Reflect it in their Art");
	table.insert("Forge their Creativity");
	table.insert("Closer to the Heart");
	table.insert("Philosophers and Plowmen");
	table.insert("Each must know their Part");
	table.insert("To sow a new Mentality");
	table.insert("Closer to the Heart");
	table.insert("You can be the Captain");
	table.insert("I will draw the Chart");
	table.insert("Sailing into Destiny");
	table.insert("Closer to the Heart");
	cout << "size is " << table.size() << "\n";
	cout << "bucket count is " << table.bucket_count() << "\n";
	cout << "load factor is " << table.load_factor() << "\n";
	cout << "max load factor is " << table.max_load_factor() << "\n";
	{
		cout << "print the table\n";
		std::stringstream ss;
		table.print_table(ss);
		cout << ss.str() << "\n";
	}
	cout << "remove \"Philosophers and Plowmen\"\n";
	table.remove("Philosophers and Plowmen");
	cout << "remove \"Each must know their Part\"\n";

	table.remove("Each must know their Part");
	cout << "size is " << table.size() << "\n";
	cout << "bucket count is " << table.bucket_count() << "\n";
	cout << "load factor is " << table.load_factor() << "\n";
	cout << "max load factor is " << table.max_load_factor() << "\n";
	{
		cout << "print the table\n";
		std::stringstream ss;
		table.print_table(ss);
		cout << ss.str() << "\n";
	}
	cout << "set max load factor to 2\n";
	table.max_load_factor(2);
	cout << "rehash the table to size 7\n";
	table.rehash(7);
	cout << "size is " << table.size() << "\n";
	cout << "bucket count is " << table.bucket_count() << "\n";
	cout << "load factor is " << table.load_factor() << "\n";
	cout << "max load factor is " << table.max_load_factor() << "\n";
	{
		cout << "print the table\n";
		std::stringstream ss;
		table.print_table(ss);
		cout << ss.str() << "\n";
	}
	cout << "find \"The Blacksmith and the Artist\"\n";
	size_t index = table.bucket("The Blacksmith and the Artist");
	cout << " ==> bucket " << index << "\n";
	cout << "     which has " << table.bucket_size(index) << " elements" <<
		"\n";
	cout << "make the table empty\n";
	table.make_empty();
	cout << "size is " << table.size() << "\n";
	cout << "bucket count is " << table.bucket_count() << "\n";
	cout << "load factor is " << table.load_factor() << "\n";
	cout << "max load factor is " << table.max_load_factor() << "\n";

	{
		cout << "print the table\n";
		std::stringstream ss;
		table.print_table(ss);
		cout << ss.str() << "\n";
	}

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(create_size);
	test(insert);
	test(insert_rehash);
	test(insert_dup);
	test(remove);
	test(remove_empty);
	test(remove_invalid);
	test(contains);
	test(load_factor);
	test(print);
	test(print_empty);
	// test(example);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
