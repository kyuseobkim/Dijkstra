#ifndef DIJKSTRA_SHORTEST_PATH_H_ 
#define DIJKSTRA_SHORTEST_PATH_H_

#include <vector>

#include "graph.h"

namespace dijkstra {

class ShortestPath {
    public:
        ShortestPath(const Graph& g): g(g) {}
        double path_size(int u, int w);
        vector<int> path(int u, int w);
    private:
        Graph g;
};

}

#endif  // DIJKSTRA_SHORTEST_PATH_H_
