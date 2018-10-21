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
void pushStack(Node ** stack, open_rect v);
void popStack(Node ** stack);
void printStack(Node * stack);
int isStackEmpty(Node * stack);
open_rect readStack(Node * stack);

#endif