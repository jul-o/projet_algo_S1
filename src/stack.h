#include <stdio.h>
#include <stdlib.h>

typedef struct node_s Node;

Node * createStack();
void pushStack(Node ** stack, int v);
void popStack(Node ** stack);
void printStack(Node * stack);
int isStackEmpty(Node * stack);