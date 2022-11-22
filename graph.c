// Grafo + Lista

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

Node *createnode(void *data){
    Node *new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->up = NULL;
    new->down = NULL;
    new->left = NULL;
    new->right = NULL;
    return new;
}

GraphList *createGraphList(){
    GraphList *l = (GraphList *)malloc(sizeof(GraphList *));
    l->head = NULL;
    l->current = l->head;
    return l;
}

void * upList(GraphList * list){
  if(list->current == NULL) return NULL;
  if (list->current->up == NULL) return NULL;
  list->current = list->current->up;
  return list->current->data;
}

void * downList(GraphList * list){
  if(list->current == NULL) return NULL;
  if (list->current->down == NULL) return NULL;
  list->current = list->current->down;
  return list->current->data;
}

void * rightList(GraphList * list){
  if(list->current == NULL) return NULL;
  if (list->current->right == NULL) return NULL;
  list->current = list->current->right;
  return list->current->data;
}

void * leftList(GraphList * list){
  if(list->current == NULL) return NULL;
  if (list->current->left == NULL) return NULL;
  list->current = list->current->left;
  return list->current->data;
}

void pushUp(GraphList * list, void * data){
    Node * newNode = createNode(data);
    newNode->down = list->current;
    newNode->up = list->current->up;
    list->current->up = newNode;
}

void pushDown(GraphList * list, void * data){
    Node * newNode = createNode(data);
    newNode->up = list->current;
    newNode->down = list->current->down;
    list->current->down = newNode;
}

void pushRight(GraphList * list, void * data){
    Node * newNode = createNode(data);
    newNode->left = list->current;
    newNode->right = list->current->right;
    list->current->right = newNode;
}

void pushLeft(GraphList * list, void * data){
    Node * newNode = createNode(data);
    newNode->right = list->current;
    newNode->left = list->current->left;
    list->current->left = newNode;
}
