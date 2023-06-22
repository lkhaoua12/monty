#include "monty.h"

void handleAdd(stack_t **stack, unsigned int line_number)
{
	stack_t *current; 

	if (stack == NULL || (*stack) == NULL || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		freeArgs(commandArgs);
		if (*stack)
			freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n += (*stack)->n;
	current = *stack;
	(*stack) = (*stack)->next;
	free(current);
}

