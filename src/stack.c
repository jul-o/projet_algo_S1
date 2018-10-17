#include "stack.h"

Node * createStack(){
    return NULL;
}

// Pré-conditions : stack not empty
void pushStack(Node ** stack, int v){
    if(*stack == NULL){
        printf("pushStack ERROR : cannot push on an empty stack");
    }

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