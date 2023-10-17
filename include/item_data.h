#ifndef ITEM_DATA_H
#define ITEM_DATA_H

#include "dolphin/types.h"

typedef struct ItemData {
    const char* name; //0x0
    const char* msgName; //0x4
    const char* msgDesc; //0x8
    const char* msgMenu; //0xC
    s16 unk10; //0x10
    s16 unk12; //0x12
    s16 unk14; //0x14
    s16 unk16; //0x16
    s16 unk18; //0x18
    s16 unk1A; //0x1A
    s8 badgePoints; //0x1C
    s8 unk1D; //0x1D
    s8 unk1E; //0x1E
    s8 unk1F; //0x1F
    s16 unk20; //0x20
    s16 unk22; //0x22
    void* unk24; //0x24
} ItemData;

extern ItemData itemDataTable[430];

#endif