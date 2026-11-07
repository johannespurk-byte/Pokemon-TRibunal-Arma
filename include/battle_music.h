#ifndef GUARD_BATTLE_MUSIC_H
#define GUARD_BATTLE_MUSIC_H

enum BattleMusicCategory
{
    BATTLE_MUSIC_WILD,
    BATTLE_MUSIC_LEGENDARY,
    BATTLE_MUSIC_TRAINER,
    BATTLE_MUSIC_RIVAL,
    BATTLE_MUSIC_TEAM,
    BATTLE_MUSIC_LEADER,
    BATTLE_MUSIC_LEAGUE,
    BATTLE_MUSIC_CATEGORY_COUNT,
};

// Choices per category: original music, random track, or one track from the list
#define BATTLE_MUSIC_CHOICE_ORIGINAL 0
#define BATTLE_MUSIC_CHOICE_RANDOM   1
#define BATTLE_MUSIC_CHOICE_TRACKS   2

const u8 *BattleMusic_GetCategoryName(u32 category);
u32 BattleMusic_GetChoice(u32 category);
void BattleMusic_SetChoice(u32 category, u32 choice);
u32 BattleMusic_GetChoiceCount(void);
const u8 *BattleMusic_GetChoiceName(u32 choice);
u16 BattleMusic_GetChoiceSong(u32 choice); // 0 if the choice is not a single track
u16 BattleMusic_GetSongForBattle(u32 category, u32 seed); // 0 means keep the original music

#endif // GUARD_BATTLE_MUSIC_H
