//-----------------------------------------------------------------------------
//
// GraphClient.c
// 
// This is a fancy test client that calculates the Radius and Diameter of 
// the graph defined on lines 41-49, along with its Central and Peripheral 
// vertices.  The definitions of these terms at:
// 
//    http://en.wikipedia.org/wiki/Distance_(graph_theory)
// 
// Place this file in a directory with copies of your List.c, List.h, Graph.c, 
// Graph.h and an appropriate Makefile, then compile and run. The output 
// is contained in the file GraphClientOut.
// 
// This program does not exercise all functions in your Graph ADT, but it 
// does a pretty good job of testing BFS().  If your output differs from 
// the above, you have a logical problem in either your Graph or List ADT.
// 
// Remember you are required to submit a file named GraphTest.c with pa4 that
// exercises your Graph functions.  Do not submit this file.
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
    int n = 15;
    Graph A = newGraph(n);

    printf("Order: %d\n", getOrder(A));
    printf("Size: %d\n", getSize(A));
    printf("Source: %d\n", getSource(A));
    printf("Parent of 1: %d\n", getParent(A, 1));
    printf("Distance to source: %d\n", getDist(A, 1));
    printf("fuck1");
    printf("\n");
    printf("fuck2");
    addEdge(A,1,2);
    addEdge(A,2,3);
    addEdge(A,3,5);
    addEdge(A,1,6);
    addEdge(A,2,5);
    addEdge(A,4,3);
    addEdge(A,10,2);
    addEdge(A,7,3);
    printf("fuck3");
    addEdge(A,11,5);
    addEdge(A,14,1);
    addEdge(A,15,2);
    addEdge(A,9,7);
    addEdge(A,13,1);

    printf("fuck4");
    printGraph(stdout, A);

    printf("Size: %d\n", getSize(A));
    printf("Source: %d\n", getSource(A));
    printf("Parent of 1: %d\n", getParent(A, 1));
    printf("Distance to source: %d\n", getDist(A, 1));
    printf("\n");

    addEdge(A,1,2);
    printGraph(stdout, A);
    printf("Size: %d\n", getSize(A));
    addArc(A,5,4);
    printGraph(stdout, A);
    printf("Size: %d\n", getSize(A));
    addArc(A,4,5);
    printGraph(stdout, A);
    printf("Size: %d\n", getSize(A));

    printf("\n");

    BFS(A,1);
    printf("Source: %d\n", getSource(A));
    printf("Parent of 1: %d\n", getParent(A, 1));
    printf("Parent of 2: %d\n", getParent(A, 2));
    printf("Parent of 3: %d\n", getParent(A, 3));
    printf("Parent of 4: %d\n", getParent(A, 4));
    printf("Parent of 5: %d\n", getParent(A, 5));
    printf("Distance (1,4): %d\n", getDist(A, 4));
    printf("Distance (1,5): %d\n", getDist(A, 5));
    printf("Distance (1,3): %d\n", getDist(A, 3));
    printf("Distance (1,2): %d\n", getDist(A, 2));
    printf("Distance (1,1): %d\n", getDist(A, 1));

    printf("\n");

    printf("Parent of 2: %d\n", getParent(A, 2));
    printf("Distance (2,15): %d\n", getDist(A, 15));

    printf("\n");

    BFS(A,3);
    printf("Source: %d\n", getSource(A));
    printf("Parent of 1: %d\n", getParent(A, 1));
    printf("Parent of 2: %d\n", getParent(A, 2));
    printf("Parent of 3: %d\n", getParent(A, 3));
    printf("Parent of 4: %d\n", getParent(A, 4));
    printf("Parent of 5: %d\n", getParent(A, 5));
    printf("Distance (3,1): %d\n", getDist(A, 4));
    printf("Distance (3,2): %d\n", getDist(A, 1));
    printf("Distance (3,3): %d\n", getDist(A, 5));
    printf("Distance (3,4): %d\n", getDist(A, 2));
    printf("Distance (3,5): %d\n", getDist(A, 3));

    printf("\n");

    makeNull(A);
    printGraph(stdout, A);
    printf("Order: %d\n", getOrder(A));
    printf("Size: %d\n", getSize(A));
    printf("Source: %d\n", getSource(A));

    freeGraph(&A);

    return(0);
   /*int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G

   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);*/
}
