#include <functional>
#include <iostream>
#include <vector>
#include <utility>
#include "sorts.h"

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

bool test_selection() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    selection_sort(vect);
    END_TEST;
}

bool test_selection_empty() {
    vector<int> vect{};

    selection_sort(vect);
    END_TEST;
}

bool test_insert() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    insertion_sort(vect);
    END_TEST;
}

bool test_insert_empty() {
    vector<int> vect{};

    insertion_sort(vect);
    END_TEST;
}

bool test_shell() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    shell_sort(vect);
    END_TEST;
}

bool test_shell_empty() {
    vector<int> vect{};

    shell_sort(vect);
    END_TEST;
}

bool test_heap() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    heap_sort(vect);
    END_TEST;
}

bool test_heap_empty() {
    vector<int> vect{};

    heap_sort(vect);
    END_TEST;
}

bool test_merge() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    merge_sort(vect);
    END_TEST;
}

bool test_merge_empty() {
    vector<int> vect{};

    merge_sort(vect);
    END_TEST;
}

bool test_quick() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    quick_sort(vect);
    END_TEST;
}

bool test_quick_empty() {
    vector<int> vect{};

    quick_sort(vect);
    END_TEST;
}

bool test_bucket() {
    vector<unsigned int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    bucket_sort(vect);
    END_TEST;
}

bool test_bucket_empty() {
    vector<unsigned int> vect{};

    bucket_sort(vect);
    END_TEST;
}

bool test_radix() {
    vector<int> vect{9, 4, 3, 1, 7, 8, 0, 5, 6, 2};

    radix_sort(vect);
    END_TEST;
}

bool test_radix_empty() {
    vector<int> vect{};

    radix_sort(vect);
    END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(selection);
    test(selection_empty);
    test(insert);
    test(insert_empty);
    test(shell);
    test(shell_empty);
    test(heap);
    test(heap_empty);
    test(merge);
    test(merge_empty);
    test(quick);
    test(quick_empty);
    test(bucket);
    test(bucket_empty);
    test(radix);
    test(radix_empty);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
