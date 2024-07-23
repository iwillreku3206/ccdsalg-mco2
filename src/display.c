#include "C:\raylib\raylib\src\raylib.h"
#include "fdgraphviz.h"
#include <stdio.h>

void draw_edge(Node a, Node b) {
    Vector2 c, d;
    c.x = a.x;
    c.y = a.y;
    d.x = b.x;
    d.y = b.y;
    DrawLineEx(c, d, 5, BLACK);
}

void draw_node(Node a) {
    Vector2 n;
    int measure;
    n.x = a.x;
    n.y = a.y;

    DrawCircleV(n, 50, WHITE);
    DrawCircleLinesV(n, 50, BLACK);
    measure = MeasureText(a.name, 20);
    DrawText(a.name, n.x - measure / 2, n.y - 10, 20, BLACK);
}

void open_window(Graph g, Node vertices[]) {
    int i, j;
    InitWindow(1600, 900, "Graph");

    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            for(i = 0; i < g.vertexCount; i++) {
                for(j = 0; j < g.vertexCount; j++) {
                    if(i != j && g.adjacencyMatrix[i][j] == true) {
                        draw_edge(vertices[i], vertices[j]);
                    }
                }
            }

            for(i = 0; i < g.vertexCount; i++) {
                draw_node(vertices[i]);
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