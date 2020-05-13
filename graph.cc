#include <ctime>
#include <iostream>
#include <numeric>
#include <random>

#include "graph.h"

using namespace std;

namespace dijkstra {

Graph::Graph(double density, int size):
    size(size) {
    adjacency_matrix.resize(size, vector<bool>(size, false));
    distances.resize(size, vector<double>(size, 0.0));
    create_adjacency_matrix(density);
}

int Graph::E() {
    int sum = 0;
    for (int i=0; i<size; i++) {
        sum = accumulate(adjacency_matrix[i].begin(), adjacency_matrix[i].end(), sum);
    }
    return sum;
}

bool Graph::adjacent(int x, int y) {
    if (x == y) return true;
    else if (x < y) return adjacency_matrix[x][y];
    else return adjacency_matrix[y][x];
}

vector<int> Graph::neighbors(int x) {
    vector<int> ns;
    for (int i=0; i<size; i++) {
        if (i != x && adjacent(x, i)) ns.push_back(i);
    }

    return ns;
}

void Graph::add(int x, int y) {
    if (x < y) adjacency_matrix[x][y] = true;
    else adjacency_matrix[y][x] = true;
}

double Graph::get_edge_value(int x, int y) {
    if (x < y) return distances[x][y];
    else return distances[y][x];
}

void Graph::set_edge_value(int x, int y, double v) {
    if (x < y) distances[x][y] = v;
    else distances[y][x] = v;
}

void Graph::create_adjacency_matrix(double density) {
    uniform_real_distribution<double> adjacency_u(0.0, 1.0);
    uniform_real_distribution<double> distance_u(0.0, 10.0);
    default_random_engine adjacency_g(time(0));
    default_random_engine distance_g(time(0));

    for (int i=0; i<size; i++) {
        for (int j=i+1; j<size; j++) {
            adjacency_matrix[i][j] = (adjacency_u(adjacency_g) <= density);
            distances[i][j] = distance_u(distance_g); 
        }
    }
}

}
