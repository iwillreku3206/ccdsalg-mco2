#include "dfs.h"
#include "graph.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>

void dfs(Graph *graph, Graph *bfsTree, int from, FILE *file, Vertex nodes[]) {
	Stack stack;
	bool discovered[graph->vertexCount];
	graph_init(bfsTree, graph->vertexList, graph->vertexCount);
	stack_init(&stack);

	for (int i = 0; i < graph->vertexCount; i++) {
		discovered[i] = false;
	}

	stack_push(&stack, from);
	discovered[from] = true;

	while (!stack_is_empty(&stack)) {
		int vertex = stack_pop(&stack).value;
		fprintf(file, "%s ", nodes[vertex].name);
		for (int i = graph->vertexCount - 1; i >= 0; i--) {
			if (graph->adjacencyMatrix[vertex][i] == true &&
				discovered[i] == false) {
				stack_push(&stack, i);
				graph_add_edge(bfsTree, vertex, i);
				discovered[i] = true;
			}
		}
	}
}
