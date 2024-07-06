#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListNode {
	int value;
	struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
	LinkedListNode *start;
	LinkedListNode *end;
} LinkedList;

void linkedlist_init(LinkedList *list);
void linkedlist_add(LinkedList *list, int value);
int linkedlist_search(LinkedList *list, int x);

#endif
