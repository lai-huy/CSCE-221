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

public:
    Graph() : _edge{size_t{}}, _graph{unordered_map<size_t, unordered_map<size_t, double>>{}}, _dist{unordered_map<size_t, double>{}} {}
    Graph(const Graph& rhs) : _edge{rhs._edge}, _graph{rhs._graph}, _dist{rhs._dist} {}
    Graph& operator=(const Graph& rhs) {
        if (this != &rhs) {
            this->_edge = rhs._edge;
            this->_graph = rhs._graph;
            this->_dist = rhs._dist;
        }

        return *this;
    }

    ~Graph() { this->_graph.clear(); this->_dist.clear(); }

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
        priority_queue<pair<double, size_t>, vector<pair<double, size_t>>, greater<pair<double, size_t>>> pq{};
        pq.push({0, source_id});
        this->_dist[source_id] = 0;

        while (!pq.empty()) {
            const auto [weight, vertex] = pq.top();
            pq.pop();
            for (const auto& [v, w] : this->_graph.at(vertex)) {
                if (this->_dist[v] > this->_dist[vertex] + w) {
                    this->_dist[v] = this->_dist[vertex] + w;
                    pq.push({this->_dist[v], v});
                }
            }
        }
    }

    double distance(size_t id) const { return this->contains_vertex(id) ? this->_dist.at(id) : INFINITY; }

    void print_shortest_path(size_t dest_id, ostream& os = cout) const {
        if (this->contains_vertex(dest_id)) {
            os << dest_id << "\t" << this->distance(dest_id) << "\n";
        } else
            os << "<no path>\n";
    }

    // ----------------------- Optional ----------------------- //
    Graph(Graph&& rhs) : _edge{move(rhs._edge)}, _graph{move(rhs._graph)}, _dist{move(rhs._dist)} {}
    Graph& operator=(Graph&& rhs) {
        if (this != &rhs) {
            this->_edge = move(rhs._edge);
            this->_graph = move(rhs._graph);
            this->_dist = move(rhs._dist);
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
