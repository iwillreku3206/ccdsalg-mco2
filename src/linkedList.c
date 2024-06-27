#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

void linkedlist_init(LinkedList *list) {
	list->start = NULL;
	list->end = NULL;
}

// Pre-condition: node has been initialized (non-null)
void linkedlist_add(LinkedList *list, int value) {
	LinkedListNode *node = malloc(sizeof(LinkedListNode));

	node->next = NULL;
	node->value = value;

	// if the linked list is empty
	if (list->start == NULL) {
		list->start = node;
		list->end = node;
	}

	list->end->next = node;
	list->end = node;
}
