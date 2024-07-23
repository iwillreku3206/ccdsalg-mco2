#ifndef QUEUE_H
#define QUEUE_H

#include "commonTypes.h"
#include <stdbool.h>

#define QUEUE_NODE_OPERATOR 0
#define QUEUE_NODE_NUMBER 1

#define QUEUE_NO_ERROR 1
#define QUEUE_ERR_OVERFLOW -1
#define QUEUE_ERR_UNDERFLOW -2
#define QUEUE_ERR_NOITEM -3

#define QUEUE_MAX_SIZE 256

// Queue structures, made using linked lists
typedef struct QueueNode {
	struct QueueNode *next;
	SQItem value;
} QueueNode;

typedef struct {
	QueueNode *head;
	QueueNode *tail;
	int size;
} Queue;

void queue_init(Queue *q);
int queue_enqueue(Queue *q, int value);
SQItem queue_dequeue(Queue *q);
SQItem queue_head(Queue *q);
SQItem queue_tail(Queue *q);
bool queue_full(Queue *q);
bool queue_empty(Queue *q);

#endif
