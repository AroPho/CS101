// PA4
// CMPS 101 Tantalo Spring 2019
// Aaron Nguyen
// anguy200
// 1585632
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"Graph.h"

typedef enum color{
    WHITE,
    GRAY,
    BLACK
}color;

/*** Constructors-Destructors ***/

typedef struct GraphObj{
    List *neighbors;
    int *parent;
    int *discover;
    int *color;
    //int *queue;
    int *finish;
    int source;
    int order;
    int size;


} GraphObj;

typedef GraphObj *Graph;

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G-> order = n;
    G-> neighbors = malloc((n+1)*sizeof(List));
    G-> size = 0;
    G-> source = NIL;
    G-> parent = malloc((n+1)*sizeof(int));
    G-> discover = malloc((n+1)* sizeof(int));
    G-> color = malloc(n* sizeof(int));
    G-> finish = malloc((n+1)* sizeof(int));
    for(int x = 0; x < n+1; x++){
        G->neighbors[x] = newList();
        G->parent[x] = NIL;
        G->finish[x] = INF;
        G->discover[x] = NIL;
        G->color[x] = WHITE;
    }
    return G;
}
void freeGraph(Graph* pG){
    for(int x = 0; x < (*pG)->order + 1; x++){
        freeList(&((*pG)->neighbors[x]));
    }
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->finish);
    free((*pG)->discover);
    free((*pG)->neighbors);
    (*pG)->color = NULL;
    (*pG)->parent = NULL;
    (*pG)->finish = NULL;
    (*pG)->discover = NULL;
    (*pG)->neighbors = NULL;
    free(*pG);
    *pG = NULL;
    return;
}

/*** Access functions ***/
int getOrder(Graph G){
    if( G != NULL){
        return  G->order;
    }
    return 0;
}
int getSize(Graph G){
    if(G != NULL){
        return G->size;
    }
    return -1;
}
int getSource(Graph G){
    if( G!= NULL){
        return  G->source;
    }
}
int getParent(Graph G, int u){
    if(G != NULL){

    } else if( u < 1 || u > getOrder(G)){

    }
    return G->parent[u];
}
int getDiscover(Graph G, int u){
    if(G != NULL){

    }else if( getSource(G) == u){
        return -1;
    }
    return G->discover[u];
}

int getFinish(Graph G, int u){
    return G->finish[u];
}

void getPath(List L, Graph G, int u){
    if (getSource(G) == NIL) {
        printf("getPath called before BFS\n");
        exit (1);
    }
    if(G->discover[u] == WHITE){
        append(L, NIL);
    }
    if (G->source == u) {
        append(L, u);
    } else if (G->parent[u] != NIL) {
        getPath(L, G, G->parent[u]);
        append(L,u);
    }
}


/*** Manipulation procedures ***/
void makeNull(Graph G){
    if(G != NULL){
        for(int x = 0; x < G->order; x++){
            clear(G->neighbors[x]);
        }
        G->size = 0;
    }else{

    }

}
void addEdge(Graph G, int u, int v){
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph verticies out of bounds\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
void addArc(Graph G, int u, int v){
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        printf("Graph verticies out of bounds\n");
        exit(1);
    }
    List adj = G->neighbors[u];
    if(length(adj) == 0) {
        prepend(adj, v);
    }else{
        moveFront(adj);
        while (index(adj) != -1 && v > get(adj)) {
            moveNext(adj);
        }
        if (index(adj) == -1){
            append(adj, v);
        }
        else{
            insertBefore(adj, v);
        }
    }
    G->size++;
    /*if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
        List A = G->neighbors[u];
        *//*if(A != NULL && length(A) == 0){
            prepend(A, v);

        }else {*//*
            moveFront(A);
            while (index(A) != -1) {
                if (index(A) > v) {
                    insertBefore(A, v);
                    break;
                } else {
                    moveNext(A);
                }
            }
            if (index(A) == -1) {
                append(A, v);
            }
        //}
        G->size++;
    }else{

    }*/
}

int Visit(Graph G, List L, int u, int *time){

    List adj = G->neighbors[u];
    moveFront(adj);
    int current;
    G->color[u] = GRAY;
    G->discover[u] = ++*time;

    while(index(adj) != -1){
        current = get(adj);
        if(G->color[current] == WHITE){
            Visit(G, L, current, time);
        }
        moveNext(adj);
    }
    G->color[u] = BLACK;
    G->finish[u] = ++*time;
    prepend(L, u);
}

void DFS(Graph G, List S){
    for(int i = 0; i <= getOrder(G);i++){
        G->discover[i] = WHITE;
        G->finish[i] = INF;
        G->parent[i] = NIL;
    }
    int time = 0;
    moveFront(S);
    while(index(S) != -1){
        int vertex = get(S);
        if(G->color[vertex] == WHITE){
            Visit(G, S, vertex, &time);
        }
        moveNext(S);
    }
}

/*** Other operations ***/

Graph transpose(Graph G){
    Graph T = newGraph(getOrder(G));
    List adj;
    for(int x = 1; x <= getOrder(G); x++){
        adj = G->neighbors[x];
        if(length(adj) != 0){
            moveFront(adj);
            while(index(adj) != -1){
                addArc(T, get(adj), x);
                moveNext(adj);
            }
        }
    }
    return T;
}

Graph copyGraph(Graph G){
    Graph A = newGraph(getOrder(G));
    List adj;
    for(int x = 1; x <= getOrder(G); x++){
        adj = G->neighbors[x];
        if(length(adj) != 0){
            moveFront(adj);
            while(index(adj) != -1){
                addArc(A, x, get(adj));
                moveNext(adj);
            }
        }
    }
    return A;
}

void printGraph(FILE* out, Graph G){
    if (out == NULL) {
        exit(1);
    } else if (G == NULL) {
        exit(1);
    } for (int i = 1; i <= getOrder(G); i++) {
        fprintf(out,"%d: ",i);
        printList(out,G->neighbors[i]);
        fprintf(out, "\n");
    }
}



