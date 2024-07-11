#include "bfs.h"
#include "dfs.h"
#include "graph.h"
#include "file.h"
#include <stdio.h>

#include "commonTypes.h"

int main() {
	Graph graph;
	Graph bfsTree;
	int i;
	Vertex nodes[MAX_VERTICES];
	int nodeCount;
    
    // I just contained everything within here for the time being
    int startIndex = graph_setup(&graph, nodes, &nodeCount);
	
	FILE *traversals = fopen("../TRAVERSALS.txt", "w");
	if (traversals == NULL) {
        printf("Writing error.\n");
        return 1;
    }

	for (i = 0; i < nodeCount; i++) {
		fprintf(traversals, "%-20s %d\n", nodes[i].name, nodes[i].linkCount);
	}
	fprintf(traversals, "\n");

	bfs(&graph, &bfsTree, startIndex, traversals, nodes);
    fprintf(traversals, "\n\n");
	dfs(&graph, &bfsTree, startIndex, traversals, nodes);

	fclose(traversals);
	return 0;
}
