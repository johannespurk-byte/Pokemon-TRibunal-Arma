#include "global.h"
#include "test/test.h"
#include "field_screen_effect.h"
#include "overworld.h"
#include "task.h"

static u32 CountActiveTasks(void)
{
    u32 i, count = 0;
    for (i = 0; i < NUM_TASKS; i++)
    {
        if (gTasks[i].isActive)
            count++;
    }
    return count;
}

static bool32 FlashAnimationEnds(u32 fromLevel, u32 toLevel)
{
    u32 frame;
    ResetTasks();
    SetFlashLevel(fromLevel);
    AnimateFlash(toLevel);
    for (frame = 0; frame < 600 && CountActiveTasks() != 0; frame++)
        RunTasks();
    return CountActiveTasks() == 0;
}

TEST("animateflash ends when the room is already lit")
{
    // Brawly's badge scene animates to full brightness after the gym was lit.
    EXPECT(FlashAnimationEnds(0, 0));
}

TEST("animateflash ends when lighting up a dark room")
{
    EXPECT(FlashAnimationEnds(7, 0));
}

TEST("animateflash ends when darkening a room")
{
    EXPECT(FlashAnimationEnds(1, 7));
}
