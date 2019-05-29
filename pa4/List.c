//PA2
//CMPS 101 Tantalo Spring 2019
//Aaron Nguyen
//anguy200
//1585632








#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "List.h"

typedef struct NodeObj{
  int data;
  struct NodeObj *next;
  struct NodeObj *prev;
} NodeObj;

typedef NodeObj *Node;

Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  assert(N != NULL);
  N->data = data;
  N->next = NULL;
  return(N);
}

void freeNode(Node *pN){
  if(pN != NULL && *pN != NULL){
    free(*pN);
    *pN = NULL;
  }
}

typedef struct ListObj{
  Node head;
  Node tail;
  Node cursor;
  int index;
  int numItems;
} ListObj;

typedef struct ListObj *List;

List newList(void){
  List L = malloc(sizeof(ListObj));
  assert(L!=NULL);
  L->head = NULL;
  L->tail = NULL;
  L->cursor = NULL;
  L-> index = -1;
  L-> numItems = 0;
  return L;
}

void freeList(List *pL){
  if(pL != NULL && *pL != NULL){
    clear(*pL);
    free(*pL);
    *pL = NULL;
  }
}


int length(List L){
  if(L == NULL){
    printf("This shit broke");
  }
  return L->numItems;
}

int index(List L){
  return L->index;
}

int front(List L){
  if(L->numItems > 0){
    return L->head->data;
  }else{
    return -1;
  }
}

int back(List L){
  if(L->numItems > 0){
    return L->tail->data;
  }else{
    return -1;
  }
}

int get(List L){
  if(L->numItems > 0 && L->index >= 0 && L->index < L->numItems){
    return L->cursor->data;
  }else{
    return -1;
  }
}

int equals(List A, List B){
  if(A->numItems != B->numItems){
    return 0;
  }else{
    Node tempA = A->head;
    Node tempB = B->head;
    for(int x = 0; x < A->numItems; x++){
      if(tempA->data != tempB->data){
        return 0;
      }else{
        tempA = tempA->next;
        tempB = tempB->next;
      }
    }
    return 1;
  }
}

void clear(List L){
  Node N = NULL;
  if( L == NULL ){
   perror("List is Null or empty");
   exit(EXIT_FAILURE);
  }
  L->cursor = NULL;
  L->index = -1;
  while(L->numItems > 0){
    N = L-> head;
    L->head = L->head->next;
    N->next = NULL;
    freeNode(&N);
    L->numItems--;
  }
}

void moveFront(List L){
  if(L->numItems == 0){
    perror("List is Empty");
    exit(EXIT_FAILURE);
  }else{
    L->cursor = L->head;
    L->index = 0;
  }
}

void moveBack(List L){
  if(L-> numItems == 0){
    perror("List is Empty");
    exit(EXIT_FAILURE);
  }else{
    L->cursor = L->tail;
    L->index = L->numItems - 1;
  }
}

void movePrev(List L){
  if(L->index != -1 && L->cursor != L->head){
    L->cursor = L->cursor->prev;
    L->index--;
  }else if(L->cursor == L->head){
    L->cursor = NULL;
    L->index = -1;
  }
}

void moveNext(List L){
  if(L->cursor != NULL && L->cursor != L->tail){
    L->cursor = L->cursor->next;
    L->index++;
  }else if(L->cursor == L->tail){
    L->cursor = NULL;
    L->index = -1;
  }
}


void prepend(List L, int data){
  //Node N = NULL;
  //Node END = NULL;
  if(L==NULL){
    perror("List was not created properly");
    exit(EXIT_FAILURE);
  }
  if(L->numItems == 0){
    Node N = newNode(data);
    L->head = L->tail = N;
  }else{
    Node temp = L->head;
    L-> head = newNode(data);
    L->head->next = temp;
    temp->prev = L->head;
    if(L->index != -1){
      L->index++;
    }
    
  }
  L->numItems++;

}

void append(List L, int data){
  if(L==NULL){
    perror("List was not created correctly");
    exit(EXIT_FAILURE);
  }if(L->numItems == 0){
    L->head =  newNode(data);
    L->tail = L->head;
  }else{
    L->tail->next = newNode(data);
    L->tail->next->prev = L->tail;
    L->tail = L->tail->next;
  }
  L->numItems++;
}

void insertBefore(List L, int data){
  if(L->numItems != 0 && L->index >= 0){
    if(L->index == 0){
      prepend(L, data);
    }else{
      Node A = L->cursor->prev;
      Node temp = newNode(data);
      A->next = temp;
      temp -> prev = A;
      temp -> next = L->cursor;
      L->cursor->prev = temp;
      L->index++;
      L->numItems++;
    }
  }
}

void insertAfter(List L, int data){
  if(L->numItems != 0 && L->numItems >= 0){
    if(L->cursor == L->tail){
      append( L, data);
    }else{
      Node A = L->cursor->next;
      Node temp = newNode(data);
      A->prev = temp;
      temp->next = A;
      temp->prev = L->cursor;
      L->cursor->next = temp;
      L->numItems++;
    }
  }
}

void deleteFront(List L){
  if(L->numItems != 0){
    Node temp = L->head;
    L->head = L-> head->next;
    L->head->prev = NULL;
    freeNode(&temp);
    L->numItems--;
    if(L->index == 0){
      L->index--;
      L->cursor = NULL;
    }else if(L-> index != -1){
      L->index--;
    }
  }
}

void deleteBack(List L){
  if(L->numItems > 0){
    if(L->cursor == L->tail){
      L->cursor = NULL;
      L->index = -1;
    }if(L->numItems == 1){
      Node temp = L->tail;
      freeNode(&temp);
      L->tail = NULL;
      L->head = NULL;
      L->numItems--;
    }else{
      Node temp = L->tail;
      L->tail = L->tail->prev;
      L->tail->next = NULL;
      freeNode(&temp);
      L->numItems--;
    }
  }

}

void delete(List L){
  if(L->index == 0 && L->numItems > 0){
    deleteFront(L);
  }else if(L-> index == L->numItems - 1 && L -> numItems > 0){
    deleteBack(L);
  }else if(L->index >= 0 && L->numItems !=0){
    Node curprev = L->cursor->prev;
    Node curnext = L->cursor->next;
    curprev->next = curnext;
    curnext->prev = curprev;
    L->numItems--;
    freeNode(&L->cursor);
    L->index = -1;
    L->cursor = NULL;
  }

}

int dequeue(List L){
  if(L != NULL){
    moveFront(L);
    int x = get(L);
    delete(L);
    return x;
  }
  return -1;
}

void printNode(FILE *out, Node N){
  fprintf(out, "%d ", N->data);
}

void printList(FILE* out, List L){
  Node N = NULL;
  if(L==NULL){
    perror("List is not initialized");
    exit(EXIT_FAILURE);
  }
  N = L->head;
  while(N!=NULL){
    fprintf(out, "%d ", N->data);
    N = N->next;
  }
}

List copyList(List L){
  List tempList = newList();
  Node temp = L->head;
  while(temp != NULL){
    append(tempList, temp->data);
    temp = temp->next;
  }
  return tempList;
}







