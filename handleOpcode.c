#include "monty.h"
#include <stdlib.h>
#include <string.h>
/**
 * handleOpcode - Handles the opcode and returns the corresponding function
 * @opcode: The opcode to handle
 *
 * Return: Pointer to the corresponding function, or NULL if not found
 */
void (*handleOpcode(char **opcode, unsigned int line_number))
(stack_t **stack, unsigned int line_number)
{
	int i;
	instruction_t instList[] = {
		{"push", handlePush},
		{"pall", handlePrint},
		{"pint", handlePint},
		{"pop", handlePop},

		{NULL, NULL}
	};

	(void)line_number;
	for (i = 0; instList[i].opcode != NULL; i++)
	{
		if (strcmp(instList[i].opcode, opcode[0]) == 0)
		{
			return (instList[i].f);
		}
	}
	return (NULL);
}
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
		exit(EXIT_FAILURE);
	}
	(void)line_number;
	if (commandArgs[1] == NULL || (atoi(commandArgs[1]) == 0 && *commandArgs[0] != '0'))
	{
		free(newNode);
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		freeArgs(commandArgs);
		freeList(*stack);
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
		exit(EXIT_FAILURE);
	}
	current = *stack;
	*stack = current->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;

	free(current);
}
