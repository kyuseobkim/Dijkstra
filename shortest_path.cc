#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#include "shortest_path.h"

using namespace std;

namespace dijkstra {
    const double max = numeric_limits<double>::max();
    const double infty = numeric_limits<double>::infinity();

    struct edge {
        int dest;
        double dist;
        edge(int dest, double dist): dest(dest), dist(dist) {}
        bool operator<(const edge& b) const {
            return dist > b.dist;
        }
    };

    struct result {
        bool reachable;
        double distance;
        vector<int> path;
    };

    result shortest_path(const Graph& g, int u, int w) {
        result r;
        vector<double> distances;
        vector<int> path;
        vector<int> predecessors;

        int edges = g.V();
        distances.resize(edges, infty);
        predecessors.resize(edges);

        distances[u] = 0;
        priority_queue<edge> pq;
        for (int i=0; i<edges; i++) {
            double distance = infty;
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
            if (e.dist >= max) break; // unreachable
            for (int v : g.neighbors(e.dest)) {
                double alt_dist = distances[e.dest] + g.get_edge_value(e.dest, v);
                if (distances[v] > alt_dist) {
                    distances[v] = alt_dist; 
                    pq.push(edge(v, alt_dist));
                    predecessors[v] = e.dest;
                }
            }
            if (e.dest == w) break;
        }

        if (distances[w] >= max) {
            r.reachable = false;
        } else {
            int temp = w;
            path.push_back(temp);
            while (predecessors[temp] != u) {
                temp = predecessors[temp];
                path.push_back(temp);
            }
            path.push_back(u);
            reverse(path.begin(), path.end());
            r.reachable = true;
            r.distance = distances[w];
            r.path = path;
        }

        return r;

    }

    double ShortestPath::path_size(int u, int w) {
        result r = shortest_path(g, u, w);
        return r.distance;
    }

    vector<int> ShortestPath::path(int u, int w) {
        result r = shortest_path(g, u, w);
        return r.path;
    }
}
