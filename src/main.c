#include "bfs.h"
#include "dfs.h"
#include "display.h"
#include "file.h"
#include "graph.h"
#include <stdio.h>
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

	// prompt the user for filename, load the graph in from the file
	// and prompt user again for the start index
	int startIndex;
	graph_setup(&graph, &startIndex);
	nodeCount = graph.vertexCount;

	if (startIndex == -1) {
		exit(1);
	} else {
		// For printing the output
		FILE *traversals = fopen("./TRAVERSALS.txt", "w");
		if (traversals == NULL) {
			printf("Writing error.\n");
			return 1;
		}

		// Prints the node names and their link count (degree)
		for (i = 0; i < nodeCount; i++) {
			int connectionCount = 0;
			for (j = 0; j < nodeCount; j++) {
				if (graph.adjacencyMatrix[i][j]) {
					connectionCount++;
				}
			}
			fprintf(traversals, "%s %d\n", graph.vertexList[i],
					connectionCount);
		}
		fprintf(traversals, "\n");

		// run traversals 
		bfs(&graph, &bfsTree, startIndex, traversals);
		fprintf(traversals, "\n\n");
		dfs(&graph, &dfsTree, startIndex, traversals);

		fclose(traversals);

    // bonus
		open_window(graph);
		open_window(bfsTree);
	}

	return 0;
}
