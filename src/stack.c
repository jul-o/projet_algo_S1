#include "stack.h"

// Defining struct here for encapsulation
struct node_s{
    int x;
    int h;
    struct node_s * next;
};

Node * createStack(){
    return NULL;
}

void pushStack(Node ** stack, int x, int h){
    Node * newNode = malloc(sizeof(Node));
    newNode->x = x;
    newNode->h = h;
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

    // free((*stack)->v);
    free(*stack);
    *stack = newHead;
}

// void printStack(Node * stack){
//     while(stack != NULL){
//         printf("%d ", (stack->v).h);
//         stack = stack->next;
//     }
//     printf("\n");
// }

// TODO : ajouter préconditions 
void readStack(Node* stack, int * x, int * h){
    *x=stack->x,
    *h=stack->h;
}