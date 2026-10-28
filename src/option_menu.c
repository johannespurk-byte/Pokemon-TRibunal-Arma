#include "global.h"
#include "option_menu.h"
#include "bg.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "gba/m4a_internal.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define tMenuSelection data[0]
#define tTextSpeed data[1]
#define tBattleSceneOff data[2]
#define tBattleStyle data[3]
#define tSound data[4]
#define tButtonMode data[5]
#define tWindowFrameType data[6]
#define tNuzlocke data[7]

enum
{
    MENUITEM_TEXTSPEED,
    MENUITEM_BATTLESCENE,
    MENUITEM_BATTLESTYLE,
    MENUITEM_SOUND,
    MENUITEM_BUTTONMODE,
    MENUITEM_FRAMETYPE,
    MENUITEM_NUZLOCKE,
    MENUITEM_CANCEL,
    MENUITEM_COUNT,
};

// Modernes Layout: Titelleiste oben, dunkle Optionskarte, Hilfezeile unten.
// Die gewählte Zeile wird per WIN0 aufgehellt, jede Option zeigt nur ihren Wert zwischen ◀ ▶.
#define OPTION_ROW_HEIGHT 14
#define OPTIONS_TOP_TILE  3
#define OPTIONS_TOP_PX    (OPTIONS_TOP_TILE * 8)

// Wert-Spalte im Optionsfenster (Pixel)
#define VALUE_ARROW_L_X   112
#define VALUE_ARROW_R_X   192
#define VALUE_CENTER_X    156

// Farben in graphics/interface/option_menu_text.pal
#define COLOR_PANEL       1
#define COLOR_TEXT        2
#define COLOR_SHADOW      3
#define COLOR_ACCENT      4
#define COLOR_DIM         6
#define COLOR_HEADER      8
#define COLOR_HELP_BG     9

enum
{
    WIN_HEADER,
    WIN_OPTIONS,
    WIN_HELP,
};

#define YPOS_TEXTSPEED    (MENUITEM_TEXTSPEED * OPTION_ROW_HEIGHT)
#define YPOS_BATTLESCENE  (MENUITEM_BATTLESCENE * OPTION_ROW_HEIGHT)
#define YPOS_BATTLESTYLE  (MENUITEM_BATTLESTYLE * OPTION_ROW_HEIGHT)
#define YPOS_SOUND        (MENUITEM_SOUND * OPTION_ROW_HEIGHT)
#define YPOS_BUTTONMODE   (MENUITEM_BUTTONMODE * OPTION_ROW_HEIGHT)
#define YPOS_FRAMETYPE    (MENUITEM_FRAMETYPE * OPTION_ROW_HEIGHT)
#define YPOS_NUZLOCKE     (MENUITEM_NUZLOCKE * OPTION_ROW_HEIGHT)

static void Task_OptionMenuFadeIn(u8 taskId);
static void Task_OptionMenuProcessInput(u8 taskId);
static void Task_OptionMenuSave(u8 taskId);
static void Task_OptionMenuTryClose(u8 taskId);
static void Task_OptionMenuConfirm(u8 taskId);
static void Task_OptionMenuFadeOut(u8 taskId);
static void HighlightOptionMenuItem(u8 selection);
static u8 TextSpeed_ProcessInput(u8 selection);
static void TextSpeed_DrawChoices(u8 selection);
static u8 BattleScene_ProcessInput(u8 selection);
static void BattleScene_DrawChoices(u8 selection);
static u8 BattleStyle_ProcessInput(u8 selection);
static void BattleStyle_DrawChoices(u8 selection);
static u8 Sound_ProcessInput(u8 selection);
static void Sound_DrawChoices(u8 selection);
static u8 FrameType_ProcessInput(u8 selection);
static void FrameType_DrawChoices(u8 selection);
static u8 ButtonMode_ProcessInput(u8 selection);
static void ButtonMode_DrawChoices(u8 selection);
static u8 Nuzlocke_ProcessInput(u8 selection);
static void Nuzlocke_DrawChoices(u8 selection);
static void DrawHeaderText(void);
static void DrawOptionMenuTexts(void);
static void DrawHelpText(u8 selection);

EWRAM_DATA static bool8 sArrowPressed = FALSE;

static const u8 gText_Option[]             = _("OPTIONS");
static const u8 gText_TextSpeedSlow[]      = _("SLOW");
static const u8 gText_TextSpeedMid[]       = _("MID");
static const u8 gText_TextSpeedFast[]      = _("FAST");
static const u8 gText_On[]                 = _("ON");
static const u8 gText_Off[]                = _("OFF");
static const u8 gText_BattleStyleShift[]   = _("SHIFT");
static const u8 gText_BattleStyleSet[]     = _("SET");
static const u8 gText_SoundMono[]          = _("MONO");
static const u8 gText_SoundStereo[]        = _("STEREO");
static const u8 gText_FrameType[]          = _("TYPE ");
static const u8 gText_ButtonTypeNormal[]   = _("NORMAL");
static const u8 gText_ButtonTypeLR[]       = _("LR");
static const u8 gText_ButtonTypeLEqualsA[] = _("L=A");
static const u8 sText_ArrowLeft[]          = { CHAR_LEFT_ARROW, EOS };
static const u8 sText_ArrowRight[]         = { CHAR_RIGHT_ARROW, EOS };

static const u8 *const sTextSpeedNames[] = { gText_TextSpeedSlow, gText_TextSpeedMid, gText_TextSpeedFast };
static const u8 *const sButtonModeNames[] = { gText_ButtonTypeNormal, gText_ButtonTypeLR, gText_ButtonTypeLEqualsA };

static const u8 sTextColors[]   = { COLOR_PANEL, COLOR_TEXT, COLOR_SHADOW };
static const u8 sValueColors[]  = { COLOR_PANEL, COLOR_ACCENT, COLOR_SHADOW };
static const u8 sArrowColors[]  = { COLOR_PANEL, COLOR_DIM, COLOR_SHADOW };
static const u8 sHeaderColors[] = { COLOR_HEADER, COLOR_TEXT, COLOR_SHADOW };
static const u8 sHelpColors[]   = { COLOR_HELP_BG, COLOR_DIM, COLOR_SHADOW };
static const u8 sConfirmColors[] = { COLOR_HELP_BG, COLOR_ACCENT, COLOR_SHADOW };

static const u16 sOptionMenuText_Pal[] = INCGFX_U16("graphics/interface/option_menu_text.pal", ".gbapal");
// note: this is only used in the Japanese release
static const u8 sEqualSignGfx[] = INCGFX_U8("graphics/interface/option_menu_equals_sign.png", ".4bpp");

static const u8 *const sOptionMenuItemsNames[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = COMPOUND_STRING("TEXT SPEED"),
    [MENUITEM_BATTLESCENE] = COMPOUND_STRING("BATTLE SCENE"),
    [MENUITEM_BATTLESTYLE] = COMPOUND_STRING("BATTLE STYLE"),
    [MENUITEM_SOUND]       = COMPOUND_STRING("SOUND"),
    [MENUITEM_BUTTONMODE]  = COMPOUND_STRING("BUTTON MODE"),
    [MENUITEM_FRAMETYPE]   = COMPOUND_STRING("FRAME"),
    [MENUITEM_NUZLOCKE]    = COMPOUND_STRING("NUZLOCKE"),
    [MENUITEM_CANCEL]      = COMPOUND_STRING("CANCEL"),
};

static const u8 *const sOptionMenuItemsHelp[MENUITEM_COUNT] =
{
    [MENUITEM_TEXTSPEED]   = COMPOUND_STRING("How fast messages are printed."),
    [MENUITEM_BATTLESCENE] = COMPOUND_STRING("Show or skip battle animations."),
    [MENUITEM_BATTLESTYLE] = COMPOUND_STRING("SHIFT offers a switch after a knockout."),
    [MENUITEM_SOUND]       = COMPOUND_STRING("Mono or stereo sound."),
    [MENUITEM_BUTTONMODE]  = COMPOUND_STRING("What the L and R buttons do."),
    [MENUITEM_FRAMETYPE]   = COMPOUND_STRING("Frame style of the message boxes."),
    [MENUITEM_NUZLOCKE]    = COMPOUND_STRING("First catch per area, fainted = lost."),
    [MENUITEM_CANCEL]      = COMPOUND_STRING("Save the settings and close."),
};

static const struct WindowTemplate sOptionMenuWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = OPTIONS_TOP_TILE,
        .width = 26,
        .height = 14,
        .paletteNum = 1,
        .baseBlock = 62
    },
    [WIN_HELP] = {
        .bg = 1,
        .tilemapLeft = 0,
        .tilemapTop = 18,
        .width = 30,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 426
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sOptionMenuBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

// Hintergrund hinter den Fenstern: dunkles Nachtblau
static const u16 sOptionMenuBg_Pal[] = {RGB(3, 4, 7)};

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitOptionMenu(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sOptionMenuBgTemplates, ARRAY_COUNT(sOptionMenuBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        ChangeBgX(3, 0, BG_COORD_SET);
        ChangeBgY(3, 0, BG_COORD_SET);
        InitWindows(sOptionMenuWinTemplates);
        DeactivateAllTextPrinters();
        // Innerhalb von WIN0 (gewählte Zeile) wird BG0 aufgehellt, außerhalb bleibt alles normal
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0 | WININ_WIN0_BG1 | WININ_WIN0_CLR);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_LIGHTEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 3);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        PutWindowTilemap(WIN_HELP);
        gMain.state++;
        break;
    case 8:
        PutWindowTilemap(WIN_OPTIONS);
        DrawOptionMenuTexts();
        gMain.state++;
    case 9:
        CopyBgTilemapBufferToVram(1);
        gMain.state++;
        break;
    case 10:
    {
        u8 taskId = CreateTask(Task_OptionMenuFadeIn, 0);

        gTasks[taskId].tMenuSelection = 0;
        gTasks[taskId].tTextSpeed = gSaveBlock2Ptr->optionsTextSpeed;
        gTasks[taskId].tBattleSceneOff = gSaveBlock2Ptr->optionsBattleSceneOff;
        gTasks[taskId].tBattleStyle = gSaveBlock2Ptr->optionsBattleStyle;
        gTasks[taskId].tSound = gSaveBlock2Ptr->optionsSound;
        gTasks[taskId].tButtonMode = gSaveBlock2Ptr->optionsButtonMode;
        gTasks[taskId].tWindowFrameType = gSaveBlock2Ptr->optionsWindowFrameType;
        gTasks[taskId].tNuzlocke = gSaveBlock2Ptr->optionsNuzlocke;

        TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
        BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
        BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
        Sound_DrawChoices(gTasks[taskId].tSound);
        ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
        FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
        Nuzlocke_DrawChoices(gTasks[taskId].tNuzlocke);
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    }
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_OptionMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_OptionMenuProcessInput;
}

static void Task_OptionMenuProcessInput(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        if (gTasks[taskId].tMenuSelection == MENUITEM_CANCEL)
            gTasks[taskId].func = Task_OptionMenuTryClose;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_OptionMenuTryClose;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (gTasks[taskId].tMenuSelection > 0)
            gTasks[taskId].tMenuSelection--;
        else
            gTasks[taskId].tMenuSelection = MENUITEM_CANCEL;
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (gTasks[taskId].tMenuSelection < MENUITEM_CANCEL)
            gTasks[taskId].tMenuSelection++;
        else
            gTasks[taskId].tMenuSelection = 0;
        HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    }
    else
    {
        u8 previousOption;

        switch (gTasks[taskId].tMenuSelection)
        {
        case MENUITEM_TEXTSPEED:
            previousOption = gTasks[taskId].tTextSpeed;
            gTasks[taskId].tTextSpeed = TextSpeed_ProcessInput(gTasks[taskId].tTextSpeed);

            if (previousOption != gTasks[taskId].tTextSpeed)
                TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
            break;
        case MENUITEM_BATTLESCENE:
            previousOption = gTasks[taskId].tBattleSceneOff;
            gTasks[taskId].tBattleSceneOff = BattleScene_ProcessInput(gTasks[taskId].tBattleSceneOff);

            if (previousOption != gTasks[taskId].tBattleSceneOff)
                BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
            break;
        case MENUITEM_BATTLESTYLE:
            previousOption = gTasks[taskId].tBattleStyle;
            gTasks[taskId].tBattleStyle = BattleStyle_ProcessInput(gTasks[taskId].tBattleStyle);

            if (previousOption != gTasks[taskId].tBattleStyle)
                BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
            break;
        case MENUITEM_SOUND:
            previousOption = gTasks[taskId].tSound;
            gTasks[taskId].tSound = Sound_ProcessInput(gTasks[taskId].tSound);

            if (previousOption != gTasks[taskId].tSound)
                Sound_DrawChoices(gTasks[taskId].tSound);
            break;
        case MENUITEM_BUTTONMODE:
            previousOption = gTasks[taskId].tButtonMode;
            gTasks[taskId].tButtonMode = ButtonMode_ProcessInput(gTasks[taskId].tButtonMode);

            if (previousOption != gTasks[taskId].tButtonMode)
                ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
            break;
        case MENUITEM_FRAMETYPE:
            previousOption = gTasks[taskId].tWindowFrameType;
            gTasks[taskId].tWindowFrameType = FrameType_ProcessInput(gTasks[taskId].tWindowFrameType);

            if (previousOption != gTasks[taskId].tWindowFrameType)
                FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
            break;
        case MENUITEM_NUZLOCKE:
            previousOption = gTasks[taskId].tNuzlocke;
            gTasks[taskId].tNuzlocke = Nuzlocke_ProcessInput(gTasks[taskId].tNuzlocke);

            if (previousOption != gTasks[taskId].tNuzlocke)
                Nuzlocke_DrawChoices(gTasks[taskId].tNuzlocke);
            break;
        default:
            return;
        }

        if (sArrowPressed)
        {
            sArrowPressed = FALSE;
            CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
        }
    }
}

static bool32 HaveOptionsChanged(u8 taskId)
{
    return gTasks[taskId].tTextSpeed != gSaveBlock2Ptr->optionsTextSpeed
        || gTasks[taskId].tBattleSceneOff != gSaveBlock2Ptr->optionsBattleSceneOff
        || gTasks[taskId].tBattleStyle != gSaveBlock2Ptr->optionsBattleStyle
        || gTasks[taskId].tSound != gSaveBlock2Ptr->optionsSound
        || gTasks[taskId].tButtonMode != gSaveBlock2Ptr->optionsButtonMode
        || gTasks[taskId].tWindowFrameType != gSaveBlock2Ptr->optionsWindowFrameType
        || gTasks[taskId].tNuzlocke != gSaveBlock2Ptr->optionsNuzlocke;
}

// Beim Verlassen mit Änderungen nachfragen, sonst direkt schließen
static void Task_OptionMenuTryClose(u8 taskId)
{
    if (!HaveOptionsChanged(taskId))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_OptionMenuFadeOut;
        return;
    }

    PlaySE(SE_SELECT);
    FillWindowPixelBuffer(WIN_HELP, PIXEL_FILL(COLOR_HELP_BG));
    AddTextPrinterParameterized3(WIN_HELP, FONT_SMALL, 16, 2, sConfirmColors, TEXT_SKIP_DRAW,
                                 COMPOUND_STRING("Save changes?  A: Yes  B: No  {UP_ARROW}{DOWN_ARROW}: Back"));
    CopyWindowToVram(WIN_HELP, COPYWIN_FULL);
    gTasks[taskId].func = Task_OptionMenuConfirm;
}

static void Task_OptionMenuConfirm(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_OptionMenuSave;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        // Änderungen verwerfen; die Stereo-Einstellung wurde beim Umschalten schon gesetzt
        PlaySE(SE_SELECT);
        SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_OptionMenuFadeOut;
    }
    else if (JOY_NEW(DPAD_UP | DPAD_DOWN))
    {
        DrawHelpText(gTasks[taskId].tMenuSelection);
        gTasks[taskId].func = Task_OptionMenuProcessInput;
    }
}

static void Task_OptionMenuSave(u8 taskId)
{
    gSaveBlock2Ptr->optionsTextSpeed = gTasks[taskId].tTextSpeed;
    gSaveBlock2Ptr->optionsBattleSceneOff = gTasks[taskId].tBattleSceneOff;
    gSaveBlock2Ptr->optionsBattleStyle = gTasks[taskId].tBattleStyle;
    gSaveBlock2Ptr->optionsSound = gTasks[taskId].tSound;
    gSaveBlock2Ptr->optionsButtonMode = gTasks[taskId].tButtonMode;
    gSaveBlock2Ptr->optionsWindowFrameType = gTasks[taskId].tWindowFrameType;
    gSaveBlock2Ptr->optionsNuzlocke = gTasks[taskId].tNuzlocke;

    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_OptionMenuFadeOut;
}

static void Task_OptionMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}

static void HighlightOptionMenuItem(u8 index)
{
    u32 top = OPTIONS_TOP_PX + index * OPTION_ROW_HEIGHT;

    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(top, top + OPTION_ROW_HEIGHT));
    DrawHelpText(index);
}

// Zeichnet den Wert einer Option zentriert zwischen ◀ und ▶
static void DrawOptionValue(const u8 *text, u8 y)
{
    s32 x = VALUE_CENTER_X - GetStringWidth(FONT_NORMAL, text, 0) / 2;

    FillWindowPixelRect(WIN_OPTIONS, PIXEL_FILL(COLOR_PANEL), VALUE_ARROW_L_X, y, DISPLAY_WIDTH - 32 - VALUE_ARROW_L_X, OPTION_ROW_HEIGHT);
    AddTextPrinterParameterized3(WIN_OPTIONS, FONT_NORMAL, VALUE_ARROW_L_X, y + 1, sArrowColors, TEXT_SKIP_DRAW, sText_ArrowLeft);
    AddTextPrinterParameterized3(WIN_OPTIONS, FONT_NORMAL, x, y + 1, sValueColors, TEXT_SKIP_DRAW, text);
    AddTextPrinterParameterized3(WIN_OPTIONS, FONT_NORMAL, VALUE_ARROW_R_X, y + 1, sArrowColors, TEXT_SKIP_DRAW, sText_ArrowRight);
}

static u8 TextSpeed_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void TextSpeed_DrawChoices(u8 selection)
{
    DrawOptionValue(sTextSpeedNames[selection], YPOS_TEXTSPEED);
}

static u8 BattleScene_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleScene_DrawChoices(u8 selection)
{
    DrawOptionValue(selection ? gText_Off : gText_On, YPOS_BATTLESCENE);
}

static u8 BattleStyle_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

static void BattleStyle_DrawChoices(u8 selection)
{
    DrawOptionValue(selection ? gText_BattleStyleSet : gText_BattleStyleShift, YPOS_BATTLESTYLE);
}

static u8 Sound_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        SetPokemonCryStereo(selection);
        sArrowPressed = TRUE;
    }

    return selection;
}

static void Sound_DrawChoices(u8 selection)
{
    DrawOptionValue(selection ? gText_SoundStereo : gText_SoundMono, YPOS_SOUND);
}

static u8 FrameType_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection < WINDOW_FRAMES_COUNT - 1)
            selection++;
        else
            selection = 0;
        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = WINDOW_FRAMES_COUNT - 1;
        sArrowPressed = TRUE;
    }
    return selection;
}

static void FrameType_DrawChoices(u8 selection)
{
    u8 text[16];
    u8 *end = StringCopy(text, gText_FrameType);

    ConvertIntToDecimalStringN(end, selection + 1, STR_CONV_MODE_LEFT_ALIGN, 2);
    DrawOptionValue(text, YPOS_FRAMETYPE);
}

static u8 ButtonMode_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (selection <= 1)
            selection++;
        else
            selection = 0;

        sArrowPressed = TRUE;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (selection != 0)
            selection--;
        else
            selection = 2;

        sArrowPressed = TRUE;
    }
    return selection;
}

static void ButtonMode_DrawChoices(u8 selection)
{
    DrawOptionValue(sButtonModeNames[selection], YPOS_BUTTONMODE);
}

static u8 Nuzlocke_ProcessInput(u8 selection)
{
    if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        selection ^= 1;
        sArrowPressed = TRUE;
    }

    return selection;
}

// 0 = aus, 1 = an (Regeln in nuzlocke.c)
static void Nuzlocke_DrawChoices(u8 selection)
{
    DrawOptionValue(selection ? gText_On : gText_Off, YPOS_NUZLOCKE);
}

static void DrawHeaderText(void)
{
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(COLOR_HEADER));
    AddTextPrinterParameterized3(WIN_HEADER, FONT_NORMAL, 16, 1, sHeaderColors, TEXT_SKIP_DRAW, gText_Option);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void DrawHelpText(u8 selection)
{
    FillWindowPixelBuffer(WIN_HELP, PIXEL_FILL(COLOR_HELP_BG));
    AddTextPrinterParameterized3(WIN_HELP, FONT_SMALL, 16, 2, sHelpColors, TEXT_SKIP_DRAW, sOptionMenuItemsHelp[selection]);
    CopyWindowToVram(WIN_HELP, COPYWIN_FULL);
}

static void DrawOptionMenuTexts(void)
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(COLOR_PANEL));
    for (i = 0; i < MENUITEM_COUNT; i++)
        AddTextPrinterParameterized3(WIN_OPTIONS, FONT_NORMAL, 8, (i * OPTION_ROW_HEIGHT) + 1, sTextColors, TEXT_SKIP_DRAW, sOptionMenuItemsNames[i]);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}
