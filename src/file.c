#include "file.h"
#include "commonTypes.h"
#include "graph.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * linear_search - perform a case-insensitive linear search on an array of
 *                 strings
 * @param A - array of strings to search
 * @param x - search key
 * @param n - length of A
 * @return index, -1 if not found
 */
int linear_search(String A[], String x, int n) {
	for (int i = 0; i < n; i++) {
		String t1;
		String t2;
		lowercase_name(t1, A[i]);
		lowercase_name(t2, x);
		if (strcmp(t1, t2) == 0) {
			return i;
		}
	}
	return -1;
}

/**
 * graph_setup - prompt user for filename and load graph
 *               as well as prompt for traversal starting vertex
 * @param graph - pointer to graph
 * @param startIndex - pointer where startIndex will be stored
 */
void graph_setup(Graph *graph, int *startIndex) {
	String fileName;
	printf("Input filename: ");
	scanf("%s", fileName);

	FILE *file = fopen(fileName, "rb");

	if (file == NULL) {
		printf("%s not found.\n", fileName);
		exit(1);
	}

	int vertexCount;
	fscanf(file, "%d\n", &vertexCount);

	String vertexNames[vertexCount];
	String tmp;
	int currentName = 0;

	// get vertex names first
	while (!feof(file)) {
		if (currentName >= vertexCount)
			break;
		fscanf(file, "%s ", vertexNames[currentName++]);
		// get rid of everything until next line
		fgets(tmp, sizeof(String), file);
	}

	graph_init(graph, vertexNames, vertexCount);
	rewind(file);

	for (int i = 0; i < vertexCount; i++) {
		// ignore the first line
		fgets(tmp, sizeof(String), file);

		// ignore the first "word"
		fscanf(file, "%s ", tmp);
		while (!feof(file)) {
			// scan in a word
			fscanf(file, "%s", tmp);
			// check if it is a "-1"
			if (strcmp(tmp, "-1") == 0) {
				break;
			}
			// if not, then search for that vertex in the list of vertices
			int idx = linear_search(vertexNames, tmp, vertexCount);
			graph_add_edge(graph, i, idx);
		}
	}
	String nodeName;
	printf("Input start vertex for traversal: ");
	scanf("%s", nodeName);

	*startIndex = linear_search(vertexNames, nodeName, vertexCount);
	if (*startIndex == -1) {
		printf("Vertex %s not found.\n", nodeName);
		exit(1);
	}
}
