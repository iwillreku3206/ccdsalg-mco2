#include "file.h"
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "commonTypes.h"
// for lowercasing
#include <ctype.h>

void to_lowercase(const char *input, String output) {
    int i;
    for (i = 0; input[i] && i < 255; i++) {
        output[i] = tolower(input[i]);
    }
    output[i] = '\0';  // Ensure null-termination
}
// Note, I've been using const char since we have string limits but it seems to be a way
// to make it so that the size 256 when strings are shorter don't mess with stuff

void split_string(const char *originalLine, String destinationNames[MAX_VERTICES + 1], int *nameCount) {
    int i = 0;
    int j = 0;
    int currentWords = 0;
    
    // Splitted words will be put here
    String newString[MAX_VERTICES + 1];

    // Loop through each character in the string
    for (i = 0; i <= (strlen(originalLine)); i++) {
        // If space/null/newline, end the word
        if (originalLine[i] == ' ' || originalLine[i] == '\0' || originalLine[i] == '\n') {
            newString[currentWords][j] = '\0';
            currentWords++;
            // reset j to zero so the next current digit is 0
            j = 0;
        } else {
            // Copy the digit from the original onto new containers
            newString[currentWords][j] = originalLine[i];
            j++;
        }
    }

    // Setting name count to 0 so it doesn't carry over or interfere in any way
    *nameCount = 0;
    for (i = 0; i < currentWords; i++) {
        strcpy(destinationNames[i], newString[i]);
        *nameCount += 1;
        
        // Stop adding after encountering "-1"
        if (strcmp(destinationNames[i], "-1") == 0) {
            break;
        }
    }
}

// For finds a valid name, for linking and for the asking of starting node
int find_index(const char *name, String vertexNames[MAX_VERTICES], int vertexCount) {
    int i;
    String lowerName;
    String lowerVertexName;

    to_lowercase(name, lowerName);

    for (i = 0; i < vertexCount; i++) {
        // case insensitivity
        to_lowercase(vertexNames[i], lowerVertexName);
        if (strcmp(lowerName, lowerVertexName) == 0) {
            return i;
        }
    }
    return -1;
}

// Adds a given index to a the links of a vertex
void add_link(Vertex *vertex, int index) {
    if (vertex->linkCount < MAX_VERTICES) {
        vertex->links[vertex->linkCount] = index;
        vertex->linkCount++;
    }
}

int graph_setup(Graph *graph, Vertex nodes[MAX_VERTICES], int *totalNodes) {
    // Counters
    int i;
    int j;
    int k;
    int lineCount = 0;

    // Finding files
    FILE *file = NULL;
    String fileName;

    // vertex from .txt
    int vertexCount;

    // Lines expected to be read from the .txt
    String lines[MAX_VERTICES];

    // The array that will store each name from each line including "-1"
    // [max number of lines to be read][max number of possible vertices + 1 because of -1][character limit]
    String names[MAX_VERTICES][MAX_VERTICES + 1];

    // Unique vertex names at the start of each line
    String vertexNames[MAX_VERTICES];
    
    // For line reading and copying
    String line;

    // Start by reading the file
    do {
        printf("Input filename: ");
        scanf("%s", fileName);

        String path = "../";
        strcat(path, fileName);

        file = fopen(path, "r");

        if (file == NULL) {
            printf("%s not found.\n", fileName);
        }
    } while (file == NULL);

    // Read starting from the vertex count
    // Has \n since it would end up reading a blank afterwards
    fscanf(file, "%d\n", &vertexCount);
    // printf("Vertex count: %d\n", vertexCount);

    while (fgets(line, sizeof(line), file)) {
        strcpy(lines[lineCount], line);
        // printf("Current line %d: %s", lineCount + 1, lines[lineCount]);
        lineCount++;
    }

    // Close file
    fclose(file);

    *totalNodes = vertexCount;

    // Initialize nodes array
    for (i = 0; i < vertexCount; i++) {
        strcpy(nodes[i].name, "");
        for (j = 0; j < MAX_VERTICES; j++) {
            nodes[i].links[j] = -1;
        }
    }

    // Splitting each line to each word so each unique vertex can be distinguished based on [0] later
    for (i = 0; i < lineCount; i++) {
        int nameCount = 0;
        split_string(lines[i], names[i], &nameCount);
        
        // to print current names
        // for (j = 0; j < nameCount; j++) {
        //     printf("Current line %d, current name %d: %s\n", i+1, j, names[i][j]);
        // }
    }

    // to copy the unique names at the start of each line
    for (k = 0; k < vertexCount; k++){
        strcpy(vertexNames[k], names[k][0]);
        strcpy(nodes[k].name, names[k][0]);
    }
    // to check unique names
    // for (k=0; k < vertexCount; k++){
    //     printf("%s\n", vertexNames[k]);
    // }

    // Adding links to nodes
    for (i = 0; i < vertexCount; i++) {
        // Start by finding fromIndex, looks at index 0
        int fromIndex = find_index(names[i][0], vertexNames, vertexCount);
        // Checks until -1 is reached
        for (j = 1; j < MAX_VERTICES && strcmp(names[i][j], "-1") != 0; j++) {
            // Find toIndex, now looping through the names after 0
            int toIndex = find_index(names[i][j], vertexNames, vertexCount);
            // Validation if any are not found
            // Notices fromindex < toIndex, it's there to stop the doubling of links for when doing to and from
            // Uses the fromIndex counter such that only those higher will be considered
            if (fromIndex != -1 && toIndex != -1 && fromIndex < toIndex) {
                // Adds the link to both
                add_link(&nodes[fromIndex], toIndex);
                add_link(&nodes[toIndex], fromIndex);
                // For checking
                // printf("From %s to %s\n", names[i][0], names[i][j]);
            }
        }
    }

    // Print the links to verify
    // for (i = 0; i < vertexCount; i++) {
    //     printf("%s's links: ", nodes[i].name);
    //     for (j = 0; j < nodes[i].linkCount; j++) {
    //         printf("%s ", vertexNames[nodes[i].links[j]]);
    //     }
    //     printf("\n");
    // }

    // GRAPH SETUP
    graph_init(graph, vertexNames, vertexCount);

    for (i = 0; i < vertexCount; i++) {
        for (j = 0; j < nodes[i].linkCount; j++) {
            int toIndex = nodes[i].links[j];
            // Has the greater than validation to avoid duplicates
            if (i < toIndex) {
                graph_add_edge(graph, i, toIndex);
            }
        }
    }

    int startIndex = -1;
    String nodeName;

    do {
        printf("Input start vertex for traversal: ");
        scanf("%s", nodeName);

        startIndex = find_index(nodeName, vertexNames, vertexCount);

        if (startIndex == -1){
            printf("Vertex %s not found.\n", nodeName);
        }
    } while (startIndex == -1);

    return startIndex;
}
