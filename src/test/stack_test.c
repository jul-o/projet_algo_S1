#include "../stack.h"

void testStack(){
    Node * stack = createStack();
    
    pushStack(&stack, 5);
    pushStack(&stack, 1);
    pushStack(&stack, 2);

    popStack(&stack);
    popStack(&stack);
    popStack(&stack);
    printf("Is stack empty : %d \n", isStackEmpty(stack));

    pushStack(&stack, 9);

    printStack(stack);
}