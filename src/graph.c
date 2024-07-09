#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void graph_init(Graph *graph, String vertexList[], int vertexCount) {
	graph->vertexCount = vertexCount;
	graph->vertexList = (String *)malloc(sizeof(String) * vertexCount);
	graph->adjacencyMatrix = (bool **)malloc(sizeof(bool *) * vertexCount);

	for (int i = 0; i < vertexCount; i++) {
		graph->adjacencyMatrix[i] =
			(bool *)malloc(sizeof(bool *) * vertexCount);
		strcpy(graph->vertexList[i], vertexList[i]);
		for (int j = 0; j < vertexCount; j++) {
			graph->adjacencyMatrix[i][j] = false;
		}
	}
}

void graph_add_edge(Graph *graph, int from, int to) {
	bool *fromList = graph->adjacencyMatrix[from];
	bool *toList = graph->adjacencyMatrix[to];
	// check if edge already exists
	if (fromList[to] == true) {
		return; // edge already exists, no need to do anything
	}

	// if not, we add the edge to both parts of the matrix 
	fromList[to] = true;
	toList[from] = true;
}
