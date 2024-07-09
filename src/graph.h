#ifndef GRAPH_H
#define GRAPH_H

#include "commonTypes.h"
#include <stdbool.h>

typedef struct Graph {
	int vertexCount;
	String *vertexList;		// array
	bool **adjacencyMatrix; // 2d array
} Graph;

void graph_init(Graph *graph, String vertexList[], int vertexCount);
void graph_add_edge(Graph *graph, int from, int to);

#endif
