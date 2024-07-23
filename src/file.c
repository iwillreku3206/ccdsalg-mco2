#include "file.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "commonTypes.h"
// for lowercasing

// NOTE: Some strings are set to const char since the String sizes might not be consistent

/* Splits a line to separate each name within as well as the -1
Precondition: None
@param const char *originalLine <the line to split>
@param String destinationNames[MAX_VERTICES + 1] <There is a max vertices set, with +1 to consider the last "-1">
@param int *nameCount <Tracks the number of words split>
@return none, places items within destinationNames
*/
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

/* Finds the index of a name to find, puts strings into lower case to be case insensitive
Precondition: None
@param const char *name <The name key>
@param String vertexNames[MAX_VERTICES] <From the list of names to be matched>
@param int vertexCount <Number of names>
@return int, index of the name found or -1 if not
*/
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

    // Not found
    return -1;
}

/* Modifies a Vertex to increase linkCounts and add a new item to the links
Precondition: None
@param Vertex *vertex <Vertex to be modified>
@param int index <index of a new link to add>
@return none, modifies Vertex content
*/
void add_link(Vertex *vertex, int index) {
    if (vertex->linkCount < MAX_VERTICES) {
        vertex->links[vertex->linkCount] = index;
        vertex->linkCount++;
    }
}

/* Modifies a Vertex to increase linkCounts and add a new item to the links
Precondition: None
@param Graph *graph <Graph being modified to be initialized and have edges added>
@param Vertex nodes[MAX_VERTICES] <Vertex array within main to be edited>
@param int *totalNodes <Total number of nodes reached>
@return int, the index of the starting node for the graph searches
*/
int graph_setup(Graph *graph, Vertex nodes[MAX_VERTICES], int *totalNodes) {

    /*
    PROCESS
    NOTE: I have the file inputs to keep looping when asking for an input, maybe its supposed to stop after 1 invalid

    1. Get the file, validate if it exists
        - Contains the File not found as per specs
        - The text files are outside of src
    2. Read the chosen file contents through fscanf of number of nodes, fgets for whole lines
        - all lines are placed within an array
    3. Now that an array of each name string is set from each line
        - Get fromIndex from the [0] of each line
        - Set toIndex from the names afterwards until "-1"
        - To avoid duplicates, compare to the current fromIndex in loop so that it must be higher
    4. Add Link to both to and from Indexes to set up their links
    5. Now that every content is ready, do graph_init
    6. Start adding graph edges, compare the current toIndex to avoid duplicates again
    7. Now that all node names have been set, ask for starting vertex name for the search
        - Keep asking until a valid answer is put
        - has Vertex <name> not found. as per specs
    8. Find the index where the name is kept, return it at the end as starting point for search
    */

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

    printf("Input filename: ");
    scanf("%s", fileName);

    // now set up to work with outside src group6.exe
    // String path = "./";
    // strcat(path, fileName);

    file = fopen(fileName, "r");

    if (file == NULL) {
        printf("%s not found.\n", fileName);
        fclose(file);
        return -1;
    }

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
        nodes[i].linkCount = 0;
        for (j = 0; j < MAX_VERTICES; j++) {
            // Set to -1 for now for not found
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

    // Adding of edges
    for (i = 0; i < vertexCount; i++) {
        for (j = 0; j < nodes[i].linkCount; j++) {
            int toIndex = nodes[i].links[j];
            // Has the greater than validation to avoid duplicates
            if (i < toIndex) {
                graph_add_edge(graph, i, toIndex);
            }
        }
    }

    int startIndex;
    String nodeName;

    // Inputting of starting node
    printf("Input start vertex for traversal: ");
    scanf("%s", nodeName);

    // has case insensitivity
    startIndex = find_index(nodeName, vertexNames, vertexCount);

    if (startIndex == -1){
        printf("Vertex %s not found.\n", nodeName);
        return -1;
    }

    return startIndex;
}
