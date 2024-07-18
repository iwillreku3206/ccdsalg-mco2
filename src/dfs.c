#include "dfs.h"
#include "graph.h"
#include "stack.h"
#include <stdio.h>

// GOAL for Recursion
// 1. Initialize everything like graph_init and boolean array for each vertex
// 2. When doing recursion change current vertex id in discovered
// 3. Check each node the current one is adjacent to
	// - If the id is discovered, skip
	// - If not, Add the edge and stuff, do recursion on it so that when it finishes
			// it can go back to the original from
// 4. Profit


/* Runs the recursion for the DFS
Precondition: A valid graph was given to start the DFS
@param Graph *graph <Graph that will be the source of the vertices>
@param Graph *dfsTree <Graph that will be modified to contain the resulting tree>
@param int activeIndex <Will become the next adjacent node's index to continue the recursion>
@param FILE *file <The TRAVERSALS.txt where the movements will be printed>
@param Vertex nodes[] <Array of nodes that contain the names, number of links, and array of linked indexes>
@return none, will keep running while there are still nodes to check and continuously update the dfsTree
*/
void dfs_recursion(Graph *graph, Graph *dfsTree, int activeIndex, bool discovered[], FILE *file, Vertex nodes[]) {
	// Set current to discovered
    discovered[activeIndex] = true;

	// Prints
    fprintf(file, "%s ", nodes[activeIndex].name);
    printf("%s ", nodes[activeIndex].name);

	// Get current vertex from the nodes so that we can limit loops to the number of links it has
    Vertex* currentVertex = &nodes[activeIndex];
    
	// Check all of the adjacencies it has
    for (int i = 0; i < currentVertex->linkCount; i++) {
        int adjacentIndex = currentVertex->links[i];
        
		// Undiscovered, add edges and recurse
        if (!discovered[adjacentIndex]) {
            graph_add_edge(dfsTree, activeIndex, adjacentIndex);
            dfs_recursion(graph, dfsTree, adjacentIndex, discovered, file, nodes);
        } else {
			// Skip since it has been discovered
        }
    }
}

/* Contains the logic for doing the Depth-First Search
Precondition: A valid graph has been set up
@param Graph *graph <Graph that will be the source of the vertices>
@param Graph *dfsTree <Graph that will be modified to contain the resulting tree>
@param int from <Starting point node's index>
@param FILE *file <The TRAVERSALS.txt where the movements will be printed>
@param Vertex nodes[] <Array of nodes that contain the names, number of links, and array of linked indexes>
@return none, puts result in new dfsTree
*/
void dfs(Graph *graph, Graph *dfsTree, int from, FILE *file, Vertex nodes[]) {
	// Initialize everything
    int i;
	bool discovered[MAX_VERTICES];
    graph_init(dfsTree, graph->vertexList, graph->vertexCount);

	// Set all ids to undiscovered
	for (i = 0; i < graph->vertexCount; i++) {
		discovered[i] = false;
	}

    // Start recursion
    dfs_recursion(graph, dfsTree, from, discovered, file, nodes);
}

// original
// void dfs(Graph *graph, Graph *bfsTree, int from, FILE *file, Vertex nodes[]) {
// 	Stack stack;
// 	bool discovered[graph->vertexCount];
// 	graph_init(bfsTree, graph->vertexList, graph->vertexCount);
// 	stack_init(&stack);

// 	for (int i = 0; i < graph->vertexCount; i++) {
// 		discovered[i] = false;
// 	}

// 	stack_push(&stack, from);
// 	discovered[from] = true;

// 	while (!stack_is_empty(&stack)) {
// 		int vertex = stack_pop(&stack).value;
// 		fprintf(file, "%s ", nodes[vertex].name);
// 		printf("%s ", nodes[vertex].name);
// 		for (int i = graph->vertexCount - 1; i >= 0; i--) {
// 			if (graph->adjacencyMatrix[vertex][i] == true &&
// 				discovered[i] == false) {
// 				stack_push(&stack, i);
// 				graph_add_edge(bfsTree, vertex, i);
// 				discovered[i] = true;
// 			}
// 		}
// 	}
// }