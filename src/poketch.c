#include "global.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "nuzlocke.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon_icon.h"
#include "pokenav.h"
#include "poketch.h"
#include "region_map.h"
#include "rtc.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/party_menu.h"
#include "constants/region_map_sections.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// Das Pokétch: eine Uhr im Vollbild statt des PokéNav-Hauptmenüs. L/R (oder links/rechts) wechselt
// die App, B geht zurück ins Startmenü. Karte, Match Call und das alte Menü laufen weiter über den
// PokéNav-Code (src/pokenav.c) und kehren danach hierher zurück.

enum
{
    POKETCH_APP_CLOCK,
    POKETCH_APP_TEAM,
    POKETCH_APP_NUZLOCKE,
    POKETCH_APP_MAP,
    POKETCH_APP_MATCH_CALL,
    POKETCH_APP_MORE,
    POKETCH_APP_COUNT,
};

// Palettenplätze der Grafik, siehe graphics/poketch/device.png
#define COLOR_LCD_LIGHT 1
#define COLOR_LCD_MID   2
#define COLOR_LCD_DARK  3

#define WIN_LCD 0
#define LCD_LEFT   3 // in Kacheln
#define LCD_TOP    2
#define LCD_WIDTH  24
#define LCD_HEIGHT 16
#define LCD_PX_X (LCD_LEFT * 8)
#define LCD_PX_Y (LCD_TOP * 8)

#define NO_ICON 0xFF

#define DIGIT_WIDTH     24
#define DIGIT_HEIGHT    40
#define SEGMENT_THICK   5

#define NUZLOCKE_COLS 6
#define NUZLOCKE_CELL_W 31
#define NUZLOCKE_CELL_H 14

STATIC_ASSERT(MAPSEC_ROUTE_134 - MAPSEC_ROUTE_101 == 33, RouteSectionsNotConsecutive);

static const u16 sDevice_Pal[] = INCGFX_U16("graphics/poketch/device.png", ".gbapal");
static const u32 sDevice_Gfx[] = INCGFX_U32("graphics/poketch/device.png", ".4bpp.smol");
static const u32 sDevice_Tilemap[] = INCGFX_U32("graphics/poketch/device.bin", ".smolTM");

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_LCD] = {
        .bg = 0,
        .tilemapLeft = LCD_LEFT,
        .tilemapTop = LCD_TOP,
        .width = LCD_WIDTH,
        .height = LCD_HEIGHT,
        .paletteNum = 0,
        .baseBlock = 1,
    },
    DUMMY_WIN_TEMPLATE,
};

static const u8 sTextColors[] = {TEXT_COLOR_TRANSPARENT, COLOR_LCD_DARK, COLOR_LCD_MID};
static const u8 sTextColorsInverted[] = {TEXT_COLOR_TRANSPARENT, COLOR_LCD_LIGHT, COLOR_LCD_MID};

static const u8 *const sAppNames[POKETCH_APP_COUNT] =
{
    [POKETCH_APP_CLOCK]      = COMPOUND_STRING("CLOCK"),
    [POKETCH_APP_TEAM]       = COMPOUND_STRING("TEAM"),
    [POKETCH_APP_NUZLOCKE]   = COMPOUND_STRING("NUZLOCKE"),
    [POKETCH_APP_MAP]        = COMPOUND_STRING("MAP"),
    [POKETCH_APP_MATCH_CALL] = COMPOUND_STRING("MATCH CALL"),
    [POKETCH_APP_MORE]       = COMPOUND_STRING("MORE"),
};

static EWRAM_DATA u8 sCurrentApp = POKETCH_APP_CLOCK; // bleibt erhalten, damit man nach der Karte hier landet
static EWRAM_DATA u8 sIconIds[PARTY_SIZE] = {0};
static EWRAM_DATA s8 sLastSecond = 0;
static EWRAM_DATA u32 sPokenavMenuToOpen = 0; // die Menü-IDs passen nicht in ein s16-Taskfeld
static EWRAM_DATA void *sBgTilemapBuffer = NULL;

static void Task_Poketch_WaitFadeIn(u8 taskId);
static void Task_Poketch_Input(u8 taskId);
static void Task_Poketch_FadeToField(u8 taskId);
static void Task_Poketch_FadeToPokenav(u8 taskId);

static void CB2_Poketch(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_Poketch(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void PrintText(u8 font, u8 x, u8 y, const u8 *str)
{
    AddTextPrinterParameterized3(WIN_LCD, font, x, y, sTextColors, TEXT_SKIP_DRAW, str);
}

static void PrintTextCentered(u8 font, u8 y, const u8 *str)
{
    s32 x = (LCD_WIDTH * 8 - GetStringWidth(font, str, 0)) / 2;

    PrintText(font, max(x, 0), y, str);
}

static void FillLcdRect(u8 color, u16 x, u16 y, u16 w, u16 h)
{
    FillWindowPixelRect(WIN_LCD, PIXEL_FILL(color), x, y, w, h);
}

static void DestroyPartyIcons(void)
{
    u32 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (sIconIds[i] != NO_ICON)
            FreeAndDestroyMonIconSprite(&gSprites[sIconIds[i]]);
        sIconIds[i] = NO_ICON;
    }
}

// App-Name oben und ein Punkt je App, der aktuelle gefüllt
static void DrawHeader(void)
{
    u32 i;
    u32 x = LCD_WIDTH * 8 - 4 - POKETCH_APP_COUNT * 8;

    PrintText(FONT_SMALL, 4, 1, sAppNames[sCurrentApp]);
    for (i = 0; i < POKETCH_APP_COUNT; i++)
    {
        FillLcdRect(COLOR_LCD_DARK, x + i * 8, 4, 6, 6);
        if (i != sCurrentApp)
            FillLcdRect(COLOR_LCD_LIGHT, x + i * 8 + 1, 5, 4, 4);
    }
    FillLcdRect(COLOR_LCD_DARK, 2, 14, LCD_WIDTH * 8 - 4, 1);
}

// Sieben-Segment-Ziffer wie auf einem LCD. Bits: oben, oben links, oben rechts, Mitte, unten links, unten rechts, unten
static void DrawDigit(u32 digit, u16 x, u16 y)
{
    static const u8 sSegments[10] =
    {
        0x77, 0x24, 0x5D, 0x6D, 0x2E, 0x6B, 0x7B, 0x25, 0x7F, 0x6F,
    };
    u32 s = sSegments[digit];
    u32 half = (DIGIT_HEIGHT - SEGMENT_THICK) / 2;

    if (s & 0x01)
        FillLcdRect(COLOR_LCD_DARK, x, y, DIGIT_WIDTH, SEGMENT_THICK);
    if (s & 0x02)
        FillLcdRect(COLOR_LCD_DARK, x, y, SEGMENT_THICK, half + SEGMENT_THICK);
    if (s & 0x04)
        FillLcdRect(COLOR_LCD_DARK, x + DIGIT_WIDTH - SEGMENT_THICK, y, SEGMENT_THICK, half + SEGMENT_THICK);
    if (s & 0x08)
        FillLcdRect(COLOR_LCD_DARK, x, y + half, DIGIT_WIDTH, SEGMENT_THICK);
    if (s & 0x10)
        FillLcdRect(COLOR_LCD_DARK, x, y + half, SEGMENT_THICK, half + SEGMENT_THICK);
    if (s & 0x20)
        FillLcdRect(COLOR_LCD_DARK, x + DIGIT_WIDTH - SEGMENT_THICK, y + half, SEGMENT_THICK, half + SEGMENT_THICK);
    if (s & 0x40)
        FillLcdRect(COLOR_LCD_DARK, x, y + DIGIT_HEIGHT - SEGMENT_THICK, DIGIT_WIDTH, SEGMENT_THICK);
}

static void DrawClockApp(void)
{
    u8 buffer[32], *end;
    u32 top = 24;

    RtcCalcLocalTime();
    sLastSecond = gLocalTime.seconds;

    DrawDigit(gLocalTime.hours / 10, 20, top);
    DrawDigit(gLocalTime.hours % 10, 50, top);
    if (gLocalTime.seconds % 2 == 0)
    {
        FillLcdRect(COLOR_LCD_DARK, 93, top + 10, 6, 6);
        FillLcdRect(COLOR_LCD_DARK, 93, top + 24, 6, 6);
    }
    DrawDigit(gLocalTime.minutes / 10, 118 - 6, top);
    DrawDigit(gLocalTime.minutes % 10, 148 - 6, top);

    end = StringCopy(buffer, COMPOUND_STRING("STEPS  "));
    ConvertIntToDecimalStringN(end, GetGameStat(GAME_STAT_STEPS), STR_CONV_MODE_LEFT_ALIGN, 8);
    PrintTextCentered(FONT_NORMAL, 76, buffer);

    end = StringCopy(buffer, COMPOUND_STRING("PLAYED  "));
    end = ConvertIntToDecimalStringN(end, gSaveBlock2Ptr->playTimeHours, STR_CONV_MODE_LEFT_ALIGN, 3);
    end = StringCopy(end, COMPOUND_STRING(":"));
    ConvertIntToDecimalStringN(end, gSaveBlock2Ptr->playTimeMinutes, STR_CONV_MODE_LEADING_ZEROS, 2);
    PrintTextCentered(FONT_NORMAL, 94, buffer);
}

static void DrawTeamMember(u32 index)
{
    static const u8 *const sAilmentNames[] =
    {
        [AILMENT_PSN] = COMPOUND_STRING("PSN"),
        [AILMENT_PRZ] = COMPOUND_STRING("PAR"),
        [AILMENT_SLP] = COMPOUND_STRING("SLP"),
        [AILMENT_FRZ] = COMPOUND_STRING("FRZ"),
        [AILMENT_BRN] = COMPOUND_STRING("BRN"),
        [AILMENT_PKRS] = COMPOUND_STRING("PKRS"),
        [AILMENT_FNT] = COMPOUND_STRING("FNT"),
        [AILMENT_FRB] = COMPOUND_STRING("FRB"),
    };
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][index];
    u8 buffer[POKEMON_NAME_BUFFER_SIZE + 8], *end;
    u32 x = (index % 2) * 96;
    u32 y = 16 + (index / 2) * 37;
    u32 textX = x + 34;
    u32 hp, maxHp, ailment;
    bool32 isEgg = GetMonData(mon, MON_DATA_IS_EGG);

    sIconIds[index] = CreateMonIconIsEgg(GetMonData(mon, MON_DATA_SPECIES), SpriteCallbackDummy,
                                         LCD_PX_X + x + 16, LCD_PX_Y + y + 16, 0,
                                         GetMonData(mon, MON_DATA_PERSONALITY), isEgg);

    if (isEgg)
    {
        PrintText(FONT_SMALL, textX, y + 1, COMPOUND_STRING("EGG"));
        return;
    }

    GetMonData(mon, MON_DATA_NICKNAME, buffer);
    StringGet_Nickname(buffer);
    PrintText(FONT_SMALL, textX, y + 1, buffer);

    hp = GetMonData(mon, MON_DATA_HP);
    maxHp = GetMonData(mon, MON_DATA_MAX_HP);
    ailment = GetMonAilment(mon);

    if (mon->box.isNuzlockeDead)
    {
        PrintText(FONT_SMALL, textX, y + 13, COMPOUND_STRING("DEAD"));
    }
    else if (ailment != AILMENT_NONE && ailment < ARRAY_COUNT(sAilmentNames))
    {
        PrintText(FONT_SMALL, textX, y + 13, sAilmentNames[ailment]);
    }
    else
    {
        end = ConvertIntToDecimalStringN(buffer, hp, STR_CONV_MODE_LEFT_ALIGN, 3);
        end = StringCopy(end, COMPOUND_STRING("/"));
        ConvertIntToDecimalStringN(end, maxHp, STR_CONV_MODE_LEFT_ALIGN, 3);
        PrintText(FONT_SMALL, textX, y + 13, buffer);
    }

    FillLcdRect(COLOR_LCD_DARK, textX, y + 26, 54, 5);
    FillLcdRect(COLOR_LCD_LIGHT, textX + 1, y + 27, 52, 3);
    if (maxHp != 0 && hp != 0)
        FillLcdRect(COLOR_LCD_DARK, textX + 1, y + 27, max(hp * 52 / maxHp, 1), 3);
}

static void DrawTeamApp(void)
{
    u32 i;

    for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
        DrawTeamMember(i);
}

static void DrawNuzlockeCell(u32 cell, const u8 *label, bool32 isUsed)
{
    u32 x = 3 + (cell % NUZLOCKE_COLS) * NUZLOCKE_CELL_W;
    u32 y = 42 + (cell / NUZLOCKE_COLS) * NUZLOCKE_CELL_H;

    if (isUsed)
    {
        FillLcdRect(COLOR_LCD_DARK, x, y, NUZLOCKE_CELL_W - 2, NUZLOCKE_CELL_H - 1);
        AddTextPrinterParameterized3(WIN_LCD, FONT_SMALL, x + 3, y, sTextColorsInverted, TEXT_SKIP_DRAW, label);
    }
    else
    {
        PrintText(FONT_SMALL, x + 3, y, label);
    }
}

static void DrawNuzlockeApp(void)
{
    u8 buffer[32], *end;
    u32 route, area, cell = 0;

    area = Nuzlocke_GetEncounterArea();
    if (area == NUZLOCKE_AREA_ROUTE_104_NORTH)
        end = StringCopy(GetMapName(buffer, MAPSEC_ROUTE_104, 0), COMPOUND_STRING(" NORTH"));
    else if (area == NUZLOCKE_AREA_ROUTE_112_NORTH)
        end = StringCopy(GetMapName(buffer, MAPSEC_ROUTE_112, 0), COMPOUND_STRING(" NORTH"));
    else
        end = GetMapName(buffer, area, 0);
    PrintText(FONT_SMALL, 4, 16, buffer);

    if (!Nuzlocke_IsActive())
        PrintText(FONT_SMALL, 4, 28, COMPOUND_STRING("Nuzlocke mode is off"));
    else if (Nuzlocke_IsAreaUsed(area))
        PrintText(FONT_SMALL, 4, 28, COMPOUND_STRING("Encounter used"));
    else
        PrintText(FONT_SMALL, 4, 28, COMPOUND_STRING("Encounter free"));

    // Alle Hoenn-Routen; dunkel = Encounter verbraucht
    for (route = MAPSEC_ROUTE_101; route <= MAPSEC_ROUTE_134; route++)
    {
        end = ConvertIntToDecimalStringN(buffer, 101 + route - MAPSEC_ROUTE_101, STR_CONV_MODE_LEFT_ALIGN, 3);
        if (route == MAPSEC_ROUTE_104 || route == MAPSEC_ROUTE_112)
            StringCopy(end, COMPOUND_STRING("S"));
        DrawNuzlockeCell(cell++, buffer, Nuzlocke_IsAreaUsed(route));

        if (route == MAPSEC_ROUTE_104)
            DrawNuzlockeCell(cell++, COMPOUND_STRING("104N"), Nuzlocke_IsAreaUsed(NUZLOCKE_AREA_ROUTE_104_NORTH));
        else if (route == MAPSEC_ROUTE_112)
            DrawNuzlockeCell(cell++, COMPOUND_STRING("112N"), Nuzlocke_IsAreaUsed(NUZLOCKE_AREA_ROUTE_112_NORTH));
    }
}

static bool32 IsMatchCallAvailable(void)
{
    return FlagGet(FLAG_ADDED_MATCH_CALL_TO_POKENAV);
}

static void DrawLauncherApp(const u8 *title, const u8 *subtitle, const u8 *action)
{
    PrintTextCentered(FONT_NORMAL, 40, title);
    PrintTextCentered(FONT_SMALL, 58, subtitle);
    PrintTextCentered(FONT_NORMAL, 90, action);
}

static void DrawCurrentApp(void)
{
    DestroyPartyIcons();
    FillWindowPixelBuffer(WIN_LCD, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    DrawHeader();

    switch (sCurrentApp)
    {
    case POKETCH_APP_CLOCK:
        DrawClockApp();
        break;
    case POKETCH_APP_TEAM:
        DrawTeamApp();
        break;
    case POKETCH_APP_NUZLOCKE:
        DrawNuzlockeApp();
        break;
    case POKETCH_APP_MAP:
        DrawLauncherApp(COMPOUND_STRING("HOENN MAP"), COMPOUND_STRING("Where am I?"), COMPOUND_STRING("A: OPEN"));
        break;
    case POKETCH_APP_MATCH_CALL:
        if (IsMatchCallAvailable())
            DrawLauncherApp(COMPOUND_STRING("MATCH CALL"), COMPOUND_STRING("Call your trainer contacts"), COMPOUND_STRING("A: OPEN"));
        else
            DrawLauncherApp(COMPOUND_STRING("MATCH CALL"), COMPOUND_STRING("Not available yet"), gText_EmptyString2);
        break;
    case POKETCH_APP_MORE:
        DrawLauncherApp(COMPOUND_STRING("MORE"), COMPOUND_STRING("Condition and ribbons"), COMPOUND_STRING("A: OPEN"));
        break;
    }
    CopyWindowToVram(WIN_LCD, COPYWIN_GFX);
}

void CB2_InitPoketch(void)
{
    u32 i;

    SetVBlankCallback(NULL);
    SetHBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET);
    ChangeBgY(1, 0, BG_COORD_SET);
    DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);

    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    sBgTilemapBuffer = AllocZeroed(BG_SCREEN_SIZE);
    SetBgTilemapBuffer(0, sBgTilemapBuffer);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    ClearScheduledBgCopiesToVram();

    DecompressDataWithHeaderVram(sDevice_Gfx, (void *)BG_CHAR_ADDR(0));
    DecompressDataWithHeaderVram(sDevice_Tilemap, (void *)BG_SCREEN_ADDR(30));
    LoadPalette(sDevice_Pal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
    LoadMonIconPalettes();

    for (i = 0; i < PARTY_SIZE; i++)
        sIconIds[i] = NO_ICON;

    FillWindowPixelBuffer(WIN_LCD, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    PutWindowTilemap(WIN_LCD);
    CopyWindowToVram(WIN_LCD, COPYWIN_FULL);
    DrawCurrentApp();

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    ShowBg(0);
    ShowBg(1);

    BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    PlaySE(SE_POKENAV_ON);

    SetVBlankCallback(VBlankCB_Poketch);
    SetMainCallback2(CB2_Poketch);
    CreateTask(Task_Poketch_WaitFadeIn, 0);
}

static void Task_Poketch_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_Poketch_Input;
}

static void SwitchApp(s32 delta)
{
    PlaySE(SE_SELECT);
    sCurrentApp = (sCurrentApp + POKETCH_APP_COUNT + delta) % POKETCH_APP_COUNT;
    DrawCurrentApp();
}

static void FreePoketchResources(void)
{
    DestroyPartyIcons();
    FreeMonIconPalettes();
    FreeAllWindowBuffers();
    TRY_FREE_AND_SET_NULL(sBgTilemapBuffer);
}

static void StartPokenavApp(u8 taskId, u32 menuId)
{
    PlaySE(SE_SELECT);
    sPokenavMenuToOpen = menuId;
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    gTasks[taskId].func = Task_Poketch_FadeToPokenav;
}

static void Task_Poketch_Input(u8 taskId)
{
    if (JOY_NEW(R_BUTTON | DPAD_RIGHT))
    {
        SwitchApp(1);
    }
    else if (JOY_NEW(L_BUTTON | DPAD_LEFT))
    {
        SwitchApp(-1);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_POKENAV_OFF);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_Poketch_FadeToField;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        if (sCurrentApp == POKETCH_APP_MAP)
            StartPokenavApp(taskId, POKENAV_REGION_MAP);
        else if (sCurrentApp == POKETCH_APP_MATCH_CALL && IsMatchCallAvailable())
            StartPokenavApp(taskId, POKENAV_MATCH_CALL);
        else if (sCurrentApp == POKETCH_APP_MORE)
            StartPokenavApp(taskId, POKENAV_MAIN_MENU);
    }
    else if (sCurrentApp == POKETCH_APP_CLOCK)
    {
        RtcCalcLocalTime();
        if (gLocalTime.seconds != sLastSecond)
            DrawCurrentApp();
    }
}

static void Task_Poketch_FadeToField(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    FreePoketchResources();
    DestroyTask(taskId);
    SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
}

static void Task_Poketch_FadeToPokenav(u8 taskId)
{
    if (gPaletteFade.active)
        return;
    FreePoketchResources();
    DestroyTask(taskId);
    OpenPokenavFromPoketch(sPokenavMenuToOpen);
}
