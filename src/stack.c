#include "stack.h"

// Defining struct here for encapsulation
struct node_s{
    int v;
    struct node_s * next;
};

Node * createStack(){
    return NULL;
}

void pushStack(Node ** stack, int v){
    Node * newNode = malloc(sizeof(Node));
    newNode->v = v;
    newNode->next = *stack;

    *stack = newNode;
}

int isStackEmpty(Node * stack){
    return stack == NULL;
}

// Pré-conditions : stack not empty
void popStack(Node ** stack){
    if(*stack == NULL){
        printf("popStack ERROR : trying to pop on a empty stack \n");
        return;
    }

    Node * newHead = (*stack)->next;
    if(newHead == NULL)  *stack = NULL;

    free(*stack);
    *stack = newHead;
}

void printStack(Node * stack){
    while(stack != NULL){
        printf("%d ", stack->v);
        stack = stack->next;
    }
    printf("\n");
}