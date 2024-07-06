#include "graph.h"
#include "linkedList.h"
#include <stdlib.h>
#include <string.h>

void init_graph(Graph *graph, String vertexList[], int vertexCount) {
	graph->vertexList = (String *)malloc(sizeof(String) * vertexCount);
	graph->adjacencyList =
		(LinkedList *)malloc(sizeof(LinkedList) * vertexCount);
	graph->vertexCount = vertexCount;

	for (int i = 0; i < vertexCount; i++) {
		strcpy(graph->vertexList[i], vertexList[i]);
		linkedlist_init(&graph->adjacencyList[i]);
	}
}

void add_edge(Graph *graph, int from, int to) {
	LinkedList *fromList = &graph->adjacencyList[from];
	LinkedList *toList = &graph->adjacencyList[from];
  // check if edge already exists
  int fromIndex = linkedlist_search(fromList, to);
  int toIndex = linkedlist_search(fromList, from);
}
