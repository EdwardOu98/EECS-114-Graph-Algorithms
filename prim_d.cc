#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "prim.h"
#include "BHeap.h"

#include "timer.c"

int main(int argc, char* argv[]){

    char* fname;
    int v;
    int s, d;
    double w;

    if(argc == 2){
        fname = argv[1];
    }
    else{
        fprintf(stderr, "usage: \n");
        fprintf(stderr, "      %s <filename>\n", argv[0]);
        fprintf(stderr, "      where <filename> is the name of the input file\n");
        return -1;
    }

    //printf("%s\n", fname);

    Graph g(fname);

    struct stopwatch_t* timer = stopwatch_create();
    assert(timer);

    //printf("Find MST\n");
    stopwatch_start(timer);
    g.MST_Prim();
    float t = stopwatch_stop(timer);

    g.WriteToFile();

    g.DeleteGraph();

    printf("Time: %f\n", t);

    stopwatch_destroy(timer);

    return 0;
}
