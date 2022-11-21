#ifndef GRAPH_h
#define GRAPH_h

typedef struct Node Node;
typedef struct List List;

Node *createnode(void *data);
List *createList();
void * upList(List * list);
void * downList(List * list);
void * rightList(List * list);
void * leftList(List * list);
void pushUp(List * list, void * data);
void pushDown(List * list, void * data);
void pushRight(List * list, void * data);
void pushLeft(List * list, void * data);

#endif /* GRAPH_h */