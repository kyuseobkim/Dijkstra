#include <iostream>
#include <queue>
#include <vector>

#include "shortest_path.h"

using namespace std;

namespace dijkstra {
    const int max_dist = 10;

    struct edge {
        int dest;
        double dist;
        edge(int dest, double dist): dest(dest), dist(dist) {}
        friend bool operator<(const edge&a, const edge& b) {
            return a.dist > b.dist;
        }
    };

    struct result {
        bool reachable;
        double distance;
        vector<int> path;
    };

    result shortest_path(const Graph& g, int u, int w) {
        result r;
        int edges = g.V();
        vector<double> distances(edges, 10000);
        vector<int> path;
        vector<int> predecessors(edges);

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
            if (e.dist >= max_dist) break; // unreachable
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

        if (distances[w] >= max_dist) {
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
