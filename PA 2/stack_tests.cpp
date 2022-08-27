#include <iostream>
#include "stack.h"

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
	Stack<int> stack;
	assert(stack.size() is 0);

	END_TEST;
}

bool test_push() {
	Stack<int> stack;
	assert(stack.size() is 0);

	stack.push(0);
	assert(stack.size() is 1);

	stack.push(1);
	assert(stack.size() is 2);

	stack.push(2);
	assert(stack.size() is 3);

	stack.push(3);
	assert(stack.size() is 4);

	stack.push(4);
	assert(stack.size() is 5);

	END_TEST;
}

bool test_pop() {
	Stack<int> stack;
	assert(stack.size() is 0);

	stack.push(0);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	stack.push(5);
	assert(stack.size() is 6);

	stack.pop();
	assert(stack.size() is 5);

	stack.pop();
	assert(stack.size() is 4);

	stack.pop();
	assert(stack.size() is 3);
	
	stack.pop();
	assert(stack.size() is 2);
	
	stack.pop();
	assert(stack.size() is 1);

	stack.pop();
	assert(stack.size() is 0);

	END_TEST;
}

bool test_pop_empty() {
	Stack<int> stack;
	assert(stack.size() is 0);

	expect_throw(stack.pop(), out_of_range);

	END_TEST;
}

bool test_top() {
	Stack<int> stack;
	assert(stack.size() is 0);

	stack.push(0);
	assert(stack.top() is 0);
	
	stack.push(1);
	assert(stack.top() is 1);
	
	stack.push(2);
	assert(stack.top() is 2);

	END_TEST;
}

bool test_top_empty() {
	Stack<int> stack;
	assert(stack.size() is 0);

	expect_throw(stack.top(), out_of_range);

	END_TEST;
}

bool test_copy() {
	Stack<int> stack;
	assert(stack.size() is 0);

	stack.push(0);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	assert(stack.size() is 4);

	Stack<int> a(stack);
	assert(a.size() is stack.size());
	assert(a.top() is stack.top());

	END_TEST;
}

bool test_copy_oper() {
	Stack<int> stack;
	assert(stack.size() is 0);

	stack.push(0);
	stack.push(1);
	stack.push(2);
	stack.push(3);
	assert(stack.size() is 4);

	Stack<int> a;
	assert(a.size() is 0);

	a.push(4);
	a.push(5);
	a.push(6);
	a.push(7);
	a.push(8);
	a.push(9);
	assert(a.size() is 6);
	assert(a.size() is_not stack.size());
	assert(a.top() is_not stack.top());

	a = stack;
	assert(a.size() is stack.size());
	assert(a.top() is stack.top());

	END_TEST;
}

int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

	test(create);
	test(push);
	test(pop);
	test(pop_empty);
	test(top);
	test(top_empty);
	test(copy);
	test(copy_oper);

	cout << "\n";
	cout << magenta << "summary:" << reset << "\n";
	cout << green << pass_cnt << " tests passing." << reset << "\n";
	cout << red << fail_cnt << " tests failing." << reset << "\n";
	cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

	return 0;
}
