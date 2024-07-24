#include "fdgraphviz.h"
#include <stdio.h>

float get_magnitude(Node n) {
    return sqrt(pow(n.x,2)+pow(n.y,2));
}

Node origin_vector(Node a, Node b) {
    //vector from Node a --> b
    Node o;
    o.x = b.x - a.x;
    o.y = b.y - a.y;

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
    Node f = unit_vector(origin_vector(b,a));
    float scalar;

    scalar = pow(IDEAL_EDGE_LENGTH, strength) / pow(get_magnitude(origin_vector(b,a)), 1);
    // printf("Repulsion from %s to %s: (%.2f, %.2f) * %.2f or %.2f / %.2f --> ", a.name, b.name, f.x, f.y, scalar, pow(IDEAL_EDGE_LENGTH, 2), get_magnitude(origin_vector(b,a)));
    f.x = scalar * f.x;
    f.y = scalar * f.y;
    // printf("(%.2f, %.2f)\n", f.x, f.y);

    return f;
}

Node attraction_force(Node a, Node b, float strength) {
    Node f = unit_vector(origin_vector(a,b));
    float scalar;

    scalar = pow(get_magnitude(origin_vector(b,a)), strength) / pow(IDEAL_EDGE_LENGTH, 1);
    // printf("Attraction from %s to %s: (%.2f, %.2f) * %.2f or %.2f / %.2f --> ", a.name, b.name, f.x, f.y, scalar, pow(get_magnitude(origin_vector(b,a)), 2), pow(IDEAL_EDGE_LENGTH, 1));
    f.x = scalar * f.x;
    f.y = scalar * f.y;
    // printf("(%.2f, %.2f)\n", f.x, f.y);
    return f;
}

float max_force(Graph g, Node vertices[], float coolingFactor, float rStr, float aStr) {
    Node max, current, rCurrent, aCurrent, repulsion, attraction;
    int i, j;
    max.x = 0;
    max.y = 0;

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

void initialize_borders(Node borders[], int nx, int ny) {
    int i;
    Node xBorderForces[nx], yBorderForces[ny];

    for(i = 0; i < nx; i++) {
        if(i < nx / 2) {
            xBorderForces[i].x = 0 + i * X_MAX / ((nx - 2) / 2);
            xBorderForces[i].y = 0;
        }
        else {
            xBorderForces[i].x = 0 + (i - nx / 2) * X_MAX / ((nx - 2) / 2);
            xBorderForces[i].y = Y_MAX;
        }
        // printf("(%.2f, %.2f)\n", xBorderForces[i].x, xBorderForces[i].y);
    }

    for(i = 0; i < ny; i++) {
        if(i < ny / 2) {
            yBorderForces[i].x = 0;
            yBorderForces[i].y = 0 + (i + 1) * Y_MAX / ((ny + 2) / 2);
        }
        else {
            yBorderForces[i].x = X_MAX;
            yBorderForces[i].y = 0 + (i + 1 - ny / 2) * Y_MAX / ((ny + 2) / 2);
        }
        // printf("(%.2f, %.2f)\n", yBorderForces[i].x, yBorderForces[i].y);
    }
    
    for(i = 0; i < nx + ny; i++) {
        if(i < nx) {
            borders[i] = xBorderForces[i];
        }
        else {
            borders[i] = yBorderForces[i - nx];
        }
    }

}

Node global_force(Node a, Node borders[], float rStr, float aStr) {
    int i;
    Node repulsion, attraction, rForce, mid, force;

    rForce.x = 0;
    rForce.y = 0;
    mid.x = X_MAX / 2;
    mid.y = Y_MAX / 2;
    for(i = 0; i < 60; i++) {
        repulsion = repulsion_force(a, borders[i], rStr);
        rForce.x = rForce.x + repulsion.x;
        rForce.y = rForce.y + repulsion.y;
    }
    attraction = attraction_force(a, mid, aStr);
    
    force.x = rForce.x + attraction.x;
    force.y = rForce.y + attraction.y;

    return force;
}

void force_directed(Graph g, Node vertices[], float threshold, int maxIterations) {
    int i, j, k, x, y;
    Node repulsion, attraction, rForce, aForce;
    Node forces[MAX_VERTICES];
    Node borderForces[60];
    float rStr, aStr;
    float factor = COOLING_FACTOR;
    i = 0;

    initialize_borders(borderForces, 42, 18);

    if(g.vertexCount <= 10) {
        rStr = 1.8;
        aStr = 1.2;
    }
    else if(g.vertexCount > 10) {
        rStr = 1.8;
        aStr = 1.3;
    }

    // printf("%f %d %f\n", max_force(g, vertices), i, FORCE_THRESHOLD);
    while(i < maxIterations && max_force(g, vertices, factor, rStr, aStr) > threshold) {
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
                x = vertices[j].x + factor * (forces[j].x + global_force(vertices[j], borderForces, rStr, aStr).x);
            }
            else if(x - 60 < 0) {
                vertices[j].x = 60;
                x = vertices[j].x + factor * (forces[j].x + global_force(vertices[j], borderForces, rStr, aStr).x);
            }
            
            if(y + 60 > Y_MAX) {
                vertices[j].y = Y_MAX - 60;
                y = vertices[j].y + factor * (forces[j].y + global_force(vertices[j], borderForces, rStr, aStr).y);
            }
            else if(y - 60 < 0) {
                vertices[j].y = 60;
                y = vertices[j].y + factor * (forces[j].y + global_force(vertices[j], borderForces, rStr, aStr).y);
            }
            vertices[j].x = x;
            vertices[j].y = y;
            // printf("(%.2f, %.2f)\n", vertices[j].x, vertices[j].y);
        }
        factor = cooling_factor(factor);
        // printf("\n\n\n");

        // printf("%f %d %f\n", max_force(g, vertices), i, FORCE_THRESHOLD);
        i++;
    }
}