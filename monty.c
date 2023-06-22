#include "monty.h"
#include <stdio.h>
char **commandArgs;
/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
	char *line;
	stack_t *head = NULL;
	int fd, commandCount;
	unsigned int line_number = 1;
	void (*f)(stack_t **stack, unsigned int line_number);

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	line = readLine(fd);
	while (line != NULL)
	{
		char *trimmed_line = trim_string(line);
		if (*trimmed_line == '\0')
		{
			free(line);
			line = readLine(fd);
			continue;
		}
		commandArgs = split_string(trimmed_line, " ", &commandCount);
		free(line);
		line = NULL;
		f = handleOpcode(commandArgs, line_number);
		if (!f)
		{
			fprintf(stderr, "L%d: unknown instruction %s", line_number, commandArgs[0]);
			freeArgs(commandArgs);
			freeList(head);
			exit(EXIT_FAILURE);
		}
		f(&head, line_number);
		line_number++;
		freeArgs(commandArgs);
		commandArgs = NULL;
		line = readLine(fd);
	}
	close(fd);
	freeList(head);
	return (EXIT_SUCCESS);
}
/**
 * freeArgs - free list of args.
 * @commands: pointer to char pointer.
 * Return: void.
 */
void freeArgs(char **commands)
{
	int i;

	for (i = 0; commands[i] != NULL; i++)
		free(commands[i]);
	free(commands);
}
void freeList(stack_t *head)
{
	stack_t *temp = head;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}
