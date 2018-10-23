#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>

typedef struct node_s Node;
struct open_rect{
    int h;
    int x;
};
typedef struct open_rect open_rect;

Node * createStack();
void pushStack(Node ** stack, int x, int h);
void popStack(Node ** stack);
void printStack(Node * stack);
int isStackEmpty(Node * stack);
void readStack(Node * stack, int * x, int * h);

#endif