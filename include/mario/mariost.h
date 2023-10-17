#ifndef MARIOST_H
#define MARIOST_H

#include "dolphin/types.h"

typedef struct GlobalWork {
    u8 unk0[0x14 - 0x0];     //0x0
    BOOL isInBattle;         //0x14
    u8 unk18[0x13D8 - 0x18]; //0x18
} GlobalWork;

//Convenient extern so we don't have to declare it at the top of every file
extern GlobalWork* gp;

#endif