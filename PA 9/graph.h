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
using std::unordered_map;
using std::swap, std::move;
using std::isinf, std::isnan;
using std::less, std::hash;

class Graph {
private:
    size_t _edge;
    unordered_map<size_t, unordered_map<size_t, double>> _graph;

public:
    Graph() : _edge{size_t{}}, _graph{unordered_map<size_t, unordered_map<size_t, double>>{}} {}
    Graph(const Graph& rhs) : _edge{rhs._edge}, _graph{rhs._graph} {}
    Graph& operator=(const Graph& rhs) {
        if (this != &rhs) {
            this->_edge = rhs._edge;
            this->_graph = rhs._graph;
        }

        return *this;
    }

    ~Graph() { this->_graph.clear(); }

    size_t vertex_count() const { return this->_graph.size(); }
    size_t edge_count() const { return this->_edge; }

    bool contains_vertex(size_t id) const { return this->_graph.find(id) != this->_graph.end(); }

    bool contains_edge(size_t src, size_t dest) const {
        if (!this->contains_vertex(src))
            return false;
        else if (!this->contains_vertex(dest))
            return false;
        const unordered_map<size_t, double>& vertex = this->_graph.at(src);
        return vertex.find(dest) != vertex.end();
    }

    double cost(size_t src, size_t dest) const { return this->contains_edge(src, dest) ? this->_graph.at(src).at(dest) : INFINITY; }

    bool add_vertex(size_t id) {
        if (this->contains_vertex(id))
            return false;
        this->_graph.insert({id, unordered_map<size_t, double>{}});
        return true;
    }

    bool add_edge(size_t src, size_t dest, double weight = 1.0) {
        if (src == dest)
            return false;
        if (!this->contains_vertex(src))
            return false;
        if (!this->contains_vertex(dest))
            return false;
        const unordered_map<size_t, double>& vertex = this->_graph.at(src);
        if (vertex.find(dest) != vertex.end())
            return false;
        this->_graph[src][dest] = weight;
        this->_graph[dest][src] = weight;
        ++this->_edge;
        return true;
    }

    bool remove_vertex(size_t id) {
        if (!this->contains_vertex(id))
            return false;

        for (auto& [vertex, neighbors] : this->_graph) {
            if (this->contains_edge(id, vertex)) {
                this->_graph[id].erase(vertex);
                this->_graph[vertex].erase(id);
                --this->_edge;
            }
        }
        this->_graph.erase(id);
        return true;
    }

    bool remove_edge(size_t src, size_t dest) {
        if (!this->contains_edge(src, dest))
            return false;
        this->_graph[src].erase(dest);
        --this->_edge;
        return true;
    }

    void dijkstra(size_t source_id) {
        if (!this->contains_vertex(source_id))
            return;
    }

    double distance(size_t id) const {
        cout << id;
        return INFINITY;
    }

    void print_shortest_path(size_t dest_id, ostream& os = cout) const {
        if (this->contains_vertex(dest_id)) {
            os << dest_id << "\n";
        } else
            os << "<no path>\n";
    }

    // ----------------------- Optional ----------------------- //
    Graph(Graph&& rhs) : _edge{move(rhs._edge)}, _graph{move(rhs._graph)} {}
    Graph& operator=(Graph&& rhs) {
        if (this != &rhs) {
            this->_edge = 0;
            this->_graph.clear();
            this->_edge = move(rhs._edge);
            this->_graph = move(rhs._graph);
        }

        return *this;
    }
};
