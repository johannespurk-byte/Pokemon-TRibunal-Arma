#include "global.h"
#include "event_data.h"
#include "field_move.h"
#include "item.h"
#include "test/overworld_script.h"
#include "test/test.h"
#include "constants/field_move.h"

TEST("(Field move) Cut works with the badge and the HM even if no Pokémon can learn it")
{
    ZeroPlayerPartyMons();
    FlagSet(FLAG_BADGE01_GET);
    AddBagItem(ITEM_HM_CUT, 1);
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_POLTCHAGEIST, 10;
        checkfieldmove FIELD_MOVE_CUT, TRUE;
    );
    EXPECT(!CanLearnTeachableMove(SPECIES_POLTCHAGEIST, MOVE_CUT));
    EXPECT_EQ(gSpecialVar_Result, 0);
}

TEST("(Field move) Cut still needs the badge when the HM is in the bag")
{
    ZeroPlayerPartyMons();
    FlagClear(FLAG_BADGE01_GET);
    AddBagItem(ITEM_HM_CUT, 1);
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_POLTCHAGEIST, 10;
        checkfieldmove FIELD_MOVE_CUT, TRUE;
    );
    EXPECT_EQ(gSpecialVar_Result, PARTY_SIZE);
}

TEST("(Field move) Waterfall works with the badge and the HM even if no Pokémon can learn it")
{
    ZeroPlayerPartyMons();
    FlagSet(FLAG_BADGE08_GET);
    AddBagItem(ITEM_HM_WATERFALL, 1);
    RUN_OVERWORLD_SCRIPT(
        givemon SPECIES_POLTCHAGEIST, 10;
        checkfieldmove FIELD_MOVE_WATERFALL;
    );
    EXPECT(!CanLearnTeachableMove(SPECIES_POLTCHAGEIST, MOVE_WATERFALL));
    EXPECT_EQ(gSpecialVar_Result, 0);
}

TEST("(Field move) Flash works with the badge and the HM even if no Pokémon can learn it")
{
    ZeroPlayerPartyMons();
    FlagSet(FLAG_BADGE02_GET);
    AddBagItem(ITEM_HM_FLASH, 1);
    RUN_OVERWORLD_SCRIPT(givemon SPECIES_POLTCHAGEIST, 10;);
    EXPECT(!CanLearnTeachableMove(SPECIES_POLTCHAGEIST, MOVE_FLASH));
    EXPECT(CanUseFlash());
}
