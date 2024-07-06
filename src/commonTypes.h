#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#define ITEM_TYPE_ERROR -1
#define ITEM_TYPE_VALUE 0

typedef char String[256];

typedef struct {
	int type;
	int value;
} SQItem; // stack or queue item

#endif
