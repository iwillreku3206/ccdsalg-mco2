#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include <stdio.h>

void dfs(Graph *graph, Graph *bfsTree, int from, FILE *file, Vertex nodes[]);

#endif
