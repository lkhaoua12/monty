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

	(void)line_number;
	if (commandArgs[1] == NULL ||
		(atoi(commandArgs[1]) == 0 && *commandArgs[0] != '0'))
	{
		free(newNode);
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		freeArgs(commandArgs);
		freeList(*stack);
		exit(EXIT_FAILURE);
	}
	newNode->n = atoi(commandArgs[1]);
	newNode->next = NULL;
	if ((*stack) == NULL)
	{
		*stack = newNode;
		newNode->prev = NULL;
	}
	else
	{
		stack_t *cur = *stack;

		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = newNode;
		newNode->prev = cur;
	}
}
/**
 * handlePrint - Handles the "pall" opcode
 * @stack: Double pointer to the stack
 * @line_number: Line number in the input file
 */
void handlePrint(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;
	while (current->next != NULL)
	{
		current = current->next;
	}
	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->prev;
	}
}
