#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "item.h"
#include "item_menu.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "constants/hold_effects.h"
#include "constants/items.h"

// Helpers for the regional form trader (Pokemon Centers) and the item
// refiller (Marts). The scripts live in data/scripts/service_npcs.inc.

#define REFILL_TARGET 99

enum
{
    REGIONAL_TRADE_OK,
    REGIONAL_TRADE_EGG,
    REGIONAL_TRADE_CANCEL,
};

enum
{
    ITEM_REFILL_DONE,
    ITEM_REFILL_NOT_ALLOWED,
    ITEM_REFILL_FULL,
};

// In:  VAR_0x8004 = party slot from ChoosePartyMon.
// Out: VAR_RESULT = REGIONAL_TRADE_*, VAR_0x8006 = level, STR_VAR_1 = nickname.
void RegionalTrade_CheckPartyMon(void)
{
    struct Pokemon *mon;
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];

    if (gSpecialVar_0x8004 >= PARTY_SIZE)
    {
        gSpecialVar_Result = REGIONAL_TRADE_CANCEL;
        return;
    }

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    if (GetMonData(mon, MON_DATA_IS_EGG) || GetMonData(mon, MON_DATA_SPECIES) == SPECIES_NONE)
    {
        gSpecialVar_Result = REGIONAL_TRADE_EGG;
        return;
    }

    gSpecialVar_0x8006 = GetMonData(mon, MON_DATA_LEVEL);
    GetMonData(mon, MON_DATA_NICKNAME, nickname);
    StringCopy_Nickname(gStringVar1, nickname);
    gSpecialVar_Result = REGIONAL_TRADE_OK;
}

// In: VAR_0x8004 = party slot. Removes that Pokemon; its held item goes to the bag.
void RegionalTrade_RemovePartyMon(void)
{
    struct Pokemon *mon;
    u16 heldItem;

    if (gSpecialVar_0x8004 >= PARTY_SIZE)
        return;

    mon = &gParties[B_TRAINER_PLAYER][gSpecialVar_0x8004];
    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (heldItem != ITEM_NONE)
        AddBagItem(heldItem, 1);

    ZeroMonData(mon);
    CompactPartySlots();
    CalculatePlayerPartyCount();
    UpdateFollowingPokemon();
}

static bool32 CanRefillItem(u16 itemId)
{
    if (itemId == ITEM_NONE || itemId >= ITEMS_COUNT)
        return FALSE;
    if (GetItemImportance(itemId))
        return FALSE;

    switch (GetItemPocket(itemId))
    {
    case POCKET_KEY_ITEMS:
    case POCKET_TM_HM:
    case POCKET_MEGA_STONES:
        return FALSE;
    default:
        break;
    }

    switch (GetItemHoldEffect(itemId))
    {
    case HOLD_EFFECT_MEGA_STONE:
    case HOLD_EFFECT_PRIMAL_ORB:
    case HOLD_EFFECT_Z_CRYSTAL:
        return FALSE;
    default:
        break;
    }

    return TRUE;
}

// Balls, berries and anything usable from the bag (potions, candies, stones...)
// count as consumables. Pure held items such as Leftovers only get +1.
static bool32 IsStackableConsumable(u16 itemId)
{
    switch (GetItemPocket(itemId))
    {
    case POCKET_POKE_BALLS:
    case POCKET_BERRIES:
        return TRUE;
    default:
        break;
    }
    if (!GetItemConsumability(itemId))
        return FALSE;
    return gItemsInfo[itemId].sortType != ITEM_TYPE_HELD_ITEM;
}

// In:  VAR_ITEM_ID = item chosen in the bag.
// Out: VAR_RESULT = ITEM_REFILL_*, VAR_0x8005 = number of items added.
// Consumables are filled up to 99, everything else gets one more copy.
void ItemRefill_TryRefill(void)
{
    u16 itemId = gSpecialVar_ItemId;
    u16 count, amount;

    gSpecialVar_0x8005 = 0;
    if (!CanRefillItem(itemId))
    {
        gSpecialVar_Result = ITEM_REFILL_NOT_ALLOWED;
        return;
    }

    count = CountTotalItemQuantityInBag(itemId);
    if (count >= REFILL_TARGET)
    {
        gSpecialVar_Result = ITEM_REFILL_FULL;
        return;
    }

    if (IsStackableConsumable(itemId))
        amount = REFILL_TARGET - count;
    else
        amount = 1;

    while (amount > 0 && !CheckBagHasSpace(itemId, amount))
        amount--;

    if (amount == 0 || !AddBagItem(itemId, amount))
    {
        gSpecialVar_Result = ITEM_REFILL_FULL;
        return;
    }

    gSpecialVar_0x8005 = amount;
    gSpecialVar_Result = ITEM_REFILL_DONE;
}
