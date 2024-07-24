#include "util.h"
#include <string.h>

/** swap - swaps the values in a and b
 * @param a - pointer to first item to swap
 * @param b - pointer to second item to swap
 */
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

/** sort_by_name - sorts an array of indices based on vertex IDs looked up from
 *                an array
 * @param names - Array of vertex ID's for lookup
 * @param A - Array of indices to be sorte
 * @param n - length of A
 */
void sort_by_name(String names[], int A[], int n) {
	if (n <= 1)
		return;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i; j < n; j++) {
			if (strcmp(names[A[i]], names[A[j]]) > 0) {
				swap(&A[i], &A[j]);
			}
		}
	}
}

/** lowercase_name - copies an ASCII-lowercase version of a string from `src` to
 *                   `dest`
 *  @param dest - location for string to be copied to
 *  @param src - source string
 */
void lowercase_name(String dest, const char *src) {
	strcpy(dest, src);

	int len = strlen(dest);
	for (int i = 0; i < len; i++) {
		if (0x41 <= dest[i] && dest[i] <= 0x5a) {
			dest[i] += 32;
		}
	}
}
