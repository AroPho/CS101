// PA4
// CMPS 101 Tantalo Spring 2019
// Aaron Nguyen
// anguy200
// 1585632

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#ifndef MAX_LEN
#define MAX_LEN 160
#endif
typedef char *string;

int main (int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        printf("FindPath <input file> <output file>\n");
        exit (1);
    }
    // Init, open and check files
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL) {
        printf("Unable to open file %s for reading.\n", argv[1]);
        exit(1);
    } if (out == NULL) {
        printf("Unable to open file %s for writing.\n", argv[2]);
        exit(1);
    }

    // Collect number of vertices and init Graph
    int v;
    fscanf(in, "%d", &v);
    Graph G = newGraph(v);

    // Populate Graph
    int x,y;
    while (fscanf(in, "%d %d", &x, &y) == 2) {
        if (x == 0 && y == 0){
            break;
        }
        addEdge(G,x,y);
    }

    // Print the Graph
    printGraph(out, G);

    // Print the paths
    List L = newList();
    int source, destination;
    while (fscanf(in, "%d %d", &source, &destination)) {
        if (source == 0 && destination == 0){
            break;
        }
        BFS(G, source);
        getPath(L, G, destination);
        fprintf(out, "\nThe distance from %d to %d is ", source, destination);
        if(getDist(G, destination) != -1){
            fprintf(out, "%d\n", getDist(G, destination));
            fprintf(out, "A shortest %d-%d path is: ", source, destination);
            printList(out, L);
            fprintf(out, "\n");
        }else {
            fprintf(out, "infinity\nNo %d-%d path exists\n", source, destination);
        }
        clear(L);
    }
    // Clean up
    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out);
}
