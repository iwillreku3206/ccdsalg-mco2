#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#define ITEM_TYPE_ERROR -1
#define ITEM_TYPE_VALUE 0

typedef char String[256];

typedef struct {
	int type;
	int value;
} SQItem; // stack or queue item

// Going to put this here for the time being
#define MAX_VERTICES 50

#endif
