#include "queue.h"
#include "commonTypes.h"
#include <stdlib.h>

void queue_init(Queue *q) {
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
}

int queue_enqueue(Queue *q, int value) {
	if (q->size >= QUEUE_MAX_SIZE) {
		return QUEUE_ERR_OVERFLOW;
	}

	QueueNode *newNode = malloc(sizeof(QueueNode));
	newNode->next = NULL;
	newNode->value.value = value;
	newNode->value.type = ITEM_TYPE_VALUE;

	if (q->tail != NULL) {
		q->tail->next = newNode;
	}

	if (q->head == NULL) {
		q->head = newNode;
	}

	q->tail = newNode;
	q->size++;
	return QUEUE_NO_ERROR;
}

SQItem queue_dequeue(Queue *q) {
	if (q->head == NULL) {
		SQItem error;
		error.value = QUEUE_ERR_UNDERFLOW;
		error.type = ITEM_TYPE_ERROR;
		return error;
	}

	SQItem returnValue = q->head->value;

	QueueNode *oldHead = q->head;
	q->head = q->head->next;
	free(oldHead);

	q->size--;

  if (q->head == NULL) {
    q->tail = NULL;
  }

	return returnValue;
}

SQItem queue_head(Queue *q) {
	if (q->head == NULL) {
		SQItem error;
		error.value = QUEUE_ERR_NOITEM;
		error.type = ITEM_TYPE_ERROR;
		return error;
	}

	return q->head->value;
}

SQItem queue_tail(Queue *q) {
	if (q->tail == NULL) {
		SQItem error;
		error.value = QUEUE_ERR_NOITEM;
		error.type = ITEM_TYPE_ERROR;
		return error;
	}

	return q->tail->value;
}

bool queue_full(Queue *q) { return q->size == QUEUE_MAX_SIZE; }

bool queue_empty(Queue *q) { return q->size == 0; }
