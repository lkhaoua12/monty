#include "monty.h"
#include <ctype.h>
#include <string.h>
/**
 * split_string - Splits a string into tokens based on a delimiter.
 * @input: The input string to be split.
 * @delim: The delimiter used to split the string.
 * @arg_num: Pointer to store the number of tokens.
 * Return: Array of strings representing the tokens.
 */
char **split_string(char *input, char *delim, int *arg_num)
{
	char *str = strdup(input);
	char **tokens = NULL;
	char *token = NULL;
	char *state;
	int count = 0;

	if (!str)
	{
		return (NULL);
	}
	token = strtok_custom(str, delim, &state);
	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (count + 1));
		tokens[count] = strdup(token);
		count++;
		token = strtok_custom(NULL, delim, &state);
	}
	tokens = realloc(tokens, sizeof(char *) * (count + 1));
	tokens[count] = NULL;
	*arg_num = count;
	free(str);
	return (tokens);
}
/**
 * strtok_custom - Custom implementation of strtok function.
 * @str: The string to be tokenized.
 * @delim: The delimiter used to tokenize the string.
 * @state: pointer to char pointer.
 *
 * Return: Pointer to the next token.
 */
char *strtok_custom(char *str, const char *delim, char **state)
{
	char *token_start, *token_end;

	if (str != NULL)
		*state = str;

	if (*state == NULL || **state == '\0')
		return (NULL);

	token_start = *state;
	token_end = strpbrk(*state, delim);

	if (token_end != NULL)
	{
		*token_end = '\0';
		*state = token_end + 1;
	}
	else
		*state += strlen(*state);

	return (token_start);
}
