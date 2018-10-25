#include "../stack.h"

void testStack() {
    open_rect r1;
    r1.x = 0;
    r1.h = 1;
    open_rect r2;
    r2.x = 1;
    r2.h = 2;
    open_rect r3;
    r3.x = 2;
    r3.h = 3;

    Node* stack = createStack();

    pushStack(&stack, &r1);
    pushStack(&stack, &r2);
    pushStack(&stack, &r3);

    printf("Is stack empty : %d \n", isStackEmpty(stack));

    popStack(&stack);
    popStack(&stack);
    popStack(&stack);
    printf("Is stack empty : %d \n", isStackEmpty(stack));

}