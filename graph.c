// Grafo + Lista

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

struct Node{
    void *data;
    Node *up;
    Node *down;
    Node *left;
    Node *right;
};

struct List{
    Node *head;
    Node *current;
};

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

List *createList(){
    List *l = (List *)malloc(sizeof(List *));
    l->head = NULL;
    l->current = l->head;
    return l;
}

void * upList(List * list){
  if(list->current == NULL) return NULL;
  if (list->current->up == NULL) return NULL;
  list->current = list->current->up;
  return list->current->data;
}

void * downList(List * list){
  if(list->current == NULL) return NULL;
  if (list->current->down == NULL) return NULL;
  list->current = list->current->down;
  return list->current->data;
}

void * rightList(List * list){
  if(list->current == NULL) return NULL;
  if (list->current->right == NULL) return NULL;
  list->current = list->current->right;
  return list->current->data;
}

void * leftList(List * list){
  if(list->current == NULL) return NULL;
  if (list->current->left == NULL) return NULL;
  list->current = list->current->left;
  return list->current->data;
}

void pushUp(List * list, void * data){
    Node * newNode = createNode(data);
    newNode->down = list->current;
    newNode->up = list->current->up;
    list->current->up = newNode;
}

void pushDown(List * list, void * data){
    Node * newNode = createNode(data);
    newNode->up = list->current;
    newNode->down = list->current->down;
    list->current->down = newNode;
}

void pushRight(List * list, void * data){
    Node * newNode = createNode(data);
    newNode->left = list->current;
    newNode->right = list->current->right;
    list->current->right = newNode;
}

void pushLeft(List * list, void * data){
    Node * newNode = createNode(data);
    newNode->right = list->current;
    newNode->left = list->current->left;
    list->current->left = newNode;
}
