#ifndef PRIM_H
#define PRIM_H

#include <vector>

#define V 100000

#include "BHeap.h"

class Graph{
    public:
        // Constructor
        Graph(const char* filename);
        // Functions
        //Vertex CreateVertex(int value);
        //Edge CreateEdge(int d, double w);
        void addEdge(int s, int d, double w);
        void DeleteGraph();
        void MST_Prim();
        void WriteToFile();

        // Getters
        int getnVert() { return nVert; }
        BHeap* getVertices() { return vertices; }
    // Parameters
    private:
        int nVert; // Number of vertices
        BHeap* vertices;
        Vertex* Result;
        bool* inMST;
};

#endif
