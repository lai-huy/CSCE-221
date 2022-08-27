#include <iostream>
#include "queue.h"

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
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << "." << reset << "\n";\
    test_passed = false;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
}

#define assert(X) try {\
  if (!(X)) {\
    std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "failed assertion that " << #X << "." << reset << "\n";\
    test_passed = false;\
    END_TEST;\
  }\
} catch(...) {\
  std::cout << red "  [fail]" reset " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << #X << " assertion threw an unexpected exception." << reset << "\n";\
  test_passed = false;\
  END_TEST;\
}

#define expect_throw(X,E) {\
  bool threw_expected_exception = false;\
  try { X; }\
  catch(const E& err) {\
    threw_expected_exception = true;\
  } catch(...) {\
    std::cout << blue << "  [help] " << #X << " threw an incorrect exception." << reset << "\n";\
  }\
  if (!threw_expected_exception) {\
    std::cout << red <<"  [fail]" << reset << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " to throw " << #E <<"." << reset <<"\n";\
    test_passed = false;\
  }\
}

#define expect_no_throw(X) {\
  try { X; }\
  catch(...) {\
    std::cout << red << "  [fail]" << red << " (" << __FILE__ << ":" << __FUNCTION__ << ":" << __LINE__ << ") " << red << "expected " << #X << " not to throw an excpetion." << reset << "\n";\
    test_passed = false;\
  }\
}

#define test(x) if (test_##x()) { std::cout << green << "[PASS] "; pass_cnt++; }\
else { std::cout << red << "[FAIL] "; fail_cnt++; }\
std::cout << #x << reset << "\n";
#define skip(x) std::cout << yellow << "[SKIP] " << #x << reset << "\n"; skip_cnt++;

#define to_be ==
#define not_to_be !=
#define is to_be
#define is_not not_to_be

namespace {
	bool test_passed = true;
}

bool test_create() {
	Queue<int> queue;
	assert(queue.size() is 0);

	END_TEST;
}

bool test_enqueue() {
	Queue<int> queue;
	assert(queue.size() is 0);

	queue.enqueue(0);
	assert(queue.size() is 1);

	queue.enqueue(1);
	assert(queue.size() is 2);

	queue.enqueue(2);
	assert(queue.size() is 3);

	queue.enqueue(3);
	assert(queue.size() is 4);

	END_TEST;
}

bool test_dequeue() {
	Queue<int> queue;
	assert(queue.size() is 0);

	queue.enqueue(0);
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	assert(queue.size() is 4);

	assert(queue.dequeue() is 0);
	assert(queue.size() is 3);

	assert(queue.dequeue() is 1);
	assert(queue.size() is 2);

	assert(queue.dequeue() is 2);
	assert(queue.size() is 1);

	assert(queue.dequeue() is 3);
	assert(queue.size() is 0);

	END_TEST;
}

bool test_dequeue_empty() {
	Queue<int> queue;
	assert(queue.size() is 0);

	expect_throw(queue.dequeue(), out_of_range);

	END_TEST;
}

bool test_front() {
	Queue<int> queue;
	assert(queue.size() is 0);

	queue.enqueue(0);
	assert(queue.front() is 0);

	queue.enqueue(1);
	assert(queue.front() is 0);

	queue.enqueue(2);
	assert(queue.front() is 0);

	queue.enqueue(3);
	assert(queue.front() is 0);

	END_TEST;
}

bool test_front_empty() {
	Queue<int> queue;
	assert(queue.size() is 0);

	expect_throw(queue.front(), out_of_range);

	END_TEST;
}

bool test_copy() {
	Queue<int> queue;
	assert(queue.size() is 0);

	queue.enqueue(0);
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	assert(queue.size() is 4);

	Queue<int> a(queue);
	assert(a.size() is queue.size());
	assert(a.front() is queue.front());

	END_TEST;
}

bool test_copy_oper() {
	Queue<int> queue;
	assert(queue.size() is 0);
	
	queue.enqueue(0);
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	assert(queue.size() is 4);

	Queue<int> a;
	a.enqueue(4);
	a.enqueue(5);
	a.enqueue(6);
	a.enqueue(7);
	a.enqueue(8);
	assert(a.size() is 5);
	assert(a.size() is_not queue.size());
	assert(a.front() is_not queue.front());

	a = queue;
	assert(a.size() is queue.size());
	assert(a.front() is queue.front());

	END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(enqueue);
	test(dequeue);
	test(dequeue_empty);
	test(front);
	test(front_empty);
	test(copy);
	test(copy_oper);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
