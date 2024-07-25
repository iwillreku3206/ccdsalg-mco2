/***************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and
applying the concepts learned. I have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and debugged by my own
efforts. I further certify that I have not copied in part or whole or otherwise plagiarized the
work of other students and/or persons.
 Hiroyuki Tabe, DLSU ID# 12207838
***************************************************************************/

/*
 Description: This file is responsible for interaction with the raylib library
 Programmed by: Hiroyuki Tabe
 [Acknowledgements: 
 	https://stackoverflow.com/questions/69863663/how-do-i-link-and-compile-raylib-on-windows
 	https://www.youtube.com/watch?v=-F6THkPkF2I - Getting Started with Raylib - C Tutorial
 	https://www.reddit.com/r/raylib/comments/rh3zm4/center_text/
    https://www.raylib.com/cheatsheet/cheatsheet.html
 ]
*/

#include "display.h"

/** draw_edge - function that draws an edge between two nodes
 *  @param a - Node representing the start of the line drawing
 *  @param b - Node representing the end of the line drawing
 *  @param size - Thickness of the line
 */
void draw_edge(Node a, Node b, int size) {
    Vector2 c, d;
    c.x = a.x;
    c.y = a.y;
    d.x = b.x;
    d.y = b.y;
    DrawLineEx(c, d, size, BLACK);
}

/** draw_node - function that draws a Node into the window using its position and name
 *  @param a - Node to be drawn
 *  @param radius - Radius of the circle
 *  @param fontSize - Font size of the text
 */
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

/** open_window - Opens a window using raylib
 *  @param g - Graph that is the source of the vertices
 */
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