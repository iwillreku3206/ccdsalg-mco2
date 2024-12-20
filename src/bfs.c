#include "bfs.h"
#include "graph.h"
#include "queue.h"
#include "util.h"
#include <stdbool.h>
#include <stdio.h>

/** bfs - Perform breadth-first search on a graph
* @param graph - Graph to perform BFS on
* @param bfsTree - Graph to insert the BFS tree into
* @param from - starting index of BFS
* @param file - file to put traversal order into
*/
void bfs(Graph *graph, Graph *bfsTree, int from, FILE *file) {
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
		// printf("%s ", graph->vertexList[vertex]);
		fprintf(file, "%s ", graph->vertexList[vertex]);

		// Place all discoverable vertices into an array
		int nextVertices[graph->vertexCount];
		int nextCount = 0;

		for (int i = 0; i < graph->vertexCount; i++) {
			if (graph->adjacencyMatrix[vertex][i] == true &&
				discovered[i] == false) {
				nextVertices[nextCount] = i;
				nextCount++;
			}
		}

		// Sort the array
		sort_by_name(graph->vertexList, nextVertices, nextCount);

		// Enqueue the next vertices in the list, in order
		for (int i = 0; i < nextCount; i++) {
			queue_enqueue(&queue, nextVertices[i]);
			graph_add_edge(bfsTree, vertex, nextVertices[i]);
			discovered[nextVertices[i]] = true;
		}
	}
}
