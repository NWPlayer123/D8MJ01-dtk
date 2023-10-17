#include "drv/itemdrv.h"

#include "mario/mariost.h"
#include "memory.h"

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