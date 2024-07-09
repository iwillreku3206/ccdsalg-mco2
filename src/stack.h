#ifndef STACK_H
#define STACK_H

#include "commonTypes.h"
#include <stdbool.h>

#define STACK_SIZE 256

#define STACK_NO_ERROR 1
#define STACK_ERR_OVERFLOW -1
#define STACK_ERR_UNDERFLOW -2
#define STACK_ERR_NOITEM -3

// Stack structure made up of tokens which will contain their types and ID
typedef struct {
	SQItem items[STACK_SIZE];
	int top;
} Stack;

void stack_init(Stack *s);
int stack_push(Stack *s, int value);
SQItem stack_pop(Stack *s);
SQItem stack_top(Stack *s);
bool stack_is_empty(Stack *s);
bool stack_is_full(Stack *s);

#endif
