#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** graph_init - initializes a graph with a set of vertices
 *  @param graph - graph to initialize
 *  @param vertexList - initial list of vertices
 *  @param vertexCount - length of vertexList
 */
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

/** graph_add_edge - adds an edge to the graph
 *  @param graph - graph to add edge to
 *  @param from - vertex index of the first index of the edge
 *  @param to - vertex index of the second index of the edge
 */
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
