#include "dfs.h"
#include "graph.h"
#include "stack.h"
#include <stdio.h>
#include "util.h"
#include <string.h>

/* Runs the recursion for the DFS
Precondition: A valid graph was given to start the DFS
@param Graph *graph <Graph that will be the source of the vertices>
@param Graph *dfsTree <Graph that will be modified to contain the resulting tree>
@param int from <Will become the next adjacent node's index to continue the recursion>
@param bool discovered[] <Array to track discovered vertices>
@param FILE *file <The TRAVERSALS.txt where the movements will be printed>
@return none, will keep running while there are still nodes to check and continuously update the dfsTree
*/
void dfs_recursion(Graph *graph, Graph *dfsTree, int from, bool discovered[], FILE *file) {
    // Set current to discovered
    discovered[from] = true;

    // Print current vertex
    fprintf(file, "%s ", graph->vertexList[from]);
    printf("%s ", graph->vertexList[from]);

    // Array to hold indices of adjacent vertices
    int links[MAX_VERTICES];
    int linkCount = 0;

    // Find all adjacent vertices
    for (int i = 0; i < graph->vertexCount; i++) {
        if (graph->adjacencyMatrix[from][i]) {
            links[linkCount++] = i;
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

/* Contains the logic for doing the Depth-First Search
Precondition: A valid graph has been set up
@param Graph *graph <Graph that will be the source of the vertices>
@param Graph *dfsTree <Graph that will be modified to contain the resulting tree>
@param int from <Starting point node's index>
@param FILE *file <The TRAVERSALS.txt where the movements will be printed>
@return none, puts result in new dfsTree
*/
void dfs(Graph *graph, Graph *dfsTree, int from, FILE *file) {
    // Initialize everything
    int i;
    bool discovered[MAX_VERTICES];
    graph_init(dfsTree, graph->vertexList, graph->vertexCount);

    // Set all ids to undiscovered to initialize
    for (i = 0; i < graph->vertexCount; i++) {
        discovered[i] = false;
    }

    // Start recursion
    dfs_recursion(graph, dfsTree, from, discovered, file);
}