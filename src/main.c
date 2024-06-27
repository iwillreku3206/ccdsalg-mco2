#include "linkedList.h"
#include <stdio.h>

int main() {
	LinkedList list;

	linkedlist_init(&list);

	linkedlist_add(&list, 10);
	linkedlist_add(&list, 9);
	linkedlist_add(&list, 8);
	linkedlist_add(&list, 7);
	linkedlist_add(&list, 6);
	linkedlist_add(&list, 5);
	linkedlist_add(&list, 4);
	linkedlist_add(&list, 3);
	linkedlist_add(&list, 2);
	linkedlist_add(&list, 1);

	LinkedListNode *current = list.start;

	do {
		printf("%d\n", current->value);
		current = current->next;
	} while (current != NULL);

	return 0;
}
