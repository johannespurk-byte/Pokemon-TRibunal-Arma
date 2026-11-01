#include "global.h"
#include "nuzlocke.h"
#include "battle.h"
#include "event_data.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/battle.h"
#include "constants/region_map_sections.h"

// Nuzlocke-Modus, im Optionsmenü an- und ausschaltbar (gSaveBlock2Ptr->optionsNuzlocke).
// Solange er an ist:
// - Pro Gebiet (Kartenabschnitt) kann nur die erste wilde Begegnung gefangen werden.
//   Arten, die schon gefangen wurden, zählen nicht (Dupes-Klausel), Shinys sind immer fangbar.
//   Begegnungen zählen erst, wenn der Spieler den Pokédex hat.
// - Pokémon, die besiegt werden, sind tot: das Pokémon-Center und der PC heilen sie nicht mehr,
//   und Items wirken auf besiegte Pokémon nicht. Ausgeschaltet heilt alles wieder normal.

STATIC_ASSERT(MAPSEC_COUNT <= sizeof(gSaveBlock1Ptr->nuzlockeEncounters) * 8, NuzlockeEncountersTooSmall);

// Ob in diesem Kampf ein Ball geworfen werden darf, gesetzt bei Kampfbeginn
static EWRAM_DATA bool8 sCatchAllowed = FALSE;

bool32 Nuzlocke_IsActive(void)
{
    return gSaveBlock2Ptr->optionsNuzlocke;
}

static bool32 IsEncounterUsed(u32 mapsec)
{
    return (gSaveBlock1Ptr->nuzlockeEncounters[mapsec / 8] >> (mapsec % 8)) & 1;
}

static void SetEncounterUsed(u32 mapsec)
{
    gSaveBlock1Ptr->nuzlockeEncounters[mapsec / 8] |= 1 << (mapsec % 8);
}

void Nuzlocke_OnBattleStart(void)
{
    struct Pokemon *wildMon = &gParties[B_TRAINER_OPPONENT_A][0];
    u32 mapsec = gMapHeader.regionMapSectionId;
    bool32 isDupe;

    sCatchAllowed = TRUE;
    if (!Nuzlocke_IsActive()
     || gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_CATCH_TUTORIAL)
     || !FlagGet(FLAG_SYS_POKEDEX_GET)
     || mapsec >= MAPSEC_COUNT)
        return;

    isDupe = GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetMonData(wildMon, MON_DATA_SPECIES)), FLAG_GET_CAUGHT);
    if (!IsEncounterUsed(mapsec) && !isDupe)
        SetEncounterUsed(mapsec);
    else
        sCatchAllowed = IsMonShiny(wildMon);
}

bool32 Nuzlocke_IsCatchBlocked(void)
{
    return Nuzlocke_IsActive() && !sCatchAllowed;
}

void Nuzlocke_MarkMonDead(struct Pokemon *mon)
{
    if (Nuzlocke_IsActive())
        mon->box.isNuzlockeDead = TRUE;
}

void Nuzlocke_MarkFaintedPartyMonsDead(void)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_SPECIES) != SPECIES_NONE
         && !GetMonData(mon, MON_DATA_IS_EGG)
         && GetMonData(mon, MON_DATA_HP) == 0)
            Nuzlocke_MarkMonDead(mon);
    }
}

// Tote Pokémon bleiben bei 0 KP. Ist der Modus aus, werden sie geheilt und sind wieder normal.
bool32 Nuzlocke_ShouldSkipHeal(struct BoxPokemon *boxMon)
{
    if (!boxMon->isNuzlockeDead)
        return FALSE;
    if (Nuzlocke_IsActive())
        return TRUE;
    boxMon->isNuzlockeDead = FALSE;
    return FALSE;
}

// Keine Items auf besiegte Pokémon (Beleber, Heilung, Sonderbonbon ...)
bool32 Nuzlocke_IsItemBlocked(struct Pokemon *mon)
{
    return Nuzlocke_IsActive() && GetMonData(mon, MON_DATA_HP) == 0;
}
