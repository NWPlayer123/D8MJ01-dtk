#ifndef ITEMDRV_H
#define ITEMDRV_H

#include "dolphin/types.h"

typedef struct ItemEntry {
    u16 flags;             //0x0
    u8 unk2[0xC - 0x2];    //0x2
    char name[0x10];       //0xC
    u8 unk1C[0x98 - 0x1C]; //0x1C
} ItemEntry;

typedef struct ItemWork {
    s32 count;           //0x0
    ItemEntry* entries;  //0x4
    s32 nextId;          //0x8, next available itemId
    u8 unkC[0x1C - 0xC]; //0xC
} ItemWork;

#endif
