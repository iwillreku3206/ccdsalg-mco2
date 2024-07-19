#include "util.h"
#include <string.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// bubble sort
void sort_by_name(String names[], int A[], int n) {
	if (n <= 1)
		return;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i; j < n; j++) {
			String tmp1;
			String tmp2;

			lowercase_name(tmp1, names[A[i]]);
			lowercase_name(tmp2, names[A[j]]);

			if (strcmp(tmp1, tmp2) > 0) {
				swap(&A[i], &A[j]);
			}
		}
	}
}

void lowercase_name(String dest, String src) {
	strcpy(dest, src);

	int len = strlen(dest);
	for (int i = 0; i < len; i++) {
		if (0x41 <= dest[i] && dest[i] <= 0x5a) {
			dest[i] += 32;
		}
	}
}

// I didn't know at the time lowercase_name existed if it did, sort it out later i guess

/* Converts a single word to lowercase using ctype.h's tolower
Precondition: None
@param const char *input <the string to convert>
@param String output <lowercased version>
@return none, changes the value of the lowercaed version
*/
void to_lowercase(const char *input, String output) {
    int i;
    for (i = 0; input[i] && i < 255; i++) {
        output[i] = tolower(input[i]);
    }
    // To close the word for sure
    output[i] = '\0';
}
