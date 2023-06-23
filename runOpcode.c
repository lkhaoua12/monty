#include "monty.h"
#include <stdlib.h>
/**
 * handlePush - Handles the "push" opcode
 * @stack: Double pointer to the stack
 * @line_number: Line number in the input file
 */
void handlePush(stack_t **stack, unsigned int line_number)
{
	stack_t *newNode = malloc(sizeof(stack_t));
	int num, is_digit = 1;

	if (newNode == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		freeArgs(commandArgs);
		freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	if (commandArgs[1] != NULL)
		is_digit = _isDigit(commandArgs[1]);
	if (commandArgs[1] == NULL || is_digit == 1)
	{
		free(newNode);
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		freeArgs(commandArgs);
		freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	num = atoi(commandArgs[1]);
	newNode->n = num;
	newNode->next = *stack;
	newNode->prev = NULL;
	if ((*stack) != NULL)
	{
		(*stack)->prev = newNode;
	}
	*stack = newNode;
}
/**
 * handlePrint - Handles the "pall" opcode
 * @stack: Double pointer to the stack
 * @line_number: Line number in the input file
 */
void handlePrint(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	(void)line_number;
	if (stack == NULL || (*stack) == NULL)
		return;

	current = *stack;
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}
/**
 * handlePint - Prints the value at the top of the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number of the command in the script file.
 */
void handlePint(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	if (stack == NULL || (*stack) == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		freeArgs(commandArgs);
		close(3);
		exit(EXIT_FAILURE);
	}
	if (stack == NULL || (*stack) == NULL)
		return;

	current = *stack;
	printf("%d\n", current->n);
}
/**
 * handlePop - Removes the top element of the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number of the command in the script file.
 */
void handlePop(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	if (stack == NULL || (*stack) == NULL)
	{
		fprintf(stderr, "L%d: can't pop, stack empty\n", line_number);
		freeArgs(commandArgs);
		close(3);
		exit(EXIT_FAILURE);
	}
	current = *stack;
	*stack = current->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;

	free(current);
}
/**
 * handleSwap - Swaps the top two elements of the stack.
 * @stack: Pointer to the stack.
 * @line_number: Line number of the command in the script file.
 */
void handleSwap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (stack == NULL || (*stack) == NULL || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		freeArgs(commandArgs);
		if (*stack)
			freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->next->n;
	(*stack)->next->n = (*stack)->n;
	(*stack)->n = temp;
}
