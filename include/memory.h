#ifndef MEMORY_H
#define MEMORY_H

#include "dolphin/types.h"

typedef enum HEAP_TYPE {
    HEAP_DEFAULT = 0,
    HEAP_INTERNAL = 1, //only used by memInit/memClear
    HEAP_EXT = 2,      //TODO: proper name for EXT
    HEAP_EFFECT = 3,
    HEAP_BATTLE = 4,
    HEAP_UNK5 = 5
} HEAP_TYPE;

void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);

#endif