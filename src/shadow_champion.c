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
#include "string_util.h"
#include "constants/abilities.h"
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

// The last fight of the game should not face a Pancham at level 74: every pick becomes its final evolution
// (any method, a random branch where there are several). An unchanged default name follows the new species.
static bool32 EvolveShadowMon(struct Pokemon *mon)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 step, i;
    u8 nick[POKEMON_NAME_BUFFER_SIZE];
    bool32 defaultName;

    GetMonData(mon, MON_DATA_NICKNAME, nick);
    defaultName = (StringCompare(nick, GetSpeciesName(species)) == 0);
    for (step = 0; step < 3; step++)
    {
        const struct Evolution *evos = GetSpeciesEvolutions(species);
        u16 targets[8];
        u32 count = 0;

        // species without evolutions have no table at all (NULL), like GetEvolutionTargetSpecies checks
        for (i = 0; evos != NULL && evos[i].method != EVOLUTIONS_END && count < ARRAY_COUNT(targets); i++)
        {
            u32 target = SanitizeSpeciesId(evos[i].targetSpecies);
            // EVO_NONE marks forms that never evolve in-game (Totem forms, Bloodmoon Ursaluna); Shedinja is a side split
            if (evos[i].method == EVO_NONE || evos[i].method == EVO_SPLIT_FROM_EVO)
                continue;
            if (target != species && target != SPECIES_NONE && IsSpeciesEnabled(target))
                targets[count++] = target;
        }
        if (count == 0)
            break;
        species = targets[Random() % count];
    }
    if (species == GetMonData(mon, MON_DATA_SPECIES))
        return FALSE;
    SetMonData(mon, MON_DATA_SPECIES, &species);
    if (defaultName)
    {
        StringCopy(nick, GetSpeciesName(species));
        SetMonData(mon, MON_DATA_NICKNAME, nick);
    }
    return TRUE;
}

// Abilities that are clearly the best pick where a species has them in one of its slots
static const u16 sStrongAbilities[] =
{
    ABILITY_HUGE_POWER, ABILITY_PURE_POWER, ABILITY_SPEED_BOOST, ABILITY_PROTEAN, ABILITY_LIBERO, ABILITY_ADAPTABILITY,
    ABILITY_TOUGH_CLAWS, ABILITY_SHEER_FORCE, ABILITY_TECHNICIAN, ABILITY_MOXIE, ABILITY_INTIMIDATE, ABILITY_MAGIC_GUARD,
    ABILITY_MULTISCALE, ABILITY_REGENERATOR, ABILITY_DROUGHT, ABILITY_DRIZZLE, ABILITY_SAND_STREAM, ABILITY_SNOW_WARNING,
    ABILITY_MAGIC_BOUNCE, ABILITY_GUTS, ABILITY_UNBURDEN, ABILITY_SERENE_GRACE, ABILITY_LEVITATE,
};

// EVs, nature and ability that fit the species' base stats: the better attacking stat gets 252 EVs and the boosting
// nature; fast species (base Speed 80+) also max Speed (Jolly/Timid), slower ones max HP (Adamant/Modest).
static void SetShadowMonSpread(struct Pokemon *mon)
{
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    const struct SpeciesInfo *info = &gSpeciesInfo[species];
    bool32 physical = info->baseAttack >= info->baseSpAttack;
    bool32 fast = info->baseSpeed >= 80;
    u8 evs[NUM_STATS] = {0};
    u32 nature = fast ? (physical ? NATURE_JOLLY : NATURE_TIMID) : (physical ? NATURE_ADAMANT : NATURE_MODEST);
    u32 i, j, abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM);

    evs[physical ? STAT_ATK : STAT_SPATK] = 252;
    if (fast)
    {
        evs[STAT_SPEED] = 252;
        evs[STAT_HP] = 4;
    }
    else
    {
        evs[STAT_HP] = 252;
        evs[STAT_SPDEF] = 4;
    }
    for (i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_EV + i, &evs[i]);
    SetMonData(mon, MON_DATA_HIDDEN_NATURE, &nature);

    // keep the player's ability slot unless it is empty for this species or another slot holds a clearly strong ability
    if (GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE)
        abilityNum = 0;
    for (i = 0; i < NUM_ABILITY_SLOTS; i++)
    {
        for (j = 0; j < ARRAY_COUNT(sStrongAbilities); j++)
        {
            if (info->abilities[i] == sStrongAbilities[j])
            {
                abilityNum = i;
                i = NUM_ABILITY_SLOTS;
                break;
            }
        }
    }
    SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
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

// Fills the opponent's party with up to six of the player's own Pokemon (different species after evolving, random pick).
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
        bool32 duplicate = FALSE, evolved;
        u32 sp;

        if (!GetShadowSourceMon(sShadowSources[i], &party[picked]))
            continue;
        evolved = EvolveShadowMon(&party[picked]);
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
        SetShadowMonSpread(&party[picked]);
        PowerUpShadowMon(&party[picked]);
        if (evolved)
            GiveMonInitialMoveset(&party[picked]);
        picked++;
    }
    return picked;
}

// Champion room: the shadow uses the player's own overworld sprite (VAR_OBJ_GFX_ID_1).
void SetShadowChampionGfx(void)
{
    VarSet(VAR_OBJ_GFX_ID_1, GetPlayerAvatarGraphicsIdByStateId(PLAYER_AVATAR_STATE_NORMAL));
}
