// The Champion of the Pokemon League is a shadow copy of the player:
// it looks like the character the player chose, carries the player's name,
// and its team is drawn at random from the Pokemon in the player's party and PC boxes.
#include "global.h"
#include "caps.h"
#include "event_data.h"
#include "field_player_avatar.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "constants/vars.h"

#define SHADOW_SOURCE_PARTY 0x8000
#define SHADOW_SOURCE_MAX   (PARTY_SIZE + TOTAL_BOXES_COUNT * IN_BOX_COUNT)

static EWRAM_DATA u16 sShadowSources[SHADOW_SOURCE_MAX] = {0};

static bool32 GetShadowSourceMon(u16 source, struct Pokemon *dest)
{
    u32 species;

    if (source & SHADOW_SOURCE_PARTY)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][source & ~SHADOW_SOURCE_PARTY];
        species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);
        if (species == SPECIES_NONE || species == SPECIES_EGG)
            return FALSE;
        *dest = *mon;
    }
    else
    {
        struct BoxPokemon *boxMon = GetBoxedMonPtr(source / IN_BOX_COUNT, source % IN_BOX_COUNT);
        species = GetBoxMonData(boxMon, MON_DATA_SPECIES_OR_EGG);
        if (species == SPECIES_NONE || species == SPECIES_EGG)
            return FALSE;
        BoxMonToMon(boxMon, dest);
    }
    return TRUE;
}

// Brings a copied Pokemon to the current level cap with perfect IVs, full HP and no status.
static void PowerUpShadowMon(struct Pokemon *mon)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 level = GetCurrentLevelCap();
    u32 iv = MAX_PER_STAT_IVS;
    u32 status = 0;
    u32 exp;

    if (level > MAX_LEVEL)
        level = MAX_LEVEL;
    if (GetMonData(mon, MON_DATA_LEVEL) < level)
    {
        exp = gExperienceTables[gSpeciesInfo[species].growthRate][level];
        SetMonData(mon, MON_DATA_EXP, &exp);
    }
    SetMonData(mon, MON_DATA_HP_IV, &iv);
    SetMonData(mon, MON_DATA_ATK_IV, &iv);
    SetMonData(mon, MON_DATA_DEF_IV, &iv);
    SetMonData(mon, MON_DATA_SPEED_IV, &iv);
    SetMonData(mon, MON_DATA_SPATK_IV, &iv);
    SetMonData(mon, MON_DATA_SPDEF_IV, &iv);
    SetMonData(mon, MON_DATA_STATUS, &status);
    CalculateMonStats(mon);
    {
        u32 hp = GetMonData(mon, MON_DATA_MAX_HP);
        SetMonData(mon, MON_DATA_HP, &hp);
    }
}

// Fills the opponent's party with up to six of the player's own Pokemon (different species, random pick).
u8 CreateShadowChampionParty(struct Pokemon *party)
{
    u32 count = 0, picked = 0, i, j;
    u16 species[PARTY_SIZE];

    for (i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&party[i]);

    for (i = 0; i < PARTY_SIZE; i++)
        sShadowSources[count++] = SHADOW_SOURCE_PARTY | i;
    for (i = 0; i < TOTAL_BOXES_COUNT * IN_BOX_COUNT; i++)
        sShadowSources[count++] = i;

    // shuffle all sources
    for (i = count - 1; i > 0; i--)
    {
        u16 tmp;
        j = Random() % (i + 1);
        tmp = sShadowSources[i];
        sShadowSources[i] = sShadowSources[j];
        sShadowSources[j] = tmp;
    }

    for (i = 0; i < count && picked < PARTY_SIZE; i++)
    {
        bool32 duplicate = FALSE;
        u32 sp;

        if (!GetShadowSourceMon(sShadowSources[i], &party[picked]))
            continue;
        sp = GetMonData(&party[picked], MON_DATA_SPECIES);
        for (j = 0; j < picked; j++)
        {
            if (species[j] == sp)
                duplicate = TRUE;
        }
        if (duplicate)
        {
            ZeroMonData(&party[picked]);
            continue;
        }
        species[picked] = sp;
        PowerUpShadowMon(&party[picked]);
        picked++;
    }
    return picked;
}

// Champion room: the shadow uses the player's own overworld sprite (VAR_OBJ_GFX_ID_1).
void SetShadowChampionGfx(void)
{
    VarSet(VAR_OBJ_GFX_ID_1, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_NORMAL));
}
