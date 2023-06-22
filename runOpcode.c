#include "monty.h"
/**
 * handlePush - Handles the "push" opcode
 * @stack: Double pointer to the stack
 * @line_number: Line number in the input file
 */
void handlePush(stack_t **stack, unsigned int line_number)
{
	stack_t *newNode = malloc(sizeof(stack_t));

	if (newNode == NULL)
	{
		fprintf(stderr, "Error: malloc failed");
		freeArgs(commandArgs);
		freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	(void)line_number;
	if (commandArgs[1] == NULL || (atoi(commandArgs[1]) == 0 && *commandArgs[0] != '0'))
	{
		free(newNode);
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		freeArgs(commandArgs);
		freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	newNode->n = atoi(commandArgs[1]);
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