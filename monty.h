#ifndef MONTY_H
#define MONTY_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
extern char **commandArgs;
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;
void freeArgs(char **commands);
char **split_string(char *input, char *delim, int *arg_num);
char *readLine(int fd);
void (*handleOpcode(char **opcode,unsigned int line_number))
(stack_t **stack, unsigned int line_number);
char *strtok_custom(char *str, const char *delim, char **state);
void handlePush(stack_t **stack, unsigned int line_number);
void handlePrint(stack_t **stack, unsigned int line_number);
void freeList(stack_t *head);
#endif

