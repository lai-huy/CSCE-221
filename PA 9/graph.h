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
    unordered_map<size_t, unordered_map<size_t, double>> _graph;
    unordered_map<size_t, double> _dist;
    unordered_map<size_t, vector<size_t>> _paths;

    void copy(const Graph& rhs) {
        this->_edge = rhs._edge;

        for (const auto& [vertex, neighbors] : rhs._graph) {
            unordered_map<size_t, double> n{};
            for (const auto& [v, weight] : neighbors)
                n.insert({v, weight});
            this->_graph.insert({vertex, n});
        }

        for (const auto& [vertex, distance] : rhs._dist)
            this->_dist.insert({vertex, distance});

        for (const auto& [vertex, path] : rhs._paths)
            this->_paths.insert({vertex, path});
    }

    void clear() {
        this->_edge = 0;
        this->_graph.clear();
        this->_dist.clear();
        this->_paths.clear();
    }

public:
    Graph() : _edge{size_t{}}, _graph{unordered_map<size_t, unordered_map<size_t, double>>{}}, _dist{unordered_map<size_t, double>{}}, _paths{unordered_map<size_t, vector<size_t>>{}} {}
    Graph(const Graph& rhs) : Graph() { this->copy(rhs); }

    Graph& operator=(const Graph& rhs) {
        if (this != &rhs) {
            this->clear();
            this->copy(rhs);
        }

        return *this;
    }

    ~Graph() { this->clear(); }

    size_t vertex_count() const { return this->_graph.size(); }
    size_t edge_count() const { return this->_edge; }

    bool contains_vertex(size_t id) const { return this->_graph.find(id) != this->_graph.end(); }

    bool contains_edge(size_t src, size_t dest) const {
        if (!this->contains_vertex(src))
            return false;
        return this->_graph.at(src).count(dest);
    }

    double cost(size_t src, size_t dest) const { return this->contains_edge(src, dest) ? this->_graph.at(src).at(dest) : INFINITY; }

    bool add_vertex(size_t id) {
        if (this->contains_vertex(id))
            return false;
        this->_graph.insert({id, unordered_map<size_t, double>{}});
        this->_dist.insert({id, INFINITY});
        this->_paths.insert({id, vector<size_t>{}});
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
        ++this->_edge;
        return true;
    }

    bool remove_vertex(size_t id) {
        if (!this->contains_vertex(id))
            return false;

        for (const auto& [vertex, neighbors] : this->_graph) {
            if (this->contains_edge(id, vertex)) {
                this->_graph.at(id).erase(vertex);
                --this->_edge;
            } else if (this->contains_edge(vertex, id)) {
                this->_graph.at(vertex).erase(id);
                --this->_edge;
            }
        }
        this->_graph.erase(id);
        this->_dist.erase(id);
        this->_paths.erase(id);
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

        // Priority queue neighbors
        priority_queue<pair<double, size_t>, vector<pair<double, size_t>>, greater<pair<double, size_t>>> pq{};
        pq.push({0, source_id});

        // Initial set up
        unordered_map<size_t, size_t> parents{};
        for (const auto& [vertex, dist] : this->_dist) {
            this->_dist.at(vertex) = vertex == source_id ? 0 : INFINITY;
            parents.insert({vertex, size_t{}});
        }

        // Traverse the graph and run Dijkstra
        while (!pq.empty()) {
            const auto [weight, vertex] = pq.top();
            pq.pop();
            for (const auto& [v, w] : this->_graph.at(vertex)) {
                if (this->_dist.at(v) > this->_dist.at(vertex) + w) {
                    this->_dist.at(v) = this->_dist.at(vertex) + w;
                    pq.push({this->_dist.at(v), v});
                    parents.at(v) = vertex;
                }
            }
        }

        // Compute the path from source to every other vertex
        for (auto& [vertex, path] : this->_paths) {
            path.push_back(source_id);
            size_t parent = parents.at(vertex);
            while (parent && parent != source_id) {
                path.insert(path.begin() + 1, parent);
                parent = parents.at(parent);
            }
            path.push_back(vertex);
        }
    }

    double distance(size_t id) const { return this->contains_vertex(id) ? this->_dist.at(id) : INFINITY; }

    void print_shortest_path(size_t dest_id, ostream& os = cout) const {
        if (this->contains_vertex(dest_id)) {
            const vector<size_t>& path = this->_paths.at(dest_id);
            double dist = this->distance(dest_id);
            if (isinf(dist)) {
                os << "<no path>";
                return;
            }

            if (path[0] == path[1])
                os << path.at(0);
            else {
                bool first = false;
                for (const size_t& vertex : this->_paths.at(dest_id)) {
                    if (first)
                        os << " --> ";
                    os << vertex;
                    first = true;
                }
            }
            os << " distance: " << dist << "\n";
        } else
            os << "<no path>";
    }

    // ----------------------- Optional ----------------------- //
    Graph(Graph&& rhs) : _edge{move(rhs._edge)}, _graph{move(rhs._graph)}, _dist{move(rhs._dist)}, _paths{move(rhs._paths)} {}
    Graph& operator=(Graph&& rhs) {
        if (this != &rhs) {
            this->_edge = move(rhs._edge);
            this->_graph = move(rhs._graph);
            this->_dist = move(rhs._dist);
            this->_paths = move(rhs._paths);
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
