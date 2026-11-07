#include "global.h"
#include "nuzlocke.h"
#include "battle.h"
#include "event_data.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "constants/battle.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"

// Nuzlocke-Modus, im Optionsmenü an- und ausschaltbar (gSaveBlock2Ptr->optionsNuzlocke).
// Solange er an ist:
// - Pro Gebiet (Kartenabschnitt) kann nur die erste wilde Begegnung gefangen werden.
//   Arten, die schon gefangen wurden, zählen nicht (Dupes-Klausel), Shinys sind immer fangbar.
//   Begegnungen zählen erst, wenn der Spieler den Pokédex hat.
// - Pokémon, die besiegt werden, sind tot: das Pokémon-Center und der PC heilen sie nicht mehr,
//   und Items wirken auf besiegte Pokémon nicht. Ausgeschaltet heilt alles wieder normal.

// Route 104 und 112 sind je eine Karte, aber zwei getrennte Stücke (durch den Petalburg-Wald bzw.
// den Schlotberg). Das obere Stück hat ein eigenes Bit, ganz am Ende, damit neue MAPSECs es nicht verschieben.
#define NUZLOCKE_AREA_ROUTE_104_NORTH 255
#define NUZLOCKE_AREA_ROUTE_112_NORTH 254
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
    u32 area;
    bool32 isDupe;

    sCatchAllowed = TRUE;
    if (!Nuzlocke_IsActive()
     || gBattleTypeFlags & (BATTLE_TYPE_TRAINER | BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED | BATTLE_TYPE_FIRST_BATTLE | BATTLE_TYPE_CATCH_TUTORIAL)
     || !FlagGet(FLAG_SYS_POKEDEX_GET)
     || mapsec >= MAPSEC_COUNT)
        return;

    isDupe = GetSetPokedexFlag(SpeciesToNationalPokedexNum(GetMonData(wildMon, MON_DATA_SPECIES)), FLAG_GET_CAUGHT);
    area = Nuzlocke_GetEncounterArea();
    if (!IsEncounterUsed(area) && !isDupe)
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
