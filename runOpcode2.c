#include "monty.h"
#include <stdio.h>
/**
 * handleAdd - Adds the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The line number of the instruction.
 */
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
/**
 * handleNop - Does nothing.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The line number of the instruction.
 */
void handleNop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
/**
 * handleSub - Adds the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The line number of the instruction.
 */
void handleSub(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	if (stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short", line_number);
		freeArgs(commandArgs);
		if (*stack)
			freeList(*stack);
		exit(EXIT_FAILURE);
	}
	current = *stack;
	current->next->n -= current->n; 
	*stack = current->next;
	free(current);
	(*stack)->prev = NULL;
}
