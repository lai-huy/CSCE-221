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

using std::cout;
using std::list, std::pair;

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

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_add_vertex_skip() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(7));

    assert(g.vertex_count() == 1);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_add_vertex_fail() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(7));

    assert(g.vertex_count() == 1);
    assert(g.edge_count() == 0);

    assert(!g.add_vertex(7));
    assert(g.vertex_count() == 1);
    assert(g.edge_count() == 0);

    END_TEST;
}

bool test_add_edge() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(1, 2, 5));
    assert(g.add_edge(1, 3, 3));
    assert(g.add_edge(2, 3, 2));
    assert(g.add_edge(2, 5, 3));
    assert(g.add_edge(2, 7, 1));
    assert(g.add_edge(3, 4, 7));
    assert(g.add_edge(3, 5, 7));
    assert(g.add_edge(4, 1, 2));
    assert(g.add_edge(4, 6, 6));
    assert(g.add_edge(5, 4, 2));
    assert(g.add_edge(5, 6, 1));
    assert(g.add_edge(7, 5, 1));
    assert(g.edge_count() == 12);
    assert(g.vertex_count() == 7);

    END_TEST;
}

bool test_add_edge_fail() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(!g.add_edge(1, 8, 1.0));
    assert(!g.add_edge(8, 1, 1.0));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(2, 1, 1.0));
    assert(!g.add_edge(2, 1, 5.0));
    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 1);
    assert(g.cost(2, 1) == 1.0);

    END_TEST;
}

bool test_remove_vertex() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(1, 2, 5));
    assert(g.add_edge(1, 3, 3));
    assert(g.add_edge(2, 3, 2));
    assert(g.add_edge(2, 5, 3));
    assert(g.add_edge(2, 7, 1));
    assert(g.add_edge(3, 4, 7));
    assert(g.add_edge(3, 5, 7));
    assert(g.add_edge(4, 1, 2));
    assert(g.add_edge(4, 6, 6));
    assert(g.add_edge(5, 4, 2));
    assert(g.add_edge(5, 6, 1));
    assert(g.add_edge(7, 5, 1));
    assert(g.edge_count() == 12);
    assert(g.vertex_count() == 7);

    assert(g.remove_vertex(7));
    assert(g.edge_count() == 10);
    assert(g.vertex_count() == 6);

    assert(g.remove_vertex(6));
    assert(g.edge_count() == 8);
    assert(g.vertex_count() == 5);

    assert(g.remove_vertex(5));
    assert(g.edge_count() == 5);
    assert(g.vertex_count() == 4);

    assert(g.remove_vertex(4));
    assert(g.edge_count() == 3);
    assert(g.vertex_count() == 3);

    assert(g.remove_vertex(3));
    assert(g.edge_count() == 1);
    assert(g.vertex_count() == 2);

    assert(g.remove_vertex(2));
    assert(g.edge_count() == 0);
    assert(g.vertex_count() == 1);

    assert(g.remove_vertex(1));
    assert(g.edge_count() == 0);
    assert(g.vertex_count() == 0);

    END_TEST;
}

bool test_remove_vertex_fail() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(!g.remove_vertex(8));
    assert(!g.remove_vertex(0));

    END_TEST;
}

bool test_cost() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(1, 2, 5));
    assert(g.add_edge(1, 3, 3));
    assert(g.add_edge(2, 3, 2));
    assert(g.add_edge(2, 5, 3));
    assert(g.add_edge(2, 7, 1));
    assert(g.add_edge(3, 4, 7));
    assert(g.add_edge(3, 5, 7));
    assert(g.add_edge(4, 1, 2));
    assert(g.add_edge(4, 6, 6));
    assert(g.add_edge(5, 4, 2));
    assert(g.add_edge(5, 6, 1));
    assert(g.add_edge(7, 5, 1));
    assert(g.edge_count() == 12);
    assert(g.vertex_count() == 7);

    assert(g.cost(1, 2) == 5);
    assert(g.cost(1, 3) == 3);
    assert(g.cost(2, 3) == 2);
    assert(g.cost(2, 5) == 3);
    assert(g.cost(2, 7) == 1);
    assert(g.cost(3, 4) == 7);
    assert(g.cost(3, 5) == 7);
    assert(g.cost(4, 1) == 2);
    assert(g.cost(4, 6) == 6);
    assert(g.cost(5, 4) == 2);
    assert(g.cost(5, 6) == 1);
    assert(g.cost(7, 5) == 1);

    END_TEST;
}

bool test_cost_invalid() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(1, 2, 5));
    assert(g.add_edge(1, 3, 3));
    assert(g.add_edge(2, 3, 2));
    assert(g.add_edge(2, 5, 3));
    assert(g.add_edge(2, 7, 1));
    assert(g.add_edge(3, 4, 7));
    assert(g.add_edge(3, 5, 7));
    assert(g.add_edge(4, 1, 2));
    assert(g.add_edge(4, 6, 6));
    assert(g.add_edge(5, 4, 2));
    assert(g.add_edge(5, 6, 1));
    assert(g.add_edge(7, 5, 1));
    assert(g.edge_count() == 12);
    assert(g.vertex_count() == 7);

    assert(g.cost(1, 1) == INFINITY);
    assert(g.cost(1, 8) == INFINITY);
    assert(g.cost(8, 1) == INFINITY);
    assert(g.cost(1, 5) == INFINITY);

    END_TEST;
}

bool test_prim() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(1, 2, 5));
    assert(g.add_edge(1, 3, 3));
    assert(g.add_edge(2, 3, 2));
    assert(g.add_edge(2, 5, 3));
    assert(g.add_edge(2, 7, 1));
    assert(g.add_edge(3, 4, 7));
    assert(g.add_edge(3, 5, 7));
    assert(g.add_edge(4, 1, 2));
    assert(g.add_edge(4, 6, 6));
    assert(g.add_edge(5, 4, 2));
    assert(g.add_edge(5, 6, 1));
    assert(g.add_edge(7, 5, 1));
    assert(g.edge_count() == 12);
    assert(g.vertex_count() == 7);

    g.prim();
    g.print_minimum_spanning_tree();

    END_TEST;
}

bool test_copy() {
    Graph g{};
    assert(g.vertex_count() == 0);
    assert(g.edge_count() == 0);

    assert(g.add_vertex(1));
    assert(g.add_vertex(2));
    assert(g.add_vertex(3));
    assert(g.add_vertex(4));
    assert(g.add_vertex(5));
    assert(g.add_vertex(6));
    assert(g.add_vertex(7));

    assert(g.vertex_count() == 7);
    assert(g.edge_count() == 0);

    assert(g.add_edge(1, 2, 5));
    assert(g.add_edge(1, 3, 3));
    assert(g.add_edge(2, 3, 2));
    assert(g.add_edge(2, 5, 3));
    assert(g.add_edge(2, 7, 1));
    assert(g.add_edge(3, 4, 7));
    assert(g.add_edge(3, 5, 7));
    assert(g.add_edge(4, 1, 2));
    assert(g.add_edge(4, 6, 6));
    assert(g.add_edge(5, 4, 2));
    assert(g.add_edge(5, 6, 1));
    assert(g.add_edge(7, 5, 1));
    assert(g.edge_count() == 12);
    assert(g.vertex_count() == 7);

    Graph h(g);
    assert(h.edge_count() == g.edge_count());
    assert(h.vertex_count() == g.vertex_count());

    END_TEST;
}

bool test_example() {
    cout << "make an empty graph\n";
    Graph g;
    cout << "add vertices\n";
    for (size_t n = 1; n <= 7; ++n)
        g.add_vertex(n);
    cout << "add undirected edges\n";
    g.add_edge(1, 2, 5);
    g.add_edge(1, 3, 3);
    g.add_edge(2, 3, 2);
    g.add_edge(2, 5, 3);
    g.add_edge(2, 7, 1);
    g.add_edge(3, 4, 7);
    g.add_edge(3, 5, 7);
    g.add_edge(4, 1, 2);
    g.add_edge(4, 6, 6);
    g.add_edge(5, 4, 2);
    g.add_edge(5, 6, 1);
    g.add_edge(7, 5, 1);
    cout << "G has " << g.vertex_count() << " vertices and ";
    cout << g.edge_count() << " edges\n";
    cout << "compute a minimum spanning tree\n";
    list<pair<size_t, size_t>> mst = g.prim();
    cout << "print minimum spanning tree\n";
    double tree_cost = 0;
    for (const pair<size_t, size_t>& edge : mst) {
        cout << edge.first << " --{" << g.cost(edge.first, edge.second) << "} " <<
            edge.second << ";\n";
        tree_cost += g.cost(edge.first, edge.second);
    }
    cout << "tree cost = " << tree_cost << "\n";


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
    test(remove_vertex_fail);
    test(prim);
    test(cost);
    test(cost_invalid);
    test(copy);
    test(example);

    cout << "\n";
    cout << magenta << "summary:" << reset << "\n";
    cout << green << pass_cnt << " tests passing." << reset << "\n";
    cout << red << fail_cnt << " tests failing." << reset << "\n";
    cout << yellow << skip_cnt << " tests skipped." << reset << "\n";

    return 0;
}
