#include "fdgraphviz.h"

float get_magnitude(Node n) {
    return sqrt(pow(n.x,2)+pow(n.y,2));
}

Node origin_vector(Node a, Node b) {
    //vector from Node a --> b
    Node o;
    o.x = a.x - b.x;
    o.y = a.y - b.y;

    //because the way graphics are rendered, y value increases when going down instead of up
    o.y = -1 * o.y;

    return o;
}

Node unit_vector(Node o) {
    Node u;
    float length = get_magnitude(o);
    u.x = o.x * (1 / length);
    u.y = o.y * (1 / length);

    return u;
}

void initialize(Graph g, Node vertices[]) {
    int i, x, y;
    srand(time(NULL));
    
    for(i = 0; i < g.vertexCount; i++) {
        strcpy(vertices[i].name, g.vertexList[i]);
        x = 150 + rand() % (X_MAX - 300);
        y = 100 + rand() % (Y_MAX - 200);
        vertices[i].x = x;
        vertices[i].y = y;
    }
}

Node repulsion_force(Node a, Node b) {
    Node f = unit_vector(origin_vector(b,a));
    float scalar;

    scalar = pow(IDEAL_EDGE_LENGTH, 2) / get_magnitude(origin_vector(b,a));
    f.x = scalar * f.x;
    f.y = scalar * f.y;

    return f;
}

Node attraction_force(Node a, Node b) {
    Node f = unit_vector(origin_vector(a,b));
    float scalar;

    scalar = pow(get_magnitude(origin_vector(b,a)), 2) / IDEAL_EDGE_LENGTH;
    f.x = scalar * f.x;
    f.y = scalar * f.y;

    return f;
}

void force_directed(Graph g, Node vertices[], float threshold, int maxIterations) {
    int i, j, k;
    Node repulsion, attraction, force;
    i = 0;

    while(i < maxIterations && 500 > threshold) {
        for(j = 0; j < g.vertexCount; j++) {
            force.x = 0;
            force.y = 0;
            for(k = 0; k < g.vertexCount; k++) {
                if(j != k && g.adjacencyMatrix[j][k] == true) {
                    repulsion = repulsion_force(vertices[j], vertices[k]);
                    attraction = attraction_force(vertices[j], vertices[k]);
                    force.x = force.x + repulsion.x + attraction.x;
                    force.y = force.y + repulsion.y + attraction.y;
                }
            }
            vertices[j].x = vertices[j].x + COOLING_FACTOR * force.x;
            vertices[j].y = vertices[j].y + COOLING_FACTOR * force.y;
        }
        i++;
    }
}