#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tag_stack
{
	int element;
	struct tag_stack *next;
}Stack;

Stack* push(Stack *top, int el)
{
	Stack *ptr = malloc(sizeof(Stack));
	ptr->element = el;
	ptr->next = top;
	return ptr;	
}

Stack* pop(Stack *top)
{
	if(top == NULL) {
		return top;
	}
	printf("%d\n", top->element);
	Stack *ptr_next = top->next;
	free(top);
	return ptr_next;
}

int peek(Stack *top)
{
	Stack *ptr_next = top->next;
	return ptr_next->element;
}

int main(int argc, char const *argv[])
{
	Stack *stack = NULL;
	for (int i = 1; i <= 5; ++i) {
		stack = push(stack, i);
	}
	while(stack != NULL) {
		stack = pop(stack);
	}
	return 0;
}
