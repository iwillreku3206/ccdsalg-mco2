#ifndef DISPLAY_H
#define DISPLAY_H
#include "raylib.h"
#include "fdgraphviz.h"
#include <stdio.h>

void draw_edge(Node a, Node b);
void draw_node(Node a);
void open_window(Graph g);

#endif