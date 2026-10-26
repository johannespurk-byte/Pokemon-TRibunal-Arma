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

const struct LevelScalingConfig gTrainerLevelScalingRules[TRAINERS_COUNT] =
{
};
