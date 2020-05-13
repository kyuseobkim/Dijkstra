#include <iostream>
#include <queue>

#include "shortest_path.h"

using namespace std;

namespace dijkstra {
    struct edge {
        int dest;
        double dist;
        edge(int dest, double dist): dest(dest), dist(dist) {}
        bool operator<(const edge& b) const {
            return dist > b.dist;
        }
    };

    double ShortestPath::path_size(int u, int w) {
        vector<double> distances;
        int edges = g.V();
        distances.resize(edges, 10000);
        distances[u] = 0;
        priority_queue<edge> pq;
        for (int i=0; i<edges; i++) {
            double distance = 10000;
            if (i != u) {
                if (g.adjacent(u, i)) {
                    distance = g.get_edge_value(i, u);
                }
            } else {
                distance = 0; 
            }
            pq.push(edge(i, distance));
        }

        while (pq.size() > 0) {
            edge e = pq.top();
            pq.pop();
            if (e.dist >= 10) return distances[w]; // unreachable
            for (int v : g.neighbors(e.dest)) {
                double alt_dist = distances[e.dest] + g.get_edge_value(e.dest, v);
                if (distances[v] > alt_dist) {
                    distances[v] = alt_dist; 
                    pq.push(edge(v, alt_dist));
                }
            }
            if (e.dest == w) return distances[w];

        }

        return distances[w];
    }
}
