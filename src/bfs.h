#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include <stdio.h>

void bfs(Graph *graph, Graph *bfsTree, int from, FILE *file, Vertex nodes[]);

#endif
