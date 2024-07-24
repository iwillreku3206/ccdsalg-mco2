#include "file.h"
#include "commonTypes.h"
#include "graph.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Splits a line to separate each name within as well as the -1
Precondition: None
@param const char *originalLine <the line to split>
@param String destinationNames[MAX_VERTICES + 1] <There is a max vertices set,
with +1 to consider the last "-1">
@param int *nameCount <Tracks the number of words split>
@return none, places items within destinationNames
*/
// void split_string(const char *originalLine,
// 				  String destinationNames[MAX_VERTICES + 1], int *nameCount) {
// 	int i = 0;
// 	int j = 0;
// 	int currentWords = 0;
//
// 	// Splitted words will be put here
// 	String newString[MAX_VERTICES + 1];
//
// 	// Loop through each character in the string
// 	for (i = 0; i <= (strlen(originalLine)); i++) {
// 		// If space/null/newline, end the word
// 		if (originalLine[i] == ' ' || originalLine[i] == '\0' ||
// 			originalLine[i] == '\n') {
// 			newString[currentWords][j] = '\0';
// 			currentWords++;
// 			// reset j to zero so the next current digit is 0
// 			j = 0;
// 		} else {
// 			// Copy the digit from the original onto new containers
// 			newString[currentWords][j] = originalLine[i];
// 			j++;
// 		}
// 	}
//
// 	// Setting name count to 0 so it doesn't carry over or interfere in any way
// 	*nameCount = 0;
// 	for (i = 0; i < currentWords; i++) {
// 		strcpy(destinationNames[i], newString[i]);
// 		*nameCount += 1;
//
// 		// Stop adding after encountering "-1"
// 		if (strcmp(destinationNames[i], "-1") == 0) {
// 			break;
// 		}
// 	}
// }
//
// /* Finds the index of a name to find, puts strings into lower case to be case
// insensitive Precondition: None
// @param const char *name <The name key>
// @param String vertexNames[MAX_VERTICES] <From the list of names to be
// matched>
// @param int vertexCount <Number of names>
// @return int, index of the name found or -1 if not
// */
// int find_index(const char *name, String vertexNames[MAX_VERTICES],
// 			   int vertexCount) {
// 	int i;
// 	String lowerName;
// 	String lowerVertexName;
//
// 	lowercase_name(lowerName, name);
//
// 	for (i = 0; i < vertexCount; i++) {
// 		// case insensitivity
// 		lowercase_name(lowerVertexName, vertexNames[i]);
// 		if (strcmp(lowerName, lowerVertexName) == 0) {
// 			return i;
// 		}
// 	}
//
// 	// Not found
// 	return -1;
// }
//
// /* Modifies a Graph to add edges based on the file data
// Precondition: None
// @param Graph *graph <Graph being modified to be initialized and have edges
// added>
// @param int *totalNodes <Number of nodes stored in main>
// @return int, the index of the starting node for the graph searches
// */
// int graph_setup(Graph *graph, int *totalNodes) {
// 	// Counters
// 	int i;
// 	int j;
// 	int k;
// 	int lineCount = 0;
//
// 	// File variables
// 	FILE *file = NULL;
// 	String fileName;
//
// 	// Number of vertices from .txt's first line
// 	int vertexCount;
//
// 	// Lines expected to be read from the .txt
// 	String lines[MAX_VERTICES];
//
// 	// The array that will store each name from each line including "-1"
// 	// [max number of lines to be read][max number of possible vertices + 1
// 	// because of -1]
// 	String names[MAX_VERTICES][MAX_VERTICES + 1];
//
// 	// Unique vertex names at the start of each line
// 	String vertexNames[MAX_VERTICES];
//
// 	// For line reading and copying
// 	String line;
//
// 	// Start by reading the file
// 	printf("Input filename: ");
// 	scanf("%s", fileName);
//
// 	file = fopen(fileName, "r");
//
// 	if (file == NULL) {
// 		printf("%s not found.\n", fileName);
// 		fclose(file);
// 		return -1;
// 	}
//
// 	// Read starting from the vertex count
// 	fscanf(file, "%d\n", &vertexCount);
//
// 	while (fgets(line, sizeof(line), file)) {
// 		// Remove last newline
// 		int lineLength = strlen(line);
// 		if (line[lineLength - 1] == '\n') {
// 			line[lineLength - 1] = '\0';
// 		}
// 		strcpy(lines[lineCount], line);
// 		lineCount++;
// 	}
//
// 	// Close file
// 	fclose(file);
//
// 	// Sets number of nodes at main
// 	*totalNodes = vertexCount;
//
// 	// Splitting each line to each word so each unique vertex can be
// 	// distinguished based on [0] later
// 	for (i = 0; i < lineCount; i++) {
// 		int nameCount = 0;
// 		split_string(lines[i], names[i], &nameCount);
// 	}
//
// 	// Copy the unique names at the start of each line
// 	for (k = 0; k < vertexCount; k++) {
// 		strcpy(vertexNames[k], names[k][0]);
// 	}
//
// 	// GRAPH SETUP
// 	graph_init(graph, vertexNames, vertexCount);
//
// 	// Adding of edges
// 	for (i = 0; i < vertexCount; i++) {
// 		int fromIndex = i;
// 		// Validation to check for -1 in names
// 		for (j = 1; j < MAX_VERTICES && strcmp(names[i][j], "-1") != 0; j++) {
// 			// uses toIndex to match with the correct nodes
// 			int toIndex = find_index(names[i][j], vertexNames, vertexCount);
//
// 			if (fromIndex < toIndex) {
// 				graph_add_edge(graph, fromIndex, toIndex);
// 			}
// 		}
// 	}
//
// 	int startIndex;
// 	String nodeName;
//
// 	// Inputting of starting node
// 	printf("Input start vertex for traversal: ");
// 	scanf("%s", nodeName);
//
// 	// Has case insensitivity
// 	startIndex = find_index(nodeName, vertexNames, vertexCount);
//
// 	if (startIndex == -1) {
// 		printf("Vertex %s not found.\n", nodeName);
// 		return -1;
// 	}
//
// 	return startIndex;
// }

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

void graph_setup(Graph *graph, int *startIndex) {
	String fileName;
	printf("Input filename: ");
	scanf("%s", fileName);

	FILE *file = fopen(fileName, "rb");

	if (file == NULL) {
		printf("%s not found.\n", fileName);
		fclose(file);
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
