#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

using namespace std;

// parameters and constructor of
// edge
struct Edge{
    int dest;
    double weight;
    Edge(const int d, const double w)
        : dest(d), weight(w) {}
};

// Parameters of a vertex
struct Vertex{
    int val;
    double key;
    int parent;
    std::vector<Edge> adj;
};

#endif
