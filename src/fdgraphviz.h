#ifndef FDGRAPHVIZ_H
#define FDGRAPHVIZ_H
#include <math.h>
#include "commonTypes.h"
#include "graph.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITERATIONS 1000 // hard cap on amount of iterations for calculating vertex position
#define FORCE_THRESHOLD __FLT_EPSILON__
#define IDEAL_EDGE_LENGTH 50 // edge length in pixels
#define COOLING_FACTOR 0.975
#define X_MAX 1760
#define Y_MAX 990
#define MAX_VERTEX_PLACEMENT 50 // 330 for circle formation without force directed
#define PI_CONST 3.141592653589

typedef struct {
    String name;
    float x;
    float y;
} Node;

Node origin_vector(Node a, Node b);
Node unit_vector(Node o);
void initialize(Graph g, Node vertices[]);
Node repulsion_force(Node a, Node b, float strength); // 1.8 for Nodes < 10
Node attraction_force(Node a, Node b, float strength); // 1.2 for Nodes < 10
float cooling_factor(float factor);
void force_directed(Graph g, Node vertices[], float threshold, int maxIterations);
void initialize_borders(Node borders[], int nx, int ny);
Node global_force(Node a, Node borders[], float rStr, float aStr);

#endif