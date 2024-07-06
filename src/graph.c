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
  int edgeIndex = linkedlist_search(fromList, to);

  if (edgeIndex != -1) {
    return; // edge already exists, no need to do anything
  }

  // if not, we add the edge to both linked lists
  linkedlist_add(fromList, to);
  linkedlist_add(toList, from);
}
