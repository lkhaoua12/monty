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
