#include "monty.h"
/**
 * handleMod - Adds the top two elements of the stack.
 * @stack: Double pointer to the top of the stack.
 * @line_number: The line number of the instruction.
 */
void handleMod(stack_t **stack, unsigned int line_number)
{
	stack_t *current;

	if (stack == NULL || (*stack) == NULL || !(*stack)->next)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		freeArgs(commandArgs);
		if (*stack)
			freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		freeArgs(commandArgs);
		if (*stack)
			freeList(*stack);
		close(3);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n %= (*stack)->n;
	current = *stack;
	(*stack) = (*stack)->next;
	free(current);
}
/**
 * _isDigit - Adds the top two elements of the stack.
 * @s: char string;
 * Return: 0 if true else 1.
 */
int _isDigit(char *s)
{
	int i;
	int is_digit = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (i == 0 && s[i] == '-')
			continue;
		if (s[i] < 48 ||  s[i] > 58)
		{
			is_digit = 1;
			break;
		}
	}
	return (is_digit);
}
