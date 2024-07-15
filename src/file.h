#ifndef FILE_H
#define FILE_H

#include "graph.h"

int graph_setup(Graph *graph, Vertex nodes[MAX_VERTICES], int *totalNodes);
void split_string(const char *originalLine, String destinationNames[MAX_VERTICES + 1], int *nameCount);
void to_lowercase(const char *input, String output);
int find_index(const char *name, String vertexNames[MAX_VERTICES], int vertexCount);
void add_link(Vertex *vertex, int index);

#endif
