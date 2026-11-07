#include "global.h"
#include "battle_music.h"
#include "event_data.h"
#include "constants/songs.h"
#include "constants/vars.h"

// Battle music remixer, set up in the Pokétch. A new track only needs one more line in sTracks,
// for example once tracks from Gen 6 to 9 exist in the project. Choices are stored in saved
// variables, two per variable: changing the size of the save blocks would invalidate saves.

struct BattleMusicTrack
{
    u16 song;
    const u8 *name;
};

static const struct BattleMusicTrack sTracks[] =
{
    // Gen 1 (FireRed/LeafGreen versions)
    {MUS_RG_VS_WILD,               COMPOUND_STRING("G1 Wild")},
    {MUS_RG_VS_TRAINER,            COMPOUND_STRING("G1 Trainer")},
    {MUS_RG_VS_GYM_LEADER,         COMPOUND_STRING("G1 Gym Leader")},
    {MUS_RG_VS_CHAMPION,           COMPOUND_STRING("G1 Champion")},
    {MUS_RG_VS_LEGEND,             COMPOUND_STRING("G1 Legendary")},
    {MUS_RG_VS_MEWTWO,             COMPOUND_STRING("G1 Mewtwo")},
    {MUS_RG_VS_DEOXYS,             COMPOUND_STRING("G1 Deoxys")},
    // Gen 2 (HeartGold/SoulSilver versions)
    {MUS_HG_VS_WILD,               COMPOUND_STRING("G2 Wild")},
    {MUS_HG_VS_WILD_KANTO,         COMPOUND_STRING("G2 Wild Kanto")},
    {MUS_HG_VS_TRAINER,            COMPOUND_STRING("G2 Trainer")},
    {MUS_HG_VS_TRAINER_KANTO,      COMPOUND_STRING("G2 Trainer Kanto")},
    {MUS_HG_VS_GYM_LEADER,         COMPOUND_STRING("G2 Gym Leader")},
    {MUS_HG_VS_GYM_LEADER_KANTO,   COMPOUND_STRING("G2 Leader Kanto")},
    {MUS_HG_VS_RIVAL,              COMPOUND_STRING("G2 Rival")},
    {MUS_HG_VS_ROCKET,             COMPOUND_STRING("G2 Team Rocket")},
    {MUS_HG_VS_CHAMPION,           COMPOUND_STRING("G2 Champion")},
    {MUS_HG_VS_FRONTIER_BRAIN,     COMPOUND_STRING("G2 Frontier Brain")},
    {MUS_C_VS_LEGEND_BEAST,        COMPOUND_STRING("G2 Beasts (GBC)")},
    {MUS_HG_VS_SUICUNE,            COMPOUND_STRING("G2 Suicune")},
    {MUS_HG_VS_ENTEI,              COMPOUND_STRING("G2 Entei")},
    {MUS_HG_VS_RAIKOU,             COMPOUND_STRING("G2 Raikou")},
    {MUS_HG_VS_HO_OH,              COMPOUND_STRING("G2 Ho-Oh")},
    {MUS_HG_VS_LUGIA,              COMPOUND_STRING("G2 Lugia")},
    {MUS_HG_VS_KYOGRE_GROUDON,     COMPOUND_STRING("G2 Kyogre/Groudon")},
    {MUS_HG_VS_ARCEUS,             COMPOUND_STRING("G2 Arceus")},
    // Gen 3
    {MUS_VS_WILD,                  COMPOUND_STRING("G3 Wild")},
    {MUS_VS_TRAINER,               COMPOUND_STRING("G3 Trainer")},
    {MUS_VS_GYM_LEADER,            COMPOUND_STRING("G3 Gym Leader")},
    {MUS_VS_RIVAL,                 COMPOUND_STRING("G3 Rival")},
    {MUS_VS_AQUA_MAGMA,            COMPOUND_STRING("G3 Aqua/Magma")},
    {MUS_VS_AQUA_MAGMA_LEADER,     COMPOUND_STRING("G3 Team Leader")},
    {MUS_VS_ELITE_FOUR,            COMPOUND_STRING("G3 Elite Four")},
    {MUS_VS_CHAMPION,              COMPOUND_STRING("G3 Champion")},
    {MUS_VS_FRONTIER_BRAIN,        COMPOUND_STRING("G3 Frontier Brain")},
    {MUS_VS_MEW,                   COMPOUND_STRING("G3 Mew")},
    {MUS_VS_REGI,                  COMPOUND_STRING("G3 Regi")},
    {MUS_VS_KYOGRE_GROUDON,        COMPOUND_STRING("G3 Kyogre/Groudon")},
    {MUS_VS_RAYQUAZA,              COMPOUND_STRING("G3 Rayquaza")},
    // Gen 4
    {MUS_DP_VS_WILD,               COMPOUND_STRING("G4 Wild")},
    {MUS_DP_VS_TRAINER,            COMPOUND_STRING("G4 Trainer")},
    {MUS_DP_VS_GYM_LEADER,         COMPOUND_STRING("G4 Gym Leader")},
    {MUS_DP_VS_RIVAL,              COMPOUND_STRING("G4 Rival")},
    {MUS_DP_VS_GALACTIC,           COMPOUND_STRING("G4 Galactic")},
    {MUS_DP_VS_GALACTIC_COMMANDER, COMPOUND_STRING("G4 Commander")},
    {MUS_DP_VS_GALACTIC_BOSS,      COMPOUND_STRING("G4 Galactic Boss")},
    {MUS_DP_VS_ELITE_FOUR,         COMPOUND_STRING("G4 Elite Four")},
    {MUS_DP_VS_CHAMPION,           COMPOUND_STRING("G4 Champion")},
    {MUS_PL_VS_FRONTIER_BRAIN,     COMPOUND_STRING("G4 Frontier Brain")},
    {MUS_DP_VS_LEGEND,             COMPOUND_STRING("G4 Legendary")},
    {MUS_DP_VS_UXIE_MESPRIT_AZELF, COMPOUND_STRING("G4 Lake Guardians")},
    {MUS_DP_VS_DIALGA_PALKIA,      COMPOUND_STRING("G4 Dialga/Palkia")},
    {MUS_DP_VS_ARCEUS,             COMPOUND_STRING("G4 Arceus")},
    {MUS_PL_VS_GIRATINA,           COMPOUND_STRING("G4 Giratina")},
    {MUS_PL_VS_REGI,               COMPOUND_STRING("G4 Regi")},
    // Gen 5
    {MUS_BW_VS_WILD,               COMPOUND_STRING("G5 Wild")},
    {MUS_BW_VS_WILD_STRONG,        COMPOUND_STRING("G5 Strong Wild")},
    {MUS_BW_VS_TRAINER,            COMPOUND_STRING("G5 Trainer")},
    {MUS_BW_VS_SUBWAY_TRAINER,     COMPOUND_STRING("G5 Subway Trainer")},
    {MUS_BW_BATTLE_SUBWAY,         COMPOUND_STRING("G5 Battle Subway")},
    {MUS_BW_BATTLE_COMPETITION,    COMPOUND_STRING("G5 Competition")},
    {MUS_BW_VS_GYM_LEADER,         COMPOUND_STRING("G5 Gym Leader")},
    {MUS_BW_VS_WINNING,            COMPOUND_STRING("G5 Gym, Winning")},
    {MUS_BW_VS_IN_PINCH,           COMPOUND_STRING("G5 Gym, In Pinch")},
    {MUS_BW_VS_RIVAL,              COMPOUND_STRING("G5 Rival")},
    {MUS_BW_VS_PLASMA,             COMPOUND_STRING("G5 Team Plasma")},
    {MUS_BW_VS_GHETSIS,            COMPOUND_STRING("G5 Ghetsis")},
    {MUS_BW_VS_N_1,                COMPOUND_STRING("G5 N")},
    {MUS_BW_VS_N_2,                COMPOUND_STRING("G5 N, Finale")},
    {MUS_BW_VS_ELITE_FOUR,         COMPOUND_STRING("G5 Elite Four")},
    {MUS_BW_VS_CHAMPION,           COMPOUND_STRING("G5 Champion")},
    {MUS_BW_VS_WCS_CHAMPION,       COMPOUND_STRING("G5 WCS Champion")},
    {MUS_BW_VS_CYNTHIA,            COMPOUND_STRING("G5 Cynthia")},
    {MUS_BW_VS_LEGEND,             COMPOUND_STRING("G5 Legendary")},
    {MUS_BW_VS_RESHIRAM_ZEKROM,    COMPOUND_STRING("G5 Reshiram/Zekrom")},
    {MUS_BW_VS_KYUREM,             COMPOUND_STRING("G5 Kyurem")},
};

STATIC_ASSERT(ARRAY_COUNT(sTracks) + BATTLE_MUSIC_CHOICE_TRACKS <= 256, BattleMusicChoicesFitInOneByte);

static const u8 *const sCategoryNames[BATTLE_MUSIC_CATEGORY_COUNT] =
{
    [BATTLE_MUSIC_WILD]      = COMPOUND_STRING("WILD"),
    [BATTLE_MUSIC_LEGENDARY] = COMPOUND_STRING("LEGENDARY"),
    [BATTLE_MUSIC_TRAINER]   = COMPOUND_STRING("TRAINER"),
    [BATTLE_MUSIC_RIVAL]     = COMPOUND_STRING("RIVAL"),
    [BATTLE_MUSIC_TEAM]      = COMPOUND_STRING("EVIL TEAM"),
    [BATTLE_MUSIC_LEADER]    = COMPOUND_STRING("LEADER"),
    [BATTLE_MUSIC_LEAGUE]    = COMPOUND_STRING("LEAGUE"),
};

static const u16 sChoiceVars[(BATTLE_MUSIC_CATEGORY_COUNT + 1) / 2] =
{
    VAR_BATTLE_MUSIC_1,
    VAR_BATTLE_MUSIC_2,
    VAR_BATTLE_MUSIC_3,
    VAR_BATTLE_MUSIC_4,
};

const u8 *BattleMusic_GetCategoryName(u32 category)
{
    return sCategoryNames[category];
}

u32 BattleMusic_GetChoice(u32 category)
{
    u32 value = VarGet(sChoiceVars[category / 2]);
    u32 choice = (category % 2) ? (value >> 8) : (value & 0xFF);

    // Tracks may be removed from the list later
    return choice < BattleMusic_GetChoiceCount() ? choice : BATTLE_MUSIC_CHOICE_ORIGINAL;
}

void BattleMusic_SetChoice(u32 category, u32 choice)
{
    u32 value = VarGet(sChoiceVars[category / 2]);

    if (category % 2)
        value = (value & 0x00FF) | (choice << 8);
    else
        value = (value & 0xFF00) | choice;
    VarSet(sChoiceVars[category / 2], value);
}

u32 BattleMusic_GetChoiceCount(void)
{
    return ARRAY_COUNT(sTracks) + BATTLE_MUSIC_CHOICE_TRACKS;
}

const u8 *BattleMusic_GetChoiceName(u32 choice)
{
    if (choice == BATTLE_MUSIC_CHOICE_ORIGINAL)
        return COMPOUND_STRING("Original");
    if (choice == BATTLE_MUSIC_CHOICE_RANDOM)
        return COMPOUND_STRING("Random");
    return sTracks[choice - BATTLE_MUSIC_CHOICE_TRACKS].name;
}

u16 BattleMusic_GetChoiceSong(u32 choice)
{
    if (choice < BATTLE_MUSIC_CHOICE_TRACKS)
        return 0;
    return sTracks[choice - BATTLE_MUSIC_CHOICE_TRACKS].song;
}

// The seed comes from the battle, so that every call during one battle gives the same track
u16 BattleMusic_GetSongForBattle(u32 category, u32 seed)
{
    u32 choice = BattleMusic_GetChoice(category);

    if (choice == BATTLE_MUSIC_CHOICE_RANDOM)
        return sTracks[seed % ARRAY_COUNT(sTracks)].song;
    return BattleMusic_GetChoiceSong(choice);
}
