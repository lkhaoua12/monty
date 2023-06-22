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
	char * new_str = trim_string(str);
	if (!new_str)
	{
		return (NULL);
	}
	token = strtok_custom(new_str, delim, &state);
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
/**
 * fix_string - Fixes a string by trimming leading and trailing spaces
 *              and removing spaces between tokens.
 * @str: The string to be fixed.
 * Return: The fixed string.
 */
char *trim_string(char *str)
{
	if (str == NULL)
		return NULL;
	while (isspace(*str))
	{
		str++;
	}

	char *end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
	{
		*end = '\0';
		end--;
	}
	char *src = str;
	char *dst = str;
	int space_flag = 0;
	while (*src)
	{
		if (isspace(*src))
		{
			space_flag = 1;
		}
		else
		{
			if (space_flag)
			{
				*dst = ' ';
				dst++;
			}
			space_flag = 0;
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
	return str;
}
