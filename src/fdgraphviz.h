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
#define IDEAL_EDGE_LENGTH 100 // edge length in pixels
#define COOLING_FACTOR 0.975
#define X_MAX 1600
#define Y_MAX 900

typedef struct {
    String name;
    int x;
    int y;
} Node;

#endif