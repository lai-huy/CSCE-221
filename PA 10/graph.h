#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::list, std::pair;
using std::cout, std::ostream;

class Graph {
    Graph();
    Graph(const Graph& rhs);
    Graph& operator=(const Graph& rhs);
    ~Graph();

    size_t vertex_count() const;
    size_t edge_count() const;

    bool contains_vertex(size_t id) const;
    bool contains_edge(size_t u, size_t v) const;
    double cost(size_t u, size_t v) const;

    bool add_vertex(size_t id);
    bool add_edge(size_t u, size_t v, double weight = 1);
    bool remove_vertex(size_t id);
    bool remove_edge(size_t u, size_t v);

    // OPTIONAL
    // Graph(Graph&& rhs);
    // Graph& operator=(Graph&& rhs);

    list<pair<size_t, size_t>> prim();
    double distance(size_t id) const;
    void print_minimum_spanning_tree(ostream& os = cout) const;
};
