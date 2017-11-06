/*  Zhiwei Huang    21450851        
    Ken Di Vincenzo 21946068
*/

// Functions for manipulating stack during DFS

// Reference - https://groups.csail.mit.edu/graphics/classes/6.837/F04/cpp_notes/stack1.html

#include "percolation.h"

void Stack_Init(Stack *S)
{
    S->size = 0;
    S->data = (int *)malloc(STACK_MAX * sizeof(int));
}

int Stack_Top(Stack *S)
{
    if (S->size == 0) {
        fprintf(stderr, "Error: stack empty\n");
        return -1;
    } 

    return S->data[S->size-1];
}

void Stack_Push(Stack *S, int d)
{
    if (S->size < STACK_MAX)
        S->data[S->size++] = d;
    else
        fprintf(stderr, "Error: stack full\n");
}


void Stack_Pop(Stack *S)
{
    if (S->size == 0)
        fprintf(stderr, "Error: stack empty\n");
    else
        S->size--;
}

