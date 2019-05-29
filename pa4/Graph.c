//
// Created by aaron on 5/23/2019.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"List.h"
#include"List.c"
#include"Graph.h"

#define INF -8
#define NIL -9
#define WHITE -1
#define GRAY -2
#define BLACK -3


/*** Constructors-Destructors ***/

typedef struct GraphObj{
    List *neighbors;
    int *parent;
    int *color;
    //int *queue;
    int *distance;
    int source;
    int order;
    int size;


} GraphObj;

typedef GraphObj *Graph;

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    assert(G != NULL);
    G-> order = n;
    G-> neighbors = malloc(n*sizeof(List));
    G-> size = 0;
    G-> source = NIL;
    G-> parent = malloc(n*sizeof(int));
    G-> color = malloc(n* sizeof(int));
    //G-> queue = malloc(n* sizeof(int));
    G-> distance = malloc(n* sizeof(int));
    for(int x = 0; x < n; x++){
        G->neighbors[x] = newList();
        G->parent[x] = NIL;
        G->distance[x] = INF;
        G->color[x] = WHITE;
        //G->queue[x] = NIL;
    }
    return G;
}
void freeGraph(Graph* pG){
    for(int x = 0; x < (*pG)->order; x++){
        freeList(&((*pG)->neighbors[x]));
    }
    //free((*pG)->queue);
    free((*pG)->parent);
    free((*pG)->distance);
    free((*pG)->color);
    free((*pG)->neighbors);
    //(*pG)->queue = NULL;
    (*pG)->parent = NULL;
    (*pG)->distance = NULL;
    (*pG)->color = NULL;
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
}
int getSize(Graph G){
    if(G != NULL){
        return G->size;
    }
}
int getSource(Graph G){
    if( G!= NULL){
        return  G->source;
    }
}
int getParent(Graph G, int u){
    if( G != NULL){

    }else if( u < 1 || u > G->order){

    }
    return G->parent[u];
}
int getDist(Graph G, int u){
    if( G != NULL){

    }else if( u < 1 || u > G->order){

    }
    return G->distance[u];
}
void getPath(List L, Graph G, int u){
    if(G->source == u){
        append(L, u);
    }else if( G->source != NIL){
        getPath(L, G, G->parent[u]);
        append(L,u);
    }else{

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
    if(G != NULL && u >= 1 && u <= getOrder(G), v >= 1 && v <= getOrder(G)){
        addArc(G, u, v);
        addArc(G, v, u);
        G->size++;
    }
}
void addArc(Graph G, int u, int v){
    if(G != NULL && u >= 1 && u <= getOrder(G), v >= 1 && v <= getOrder(G)){
        List A = G->neighbors[u];
        if(length(A) == 0){
            prepend(A, v);
        }else {
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
        }
        G->size++;
    }else{

    }
}


/*** Other operations ***/
void printGraph(FILE* out, Graph G){

}

void BFS(Graph G, int s){
    if(G != NULL && s >= 1 && s <= G->order){
        G->source = s;
        G->distance[s] = 0;
        G->color[s] = GRAY;
        List Q = newList();
        List adj;
        append(Q, s);
        int current;
        while(length(Q) != 0){
            current = dequeue(Q);
            adj = G->neighbors[current];
            moveFront(adj);
            while(index(adj) != -1){
                if(G->color[index(adj)] == WHITE){
                    append(Q, index(adj));
                    G->parent[index(adj)] = current;
                    G->color[index(adj)] = GRAY;
                    G->distance[index(adj)] = G->distance[current] + 1;
                }
                moveNext(adj);
            }
            G->color[current] = BLACK;
        }
        freeList(&Q);
    }
}