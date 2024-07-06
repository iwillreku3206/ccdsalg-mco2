#include "stack.h"
#include "commonTypes.h"

void stack_init(Stack *s) {
	for (int i = 0; i < STACK_SIZE; i++) {
		s->top = -1;
	}
}

int stack_push(Stack *s, int type, int value) {
	if (s->top >= STACK_SIZE - 1) {
		return STACK_ERR_OVERFLOW;
	}
	SQItem item;
	item.value = value;
	item.type = type;
	s->items[++s->top] = item;
	return STACK_NO_ERROR;
}

SQItem stack_pop(Stack *s) {
	if (s->top < 0) {
		SQItem error;
		error.type = ITEM_TYPE_ERROR;
		error.value = STACK_ERR_UNDERFLOW;
		return error;
	}
	return s->items[s->top--];
}

SQItem stack_top(Stack *s) {
	if (s->top < 0) {
		SQItem error;
		error.type = ITEM_TYPE_ERROR;
		error.value = STACK_ERR_NOITEM;
		return error;
	}
	return s->items[s->top];
}
bool stack_is_empty(Stack *s) { return s->top == -1; }
bool stack_is_full(Stack *s) { return s->top == STACK_SIZE - 1; }
