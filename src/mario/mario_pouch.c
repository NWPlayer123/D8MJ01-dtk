#include "mario/mario_pouch.h"

#include "drv/msgdrv.h"
#include "evt/evt_badgeshop.h"
#include "item_data.h"
#include "memory.h"

//.sbss
PouchData* mpp;

s16 _party_max_hp_table[8][4] = {
    {0,  0,  0,  0  },
    {10, 20, 30, 200},
    {10, 15, 25, 200},
    {20, 30, 40, 200},
    {10, 20, 30, 200},
    {15, 25, 35, 200},
    {15, 20, 30, 200},
    {15, 20, 25, 200}
};

//function prototypes
s32 pouchGetPartyMaxHpBase(void);
s32 pouchEquipCheckBadge(ItemType item);

PouchData* pouchGetPtr(void) {
    return mpp;
}

void pouchInit(void) {
    int i;

    mpp = __memAlloc(HEAP_DEFAULT, sizeof(PouchData));
    memset(mpp, 0, sizeof(PouchData));
    for (i = 0; i < MAX_KEY_ITEMS; i++) {
        mpp->keyItems[i] = ITEM_NULL;
    }
    for (i = 0; i < MAX_HELD_ITEMS; i++) {
        mpp->heldItems[i] = ITEM_NULL;
    }
    for (i = 0; i < MAX_STORED_ITEMS; i++) {
        mpp->storedItems[i] = ITEM_NULL;
    }
    for (i = 0; i < MAX_BADGES; i++) {
        mpp->badges[i] = ITEM_NULL;
    }
    for (i = 0; i < MAX_BADGES; i++) {
        mpp->equippedBadges[i] = ITEM_NULL;
    }
}

s32 pouchCheckItem(ItemType item) {
    int i;
    s32 count;

    if ((item >= ITEM_MIN) && (item < ITEM_MAX)) {
        count = 0;
        for (i = 0; i < MAX_HELD_ITEMS; i++) {
            if (item == mpp->heldItems[i]) {
                count++;
            }
        }
        return count;
    }
    if ((item >= KEY_ITEM_MIN) && (item < KEY_ITEM_MAX)) {
        count = 0;
        for (i = 0; i < MAX_KEY_ITEMS; i++) {
            if (item == mpp->keyItems[i]) {
                count++;
            }
        }
        return count;
    }
    if ((item >= BADGE_MIN) && (item < BADGE_MAX)) {
        count = 0;
        for (i = 0; i < MAX_BADGES; i++) {
            if (item == mpp->badges[i]) {
                count++;
            }
        }
        return count;
    }
    return 0;
}

s32 comp_aiueo(const s16* arg0, const s16* arg1) {
    s32 id1 = *arg0;
    s32 id2 = *arg1;

    s32 result =
        strcmp(msgSearch(itemDataTable[id1].msgName), msgSearch(itemDataTable[id2].msgName));

    if (result > 0) {
        return 1;
    }

    return result < 0 ? -1 : 0;
}

s32 comp_kind(const s16* arg0, const s16* arg1) {
    s32 id1 = *arg0;
    s32 id2 = *arg1;
    s16 temp_r3;
    s16 temp_r5;

    temp_r5 = itemDataTable[id1].unk12;
    temp_r3 = itemDataTable[id2].unk12;
    if (temp_r5 > temp_r3) {
        return 1;
    }
    return temp_r5 < temp_r3 ? -1 : 0;
}

s32 comp_aiueo_r(const s16* arg0, const s16* arg1) {
    s32 id1 = *arg0;
    s32 id2 = *arg1;

    s32 result =
        strcmp(msgSearch(itemDataTable[id1].msgName), msgSearch(itemDataTable[id2].msgName));

    if (result < 0) {
        return 1;
    }

    return result > 0 ? -1 : 0;
}

s32 comp_kind_r(const s16* arg0, const s16* arg1) {
    s32 id1 = *arg0;
    s32 id2 = *arg1;
    s16 temp_r3;
    s16 temp_r5;

    temp_r5 = itemDataTable[id1].unk12;
    temp_r3 = itemDataTable[id2].unk12;
    if (temp_r5 < temp_r3) {
        return 1;
    }
    return temp_r5 > temp_r3 ? -1 : 0;
}

s16 pouchGetCoin(void) {
    return mpp->coins;
}

s16 pouchAddCoin(s16 coins) {
    mpp->coins += coins;
    if (mpp->coins < 0) {
        mpp->coins = 0;
    }
    if (mpp->coins > 999) {
        mpp->coins = 999;
    }
    return mpp->coins;
}

s16 pouchSetCoin(s16 coins) {
    mpp->coins = coins;
    if (mpp->coins < 0) {
        mpp->coins = 0;
    }
    if (mpp->coins > 999) {
        mpp->coins = 999;
    }
    return mpp->coins;
}

s16 pouchGetSuperCoin(void) {
    return mpp->shineSprites;
}

s16 pouchSetSuperCoin(s16 shines) {
    mpp->shineSprites = shines;
    return mpp->shineSprites;
}

s16 pouchGetStarPiece(void) {
    return mpp->starPieces;
}

s16 pouchAddStarPiece(s16 pieces) {
    mpp->starPieces += pieces;
    return mpp->starPieces;
}

s16 pouchAddHP(s16 points) {
    mpp->currentHP = (s32)(mpp->currentHP + points);
    if (mpp->currentHP < 0) {
        mpp->currentHP = 0;
    }
    if (mpp->currentHP > mpp->maximumHP) {
        mpp->currentHP = mpp->maximumHP;
    }
    return mpp->currentHP;
}

s16 pouchGetHP(void) {
    return mpp->currentHP;
}

s16 pouchGetMaxHP(void) {
    return mpp->maximumHP;
}

void pouchSetHP(s16 points) {
    mpp->currentHP = points;
    if (mpp->currentHP > mpp->maximumHP) {
        mpp->currentHP = mpp->maximumHP;
    }
}

void pouchSetMaxHP(s16 points) {
    mpp->maximumHP = points;
    mpp->baseMaxHP = mpp->maximumHP;
}

s32 pouchGetPartyHP(s32 slot) {
    return mpp->party[slot].currentHP;
}

void pouchSetPartyHP(s32 slot, s16 points) {
    PouchPartyData* party;

    mpp->party[slot].currentHP = points;
    party = &mpp->party[slot];
    if (party->currentHP > party->maximumHP) {
        party->currentHP = party->maximumHP;
    }
}

s16 pouchGetFP(void) {
    return mpp->currentFP;
}

s16 pouchGetMaxFP(void) {
    return mpp->maximumFP;
}

void pouchSetFP(s16 points) {
    mpp->currentFP = points;
    if (mpp->currentFP > mpp->maximumFP) {
        mpp->currentFP = mpp->maximumFP;
    }
}

void pouchSetMaxFP(s16 points) {
    mpp->maximumFP = points;
    mpp->baseMaxFP = mpp->maximumFP;
}

s16 pouchGetAP(void) {
    return mpp->currentSP;
}

void pouchAddAP(s16 points) {
    mpp->currentSP += points;
    if (mpp->currentSP < 0) {
        mpp->currentSP = 0;
    }
    if (mpp->currentSP > mpp->maximumSP) {
        mpp->currentSP = mpp->maximumSP;
    }
}

void pouchSetAP(s16 points) {
    mpp->currentSP = points;
    if (mpp->currentSP < 0) {
        mpp->currentSP = 0;
    }
    if (mpp->currentSP > mpp->maximumSP) {
        mpp->currentSP = mpp->maximumSP;
    }
}

s16 pouchGetMaxAP(void) {
    return mpp->maximumSP;
}

f32 pouchGetAudienceNum(void) {
    return mpp->audienceCount;
}

void pouchSetAudienceNum(f32 count) {
    mpp->audienceCount = count;
}

s32 pouchGetJumpLv(void) {
    s32 level = 0;

    if (pouchCheckItem(ITEM_ULTRA_BOOTS)) {
        level = 3;
    }
    else if (pouchCheckItem(ITEM_SUPER_BOOTS)) {
        level = 2;
    }
    else if (pouchCheckItem(ITEM_BOOTS)) {
        level = 1;
    }

    mpp->jumpLevel = level;
    return mpp->jumpLevel;
}

s32 pouchGetHammerLv(void) {
    s32 level = 0;

    if (pouchCheckItem(ITEM_ULTRA_HAMMER)) {
        level = 3;
    }
    else if (pouchCheckItem(ITEM_SUPER_HAMMER)) {
        level = 2;
    }
    else if (pouchCheckItem(ITEM_HAMMER)) {
        level = 1;
    }

    mpp->hammerLevel = level;
    return mpp->hammerLevel;
}

s16 pouchGetPartyAttackLv(s32 slot) {
    PouchPartyData* party = &mpp->party[slot];
    return party->attackLevel;
}

BOOL pouchAddKeepItem(ItemType item) {
    int i;
    for (i = 0; i < MAX_STORED_ITEMS; i++) {
        if (mpp->storedItems[i] == ITEM_NULL) {
            break;
        }
    }
    if (i < MAX_STORED_ITEMS) {
        mpp->storedItems[i] = item;
        return TRUE;
    }
    return FALSE;
}

BOOL pouchRemoveKeepItem(ItemType item) {
    int i;
    for (i = 0; i < MAX_STORED_ITEMS; i++) {
        if (mpp->storedItems[i] == item) {
            break;
        }
    }
    if (i < MAX_STORED_ITEMS) {
        mpp->storedItems[i] = 0;
        return TRUE;
    }
    return FALSE;
}

void pouchReviseMarioParam(void) {
    ItemData* item;
    int i;

    mpp->maximumHP = mpp->baseMaxHP;
    mpp->maximumFP = mpp->baseMaxFP;
    for (i = 0; i < MAX_BADGES; i++) {
        if (((s32)mpp->equippedBadges[i]) != ITEM_NULL) {
            switch (((s32)mpp->equippedBadges[i])) {
            case ITEM_HP_PLUS:
                mpp->maximumHP += 5;
                break;
            case ITEM_FP_PLUS:
                mpp->maximumFP += 5;
                break;
            }
        }
    }

    if (mpp->currentHP > mpp->maximumHP) {
        mpp->currentHP = mpp->maximumHP;
    }

    if (mpp->currentFP > mpp->maximumFP) {
        mpp->currentFP = mpp->maximumFP;
    }

    mpp->availableBP = mpp->maximumBP;
    for (i = 0; i < MAX_BADGES; i++) {
        item = &itemDataTable[mpp->equippedBadges[i]];
        mpp->availableBP -= item->badgePoints;
    }
}

void pouchRevisePartyParam(void) {
    PouchPartyData* party;
    int count;
    int j;

    count = pouchGetPartyMaxHpBase();
    count *= 5;
    for (j = 0; j < 8; j++) {
        if (j != 0) {
            party = &mpp->party[j];
            party->unk4 = _party_max_hp_table[j][party->unk8];
            party->maximumHP = party->unk4 + count;
            if (party->currentHP > party->maximumHP) {
                party->currentHP = party->maximumHP;
            }
        }
    }
}

inline s32 pouchGetPartyMaxHpBase(void) {
    return pouchEquipCheckBadge(ITEM_HP_PLUS_P);
}

s16 pouchGetStarPoint(void) {
    return mpp->starPoints;
}

BOOL pouchEquipBadgeIndex(s32 index) {
    s16 badge = mpp->badges[index];
    if (badge == ITEM_NULL) {
        return FALSE;
    }
    mpp->equippedBadges[index] = badge;
    return TRUE;
}

BOOL pouchUnEquipBadgeIndex(s32 index) {
    s16 badge = mpp->equippedBadges[index];
    if (badge == ITEM_NULL) {
        return FALSE;
    }
    mpp->equippedBadges[index] = ITEM_NULL;
    return TRUE;
}

s32 pouchEquipCheckBadge(ItemType item) {
    int i, count;

    for (count = 0, i = 0; i < MAX_BADGES; i++) {
        if (item == mpp->equippedBadges[i]) {
            count++;
        }
    }
    return count;
}

BOOL pouchEquipCheckBadgeIndex(s32 index) {
    return mpp->equippedBadges[index] != 0;
}

BOOL pouchEquipBadgeID(ItemType item) {
    int i;

    for (i = 0; i < 200; i++) {
        if (mpp->badges[i] == item) {
            if (mpp->badges[i] != ITEM_NULL) {
                mpp->equippedBadges[i] = mpp->badges[i];
            }
            return TRUE;
        }
    }
    return FALSE;
}

s32 pouchArriveBadge(ItemType item) {
    return badgeShop_add(bdsw->bargainTable, (s16)item, 1);
}

void pouchMajinaiInit(s32 spells) {
    if ((u8)mpp->merleeSpellsLeft < spells) {
        mpp->merleeSpellsLeft = spells;
        mpp->merleeTurnsLeft = -1;
        mpp->merleeSpellType = 0;
    }
}

s8 pouchGetKpaCoin(void) {
    return mpp->bowserCoins;
}

BOOL pouchAddKpaCoin(s8 coins) {
    BOOL result = FALSE;
    mpp->bowserCoins += coins;
    if ((u8)mpp->bowserCoins >= 100) {
        result = TRUE;
        mpp->bowserCoins -= 100;
    }
    return result;
}

s32 pouchGetKpaScore(void) {
    return mpp->bowserScore;
}

void pouchAddKpaScore(s32 score) {
    mpp->bowserScore += score;
    if (mpp->bowserScore > 999999u) {
        mpp->bowserScore = 999999;
    }
}

void pouchGetStarStone(s32 level) {
    if (!mpp->starPowerLevel) {
        mpp->audienceCount = 2.0;
    }
    mpp->starPowerLevel |= 1 << level;
    mpp->maximumSP = 100 * (level + 1);
    if (mpp->maximumSP < 0) {
        mpp->maximumSP = 0;
    }
    if (mpp->maximumSP > 800) {
        mpp->maximumSP = 800;
    }
}

s32 pouchReceiveMailCount(void) {
    int i, count = 0;

    for (i = 0; i < 99; i++) {
        if (mpp->emailReceivedFlags[i / 32] & (1 << (i % 32))) {
            count++;
        }
    }
    return count;
}

void pouchReceiveMail(s32 email) {
    s32 index, shift, count;

    index = email / 32;
    shift = email % 32;
    count = pouchReceiveMailCount();
    mpp->emailReceivedFlags[index] |= 1 << shift;
    mpp->emailIds[count] = email;
}

void pouchOpenMail(s32 email) {
    mpp->emailReadFlags[email / 32] |= 1 << (email % 32);
}

s32 pouchCheckMail(s32 email) {
    if (mpp->emailReadFlags[email / 32] & (1 << (email % 32))) {
        return 2;
    }
    return (mpp->emailReceivedFlags[email / 32] & (1 << (email % 32))) != 0;
}

s32 pouchGetPartyColor(s32 slot) {
    return mpp->party[slot].flags >> 13;
}

void pouchSetPartyColor(s32 slot, u16 color) {
    mpp->party[slot].flags = (mpp->party[slot].flags & 0x1FFF) | ((color << 13) & 0xE000);
}

void pouchSetYoshiName(const char* name) {
    strcpy(mpp->yoshiName, name);
}

const char* pouchGetYoshiName(void) {
    if (strlen(mpp->yoshiName) < 1U) {
        return msgSearch("name_party3");
    }
    return mpp->yoshiName;
}
