#include "bfs.h"
#include "dfs.h"
#include "file.h"
#include "graph.h"
#include <stdio.h>

#include "commonTypes.h"
#include "util.h"

int main() {
	Graph graph;
	Graph bfsTree;
	int i;
	int j;

	int nodeCount;

	// Contains the reading of the text file as well as compilation of nodes
	// and setting up connections
	// Returns -1 if terminating
	int startIndex = graph_setup(&graph, &nodeCount);

	if (startIndex > -1) {
		// For printing the output

		FILE *traversals = fopen("./TRAVERSALS.txt", "w");
		if (traversals == NULL) {
			printf("Writing error.\n");
			return 1;
		}

		// Prints the node names,
        for (i = 0; i < nodeCount; i++) {
            int connectionCount = 0;
            for (j = 0; j < nodeCount; j++) {
                if (graph.adjacencyMatrix[i][j]) {
                    connectionCount++;
                }
            }
            // SET TO 9, the outputs in the specs seem to be of size 9 or so
            // May be adjusted to be higher later, just following the specs for now
            fprintf(traversals, "%-9s %d\n", graph.vertexList[i], connectionCount);
            printf("%-9s %d\n", graph.vertexList[i], connectionCount);
        }
		fprintf(traversals, "\n");

	// 	// bfs and dfs was edited to print into the text file as well as print
	// 	// the names of each node instead of the previous just index + 1 version
		bfs(&graph, &bfsTree, startIndex, traversals);
		fprintf(traversals, "\n\n");
		printf("\n\n");
		dfs(&graph, &bfsTree, startIndex, traversals);

		fclose(traversals);
	}

	return 0;
}
