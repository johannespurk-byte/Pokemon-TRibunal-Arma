#include "global.h"
#include "nuzlocke.h"
#include "battle.h"
#include "battle_setup.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/battle.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/region_map_sections.h"

// Nuzlocke-Modus, im Optionsmenü an- und ausschaltbar (gSaveBlock2Ptr->optionsNuzlocke).
// Solange er an ist:
// - Pro Gebiet (Kartenabschnitt) kann nur die erste wilde Begegnung gefangen werden.
//   Arten, die schon gefangen wurden, zählen nicht (Dupes-Klausel), Shinys sind immer fangbar.
//   Begegnungen zählen von Anfang an, nur Birchs Starter-Kampf und Wallys Fang-Tutorial nicht.
// - Pokémon, die besiegt werden, sind tot: das Pokémon-Center und der PC heilen sie nicht mehr,
//   und Items wirken auf besiegte Pokémon nicht. Ausgeschaltet heilt alles wieder normal.
// - Ausnahme: Der finale Kampf in der Fossilruine 6 (Giovanni, Maxie, Archie) zählt nicht.
//   Dort besiegte Pokémon bleiben am Leben, und im Kampf wirken Items auch auf sie.
// - Zufalls-Eier von Trainern sind unabhängig: Sie verbrauchen keine Begegnung, und das
//   geschlüpfte Pokémon ist ein normales Teammitglied. Nichts hier darf Eier anfassen.

#define ROUTE_104_NORTH_MAX_Y 33 // oberes Stück bis y=30, unteres ab y=38
#define ROUTE_112_NORTH_MAX_Y 17 // oberes Stück bis y=13, unteres ab y=23

STATIC_ASSERT(MAPSEC_COUNT <= NUZLOCKE_AREA_ROUTE_112_NORTH, NuzlockeAreasOverlapMapsecs);
STATIC_ASSERT(NUZLOCKE_AREA_ROUTE_104_NORTH < sizeof(gSaveBlock1Ptr->nuzlockeEncounters) * 8, NuzlockeEncountersTooSmall);

// Ob in diesem Kampf ein Ball geworfen werden darf, gesetzt bei Kampfbeginn
static EWRAM_DATA bool8 sCatchAllowed = FALSE;

bool32 Nuzlocke_IsActive(void)
{
    return gSaveBlock2Ptr->optionsNuzlocke;
}

// Für Scripts: VAR_RESULT = 1, wenn der Nuzlocke-Modus an ist
bool8 Nuzlocke_ScriptIsActive(void)
{
    return Nuzlocke_IsActive();
}

// Der finale Kampf in der Fossilruine 6 wird nicht gewertet
static bool32 IsExemptBattle(void)
{
    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        return FALSE;
    switch (TRAINER_BATTLE_PARAM.opponentA)
    {
    case TRAINER_GIOVANNI_FOSSIL_RUINS_6:
    case TRAINER_MAXIE_FOSSIL_RUINS_6:
    case TRAINER_ARCHIE_FOSSIL_RUINS_6:
        return TRUE;
    }
    return FALSE;
}

u32 Nuzlocke_GetEncounterArea(void)
{
    s16 x, y;

    PlayerGetDestCoords(&x, &y);
    y -= MAP_OFFSET;
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_ROUTE104)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_ROUTE104)
     && y <= ROUTE_104_NORTH_MAX_Y)
        return NUZLOCKE_AREA_ROUTE_104_NORTH;
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_ROUTE112)
     && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_ROUTE112)
     && y <= ROUTE_112_NORTH_MAX_Y)
        return NUZLOCKE_AREA_ROUTE_112_NORTH;
    return gMapHeader.regionMapSectionId;
}

bool32 Nuzlocke_IsAreaUsed(u32 area)
{
    return (gSaveBlock1Ptr->nuzlockeEncounters[area / 8] >> (area % 8)) & 1;
}

static void SetEncounterUsed(u32 mapsec)
{
    gSaveBlock1Ptr->nuzlockeEncounters[mapsec / 8] |= 1 << (mapsec % 8);
}

void Nuzlocke_OnBattleStart(void)
{
    struct Pokemon *wildMon = &gParties[B_TRAINER_OPPONENT_A][0];
    u32 mapsec = gMapHeader.regionMapSectionId;
    u32 area;
    bool32 isDupe;

    sCatchAllowed = TRUE;
    if (!Nuzlocke_IsActive()
     || gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_CATCH_TUTORIAL)
     || mapsec >= MAPSEC_COUNT)
        return;

    isDupe = GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetMonData(wildMon, MON_DATA_SPECIES)), FLAG_GET_CAUGHT);
    area = Nuzlocke_GetEncounterArea();
    if (!Nuzlocke_IsAreaUsed(area) && !isDupe)
        SetEncounterUsed(area);
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

    if (IsExemptBattle())
        return;
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
    if (gMain.inBattle && IsExemptBattle())
        return FALSE;
    return Nuzlocke_IsActive() && GetMonData(mon, MON_DATA_HP) == 0;
}
