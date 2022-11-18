#pragma once

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
using std::vector, std::priority_queue;
using std::swap, std::move;
using std::isinf, std::isnan;
using std::less;

class Graph {
private:
    size_t _size;
    size_t _edge;
    vector<vector<double>> _graph;

public:
    Graph() : _size{0}, _edge{0}, _graph{vector<vector<double>>{}} {}
    Graph(const Graph& rhs) : _size{rhs._size}, _edge{rhs._edge}, _graph{rhs._graph} {}
    Graph& operator=(const Graph& rhs) {
        if (this != &rhs) {
            this->_size = rhs._size;
            this->_edge = rhs._edge;
            this->_graph = rhs._graph;
        }

        return *this;
    }

    ~Graph() { this->_graph.clear(); }

    size_t vertex_count() const { return this->_size; }
    size_t edge_count() const { return this->_edge; }

    bool contains_vertex(size_t id) const { return id < this->_size; }

    bool contains_edge(size_t src, size_t dest) const {
        if (!this->contains_vertex(src))
            return false;
        else if (!this->contains_vertex(dest))
            return false;
        return !isinf(this->_graph[src][dest]);
    }

    double cost(size_t src, size_t dest) const { return this->contains_edge(src, dest) ? this->_graph[src][dest] : INFINITY; }

    bool add_vertex(size_t id) {
        if (id < this->_size)
            return false;
        this->_size = id + 1;
        for (vector<double>& row : this->_graph)
            row.resize(this->_size, INFINITY);
        this->_graph.resize(this->_size, vector<double>(this->_size, INFINITY));
        return true;
    }

    bool add_edge(size_t src, size_t dest, double weight = 1.0) {
        if (this->contains_edge(src, dest))
            return false;
        if (src == dest)
            return false;
        if (!this->contains_vertex(src))
            return false;
        if (!this->contains_vertex(dest))
            return false;
        if (isinf(weight))
            return false;
        if (isnan(weight))
            return false;
        this->_graph[src][dest] = weight;
        ++this->_edge;
        return true;
    }

    bool remove_vertex(size_t id) {
        if (!this->contains_vertex(id))
            return false;

        for (size_t i = 0; i < this->_size; ++i) {
            this->remove_edge(i, id);
            this->remove_edge(id, i);
        }

        --this->_size;
        return true;
    }

    bool remove_edge(size_t src, size_t dest) {
        if (!this->contains_edge(src, dest))
            return false;
        this->_graph[src][dest] = INFINITY;
        --this->_edge;
        return true;
    }

    void dijkstra(size_t source_id) {
        if (!this->contains_vertex(source_id))
            return;
        priority_queue<double, vector<double>, less<double>> pq(less<double>{}, this->_graph[source_id]);
    }

    double distance(size_t id) const {
        cout << id;
        return INFINITY;
    }

    void print_shortest_path(size_t dest_id, ostream& os = cout) const {
        if (this->contains_vertex(dest_id)) {
            os << dest_id;
        }
        os << "<no path>\n";
    }

    void print_graph(ostream& os = cout) const {
        if (this->_size) {
            for (const vector<double>& row : this->_graph) {
                os << "[";
                for (size_t j = 0; j < row.size(); ++j) {
                    os << row[j];
                    if (j != row.size() - 1)
                        os << ", ";
                }
                os << "]\n";
            }
        } else
            os << "<empty>\n";
    }

    // ----------------------- Optional ----------------------- //
    Graph(Graph&& rhs) : _size{move(rhs._size)}, _edge{move(rhs._edge)}, _graph{move(rhs._graph)} {}
    Graph& operator=(Graph&& rhs) {
        if (this != &rhs) {
            this->_size = 0;
            this->_edge = 0;
            this->_graph.clear();
            this->_size = move(rhs._size);
            this->_edge = move(rhs._edge);
            this->_graph = move(rhs._graph);
        }

        return *this;
    }
};
