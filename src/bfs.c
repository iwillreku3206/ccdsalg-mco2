#include "bfs.h"
#include "graph.h"
#include "queue.h"
#include "util.h"
#include <stdio.h>

bool all_discovered(bool A[], int n) {
	for (int i = 0; i < n; i++) {
		if (A[n] == false) {
			return false;
		}
	}
	return true;
}

void bfs(Graph *graph, Graph *bfsTree, int from, FILE *file, Vertex nodes[]) {
	Queue queue;
	bool discovered[graph->vertexCount];
	graph_init(bfsTree, graph->vertexList, graph->vertexCount);
	queue_init(&queue);

	for (int i = 0; i < graph->vertexCount; i++) {
		discovered[i] = false;
	}

	queue_enqueue(&queue, from);
	discovered[from] = true;

	while (!queue_empty(&queue)) {
		int vertex = queue_dequeue(&queue).value;
		fprintf(file, "%s ", nodes[vertex].name);
		printf("%s ", nodes[vertex].name);

		// get the number of next vertices
		int numNextVertices = 0;
		for (int i = 0; i < graph->vertexCount; i++) {
			if (graph->adjacencyMatrix[vertex][i] == true &&
				discovered[i] == false) {
				numNextVertices++;
			}
		}

		// next, place them all in an array
		int nextVertices[numNextVertices];
		int tmp = 0;

		for (int i = 0; i < graph->vertexCount; i++) {
			if (graph->adjacencyMatrix[vertex][i] == true &&
				discovered[i] == false) {
				nextVertices[tmp] = i;
				tmp++;
			}
		}

		// next, sort the array
		sort_by_name(graph->vertexList, nextVertices, numNextVertices);

    if (numNextVertices > 0) {
		// enqueue the lowest vertex in the list
		queue_enqueue(&queue, nextVertices[0]);
		graph_add_edge(bfsTree, vertex, nextVertices[0]);
		discovered[nextVertices[0]] = true;

    }
	}
}
