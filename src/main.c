#include "bfs.h"
#include "dfs.h"
#include "file.h"
#include "graph.h"
#include <stdio.h>
#include "display.h"
#include <stdlib.h>

#include "commonTypes.h"
#include "util.h"

int main() {
	// Contains the original graph structure
	Graph graph;
	// Contains the updated graph structures
	Graph bfsTree;
	Graph dfsTree;
	int i;
	int j;

	int nodeCount;

	// Contains the reading of the text file as well as compilation of nodes
	// and setting up connections
	// Returns -1 if terminating
	int startIndex = graph_setup(&graph, &nodeCount);

	if (startIndex == -1){
		exit(1);
	} else {
		// For printing the output

		FILE *traversals = fopen("./TRAVERSALS.txt", "w");
		if (traversals == NULL) {
			printf("Writing error.\n");
			return 1;
		}

		// Prints the node names and their link count
		for (i = 0; i < nodeCount; i++) {
			int connectionCount = 0;
			for (j = 0; j < nodeCount; j++) {
				if (graph.adjacencyMatrix[i][j]) {
					connectionCount++;
				}
			}
			// name length currently set to only print 8 digits
			fprintf(traversals, "%-8s %d\n", graph.vertexList[i],
					connectionCount);
			// printf("%-8s %d\n", graph.vertexList[i], connectionCount);
		}
		fprintf(traversals, "\n");

		// for (int i = 0; i < graph.vertexCount; i++) {
		// 	printf("%s ", graph.vertexList[i]);
		// 	for (int j = 0; j < graph.vertexCount; j++) {
		// 		printf("%d ", graph.adjacencyMatrix[i][j]);
		// 	}
		// 	printf("\n");
		// }

		// Triggers search trees
		bfs(&graph, &bfsTree, startIndex, traversals);
		fprintf(traversals, "\n\n");
		// printf("\n\n");
		dfs(&graph, &dfsTree, startIndex, traversals);

		fclose(traversals);

		open_window(graph);
	}

	return 0;
}
