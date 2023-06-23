#include "monty.h"
#include <stdlib.h>
#include <string.h>
/**
 * handleOpcode - Handles the opcode and returns the corresponding function
 * @opcode: The opcode to handle
 * @line_number: number_line to print
 * @stack: top of the stack pointer.
 * Return: Pointer to the corresponding function, or NULL if not found
 */
int handleOpcode(char **opcode, unsigned int line_number, stack_t **stack)
{
	int i;
	instruction_t instList[] = {
		{"push", handlePush},
		{"pall", handlePrint},
		{"pint", handlePint},
		{"pop", handlePop},
		{"swap", handleSwap},
		{"add", handleAdd},
		{"nop", handleNop},
		{"sub", handleSub},
		{"div", handleDiv},
		{"mul", handleMul},
		{"mod", handleMod},
		{NULL, NULL}
	};

	for (i = 0; instList[i].opcode != NULL; i++)
	{
		if (strcmp(instList[i].opcode, opcode[0]) == 0)
		{
			instList[i].f(stack, line_number);
			return (0);
		}
	}
	return (1);
}
