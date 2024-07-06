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

	int i = 0;

	do {
		printf("%d: %d\n", i, current->value);
		current = current->next;
		i++;
	} while (current != NULL);

	printf("search: %d\n", linkedlist_search(&list, 7));

	return 0;
}
