#include "bfs.h"
#include "dfs.h"
#include "graph.h"
#include "file.h"
#include <stdio.h>

#include "commonTypes.h"

int main() {
	Graph graph;
	Graph bfsTree;
	Vertex nodes[MAX_VERTICES];
    
    // I just contained everything within here for the time being
    int startIndex = graph_setup(&graph, nodes);
	
	FILE *traversals = fopen("../TRAVERSALS.txt", "w");
	if (traversals == NULL) {
        printf("Writing error.\n");
        return 1;
    }

	bfs(&graph, &bfsTree, startIndex);
    printf("\n");
	dfs(&graph, &bfsTree, startIndex);


	fclose(traversals);
	return 0;
}
