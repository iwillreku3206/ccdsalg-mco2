#include "display.h"

void draw_edge(Node a, Node b, int size) {
    Vector2 c, d;
    c.x = a.x;
    c.y = a.y;
    d.x = b.x;
    d.y = b.y;
    DrawLineEx(c, d, size, BLACK);
}

void draw_node(Node a, int radius, int fontSize) {
    Vector2 n;
    int measure;
    n.x = a.x;
    n.y = a.y;

    DrawCircleV(n, radius, WHITE);
    DrawCircleLinesV(n, radius, BLACK);
    measure = MeasureText(a.name, fontSize);
    DrawText(a.name, n.x - measure / 2, n.y - fontSize / 2, fontSize, BLACK);
}

void open_window(Graph g) {
    int i, j, radius, edgeSize, fontSize;
    Node vertices[MAX_VERTICES];
    SetTraceLogLevel(LOG_ERROR);
    initialize(g, vertices);
    force_directed(g, vertices, FORCE_THRESHOLD, MAX_ITERATIONS);

    if(g.vertexCount < 10) {
        radius = 50;
        edgeSize = 5;
        fontSize = 20;
    }
    else if(g.vertexCount >= 10) {
        radius = 30;
        edgeSize = 3;
        fontSize = 16;
    }

    InitWindow(X_MAX, Y_MAX, "Graph");

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for(i = 0; i < g.vertexCount; i++) {
                for(j = 0; j < g.vertexCount; j++) {
                    if(i != j && g.adjacencyMatrix[i][j] == true) {
                        draw_edge(vertices[i], vertices[j], edgeSize);
                    }
                }
            }

            for(i = 0; i < g.vertexCount; i++) {
                draw_node(vertices[i], radius, fontSize);
            }
            // DrawLineEx(start, end, 5, BLACK);
            // DrawCircleV(start, 50, WHITE);
            // DrawCircleLinesV(start, 50, BLACK);
            // DrawCircleV(end, 50, WHITE);
            // DrawCircleLinesV(end, 50, BLACK);
            // measure = MeasureText("Hello", 20);
            // DrawText("Hello", start.x - measure / 2, start.y - 10, 20, BLACK);
            
        EndDrawing();
    }

    CloseWindow();
}