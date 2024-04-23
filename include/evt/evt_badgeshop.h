#ifndef EVT_BADGESHOP_H
#define EVT_BADGESHOP_H

#include "dolphin/types.h"

typedef struct BadgeShopWork {
    u8 normalTable[25];     //0x0, Lovely Howz of Badges
    u8 bargainTable[25];    //0x19, Lovely Howz of Badges Discount
    u8 starPieceTable[25];  //0x32, Dazzle's Badges
    u8 salesmanTable[85];   //0x4B, Charlieton's Items
    u8 parlorTable[85];     //0xA0, Pianta Parlor
    u8 unkF5[0x124 - 0xF5]; //0xF5
} BadgeShopWork;

extern BadgeShopWork* bdsw;

s32 badgeShop_add(u8* table, s32 id, s32 value);

#endif
