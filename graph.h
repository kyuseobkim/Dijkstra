#ifndef DIJKSTRA_GRAPH_H_ 
#define DIJKSTRA_GRAPH_H_

#include <vector>

using namespace std;

namespace dijkstra {

class Graph {
    public:
        Graph(double density, int size);
        int V() const { return size; }
        int E() const;
        bool adjacent(int x, int y) const;
        vector<int> neighbors(int x) const;
        void add(int x, int y);
        int get_node_value(int x) const;
        void set_node_value(int x, int a);
        double get_edge_value(int x, int y) const;
        void set_edge_value(int x, int y, double v);
    private:
        const int size;
        vector<vector<bool> > adjacency_matrix;
        vector<vector<double> > distances;
        void create_adjacency_matrix(double density);
};

}

#endif  // DIJKSTRA_GRAPH_H_ 
