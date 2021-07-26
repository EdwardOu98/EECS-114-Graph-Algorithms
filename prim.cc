#include "prim.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <iomanip>

#include "BHeap.h"

using namespace std;

// Constructor
Graph::Graph(const char* filename){

    FILE *fp;

    if((fp = fopen(filename, "r")) == NULL){
        fprintf(stderr, "Fail to open input file \'%s\', aborting\n", filename);
        exit(10);
    }
    fscanf(fp, "%d", &nVert);
    vertices = new BHeap(nVert);
    Result =  new Vertex[nVert];
    inMST = new bool[nVert];
    int s, d;
    double w;
    // Read from file
    while(!feof(fp)){
        fscanf(fp, " %d %d %lf ", &s, &d, &w);
        // Because the graph is undirected, we
        // need count one edge twice, one with
        // source to destination, the other with
        // destination to source
        addEdge(s, d, w);
        addEdge(d, s, w);
    }

    fclose(fp);

    //vertices->printHeap();
}

// Add an edge to the graph
void Graph::addEdge(int s, int d, double w){
    Edge e(d, w);
    vertices->getElem(s)->adj.push_back(e);
}

// Deallocates memory for the graph
void Graph::DeleteGraph(){
    vertices->deleteHeap();
    delete vertices;
    delete[] Result;
    delete[] inMST;
}

// Prim's algorithm
void Graph::MST_Prim(){

    // Initialize the result array, where the
    // information of MST is stored, and the
    // inMST array which will keep track of 
    // whether a vertex has been added to the MST
    for(int i = 0; i < nVert; i++){
        Result[i].val = i;
        if(i == 0){
            Result[i].key = 0.0;
        }
        else{
            Result[i].key = INFINITY;
        }
        Result[i].parent = -1;
        inMST[i] = false;
    }
    // Main loop
    while(!(vertices->empty())){
        // Extract the root vertex
        Vertex* u;
        u = vertices->ExtractMin();
        int val = u->val;
        // Go through each vertex in u's adjacency list
        for(int j = 0; j < u->adj.size(); j++){
            int v = u->adj.at(j).dest;
            double w = u->adj.at(j).weight;
            // if v is nor in MST and w(u,v) is smaller
            // than the current key of v, update v.key
            // with the new weight and set v.parent to
            // u
            if((!inMST[v]) && (w < Result[v].key)){
                // This for-loop updates the priority queue
                // by looking for the position of the 
                // given v value
                // It takes up the majority of running time, 
                // Resulting in O(v) time
                for(int l = 0; l < vertices->getSize(); l++){
                    if(vertices->getVertVal(l) == v){
                        vertices->decreaseKey(l, w);
                        break;
                    }
                }
                // Wirte the information to the Result array
                Result[v].key = w;
                Result[v].parent = val;
            }
        }
        // After going through u's adjacency list, update the
        // inMST array, which indicates that u has been added
        // to the MST
        inMST[val] = true;
        // Deallocates memory
        //delete u;
    }
}

// Write to output file
void Graph::WriteToFile(){
    FILE *fp;
    if((fp = fopen("mst.txt", "w")) == NULL){
        fprintf(stderr, "Failed to open output file\n");
        exit(11);
    }

    double sum = 0.0;

    for(int i = 0; i < nVert; i++){
        // If Result[i].key is infinity, then it means
        // the vertex corresponding to i doesn't exist
        // in the graph
        if(Result[i].key != INFINITY){
            sum += Result[i].key;
        }
    }

    fprintf(fp, "%lf\n", sum);

    for(int j = 1; j < nVert; j++){
        if(Result[j].key != INFINITY){
            //fprintf(fp, "\n");
            fprintf(fp, "%d %d %lf\n", Result[j].val, Result[j].parent, Result[j].key);
        }
    }

    fclose(fp);
}
