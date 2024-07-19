#ifndef UTIL_H
#define UTIL_H

#include "commonTypes.h"
#include <ctype.h>

void sort_by_name(String names[], int A[], int n);
void lowercase_name(String dest, String src);
void to_lowercase(const char *input, String output);

#endif
