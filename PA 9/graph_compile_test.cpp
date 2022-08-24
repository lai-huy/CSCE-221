#include <iostream>
#include <sstream>
#include "graph.h"

int main() {
    Graph G;
    G.add_vertex(1);
    std::cout << G.vertex_count() << std::endl;
    std::cout << G.contains_vertex(1) << std::endl;
    std::cout << G.distance(1) << std::endl;
    G.add_edge(1,1);
    std::cout << G.edge_count() << std::endl;
    std::cout << G.contains_edge(1,1) << std::endl;
    std::cout << G.cost(1,1) << std::endl;
    Graph copy = G;
    G = copy;
    G.remove_vertex(1);    
    G.remove_edge(1,1);
    G.dijkstra(1);
    std::stringstream ss;
    G.print_shortest_path(1, ss);
}
