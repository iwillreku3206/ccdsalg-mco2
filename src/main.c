#include "graph.h"
#include <stdio.h>

int main() {
	// LinkedList list;
	// linkedlist_init(&list);

	// linkedlist_add(&list, 5);
	// printf("%p, %p\n", list.start, list.start->next);
	// printf("INDEX: %d\n", linkedlist_search(&list, 5));
	// printf("%p, %p\n", list.start, list.start->next);
	// printf("INDEX: %d\n", linkedlist_search(&list, 10));
	// printf("%p, %p\n", list.start, list.start->next);
	// linkedlist_add(&list, 6);
	// linkedlist_add(&list, 10);
	// linkedlist_add(&list, 15);

	// printf("INDEX: %d\n", linkedlist_search(&list, 20));

	Graph graph;
	graph_init(&graph, (String[]){"1", "2", "3", "4", "5", "6", "7", "8"}, 8);

	graph_add_edge(&graph, 1 - 1, 2 - 1);
	graph_add_edge(&graph, 1 - 1, 6 - 1);
	graph_add_edge(&graph, 2 - 1, 5 - 1);
	graph_add_edge(&graph, 2 - 1, 3 - 1);
	graph_add_edge(&graph, 3 - 1, 5 - 1);
	graph_add_edge(&graph, 6 - 1, 8 - 1);
	graph_add_edge(&graph, 3 - 1, 4 - 1);
	graph_add_edge(&graph, 3 - 1, 7 - 1);
	graph_add_edge(&graph, 3 - 1, 8 - 1);

	return 0;
}
