#ifndef GRAPH_H
#define GRAPH_H

#include "commonTypes.h"
#include "linkedList.h"

typedef struct Graph {
	int vertexCount;
	String *vertexList;		   // array
	LinkedList *adjacencyList; // array
							   // stores index of vertex from vertexList
} Graph;

void init_graph(Graph *graph, String vertexList[], int vertexCount);

#endif
