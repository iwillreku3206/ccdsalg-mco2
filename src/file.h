#ifndef FILE_H
#define FILE_H

#include "graph.h"

int graph_setup(Graph *graph, int *totalNodes);
void split_string(const char *originalLine, String destinationNames[MAX_VERTICES + 1], int *nameCount);
int find_index(const char *name, String vertexNames[MAX_VERTICES], int vertexCount);

#endif
