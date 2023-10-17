#ifndef MARIO_POUCH_H
#define MARIO_POUCH_H

#include "dolphin/types.h"

#define MAX_KEY_ITEMS    121
#define MAX_HELD_ITEMS   20
#define MAX_STORED_ITEMS 32
#define MAX_BADGES       200

typedef enum ItemType {
    ITEM_NULL = 0,             //0x0
    ITEM_STRANGE_SACK,         //0x1
    ITEM_BOOTS = 6,            //0x6
    ITEM_SUPER_BOOTS,          //0x7
    ITEM_ULTRA_BOOTS,          //0x8
    ITEM_HAMMER,               //0x9
    ITEM_SUPER_HAMMER,         //0xA
    ITEM_ULTRA_HAMMER,         //0xB
    ITEM_CRYSTAL_STAR = 120,   //0x78
    ITEM_COIN,                 //0x79
    ITEM_FRESH_JUICE = 235,    //0xEB
    ITEM_AUDIENCE_CAN,         //0xEC
    ITEM_AUDIENCE_ROCK,        //0xED
    ITEM_AUDIENCE_BONE,        //0xEE
    ITEM_AUDIENCE_HAMMER,      //0xEF
    ITEM_POWER_JUMP,           //0xF0
    ITEM_HP_PLUS = 278,        //0x116
    ITEM_HP_PLUS_P,            //0x117
    ITEM_FP_PLUS,              //0x118
    ITEM_SUPER_CHARGE_P = 338, //0x152
    ITEM_MAX,                  //0x153
} ItemType;

#define KEY_ITEM_MIN ITEM_STRANGE_SACK
#define KEY_ITEM_MAX ITEM_CRYSTAL_STAR + 1
#define ITEM_MIN     ITEM_COIN
#define ITEM_MAX     ITEM_FRESH_JUICE + 1
#define BADGE_MIN    ITEM_POWER_JUMP
#define BADGE_MAX    ITEM_SUPER_CHARGE_P + 1

typedef struct PouchPartyData {
    u16 flags;       //0x0
    s16 maximumHP;   //0x2
    s16 unk4;        //0x4
    s16 currentHP;   //0x6
    s16 unk8;        //0x8
    s16 attackLevel; //0xA
    s16 unkC;        //0xC
} PouchPartyData;

typedef struct PouchData {
    PouchPartyData party[8];           //0x0
    s16 currentHP;                     //0x70
    s16 maximumHP;                     //0x72, includes HP Plus badges
    s16 currentFP;                     //0x74
    s16 maximumFP;                     //0x76, includes FP Plus badges
    s16 coins;                         //0x78
    s16 currentSP;                     //0x7A
    s16 maximumSP;                     //0x7C
    u8 unk7E[0x84 - 0x7E];             //0x7E
    f32 audienceCount;                 //0x84
    u8 unk88[0x8C - 0x88];             //0x88
    u16 starPowerLevel;                //0x8C, how many star powers we've obtained
    s16 baseMaxHP;                     //0x8E
    s16 baseMaxFP;                     //0x90
    s16 availableBP;                   //0x92
    s16 maximumBP;                     //0x94
    s16 starPoints;                    //0x96
    s8 jumpLevel;                      //0x98
    s8 hammerLevel;                    //0x99
    s16 starPieces;                    //0x9A
    s16 shineSprites;                  //0x9C
    u8 unk9E[0xA0 - 0x9E];             //0x9E
    s16 keyItems[MAX_KEY_ITEMS];       //0xA0
    s16 heldItems[MAX_HELD_ITEMS];     //0x192
    s16 storedItems[MAX_STORED_ITEMS]; //0x1BA
    s16 badges[MAX_BADGES];            //0x1FA
    s16 equippedBadges[MAX_BADGES];    //0x38A
    s8 emailIds[100];                  //0x51A
    u8 unk57E[0x580 - 0x57E];          //0x57E
    s32 emailReceivedFlags[4];         //0x580
    s32 emailReadFlags[4];             //0x590
    u8 unk5A0[0x5B8 - 0x5A0];          //0x5A0
    s8 merleeSpellsLeft;               //0x5B8, number of spells left
    s8 merleeTurnsLeft;                //0x5B9, number of turns until next spell
    s8 merleeSpellType;                //0x5BA, type of next spell
    s8 bowserCoins;                    //0x5BB
    s32 bowserScore;                   //0x5BC
    char yoshiName[16];                //0x5C0
    u8 unk5D0[0x5D4 - 0x5D0];          //0x5D0
} PouchData;

s32 pouchCheckItem(ItemType item);

#endif