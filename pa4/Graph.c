//
// Created by aaron on 5/23/2019.
//
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
    G-> neighbors = malloc((n+1)*sizeof(List));
    G-> size = 0;
    G-> source = NIL;
    G-> parent = malloc((n+1)*sizeof(int));
    G-> color = malloc((n+1)* sizeof(int));
    //G-> queue = malloc(n* sizeof(int));
    G-> distance = malloc((n+1)* sizeof(int));
    for(int x = 0; x < n+1; x++){
        G->neighbors[x] = newList();
        G->parent[x] = NIL;
        G->distance[x] = INF;
        G->color[x] = WHITE;
        //G->queue[x] = NIL;
    }
    return G;
}
void freeGraph(Graph* pG){
    for(int x = 0; x < (*pG)->order + 1; x++){
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
int getDist(Graph G, int u){
  if(G != NULL){

  }else if( getSource(G) == u){
        return -1;
    }
    return G->distance[u];
}
void getPath(List L, Graph G, int u){
    if(u >= 1 && u <=  getOrder(G)) {
        if (getSource(G) == NIL) {
            printf("getPath called before BFS\n");
            exit(1);
        }
        if (G->source == u) {
            append(L, u);
        } else if (G->parent[u] != NIL) {
            getPath(L, G, G->parent[u]);
            append(L, u);
        }
    }else{
        append(L, NIL);
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


/*** Other operations ***/
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

void BFS(Graph G, int s){
    if(G != NULL && s >= 1 && s <= G->order){
      for(int i = 0; i <= getOrder(G);i++){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
      }
        G->source = s;
        G->distance[s] = 0;
        G->color[s] = GRAY;
        G->parent[s] = NIL;
        List Q = newList();
        List adj;
        append(Q, s);
        int current;
        while(length(Q) != 0){
            current = dequeue(Q);
            adj = G->neighbors[current];
            if(length(adj) != 0) {
                moveFront(adj);
                while (index(adj) != -1) {
                    if (G->color[get(adj)] == WHITE) {
                        append(Q, get(adj));
                        G->parent[get(adj)] = current;
                        G->color[get(adj)] = GRAY;
                        G->distance[get(adj)] = G->distance[current] + 1;
                    }
                    moveNext(adj);
                }
            }
            G->color[current] = BLACK;
        }
        freeList(&Q);
    }
}
