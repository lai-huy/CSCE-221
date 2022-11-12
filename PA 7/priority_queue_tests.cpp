#include <functional>
#include <deque>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "priority_queue.h"

using std::vector, std::deque;
using std::less, std::greater;
using std::move;
using std::cout, std::stringstream;

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
    PriorityQueue<int> queue{};

    assert(queue.size() == 0);
    assert(queue.empty());

    END_TEST;
}

bool test_create_cont() {
    deque<int> dq{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    PriorityQueue<int, deque<int>, less<int>> queue(dq);

    assert(queue.size() == dq.size());
    END_TEST;
}

bool test_create_comp() {
    greater<int> comp{};
    PriorityQueue<int, vector<int>, greater<int>> queue(comp);
    assert(queue.size() == 0);
    assert(queue.empty());

    END_TEST;
}

bool test_create_cc() {
    deque<int> dq{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    greater<int> comp{};

    PriorityQueue<int, deque<int>, greater<int>> queue(comp, dq);
    assert(queue.size() == dq.size());

    END_TEST;
}

bool test_top() {
    vector<int> vect{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    PriorityQueue<int> queue(vect);
    assert(queue.size() == vect.size());

    assert(queue.top() == 1);

    END_TEST;
}

bool test_top_empty() {
    PriorityQueue<int> queue{};

    expect_throw(queue.top(), invalid_argument);
    END_TEST;
}

bool test_push() {
    vector<int> vect{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    PriorityQueue<int> queue(vect);
    assert(queue.size() == vect.size());

    expect_no_throw(queue.push(0));
    assert(queue.top() == 0);
    assert(queue.size() == 16);

    END_TEST;
}

bool test_push_empty() {
    PriorityQueue<int> queue{};
    assert(queue.size() == 0);
    assert(queue.empty());

    queue.push(15);
    queue.push(8);
    queue.push(4);
    queue.push(3);
    queue.push(1);
    queue.push(7);
    queue.push(11);
    queue.push(10);
    queue.push(2);
    queue.push(9);
    queue.push(6);
    queue.push(5);
    queue.push(12);
    queue.push(14);
    queue.push(13);
    assert(queue.size() == 15);
    assert(queue.top() == 1);

    END_TEST;
}

bool test_pop() {
    vector<int> vect{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    PriorityQueue<int> queue(vect);
    assert(queue.size() == vect.size());

    expect_no_throw(queue.pop());
    assert(queue.size() == 14);

    END_TEST;
}

bool test_pop_empty() {
    PriorityQueue<int> queue{};
    assert(queue.size() == 0);
    assert(queue.empty());

    expect_throw(queue.pop(), invalid_argument);

    END_TEST;
}

bool test_pop_until_empty() {
    vector<int> vect{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    PriorityQueue<int> queue(vect);
    assert(queue.size() == vect.size());

    while (!queue.empty())
        expect_no_throw(queue.pop());

    assert(queue.size() == 0);
    assert(queue.empty());

    END_TEST;
}

bool test_print() {
    vector<int> vect{15, 8, 4, 3, 1, 7, 11, 10, 2, 9, 6, 5, 12, 14, 13};
    PriorityQueue<int> queue(vect);
    assert(queue.size() == vect.size());

    stringstream ss;
    queue.print_queue(ss);
    cout << ss.str() << "\n";

    END_TEST;
}

bool test_print_empty() {
    PriorityQueue<int> queue{};
    assert(queue.size() == 0);
    assert(queue.empty());

    stringstream ss;
    queue.print_queue(ss);
    cout << ss.str();

    END_TEST;
}

bool test_example() {
    std::cout << "SELECTION PROBLEM\n";
    std::cout << "make a priority queue from N = 168 elements in O(N) time\n";
    std::vector<int> values{509, 887, 53, 739, 491, 307, 727, 223, 919, 263, 983,
    7, 809, 353, 659, 769, 173, 431, 619, 139, 2, 3, 181, 23, 283, 617, 463, 757,
    89, 541, 997, 743, 907, 13, 337, 349, 523, 857, 97, 827, 661, 67, 373, 59, 11,
    277, 379, 19, 941, 607, 367, 101, 457, 929, 599, 971, 967, 647, 71, 991, 211,
    467, 881, 137, 311, 673, 197, 179, 859, 239, 233, 631, 449, 281, 499, 269,
    877, 421, 419, 613, 593, 383, 937, 569, 487, 839, 479, 461, 683, 653, 227, 61,
    107, 113, 947, 191, 103, 313, 733, 151, 257, 73, 821, 547, 521, 691, 83, 823,
    443, 31, 5, 643, 131, 389, 571, 163, 271, 601, 359, 199, 853, 29, 167, 557,
    157, 193, 977, 37, 41, 773, 347, 709, 251, 331, 829, 503, 409, 719, 397, 241,
    47, 641, 787, 863, 109, 587, 17, 751, 229, 911, 811, 317, 563, 701, 797, 953,
    293, 149, 439, 127, 883, 577, 79, 433, 43, 761, 401, 677};
    PriorityQueue<int> pq(values);
    std::cout << "pop k = 42 = O(N / log N) elements in O(k log N) = O(N) time\n";
    for (int i = 0; i < 41; i++) { pq.pop(); }
    // ^^^ pops 41, top is would-be 42nd pop vvvvv
    std::cout << "found k-th smallest element = " << pq.top() << " in O(N + k log N) = O(N) time\n";
    std::cout << "\n" << "INTERMISSION\n";
    std::cout << "empty the queue in O(1) time\n";
    pq.make_empty();
    std::cout << "\nDISCRETE EVENT SIMULATION\n";
    int t = 0;
    size_t busy_start = 0, busy_stop = 0, busy_time = 0, wait_time = 0, cnt = 0, cust_id = 0, next = 7;
    bool busy = false;
    std::deque<size_t> line;
    pq.push(t);
    while (!pq.empty()) {
        t = pq.top();
        pq.pop();
        if (t % 2) {
            // departure
            std::cout << "customer departed at time " << t << "\n";
            cnt++;
            if (line.empty()) {
                busy = false;
                busy_stop = t;
                busy_time += busy_stop - busy_start;
            } else {
                // next in line
                int arrival_time = line.front();
                line.pop_front();
                wait_time += (t - arrival_time);
                std::cout << "next customer in line has been waiting " << (t - arrival_time) << " time units\n";
                // schedule departure at odd time (t is odd right now), >0 from now
                int service_time = 2 * ((next + 3) % 5) + 2;
                pq.push(t + service_time);
                next = (next + 5) % 11;
            }
        } else {
            // arrival
            std::cout << "customer " << ++cust_id << " arrived at time " << t <<
                "\n";
            if (cust_id < 10) {
                // schedule next arrival at even time (t is even right now)
                int interarrival_time = 2 * ((next + 3) % 5) + 2;
                pq.push(t + interarrival_time);
                next = (next + 5) % 11;
            }
            if (busy) {
                // wait in line
                line.push_back(t);
                std::cout << "  server is busy, customer must wait in line, there are " << line.size() << " in line\n";
            } else {
                // serve
                busy = true;
                busy_start = t;
                std::cout << "  service begins immediately\n";
                // schedule departure at odd time (t is even right now), >0 from now
                int service_time = 2 * ((next + 3) % 5) + 1;
                pq.push(t + service_time);
                next = (next + 5) % 11;
            }
        }
    }

    std::cout << "end of simulation\n-----------------\n";
    std::cout << "served 10 customers in " << t << " time units\n";
    std::cout << "server was busy for " << busy_time << " total time units\n";
    std::cout << "customers waited " << wait_time << " total time units\n";

    END_TEST;
}


int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(create);
    test(create_cont);
    test(create_comp);
    test(create_cc);
    test(top);
    test(top_empty);
    test(push);
    test(push_empty);
    test(pop);
    test(pop_empty);
    test(pop_until_empty);
    test(print);
    test(print_empty);
    test(example);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
