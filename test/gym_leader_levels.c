#include "global.h"
#include "test/test.h"
#include "caps.h"
#include "event_data.h"
#include "level_scaling.h"
#include "constants/opponents.h"

static const struct {
    u16 trainerId;
    u8 badgesBefore;
    u8 expectedLevel;
} sGymLeaderLevels[] =
{
    { TRAINER_ROXANNE_1,        0, 18 },
    { TRAINER_BLAINE,           0, 18 },
    { TRAINER_BRAWLY_1,         1, 36 },
    { TRAINER_BRANDON_DEWFORD,  1, 36 },
    { TRAINER_WATTSON_1,        2, 50 },
    { TRAINER_LORELEI_MAUVILLE, 2, 50 },
    { TRAINER_FLANNERY_1,       3, 60 },
    { TRAINER_NORMAN_1,         4, 68 },
    { TRAINER_MISTY,            4, 68 },
    { TRAINER_WINONA_1,         5, 74 },
    { TRAINER_TATE_AND_LIZA_1,  6, 80 },
    { TRAINER_JUAN_1,           7, 90 },
};

TEST("Gym leaders fight at the level cap from caps.c")
{
    u32 i, badge;
    for (i = 0; i < ARRAY_COUNT(sGymLeaderLevels); i++)
    {
        const struct LevelScalingConfig *config = GetTrainerLevelScalingConfig(sGymLeaderLevels[i].trainerId);
        for (badge = 0; badge < 8; badge++)
        {
            if (badge < sGymLeaderLevels[i].badgesBefore)
                FlagSet(FLAG_BADGE01_GET + badge);
            else
                FlagClear(FLAG_BADGE01_GET + badge);
        }
        FlagClear(FLAG_SYS_GAME_CLEAR);
        InvalidatePartyLevelCache();
        EXPECT_EQ(config->mode, LEVEL_SCALING_TO_LEVEL_CAP);
        EXPECT_EQ(CalculateScaledLevel(config, 5), sGymLeaderLevels[i].expectedLevel);
    }
}
