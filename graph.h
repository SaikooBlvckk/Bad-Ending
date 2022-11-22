#ifndef GRAPH_h
#define GRAPH_h

typedef struct{
    void *data;
    Node *up;
    Node *down;
    Node *left;
    Node *right;
}Node;

typedef struct GraphList{
    Node *head;
    Node *current;
}GraphList;

Node *createnode(void *data);
GraphList *createGraphList();
void * upList(GraphList * list);
void * downList(GraphList * list);
void * rightList(GraphList * list);
void * leftList(GraphList * list);
void pushUp(GraphList * list, void * data);
void pushDown(GraphList * list, void * data);
void pushRight(GraphList * list, void * data);
void pushLeft(GraphList * list, void * data);

#endif /* GRAPH_h */