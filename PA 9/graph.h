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

using std::cout, std::ostream;

class Graph {
    Graph();
    Graph(const Graph& rhs);
    Graph& operator=(const Graph& rhs);
    ~Graph();

    size_t vertex_count() const;
    size_t edge_count() const;

    bool contains_vertex(size_t id) const;
    bool contains_edge(size_t src, size_t dest) const;
    double cost(size_t src, size_t dest) const;

    bool add_vertex(size_t id);
    bool add_edge(size_t src, size_t dest, double weight = 1.0);
    bool remove_vertex(size_t id);
    bool remove_edge(size_t src, size_t dest);

    // ----------------------- Optional ----------------------- //
    // Graph(Graph&& rhs);
    // Graph& operator=(Graph&& rhs);

    void dijkstra(size_t source_id);
    double distance(size_t id) const;
    void print_shortest_path(size_t dest_id, ostream& os = cout) const;
};
