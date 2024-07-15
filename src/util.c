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
