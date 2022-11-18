#include "graph.h"

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
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_add_vertex() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(0));
    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_add_vertex_skip() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(7));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_add_vertex_fail() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(7));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    assert(!g.add_vertex(3));

    END_TEST;
}

bool test_add_edge() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(0));
    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    assert(g.add_edge(0, 1, 1.0));
    assert(g.add_edge(0, 3, 5.0));
    assert(g.add_edge(1, 3, 3.0));
    assert(g.add_edge(2, 1, 2.0));
    assert(g.add_edge(2, 5, 1.5));
    assert(g.add_edge(4, 2, 0.5));
    assert(g.add_edge(7, 4, 4.0));
    assert(g.edge_count() == 7);
    assert(g.vertex_count() == 8);

    END_TEST;
}

bool test_add_edge_fail() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(0));
    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    assert(!g.add_edge(1, 0, INFINITY));
    assert(!g.add_edge(0, 1, NAN));
    assert(!g.add_edge(0, 9, 1.0));
    assert(!g.add_edge(9, 0, 1.0));
    assert(!g.add_edge(0, 0, 1.0));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_remove_vertex() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(0));
    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 8);
    assert(g.edge_count() == 0);

    assert(g.add_edge(0, 1, 1.0));
    assert(g.add_edge(0, 3, 5.0));
    assert(g.add_edge(1, 3, 3.0));
    assert(g.add_edge(2, 1, 2.0));
    assert(g.add_edge(2, 5, 1.5));
    assert(g.add_edge(4, 2, 0.5));
    assert(g.add_edge(7, 4, 4.0));
    assert(g.edge_count() == 7);
    assert(g.vertex_count() == 8);

    assert(g.remove_vertex(2));
    assert(g.edge_count() == 4);
    assert(g.vertex_count() == 7);
    assert(g.contains_vertex(2));

    END_TEST;
}

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;

    test(create);
    test(add_vertex);
    test(add_vertex_skip);
    test(add_vertex_fail);
    test(add_edge);
    test(add_edge_fail);
    test(remove_vertex);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
