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
	int fd;

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
	executeCommands(fd);
	close(fd);
	return (EXIT_SUCCESS);
}
/**
 * executeCommands - radlines and run the commands.
 * @fd: number of the open file.
 * Return: void.
 */
void executeCommands(int fd)
{
	int commandCount;
	char *line, *trimmed_line;
	stack_t *head = NULL;
	unsigned int line_number = 1;
	int f;

	line = readLine(fd);
	while (line != NULL)
	{
		trimmed_line = trim_string(line);
		if (*trimmed_line == '\0' || *trimmed_line == '#')
		{
			free(line);
			line = readLine(fd);
			continue;
		}
		commandArgs = split_string(trimmed_line, " ", &commandCount);
		free(line);
		line = NULL;

		f = handleOpcode(commandArgs, line_number, &head);
		if (f == 1)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n",
		line_number, commandArgs[0]);
			freeArgs(commandArgs);
			freeList(head);
			close(fd);
			exit(EXIT_FAILURE);
		}
		line_number++;
		freeArgs(commandArgs);
		commandArgs = NULL;
		line = readLine(fd);
	}
	if (head != NULL)
		freeList(head);
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
/**
 * freeList - free list of args.
 * @head: pointer to top of the stack.
 * Return: void.
 */
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
