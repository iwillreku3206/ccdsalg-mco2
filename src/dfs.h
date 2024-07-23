#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include <stdio.h>
#include "util.h"

void dfs(Graph *graph, Graph *bfsTree, int from, FILE *file);
void dfs_recursion(Graph *graph, Graph *dfsTree, int activeIndex, bool discovered[], FILE *file);

#endif
