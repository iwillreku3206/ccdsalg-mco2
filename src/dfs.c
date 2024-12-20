#include "dfs.h"
#include "graph.h"
#include "stack.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

/** dfs_recusion - Runs the recursion for the DFS
 * Precondition: A valid graph was given to start the DFS
 * @param graph - Graph that will be the source of the vertices
 * @param dfsTree - Graph that will be modified to contain the resulting tree
 * @param from - Becomes the next adjacent node's index to continue the
 *               recursion
 * @param discovered - Array to track discovered vertices
 * @param file - The file TRAVERSALS.txt where the movements will be printed
 */
void dfs_recursion(Graph *graph, Graph *dfsTree, int from, bool discovered[],
				   FILE *file) {
	// Mark current as discovered
	discovered[from] = true;

	// Print current vertex
	fprintf(file, "%s ", graph->vertexList[from]);

	// Array to hold indices of adjacent vertices
	int links[MAX_VERTICES];
	int linkCount = 0;

	// Find all adjacent vertices
	for (int i = 0; i < graph->vertexCount; i++) {
		if (graph->adjacencyMatrix[from][i]) {
			links[linkCount] = i;
			linkCount++;
		}
	}

	// Sort the adjacent vertices
	sort_by_name(graph->vertexList, links, linkCount);

	// Check all adjacent vertices
	for (int i = 0; i < linkCount; i++) {
		int adjacentIndex = links[i];

		// If undiscovered, add edge and recurse
		if (!discovered[adjacentIndex]) {
			graph_add_edge(dfsTree, from, adjacentIndex);
			dfs_recursion(graph, dfsTree, adjacentIndex, discovered, file);
		}
	}
}

/** dfs - Contains the logic for containing the Depth-First Search
 * Precondition - A valid graph has been set up
 * @param graph - Graph that will be the source of the vertices
 * @param dfsTree - Graph that will be modified to contain the resulting tree
 * @param from - Starting point node's index
 * @param file - The TRAVERSALS.txt where the movements will be printed
 */
void dfs(Graph *graph, Graph *dfsTree, int from, FILE *file) {
	// Initialize everything
	int i;
	bool discovered[MAX_VERTICES];
	graph_init(dfsTree, graph->vertexList, graph->vertexCount);

	// Initialize all ids to be undiscovered
	for (i = 0; i < graph->vertexCount; i++) {
		discovered[i] = false;
	}

	// Start recursion
	dfs_recursion(graph, dfsTree, from, discovered, file);
}
