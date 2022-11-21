#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    void *data;
    Node *up;
    Node *down;
    Node *left;
    Node *right;
} Node;

