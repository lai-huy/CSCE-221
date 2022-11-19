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
using std::unordered_map, std::unordered_set;
using std::swap, std::move;
using std::isinf, std::isnan;
using std::find, std::greater;
using std::pair;

class Graph {
private:
    size_t _edge;
    size_t _source;
    unordered_map<size_t, unordered_map<size_t, double>> _graph;
    unordered_map<size_t, double> _dist;
    unordered_map<size_t, size_t> _parents;

public:
    Graph() : _edge{size_t{}}, _source{size_t{}}, _graph{unordered_map<size_t, unordered_map<size_t, double>>{}}, _dist{unordered_map<size_t, double>{}}, _parents{unordered_map<size_t, size_t>{}} {}
    Graph(const Graph& rhs) : _edge{rhs._edge}, _source{rhs._source}, _graph{rhs._graph}, _dist{rhs._dist}, _parents{rhs._parents} {}

    Graph& operator=(const Graph& rhs) {
        if (this != &rhs) {
            this->_edge = rhs._edge;
            this->_source = rhs._source;
            this->_graph = rhs._graph;
            this->_dist = rhs._dist;
            this->_parents = rhs._parents;
        }

        return *this;
    }

    ~Graph() {}

    size_t vertex_count() const { return this->_graph.size(); }
    size_t edge_count() const { return this->_edge; }

    bool contains_vertex(size_t id) const { return this->_graph.find(id) != this->_graph.end(); }

    bool contains_edge(size_t src, size_t dest) const { return this->contains_vertex(src) ? this->_graph.at(src).count(dest) : false; }

    double cost(size_t src, size_t dest) const { return this->contains_edge(src, dest) ? this->_graph.at(src).at(dest) : INFINITY; }

    bool add_vertex(size_t id) {
        if (this->contains_vertex(id))
            return false;
        this->_graph.insert({id, unordered_map<size_t, double>{}});
        this->_dist.insert({id, INFINITY});
        this->_parents.insert({id, size_t{}});
        return true;
    }

    bool add_edge(size_t src, size_t dest, double weight = 1.0) {
        if (src == dest)
            return false;
        if (!this->contains_vertex(src))
            return false;
        if (!this->contains_vertex(dest))
            return false;
        if (this->_graph.at(src).count(dest))
            return false;
        this->_graph[src][dest] = weight;
        ++this->_edge;
        return true;
    }

    bool remove_vertex(size_t id) {
        if (!this->contains_vertex(id))
            return false;

        for (const auto& [vertex, neighbors] : this->_graph) {
            if (this->contains_edge(id, vertex)) {
                this->_graph.at(id).erase(vertex);
                this->_graph.at(vertex).erase(id);
                --this->_edge;
            }
        }
        this->_graph.erase(id);
        this->_dist.erase(id);
        this->_parents.erase(id);
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

        this->_source = source_id;
        // Priority queue neighbors
        priority_queue<pair<double, size_t>, vector<pair<double, size_t>>, greater<pair<double, size_t>>> pq{};
        pq.push({0, source_id});

        // Initial set up
        for (const auto& [vertex, dist] : this->_dist)
            this->_dist.at(vertex) = vertex == source_id ? 0 : INFINITY;

        // Traverse the graph and run Dijkstra
        while (!pq.empty()) {
            const auto [weight, vertex] = pq.top();
            pq.pop();
            for (const auto& [v, w] : this->_graph.at(vertex)) {
                if (this->_dist.at(v) > this->_dist.at(vertex) + w) {
                    this->_dist.at(v) = this->_dist.at(vertex) + w;
                    pq.push({this->_dist.at(v), v});
                    this->_parents.at(v) = vertex;
                }
            }
        }
    }

    double distance(size_t id) const { return this->contains_vertex(id) ? this->_dist.at(id) : INFINITY; }

    void print_shortest_path(size_t dest_id, ostream& os = cout) const {
        if (!this->contains_vertex(dest_id)) {
            os << "<no path>\n";
            return;
        }
        const double dist = this->_dist.at(dest_id);
        if (isinf(dist)) {
            os << "<no path>\n";
            return;
        } else if (dist == 0) {
            os << dest_id << " distance: 0\n";
            return;
        }

        vector<size_t> path{dest_id};
        size_t curr = dest_id;
        while (curr != this->_source) {
            if (this->_parents.count(this->_parents.at(curr))) {
                curr = this->_parents.at(curr);
                path.push_back(curr);
            } else {
                os << "<no path>\n";
                return;
            }
        }

        for (auto iter = path.crbegin(); iter != path.crend() - 1; ++iter)
            os << *iter << " --> ";
        os << *path.begin() << " distance: " << dist << "\n";
    }

    // ----------------------- Optional ----------------------- //
    Graph(Graph&& rhs) : Graph() {
        swap(this->_edge, rhs._edge);
        swap(this->_source, rhs._source);
        this->_graph.swap(rhs._graph);
        this->_dist.swap(rhs._dist);
        this->_parents.swap(rhs._parents);
    }

    Graph& operator=(Graph&& rhs) {
        if (this != &rhs) {
            swap(this->_edge, rhs._edge);
            swap(this->_source, rhs._source);
            this->_graph.swap(rhs._graph);
            this->_dist.swap(rhs._dist);
            this->_parents.swap(rhs._parents);
        }

        return *this;
    }

    void print_graph(ostream& os = cout) const {
        if (this->_edge) {
            for (const auto& [src, neighbors] : this->_graph)
                for (const auto& [dest, weight] : neighbors)
                    cout << src << " ->{" << dest << "} " << weight << "\n";
        } else
            os << "<empty>\n";
    }
};
