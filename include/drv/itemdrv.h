#ifndef ITEMDRV_H
#define ITEMDRV_H

#include "dolphin/types.h"

#include "mario/mario_pouch.h"

typedef struct ItemEntry {
    u16 flags;             //0x0
    u8 unk2[0x4 - 0x2];    //0x2
    ItemType type;         //0x4
    u8 unk8[0xC - 0x8];    //0x8
    char name[0x10];       //0xC
    u8 unk1C[0x38 - 0x1C]; //0x1C
    s32 unk38;             //0x38
    u8 unk3C[0x98 - 0x3C]; //0x3C
} ItemEntry;

typedef struct ItemWork {
    s32 count;           //0x0
    ItemEntry* entries;  //0x4
    s32 nextId;          //0x8, next available itemId
    u8 unkC[0x1C - 0xC]; //0xC
} ItemWork;

void itemInit(void);
ItemEntry* itemNameToPtr(char* name);
void itemFlagOn(ItemEntry* item, s32 mask);
void itemFlagOff(ItemEntry* item, s32 mask);
u16 itemFlag(ItemEntry* item, s32 mask);

#endif
