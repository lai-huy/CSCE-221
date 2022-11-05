#include <functional>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "heap.h"

using std::cout, std::ostream;
using std::vector;
using std::less, std::greater;

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

template <typename Object>
void print(const vector<Object>& vect, ostream& os = cout) {
    for (const Object& obj : vect)
        os << obj << " ";
    os << "\n";
}

bool test_heapify() {
    vector<int> heap = {3, 2, 4, 1, 5, 9};
    print(heap);

    heapify(&heap, less<int>{});
    print(heap);

    END_TEST;
}

bool test_min() {
    vector<int> heap = {3, 2, 4, 1, 5, 9};
    heapify(heap, less<int>{});

    assert(heap_get_min(heap) == 1);

    END_TEST;
}

bool test_min_empty() {
    vector<int> heap;
    expect_throw(heap_get_min(heap), invalid_argument);
    END_TEST;
}

bool test_delete_min() {
    vector<int> heap = {3, 2, 4, 1, 5, 9};
    less<int> comp{};
    heapify(heap, comp);

    heap_delete_min(heap, comp);
    print(heap);
    END_TEST;
}

bool test_delete_min_empty() {
    vector<int> heap;
    expect_throw(heap_delete_min(heap, less<int>{}), invalid_argument);
    END_TEST;
}

bool test_example() {
    vector<int> heap{150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};
    cout << "before heapify: ";
    for (int i : heap) { cout << i << " "; }
    cout << std::endl;
    heapify(&heap);
    cout << "after heapify: ";
    for (int i : heap) { cout << i << " "; }
    cout << std::endl;
    for (unsigned j = 0; j < 4; j++) {
        cout << "minimum is " << heap_get_min(heap) << std::endl;
        cout << "delete min" << std::endl;
        heap_delete_min(&heap);
        cout << "heap: ";
        for (int i : heap) { cout << i << " "; }
        cout << std::endl;
    }
    int values[] = {47,54,57,43,120,3};
    for (unsigned j = 0; j < 6; j++) {
        cout << "insert " << values[j] << std::endl;
        heap_insert(&heap, values[j]);
        cout << "heap: ";
        for (int i : heap) { cout << i << " "; }
        cout << std::endl;
    }

    END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(heapify);
    test(min);
    test(min_empty);
    test(delete_min);
    test(delete_min_empty);
    test(example);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
