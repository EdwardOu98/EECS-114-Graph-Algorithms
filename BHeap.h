#ifndef BHEAP_H
#define BHEAP_H

#include "Graph.h"

class BHeap{
    public:
        /* Constructor */
        BHeap(int c);

        /* Functions */
        void swap(Vertex* x, Vertex* y);
        void insertKey(Vertex vert);
        void decreaseKey(int i, double new_val);
        void deleteKey(int i);
        void MinHeapify(int i);
        void printHeap();
        void deleteHeap();
        bool empty();
        int findParent(int i);
        int findLeftChild(int i);
        int findRightChild(int i);
        Vertex* ExtractMin();

        /* Getters */
        int getCapacity() { return capacity; }
        int getSize() { return size; }
        Vertex* getMin() { return &heap[0]; };
        Vertex* getElem(int i) { return &heap[i]; }
        int getVertVal(int i) { return heap[i].val; }
        Vertex* getHeap() { return heap; }

    private:
        /* Parameters */
        int capacity;
        int size;
        Vertex* heap;
};

#endif

/* eof */
