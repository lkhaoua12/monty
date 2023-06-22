#include "monty.h"
/**
 * readLine - Reads a line from a file descriptor.
 * @fd: The file descriptor to read from.
 *
 * Return: On success, returns a pointer to the read line.
 *         If the end of file is reached, returns NULL.
 *         On failure, exits the program with EXIT_FAILURE.
 */
char *readLine(int fd)
{
	char *buffer = malloc(sizeof(char) * BUFSIZ);
	ssize_t bytesRead;
	char c;
	int index = 0;

	if (buffer == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for buffer\n");
		exit(EXIT_FAILURE);
	}
	while ((bytesRead = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
		{
			buffer[index] = '\0';
			break;
		}
		buffer[index] = c;
		index++;
	}

	if (bytesRead == -1)
	{
		fprintf(stderr, "Failed to read line\n");
		free(buffer);
		exit(EXIT_FAILURE);
	}

	if (index == 0 && bytesRead == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
