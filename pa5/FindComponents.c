// PA5
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
        addArc(G,x,y);
    }
    List S = newList();
    for (int i = 0; i < getOrder(G); ++i) {
        append(S,i);
    }

    // Print the Graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    DFS(G, S);
    Graph Gt = transpose(G);



    DFS(Gt, S);
    int scc = 0;
    for(int x = 1; x <= getOrder(G); x++){
        if(getParent(Gt, x) == NIL){
            scc++;
        }
    }
    List Components[scc];
    for(int x = 0; x < scc; x++){
        Components[x] = newList();
    }
    int comp = 0;
    moveFront(S);
    while(index(S) != -1 && comp != scc){
        if(getParent(Gt, get(S)) == NIL){
            comp++;
        }
        append(Components[comp], get(S));
        moveNext(S);
    }
    fprintf(out, "\nG contains 4 strongly connected components:");
    for(int x = 0; x < scc; x++){
        fprintf(out, "\nComponent %d: ", (x + 1));
        printList(out, Components[x]);
    }



    clear(S);
    clear(Components);
    // Clean up
    freeGraph(&G);
    freeList(&S);
    freeList(Components);
    fclose(in);
    fclose(out);
}

