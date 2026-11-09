// ============================================================================
// PER-TRAINER LEVEL SCALING CONFIGURATION
// ============================================================================
//
// This file allows you to override the default scaling behavior for specific trainers.
//
// HOW IT WORKS:
// - Default behavior is defined in include/config/level_scaling.h
// - If B_TRAINER_SCALING_DEFAULT_MODE is set to anything other than LEVEL_SCALING_NONE,
//   ALL trainers will use that default configuration
// - Trainers listed here can override the default with custom rules
// - Use LEVEL_SCALING_CONFIG_NONE to explicitly disable scaling for a specific trainer
//
// EXAMPLES:
//
// 1. Override with custom config:
//    [TRAINER_ROXANNE_1] = {
//        .mode = LEVEL_SCALING_TO_LEVEL_CAP,
//        .levelAugmentAdd = 2,         // +2 levels above cap
//        .levelVariationPct = 10,         // Up to 10% level reduction
//        .minLevel = 10,
//        .maxLevel = 50,
//        .manageEvolutions = TRUE,
//        .excludeFainted = FALSE,
//    },
//
// 2. Use a preset macro:
//    [TRAINER_BRAWLY_1] = LEVEL_SCALING_CONFIG_PARTY_AVG,
//
// 3. Explicitly disable scaling (opt-out):
//    [TRAINER_WALLY_VR_1] = LEVEL_SCALING_CONFIG_NONE,
//
// 4. Opt-in to EV scaling and/or moveset filtering for a specific trainer:
//    [TRAINER_STEVEN] = {
//        .mode = LEVEL_SCALING_PARTY_AVG,
//        .scaleEVs = TRUE,        // Scale defined EVs proportionally to scaled level
//        .scaleMoves = TRUE,      // Drop trainer-defined moves illegal for the scaled species/level
//                                 // (filled from the scaled species' level-up learnset)
//        .manageEvolutions = TRUE,
//    },
//
// Available macros: LEVEL_SCALING_CONFIG_NONE, LEVEL_SCALING_CONFIG_LEVEL_CAP,
//                   LEVEL_SCALING_CONFIG_PARTY_AVG, LEVEL_SCALING_CONFIG_PARTY_HIGHEST

#include "constants/opponents.h"

// Rocket Hideout grunts and Giovanni always fight at the current level cap (caps.c)
#define ROCKET_HIDEOUT_SCALING { .mode = LEVEL_SCALING_TO_LEVEL_CAP }

// Gym leaders and their gym partners fight at the level cap that applies while
// their badge is still missing (caps.c), not at the player's highest level
#define GYM_LEADER_SCALING { .mode = LEVEL_SCALING_TO_LEVEL_CAP }

// Route 112 trainers fight just below the level cap
#define ROUTE_112_SCALING { .mode = LEVEL_SCALING_TO_LEVEL_CAP, .levelAugmentAdd = -2 }

// Route 113 trainers fight at the level cap
#define ROUTE_113_SCALING { .mode = LEVEL_SCALING_TO_LEVEL_CAP }
// Route 114 and Meteor Falls: strong teams of six, scaled to the level cap
#define ROUTE_114_SCALING { .mode = LEVEL_SCALING_TO_LEVEL_CAP }

const struct LevelScalingConfig gTrainerLevelScalingRules[TRAINERS_COUNT] =
{
    [TRAINER_ROXANNE_1]        = GYM_LEADER_SCALING, // Cap 18
    [TRAINER_BLAINE]           = GYM_LEADER_SCALING,
    [TRAINER_BRAWLY_1]         = GYM_LEADER_SCALING, // Cap 36
    [TRAINER_BRANDON_DEWFORD]  = GYM_LEADER_SCALING,
    [TRAINER_WATTSON_1]        = GYM_LEADER_SCALING, // Cap 50
    [TRAINER_LORELEI_MAUVILLE] = GYM_LEADER_SCALING,
    [TRAINER_MAXIE_FOSSIL_RUINS]    = GYM_LEADER_SCALING,
    [TRAINER_GIOVANNI_FOSSIL_RUINS] = GYM_LEADER_SCALING,
    [TRAINER_STEVE_1] = ROUTE_114_SCALING,
    [TRAINER_STEVE_2] = ROUTE_114_SCALING,
    [TRAINER_STEVE_3] = ROUTE_114_SCALING,
    [TRAINER_STEVE_4] = ROUTE_114_SCALING,
    [TRAINER_STEVE_5] = ROUTE_114_SCALING,
    [TRAINER_BERNIE_1] = ROUTE_114_SCALING,
    [TRAINER_BERNIE_2] = ROUTE_114_SCALING,
    [TRAINER_BERNIE_3] = ROUTE_114_SCALING,
    [TRAINER_BERNIE_4] = ROUTE_114_SCALING,
    [TRAINER_BERNIE_5] = ROUTE_114_SCALING,
    [TRAINER_NICOLAS_1] = ROUTE_114_SCALING,
    [TRAINER_NICOLAS_2] = ROUTE_114_SCALING,
    [TRAINER_NICOLAS_3] = ROUTE_114_SCALING,
    [TRAINER_NICOLAS_4] = ROUTE_114_SCALING,
    [TRAINER_NICOLAS_5] = ROUTE_114_SCALING,
    [TRAINER_JOHN_AND_JAY_1] = ROUTE_114_SCALING,
    [TRAINER_JOHN_AND_JAY_2] = ROUTE_114_SCALING,
    [TRAINER_JOHN_AND_JAY_3] = ROUTE_114_SCALING,
    [TRAINER_JOHN_AND_JAY_4] = ROUTE_114_SCALING,
    [TRAINER_JOHN_AND_JAY_5] = ROUTE_114_SCALING,
    [TRAINER_SHANE] = ROUTE_114_SCALING,
    [TRAINER_CLAUDE] = ROUTE_114_SCALING,
    [TRAINER_NOLAN] = ROUTE_114_SCALING,
    [TRAINER_KAI] = ROUTE_114_SCALING,
    [TRAINER_NANCY] = ROUTE_114_SCALING,
    [TRAINER_ANGELINA] = ROUTE_114_SCALING,
    [TRAINER_CHARLOTTE] = ROUTE_114_SCALING,
    [TRAINER_LENNY] = ROUTE_114_SCALING,
    [TRAINER_LUCAS_1] = ROUTE_114_SCALING,
    [TRAINER_TYRA_AND_IVY] = ROUTE_114_SCALING,
    [TRAINER_ARCHIE_FOSSIL_RUINS]   = GYM_LEADER_SCALING,
    [TRAINER_GIOVANNI_FOSSIL_RUINS_5] = GYM_LEADER_SCALING,
    [TRAINER_AQUA_GRUNT_FOSSIL_RUINS_5_A] = ROUTE_112_SCALING,
    [TRAINER_AQUA_GRUNT_FOSSIL_RUINS_5_B] = ROUTE_112_SCALING,
    [TRAINER_VICTOR]           = GYM_LEADER_SCALING, // the Winstrate family
    [TRAINER_VICTORIA]         = GYM_LEADER_SCALING,
    [TRAINER_VIVI]             = GYM_LEADER_SCALING,
    [TRAINER_VICKY]            = GYM_LEADER_SCALING,
    [TRAINER_BRICE] = ROUTE_112_SCALING,
    [TRAINER_LARRY] = ROUTE_112_SCALING,
    [TRAINER_CAROL] = ROUTE_112_SCALING,
    [TRAINER_TRENT_1] = ROUTE_112_SCALING,
    [TRAINER_BRYANT] = ROUTE_112_SCALING,
    [TRAINER_SHAYLA] = ROUTE_112_SCALING,
    [TRAINER_JAYLEN] = ROUTE_113_SCALING,
    [TRAINER_DILLON] = ROUTE_113_SCALING,
    [TRAINER_MADELINE_1] = ROUTE_113_SCALING,
    [TRAINER_LAO_1] = ROUTE_113_SCALING,
    [TRAINER_LUNG] = ROUTE_113_SCALING,
    [TRAINER_TORI_AND_TIA] = ROUTE_113_SCALING,
    [TRAINER_SOPHIE] = ROUTE_113_SCALING,
    [TRAINER_COBY] = ROUTE_113_SCALING,
    [TRAINER_LAWRENCE] = ROUTE_113_SCALING,
    [TRAINER_WYATT] = ROUTE_113_SCALING,
    [TRAINER_MADELINE_2] = ROUTE_113_SCALING,
    [TRAINER_MADELINE_3] = ROUTE_113_SCALING,
    [TRAINER_MADELINE_4] = ROUTE_113_SCALING,
    [TRAINER_MADELINE_5] = ROUTE_113_SCALING,
    [TRAINER_LAO_2] = ROUTE_113_SCALING,
    [TRAINER_LAO_3] = ROUTE_113_SCALING,
    [TRAINER_LAO_4] = ROUTE_113_SCALING,
    [TRAINER_LAO_5] = ROUTE_113_SCALING,
    [TRAINER_FLANNERY_1]       = GYM_LEADER_SCALING, // Cap 60
    [TRAINER_NORMAN_1]         = GYM_LEADER_SCALING, // Cap 68
    [TRAINER_MISTY]            = GYM_LEADER_SCALING,
    [TRAINER_WINONA_1]         = GYM_LEADER_SCALING, // Cap 74
    [TRAINER_TATE_AND_LIZA_1]  = GYM_LEADER_SCALING, // Cap 80
    [TRAINER_JUAN_1]           = GYM_LEADER_SCALING, // Cap 90

    // In Emerald these names point at the hideout under the Mauville Game Corner (constants/opponents.h)
    [TRAINER_TEAM_ROCKET_GRUNT_8]  = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_9]  = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_10] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_11] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_12] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_13] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_14] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_15] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_16] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_17] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_TEAM_ROCKET_GRUNT_18] = ROCKET_HIDEOUT_SCALING,
    [TRAINER_BOSS_GIOVANNI]        = ROCKET_HIDEOUT_SCALING,
};
