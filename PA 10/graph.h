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
using std::vector, std::list, std::priority_queue;
using std::unordered_map, std::unordered_set;
using std::swap, std::move;
using std::isinf, std::isnan;
using std::greater, std::pair;

class Graph {
private:
    /**
     * @brief The number of edges in the graph
     */
    size_t _edge;

    /**
     * @brief Source vertex to call Dijkstra's algorithm on
     */
    size_t _source;

    /**
     * @brief The actual graph, stores each vertex, its neighbors, and the weight to those neighbors
     */
    unordered_map<size_t, unordered_map<size_t, double>> _graph;

    /**
     * @brief Holds the distance from the source vertex to every other vertex in the graph
     */
    unordered_map<size_t, double> _dist;

    /**
     * @brief Holds each nodes' parent
     */
    unordered_map<size_t, size_t> _parents;

    /**
     * @brief Prevents memory errors by deallocating the entire graph
     */
    void clear() {
        this->_graph.clear();
        this->_dist.clear();
        this->_parents.clear();
        this->_edge = 0;
        this->_source = 0;
    }

public:
    /**
     * @brief Construct a new Graph object
     */
    Graph() : _edge{size_t{}}, _source{size_t{}}, _graph{unordered_map<size_t, unordered_map<size_t, double>>{}}, _dist{unordered_map<size_t, double>{}}, _parents{unordered_map<size_t, size_t>{}} {}

    /**
     * @brief Construct a new Graph object
     *
     * @param rhs Graph to copy from
     */
    Graph(const Graph& rhs) : _edge{rhs._edge}, _source{rhs._source}, _graph{rhs._graph}, _dist{rhs._dist}, _parents{rhs._parents} {}

    /**
     * @brief Copy assignment operator
     *
     * @param rhs graph to copy from
     * @return Graph& *this
     */
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

    /**
     * @brief Destroy the Graph object
     */
    ~Graph() { this->clear(); }

    /**
     * @brief Determines the number of vertices in the graph
     *
     * @return size_t the number of verticies in the graph
     */
    size_t vertex_count() const { return this->_graph.size(); }

    /**
     * @brief Determines the number of edges in the graph
     *
     * @return size_t the number of edges in the graph
     */
    size_t edge_count() const { return this->_edge; }

    /**
     * @brief Determine if the graph contains a vertex
     *
     * @param id Vertex to find
     * @return true if the graph contains the specified vertex
     * @return false otherwise
     */
    bool contains_vertex(size_t id) const { return this->_graph.count(id); }

    /**
     * @brief Determines if an edge exists in the graph
     *
     * @param src source vertex
     * @param dest destination vertex
     * @return true if an edge exists between two verticies
     * @return false otherwise
     */
    bool contains_edge(size_t src, size_t dest) const { return this->contains_vertex(src) ? this->_graph.at(src).count(dest) : false; }

    /**
     * @brief Determine the cost of the edge between two specified verticies
     *
     * @param src source vertex
     * @param dest destination vertex
     * @return double edge weight
     */
    double cost(size_t src, size_t dest) const { return this->contains_edge(src, dest) ? this->_graph.at(src).at(dest) : INFINITY; }

    /**
     * @brief adds a vertex to the graph
     *
     * @param id vertex to add
     * @return true if insertion succeeded
     * @return false otherwise
     */
    bool add_vertex(size_t id) {
        if (this->contains_vertex(id))
            return false;
        this->_graph.insert({id, unordered_map<size_t, double>{}});
        this->_dist.insert({id, INFINITY});
        this->_parents.insert({id, size_t{}});
        return true;
    }

    /**
     * @brief adds an edge to the graph
     *
     * @param src source vertex
     * @param dest destination vertex
     * @param weight edge weight
     * @return true if insertion succeeded
     * @return false otherwise
     */
    bool add_edge(size_t src, size_t dest, double weight = 1.0) {
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

    /**
     * @brief Removes a vertex from the graph
     *
     * @param id vertex to remove
     * @return true if removal succeeded
     * @return false otherwise
     */
    bool remove_vertex(size_t id) {
        if (!this->contains_vertex(id))
            return false;

        for (const auto& [vertex, neighbors] : this->_graph) {
            this->remove_edge(vertex, id);
            this->remove_edge(id, vertex);
        }
        this->_graph.erase(id);
        this->_dist.erase(id);
        this->_parents.erase(id);
        return true;
    }

    /**
     * @brief Removes an edge from the graph
     *
     * @param src source vertex
     * @param dest destination vertex
     * @return true if removal succeeded
     * @return false otherwise
     */
    bool remove_edge(size_t src, size_t dest) {
        if (!this->contains_edge(src, dest))
            return false;
        this->_graph[src].erase(dest);
        --this->_edge;
        return true;
    }

    list<pair<size_t, size_t>> prim() {
        list<pair<size_t, size_t>> result{};
        if (!this->_edge) {
            for (const auto& [vertex, neighbors] : this->_graph)
                this->_dist[vertex] = INFINITY;
            return result;
        }

        this->_source = this->_graph.begin()->first;
        // Priority queue neighbors
        priority_queue<pair<size_t, double>, vector<pair<size_t, double>>, greater<pair<size_t, double>>> pq{};
        pq.push({this->_source, 0});

        // Initial set up
        for (const auto& [vertex, dist] : this->_dist)
            this->_dist[vertex] = vertex == this->_source ? 0 : INFINITY;

        // Traverse the graph and run Dijkstra
        while (!pq.empty()) {
            const auto [vertex, weight] = pq.top();
            pq.pop();
            for (const auto& [v, w] : this->_graph[vertex]) {
                if (this->_dist[v] > this->_dist[vertex] + w) {
                    this->_dist[v] = this->_dist[vertex] + w;
                    pq.push({v, this->_dist[v]});
                    this->_parents[v] = vertex;
                }
            }
        }

        for (const auto& [vertex, parent] : this->_parents)
            if (parent)
                result.push_back({parent, vertex});

        return result;
    }

    double distance(size_t id) const { return this->contains_vertex(id) ? this->_dist.at(id) : INFINITY; }

    void print_minimum_spanning_tree(ostream& os = cout) const {
        for (const auto& [vertex, parent] : this->_parents)
            if (parent)
                os << parent << " --{" << this->_graph.at(parent).at(vertex) << "} " << vertex << ";\n";
    }

    // ----------------------- Optional ----------------------- //
    Graph(Graph&& rhs) : _edge{move(rhs._edge)}, _source{move(rhs._source)}, _graph{move(rhs._graph)}, _dist{move(rhs._dist)}, _parents{move(rhs._parents)} {}
    Graph& operator=(Graph&& rhs) {
        if (this != &rhs) {
            this->clear();
            swap(this->_edge, rhs._edge);
            swap(this->_source, rhs._source);
            this->_graph.swap(rhs._graph);
            this->_dist.swap(rhs._dist);
            this->_parents.swap(rhs._parents);
        }

        return *this;
    }
};
