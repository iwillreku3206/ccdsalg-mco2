#include "fdgraphviz.h"
#include <stdio.h>

float get_magnitude(Node n) {
    return sqrt(pow(n.x,2)+pow(n.y,2));
}

Node origin_vector(Node a, Node b) {
    //vector from Node a --> b
    Node o;
    o.x = a.x - b.x;
    o.y = a.y - b.y;

    //because the way graphics are rendered, y value increases when going down instead of up
    // o.y = -1 * o.y;

    // printf("(%.2f, %.2f)\n", o.x, o.y);

    return o;
}

Node unit_vector(Node o) {
    Node u;
    float length = get_magnitude(o);
    u.x = o.x * (1.0 / length);
    u.y = o.y * (1.0 / length);

    // printf("(%.2f, %.2f)\n", u.x, u.y);

    return u;
}

void initialize(Graph g, Node vertices[]) {
    int i, x, y;
    srand(time(NULL));
    
    for(i = 0; i < g.vertexCount; i++) {
        strcpy(vertices[i].name, g.vertexList[i]);
        // x = 500 + rand() % (X_MAX - 1000);
        // y = 350 + rand() % (Y_MAX - 700);
        x = (X_MAX / 2) + MAX_VERTEX_PLACEMENT * cos(2 * i * PI_CONST / g.vertexCount) - 100;
        y = (Y_MAX / 2) + MAX_VERTEX_PLACEMENT * sin(2 * i * PI_CONST / g.vertexCount) - 50;
        vertices[i].x = x;
        vertices[i].y = y;
        // printf("(%d, %d)\n", x, y);
    }
    // printf("\n\n\n");
}

Node repulsion_force(Node a, Node b, float strength) {
    Node f = unit_vector(origin_vector(a,b));
    // Node f = origin_vector(b,a);
    float scalar;

    scalar = pow(IDEAL_EDGE_LENGTH, strength) / pow(get_magnitude(origin_vector(b,a)), 1);
    // scalar = REPULSION_CONST / pow(get_magnitude(origin_vector(b,a)), 2);
    // printf("Repulsion from %s to %s: (%.2f, %.2f) * %.2f or %.2f / %.2f --> ", a.name, b.name, f.x, f.y, scalar, pow(IDEAL_EDGE_LENGTH, 2), get_magnitude(origin_vector(b,a)));
    f.x = scalar * f.x;
    f.y = scalar * f.y;
    // printf("(%.2f, %.2f)\n", f.x, f.y);

    return f;
}

Node attraction_force(Node a, Node b, float strength) {
    Node f = unit_vector(origin_vector(b,a));
    // Node f = origin_vector(a,b);
    float scalar;

    scalar = pow(get_magnitude(origin_vector(b,a)), strength) / pow(IDEAL_EDGE_LENGTH, 1);
    // scalar = SPRING_CONST * log(get_magnitude(origin_vector(b,a))/IDEAL_EDGE_LENGTH);
    // printf("Attraction from %s to %s: (%.2f, %.2f) * %.2f or %.2f / %.2f --> ", a.name, b.name, f.x, f.y, scalar, pow(get_magnitude(origin_vector(b,a)), 2), pow(IDEAL_EDGE_LENGTH, 1));
    f.x = scalar * f.x;
    f.y = scalar * f.y;
    // printf("(%.2f, %.2f)\n", f.x, f.y);
    return f;
}

float max_force(Graph g, Node vertices[], float coolingFactor) {
    Node max, current, rCurrent, aCurrent, repulsion, attraction;
    int i, j;
    float rStr, aStr;
    max.x = 0;
    max.y = 0;

    if(g.vertexCount <= 10) {
        rStr = 1.8;
        aStr = 1.2;
    }
    else if(g.vertexCount > 10) {
        rStr = 1.5;
        aStr = 1.2;
    }

    for(i = 0; i < g.vertexCount; i++) {
        rCurrent.x = 0;
        rCurrent.y = 0;
        aCurrent.x = 0;
        aCurrent.y = 0;
        for(j = 0; j < g.vertexCount; j++) {
            if(i != j) {
                if(g.adjacencyMatrix[i][j] == true) {
                    attraction = attraction_force(vertices[i], vertices[j], aStr);
                    aCurrent.x = aCurrent.x + attraction.x;
                    aCurrent.y = aCurrent.y + attraction.y;
                }
                repulsion = repulsion_force(vertices[i], vertices[j], rStr);
                rCurrent.x = rCurrent.x + repulsion.x;
                rCurrent.y = rCurrent.y + repulsion.y;
            }
        }
        current.x = rCurrent.x + aCurrent.x;
        current.y = rCurrent.y + aCurrent.y;

        current.x = current.x * coolingFactor;
        current.y = current.y * coolingFactor;

        if(get_magnitude(max) < get_magnitude(current)) {
            max.x = current.x;
            max.y = current.y;
        }
    }
    return get_magnitude(max);
}

float cooling_factor(float factor) {
    return factor * COOLING_FACTOR;
}

void force_directed(Graph g, Node vertices[], float threshold, int maxIterations) {
    int i, j, k, x, y;
    Node repulsion, attraction, rForce, aForce;
    Node forces[MAX_VERTICES];
    float rStr, aStr;
    float factor = COOLING_FACTOR;
    i = 0;

    if(g.vertexCount <= 10) {
        rStr = 1.8;
        aStr = 1.2;
    }
    else if(g.vertexCount > 10) {
        rStr = 1.8;
        aStr = 1.3;
    }

    // printf("%f %d %f\n", max_force(g, vertices), i, FORCE_THRESHOLD);
    while(i < maxIterations && max_force(g, vertices, factor) > threshold) {
        for(j = 0; j < g.vertexCount; j++) {
            rForce.x = 0;
            rForce.y = 0;
            aForce.x = 0;
            aForce.y = 0;
            for(k = 0; k < g.vertexCount; k++) {
                if(j != k) {
                    if(g.adjacencyMatrix[j][k] == true) {
                        attraction = attraction_force(vertices[j], vertices[k], aStr);
                        aForce.x = aForce.x + attraction.x;
                        aForce.y = aForce.y + attraction.y;
                    }
                    repulsion = repulsion_force(vertices[j], vertices[k], rStr);
                    rForce.x = rForce.x + repulsion.x;
                    rForce.y = rForce.y + repulsion.y;
                }
            }
            forces[j].x = rForce.x + aForce.x;
            forces[j].y = rForce.y + aForce.y;
            // printf("Force on %s: (%.2f, %.2f)\n", vertices[j].name, forces[j].x, forces[j].y);
        }

        for(j = 0; j < g.vertexCount; j++) {
            x = vertices[j].x + factor * forces[j].x;
            y = vertices[j].y + factor * forces[j].y;

            if(x + 60 > X_MAX) {
                vertices[j].x = X_MAX - 60;
            }
            else if(x - 60 < 0) {
                vertices[j].x = 60;
            }
            else {
                vertices[j].x = x;
            }
            
            if(y + 60 > Y_MAX) {
                vertices[j].y = Y_MAX - 60;
            }
            else if(y - 60 < 0) {
                vertices[j].y = 60;
            }
            else {
                vertices[j].y = y;
            }
            // printf("(%.2f, %.2f)\n", vertices[j].x, vertices[j].y);
        }
        factor = cooling_factor(factor);
        // printf("\n\n\n");

        // printf("%f %d %f\n", max_force(g, vertices), i, FORCE_THRESHOLD);
        i++;
    }
}