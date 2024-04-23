#include "drv/itemdrv.h"

#include "dolphin/mtx.h"
#include "mario/mariost.h"
#include "memory.h"
#include "string.h"

//.bss
ItemWork work[2];

#define itemGetWork() (gp->isInBattle ? &work[1] : &work[0])

void itemInit(void) {
    ItemWork* wp;

    wp = &work[0];
    wp->count = 32;
    wp->entries = __memAlloc(0, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->nextId = 0;

    wp = &work[1];
    wp->count = 32;
    wp->entries = __memAlloc(0, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->nextId = 0;
}

s32 pouchArriveBadge(ItemType type);
void iconDelete(const char* name);

void itemReInit(void) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    ItemType type;
    int i;

    if (!gp->isInBattle) {
        for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
            if (entry->flags & 1) {
                type = entry->type;
                if (type >= BADGE_MIN && type < BADGE_MAX && (entry->flags & 0x100) == 0) {
                    pouchArriveBadge(type);
                }
            }
        }
    }

    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        iconDelete(entry->name);
        entry->flags &= ~1;
        memset(entry->name, 0, sizeof(entry->name));
    }
}

s32 pouchGetCoin(void);
void pouchAddCoin(s32 amount);
ItemEntry* itemEntry(const char* name, ItemType type, s32 a3, s32 a4, s32 a5, f32 x, f32 y, f32 z);

void itemCoinDrop(Vec position) {
    ItemEntry* entry;
    
    //If we actually have a coin to drop, drop it and spawn a new item
    if (pouchGetCoin() > 0) {
        pouchAddCoin(-1);
        entry = itemEntry(NULL, ITEM_COIN, 8, -1, 0, position.x, position.y, position.z);
        if (entry) {
            entry->unk38 |= 0x40;
        }
    }
}

ItemEntry* itemNameToPtr(char* name) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry = wp->entries;
    int i;

    for (i = 0; i < wp->count; i++, entry++) {
        if (!strcmp(entry->name, name)) {
            return entry;
        }
    }
    return 0;
}

void itemFlagOn(ItemEntry* item, s32 mask) {
    item->flags |= mask;
}

void itemFlagOff(ItemEntry* item, s32 mask) {
    item->flags &= ~mask;
}

u16 itemFlag(ItemEntry* item, s32 mask) {
    return item->flags & mask;
}
