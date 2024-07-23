#include "bfs.h"
#include "graph.h"
#include "queue.h"
#include "util.h"
#include <stdio.h>
#include <stdbool.h>

// Corrected all_discovered function
bool all_discovered(bool A[], int n) {
    for (int i = 0; i < n; i++) {
        if (A[i] == false) {
            return false;
        }
    }
    return true;
}

void bfs(Graph *graph, Graph *bfsTree, int from, FILE *file) {
    Queue queue;
    bool discovered[graph->vertexCount];
    graph_init(bfsTree, graph->vertexList, graph->vertexCount);
    queue_init(&queue);

    for (int i = 0; i < graph->vertexCount; i++) {
        discovered[i] = false;
    }

    queue_enqueue(&queue, from);
    discovered[from] = true;

    while (!queue_empty(&queue)) {
        printf("LOOP START\n");
        int vertex = queue_dequeue(&queue).value;
        printf("CURRENT VERTEX: %d\n", vertex);
        printf("%s ", graph->vertexList[vertex]);
        fprintf(file, "%s ", graph->vertexList[vertex]);

        // Place all discoverable vertices into an array
        int nextVertices[graph->vertexCount];
        int nextCount = 0;

        for (int i = 0; i < graph->vertexCount; i++) {
            if (graph->adjacencyMatrix[vertex][i] == true &&
                discovered[i] == false) {
                nextVertices[nextCount] = i;
                nextCount++;
            }
        }

        // Sort the array
        sort_by_name(graph->vertexList, nextVertices, nextCount);
        printf("JUST SORTED\n");

        // Enqueue the next vertices in the list, in order
        for (int i = 0; i < nextCount; i++) {
            queue_enqueue(&queue, nextVertices[i]);
            graph_add_edge(bfsTree, vertex, nextVertices[i]);
            printf("ADDED EDGE %d\n", vertex);
            discovered[nextVertices[i]] = true;
            printf("discovered %d\n", vertex);
        }
    }
}
