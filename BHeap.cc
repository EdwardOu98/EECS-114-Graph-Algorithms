#include "BHeap.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Create a binary heap of vertices
BHeap::BHeap(int c){
    size = c;
    capacity = c;
    heap = new Vertex[c];
    for(int i = 0; i < c; i++){
        heap[i].val = i;
        if(i == 0){
            heap[i].key = 0;
        }
        else{
            heap[i].key = INFINITY;
        }
    }
}

// Swap to nodes of the heap
void BHeap::swap(Vertex* x, Vertex* y){
    Vertex tmp = *x;
    *x = *y;
    *y = tmp;
}

// Insert a node into the heap
void BHeap::insertKey(Vertex vert){
    if(size == capacity){
        printf(" Heap is full, failed to insert \n");
        return;
    }

    heap[size] = vert;
    int i = size;
    int p = findParent(i);
    size++;

    while((i != 0) && (heap[p].key > heap[i].key)){
        swap(&heap[p], &heap[i]);
        i = p;
        p = findParent(i);
    }
}

// Decrease the key value of node at index i
void BHeap::decreaseKey(int i, double new_val){
    if(new_val > heap[i].key){
        printf("New value is larger than the old value, failed to decrease\n");
        return;
    }

    heap[i].key = new_val;
    int p = findParent(i);

    while((i != 0) && (heap[p].key > heap[i].key)){
        swap(&heap[p], &heap[i]);
        i = p;
        p = findParent(i);
    }
}

// Delete the node at index i
void BHeap::deleteKey(int i){
    decreaseKey(i, -1.0);
    ExtractMin();
}

// Maintain the property of min heap
void BHeap::MinHeapify(int i){
    int l = findLeftChild(i);
    int r = findRightChild(i);
    int min = i;
    if((l < size) && (heap[l].key < heap[i].key)){
        min = l;
    }
    if((r < size) && (heap[r].key < heap[min].key)){
        min = r;
    }
    if(min != i){
        swap(&heap[min], &heap[i]);
        MinHeapify(min);
    }
}

// Print out the content of heap
void BHeap::printHeap(){

    for(int i = 0; i < size; i++){
        for(int j = 0; j < heap[i].adj.size(); j++){
            printf("%d - %d, %lf\n", i, heap[i].adj[j].dest, heap[i].adj[j].weight);
        }
    }

}

// Deallocate memory
void BHeap::deleteHeap(){
    delete[] heap;
}

// Check if the heap is empty
bool BHeap::empty(){
    if(size == 0){
        return true;
    }
    return false;
}

// Extract the vertex with the minimum key value
Vertex* BHeap::ExtractMin(){

    // Move the last vertex in the heap
    // to the head of the heap, decrement
    // size and make sure the property
    // of min heap is maintained
    swap(&heap[0], &heap[size-1]);
    size--;
    MinHeapify(0);

    // Return the element at index
    // size, which is the minimum
    // element of the original heap
    return &heap[size];
}

// Calculate the parent of index i
int BHeap::findParent(int i){
    return (i-1)/2;
}

// Calculate the left child of index i
int BHeap::findLeftChild(int i){
    return 2 * i + 1;
}

// Calculate the right child of index i
int BHeap::findRightChild(int i){
    return 2 * i + 2;
}
