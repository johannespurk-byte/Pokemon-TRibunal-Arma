#include "global.h"
#include "test/test.h"
#include "battle.h"
#include "battle_main.h"
#include "data.h"
#include "graphics.h"
#include "malloc.h"
#include "trainer_pools.h"
#include "battle_transition.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/trainers.h"
#include "constants/battle.h"
#include "constants/battle_ai.h"

// The test build swaps gTrainers for the test trainers, so pull the game's
// real parties in here and build every one of them.
static const struct Trainer sGameTrainers[DIFFICULTY_COUNT][TRAINERS_COUNT] =
{
#include "../src/data/trainers.h"
};

TEST("Every trainer party in trainers.party can be created")
{
    u32 difficulty, trainerId;
    struct Pokemon *party = Alloc(PARTY_SIZE * sizeof(struct Pokemon));

    for (difficulty = 0; difficulty < DIFFICULTY_COUNT; difficulty++)
    {
        for (trainerId = 1; trainerId < TRAINERS_COUNT; trainerId++)
        {
            const struct Trainer *trainer = &sGameTrainers[difficulty][trainerId];
            if (trainer->partySize == 0)
                continue;
            CreateNPCTrainerPartyFromTrainer(party, trainer, TRUE, BATTLE_TYPE_TRAINER, trainerId);
        }
    }

    Free(party);
}
