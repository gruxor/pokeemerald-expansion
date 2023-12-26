#include "global.h"
#include "gba/m4a_internal.h"
//#include "intro.h"
//#include "data2.h"
#include "decompress.h"
#include "hall_of_fame.h"
//#include "intro_credits_graphics.h"
//#include "libgncmultiboot.h"
#include "link.h"
#include "m4a.h"
#include "main.h"
#include "new_game.h"
#include "palette.h"
#include "random.h"
#include "save.h"
#include "constants/songs.h"
#include "sound.h"
#include "constants/species.h"
#include "task.h"
#include "title_screen.h"
#include "trig.h"
#include "scanline_effect.h"
//#include "ewram.h"

// * new RSTN stuff/default intro stuff brought in
#include "rs_intro.h"
#include "rs_intro_credits_graphics.h"
#include "graphics.h"
#include "gpu_regs.h"
#include "malloc.h"
#include "constants/rgb.h"
#include "libgcnmultiboot.h" // lol
#include "multiboot_pokemon_colosseum.h"
#include "data.h"
#include "load_save.h"
#include "expansion_intro.h"
#include "battle_anim.h"
#include "dma3.h"

#define COLOSSEUM_GAME_CODE 0x65366347 // "Gc6e" in ASCII

#define GFXTAG_DROPS_LOGO 2000
#define PALTAG_DROPS      2000
#define PALTAG_LOGO       2001
#define TAG_EON_SILHOUETTE 2002
#define TAG_RAYQUAZA_ORB      2003
// * end RSTN stuff


extern struct SpriteTemplate gMultiuseSpriteTemplate;
extern u16 gSaveFileStatus;
extern u8 gReservedSpritePaletteCount;
extern const u16 gIntroCopyright_Pal[];
extern const u32 gIntroCopyright_Tilemap[];

static EWRAM_DATA u16 sIntroCharacterGender = 0;
static EWRAM_DATA u16 gUnknown_0203931A = 0;

// TODO_RSTN probably remove these in place of the normal ones (may need to ensure they aren't used anywhere else)
u32 gRSIntroFrameCounter;
struct GcmbStruct gRSMultibootProgramStruct;

//--------------------------------------------------
// Graphics Data
//--------------------------------------------------

static const u32 gIntro1BG0_Tilemap[] = INCBIN_U32("graphics/rstoration/intro/intro1_bg0_map.bin.lz");
static const u32 gIntro1BG1_Tilemap[] = INCBIN_U32("graphics/rstoration/intro/intro1_bg1_map.bin.lz");
static const u32 gIntro1BG2_Tilemap[] = INCBIN_U32("graphics/rstoration/intro/intro1_bg2_map.bin.lz");
static const u32 gIntro1BG3_Tilemap[] = INCBIN_U32("graphics/rstoration/intro/intro1_bg3_map.bin.lz");
static const u32 gIntro1BGLeavesGfx[] = INCBIN_U32("graphics/rstoration/intro/introgfx.4bpp.lz");
static const u16 gIntro1BGPals[][16] =
{
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal1.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal2.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal3.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal4.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal5.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal6.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal7.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal8.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal9.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal10.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal11.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal12.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal13.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal14.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal15.gbapal"),
    INCBIN_U16("graphics/rstoration/intro/intro1_bgpal16.gbapal"),
};

static const u16 gIntro1EonPalette[] = INCBIN_U16("graphics/rstoration/intro/intro1_eon.gbapal");
static const u32 gIntro1EonTiles[] = INCBIN_U32("graphics/rstoration/intro/intro1_eon.4bpp.lz");
static const u16 gIntroDrops_Pal[] = INCBIN_U16("graphics/rstoration/intro/unknown1.gbapal");
static const u16 gIntroLogo_Pal[] = INCBIN_U16("graphics/rstoration/intro/unknown2.gbapal");
static const u32 gIntroTiles[] = INCBIN_U32("graphics/rstoration/intro/intro.4bpp.lz");

static const struct OamData gOamData_WaterDrop =
{
    .y = 160,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 2,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
static const union AnimCmd gSpriteAnim_WaterDrop0[] =
{
    ANIMCMD_FRAME(16, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_WaterDrop1[] =
{
    ANIMCMD_FRAME(24, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_WaterDrop2[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_WaterDrop3[] =
{
    ANIMCMD_FRAME(48, 8),
    ANIMCMD_END,
};
static const union AnimCmd *const gSpriteAnimTable_WaterDrop[] =
{
    gSpriteAnim_WaterDrop0,
    gSpriteAnim_WaterDrop1,
    gSpriteAnim_WaterDrop2,
    gSpriteAnim_WaterDrop3,
};
static void SpriteCB_WaterDrop(struct Sprite *sprite);
static const struct SpriteTemplate gSpriteTemplate_WaterDrop =
{
    .tileTag = GFXTAG_DROPS_LOGO,
    .paletteTag = PALTAG_DROPS,
    .oam = &gOamData_WaterDrop,
    .anims = gSpriteAnimTable_WaterDrop,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_WaterDrop,
};
static const union AnimCmd Unknown_40AE38[] =
{
    ANIMCMD_FRAME(0, 4),
    ANIMCMD_FRAME(64, 4),
    ANIMCMD_FRAME(128, 4),
    ANIMCMD_FRAME(192, 4),
    ANIMCMD_JUMP(0),
};
static const union AnimCmd Unknown_40AE4C[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(64, 8),
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_FRAME(192, 8),
    ANIMCMD_JUMP(0),
};
static const union AnimCmd Unknown_40AE60[] =
{
    ANIMCMD_FRAME(256, 4),
    ANIMCMD_FRAME(0x140, 4),
    ANIMCMD_FRAME(0x180, 4),
    ANIMCMD_END,
};
static const union AnimCmd Unknown_40AE70[] =
{
    ANIMCMD_FRAME(0x180, 16),
    ANIMCMD_FRAME(0x140, 16),
    ANIMCMD_FRAME(256, 16),
    ANIMCMD_END,
};
static const union AnimCmd *const gUnknown_0840AE80[] =
{
    Unknown_40AE38,
    Unknown_40AE4C,
    Unknown_40AE60,
    Unknown_40AE70,
};
static const struct OamData gOamData_GameFreakLetter =
{
    .y = 160,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 1,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
static const struct OamData gOamData_PresentsLetter =
{
    .y = 160,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 0,
    .x = 0,
    .matrixNum = 0,
    .size = 0,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
static const struct OamData gOamData_GameFreakLogo =
{
    .y = 160,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 2,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
static const union AnimCmd gSpriteAnim_840AEA8[] =
{
    ANIMCMD_FRAME(80, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEB0[] =
{
    ANIMCMD_FRAME(84, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEB8[] =
{
    ANIMCMD_FRAME(88, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEC0[] =
{
    ANIMCMD_FRAME(92, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEC8[] =
{
    ANIMCMD_FRAME(96, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AED0[] =
{
    ANIMCMD_FRAME(100, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AED8[] =
{
    ANIMCMD_FRAME(104, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEE0[] =
{
    ANIMCMD_FRAME(112, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEE8[] =
{
    ANIMCMD_FRAME(113, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEF0[] =
{
    ANIMCMD_FRAME(114, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AEF8[] =
{
    ANIMCMD_FRAME(115, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AF00[] =
{
    ANIMCMD_FRAME(116, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AF08[] =
{
    ANIMCMD_FRAME(117, 8),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_840AF10[] =
{
    ANIMCMD_FRAME(128, 8),
    ANIMCMD_END,
};
static const union AnimCmd *const gSpriteAnimTable_GameFreakLetter[] =
{
    gSpriteAnim_840AEA8,
    gSpriteAnim_840AEB0,
    gSpriteAnim_840AEB8,
    gSpriteAnim_840AEC0,
    gSpriteAnim_840AEC8,
    gSpriteAnim_840AED0,
    gSpriteAnim_840AED8,
};
static const union AnimCmd *const gSpriteAnimTable_PresentsLetter[] =
{
    gSpriteAnim_840AEE0,
    gSpriteAnim_840AEE8,
    gSpriteAnim_840AEF0,
    gSpriteAnim_840AEF8,
    gSpriteAnim_840AF00,
    gSpriteAnim_840AF08,
};
static const union AnimCmd *const gSpriteAnimTable_GameFreakLogo[] =
{
    gSpriteAnim_840AF10,
};
static const s16 gUnknown_0840AF50[][2] =
{
    {0, -72},
    {1, -56},
    {2, -40},
    {3, -24},
    {4, 8},
    {5, 24},
    {3, 40},
    {1, 56},
    {6, 72},
};
static const s16 gUnknown_0840AF74[][2] =
{
    {0, -28},
    {1, -20},
    {2, -12},
    {3, -4},
    {2, 4},
    {4, 12},
    {5, 20},
    {3, 28},
};
static void SpriteCB_LogoLetter(struct Sprite *sprite);
static const struct SpriteTemplate gSpriteTemplate_GameFreakLetter =
{
    .tileTag = GFXTAG_DROPS_LOGO,
    .paletteTag = PALTAG_LOGO,
    .oam = &gOamData_GameFreakLetter,
    .anims = gSpriteAnimTable_GameFreakLetter,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_LogoLetter,
};
static const struct SpriteTemplate gSpriteTemplate_PresentsLetter =
{
    .tileTag = GFXTAG_DROPS_LOGO,
    .paletteTag = PALTAG_LOGO,
    .oam = &gOamData_PresentsLetter,
    .anims = gSpriteAnimTable_PresentsLetter,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_LogoLetter,
};
static const struct SpriteTemplate gSpriteTemplate_GameFreakLogo =
{
    .tileTag = GFXTAG_DROPS_LOGO,
    .paletteTag = PALTAG_LOGO,
    .oam = &gOamData_GameFreakLogo,
    .anims = gSpriteAnimTable_GameFreakLogo,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_LogoLetter,
};
static const struct OamData gOamData_EonSilhouette =
{
    .y = 160,
    .affineMode = 0,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = 1,
    .x = 0,
    .matrixNum = 0,
    .size = 3,
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0,
};
static const union AnimCmd gSpriteAnim_EonSilhouette[] =
{
    ANIMCMD_FRAME(0, 10),
    ANIMCMD_JUMP(0),
};
static const union AnimCmd *const gSpriteAnimTable_EonSilhouette[] =
{
    gSpriteAnim_EonSilhouette,
};
static void SpriteCB_EonSilhouette(struct Sprite *sprite);
static const struct SpriteTemplate gSpriteTemplate_EonSilhouette =
{
    .tileTag = 2002,
    .paletteTag = 2002,
    .oam = &gOamData_EonSilhouette,
    .anims = gSpriteAnimTable_EonSilhouette,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_EonSilhouette,
};

// gUnknown_0840B008
const struct CompressedSpriteSheet sSpriteSheet_WaterDropsAndLogo[] =
{
    {gIntroTiles, 0x1400, GFXTAG_DROPS_LOGO},
    {},
};

// gUnknown_0840B018
const struct CompressedSpriteSheet sSpriteSheet_EonSilhouette[] =
{
    // * gIntro1EonTiles
    {gIntro1EonTiles, 0x400, TAG_EON_SILHOUETTE},
    {},
};

// gUnknown_0840B028
const struct SpritePalette sSpritePalettes_Intro1[] =
{
    {gIntroDrops_Pal, PALTAG_DROPS}, // Palette_406340
    {gIntroLogo_Pal, PALTAG_LOGO}, // Palette_406360
    {gIntro1EonPalette, 2002},
    {},
};

static void MainCB2_RSEndIntro(void);
void Task_IntroLoadPart1Graphics(u8);
static void Task_IntroFadeIn(u8);
static void Task_IntroWaterDrops(u8);
static void Task_IntroScrollDownAndShowEon(u8);
static void Task_IntroWaitToSetupPart2(u8);
static void Task_IntroLoadPart2Graphics(u8);
static void Task_IntroStartBikeRide(u8);
static void Task_IntroHandleBikeAndEonMovement(u8);
static void Task_IntroWaitToSetupPart3(u8);
static void Task_IntroLoadPart3Graphics(u8);
static void Task_IntroSpinAndZoomPokeball(u8);
static void Task_GoToTitleScreen(u8);
static void IntroResetGpuRegs(void);
static void Task_CreateSparkles(u8);
static void SpriteCB_WaterDrop_Slide(struct Sprite *);
static void SpriteCB_WaterDrop_ReachLeafEnd(struct Sprite *);
static void SpriteCB_WaterDrop_DangleFromLeaf(struct Sprite *);
static void SpriteCB_WaterDrop_Fall(struct Sprite *);
static u8 CreateWaterDrop(s16, s16, u16, u16, u16, u8);
static void SpriteCB_PlayerOnBicycle(struct Sprite *);
static void SpriteCB_Eon(struct Sprite *);
static u8 CreateGameFreakLogo(s16, s16, u8);

static void VBlankCB_RSIntro(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void MainCB2_RSIntro(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    if (gMain.newKeys && !gPaletteFade.active)
        SetMainCallback2(MainCB2_RSEndIntro);
    else if (gRSIntroFrameCounter != -1)
        gRSIntroFrameCounter++;
}

static void MainCB2_RSEndIntro(void)
{
    if (!UpdatePaletteFade())
        SetMainCallback2(CB2_InitTitleScreen);
}

const u32 sIntroCopyright_Gfx[] = INCBIN_U32("graphics/rstoration/intro/copyright.4bpp.lz");

static void RSLoadCopyrightGraphics(u16 tilesetAddress, u16 tilemapAddress, u16 paletteOffset)
{
    LZ77UnCompVram(sIntroCopyright_Gfx, (void *)(VRAM + tilesetAddress));
    LZ77UnCompVram(gIntroCopyright_Tilemap, (void *)(VRAM + tilemapAddress));
    LoadPalette(gIntroCopyright_Pal, paletteOffset, PLTT_SIZE_4BPP);
}

static void SerialCB_CopyrightScreen(void)
{
    GameCubeMultiBoot_HandleSerialInterrupt(&gRSMultibootProgramStruct);
}

static u8 RSSetUpCopyrightScreen(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        *(u16 *)PLTT = RGB_WHITE;
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        CpuFill32(0, (void *)VRAM, VRAM_SIZE);
        CpuFill32(0, (void *)OAM, OAM_SIZE);
        CpuFill16(0, (void *)(PLTT + 2), PLTT_SIZE - 2);
        ResetPaletteFade();
        RSLoadCopyrightGraphics(0, 0x3800, BG_PLTT_ID(0));
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_WHITEALPHA);
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0)
                                   | BGCNT_CHARBASE(0)
                                   | BGCNT_SCREENBASE(7)
                                   | BGCNT_16COLOR
                                   | BGCNT_TXT256x256);
        EnableInterrupts(INTR_FLAG_VBLANK);
        SetVBlankCallback(VBlankCB_RSIntro);
        REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON;
        SetSerialCallback(SerialCB_CopyrightScreen);
        GameCubeMultiBoot_Init(&gRSMultibootProgramStruct);
    default:
        UpdatePaletteFade();
        gMain.state++;
        GameCubeMultiBoot_Main(&gRSMultibootProgramStruct);
        break;
    case 140:
        GameCubeMultiBoot_Main(&gRSMultibootProgramStruct);
        if (gRSMultibootProgramStruct.gcmb_field_2 != 1)
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB(0, 0, 0));
            gMain.state++;
        }
        break;
    case 141:
        if (UpdatePaletteFade())
            break;
        // TODO_RSTN add expansion intro here
        CreateTask(Task_IntroLoadPart1Graphics, 0);
        SetMainCallback2(MainCB2_RSIntro);
        if (gRSMultibootProgramStruct.gcmb_field_2 != 0)
        {
            if (gRSMultibootProgramStruct.gcmb_field_2 == 2)
            {
                // check the multiboot ROM header game code to see if we already did this
                if (*(u32 *)(EWRAM_START + 0xAC) == COLOSSEUM_GAME_CODE)
                {
                    CpuCopy16(&gMultiBootProgram_PokemonColosseum_Start, (void *)EWRAM_START, sizeof(gMultiBootProgram_PokemonColosseum_Start));
                    *(u32 *)(EWRAM_START + 0xAC) = COLOSSEUM_GAME_CODE;
                }
                GameCubeMultiBoot_ExecuteProgram(&gRSMultibootProgramStruct);
            }
        }
        else
        {
            GameCubeMultiBoot_Quit();
            SetSerialCallback(SerialCB);
        }
        return 0;
    }

    return 1;
}

void CB2_RSInitCopyrightScreenAfterBootup(void)
{
    if (!RSSetUpCopyrightScreen())
    {
        SetSaveBlocksPointers(GetSaveBlocksPointersBaseOffset());
        ResetMenuAndMonGlobals();
        Save_ResetSaveCounters();
        LoadGameSave(SAVE_NORMAL);
        if (gSaveFileStatus == SAVE_STATUS_EMPTY || gSaveFileStatus == SAVE_STATUS_CORRUPT)
            Sav2_ClearSetDefault();
        SetPokemonCryStereo(gSaveBlock2Ptr->optionsSound);
        InitHeap(gHeap, HEAP_SIZE);
    }
}

void CB2_RSInitCopyrightScreenAfterTitleScreen(void)
{
    RSSetUpCopyrightScreen();
}

void Task_IntroLoadPart1Graphics(u8 taskId)
{
    SetVBlankCallback(NULL);
    sIntroCharacterGender = Random() & 1;
    IntroResetGpuRegs();
    // intro_reset_and_hide_bgs();
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 80);
    SetGpuReg(REG_OFFSET_BG1VOFS, 24);
    SetGpuReg(REG_OFFSET_BG0VOFS, 40);
    LZ77UnCompVram(gIntro1BGLeavesGfx, (void *)VRAM); // * gIntro1BGLeavesGfx
    LZ77UnCompVram(gIntro1BG0_Tilemap, (void *)(BG_CHAR_ADDR(2))); // * gIntro1BG0_Tilemap
    DmaClear16(3, BG_SCREEN_ADDR(17), BG_SCREEN_SIZE);
    LZ77UnCompVram(gIntro1BG1_Tilemap, (void *)(VRAM + 0x9000)); // * gIntro1BG1_Tilemap
    DmaClear16(3, BG_SCREEN_ADDR(19), BG_SCREEN_SIZE);
    LZ77UnCompVram(gIntro1BG2_Tilemap, (void *)(VRAM + 0xA000)); // * gIntro1BG2_Tilemap
    DmaClear16(3, BG_SCREEN_ADDR(21), BG_SCREEN_SIZE);
    LZ77UnCompVram(gIntro1BG3_Tilemap, (void *)(VRAM + 0xB000)); // * gIntro1BG3_Tilemap
    DmaClear16(3, BG_SCREEN_ADDR(23), BG_SCREEN_SIZE);
    LoadPalette(gIntro1BGPals, 0, sizeof(gIntro1BGPals)); // * gIntro1BGPals
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 80);
    SetGpuReg(REG_OFFSET_BG1VOFS, 24);
    SetGpuReg(REG_OFFSET_BG0VOFS, 40);
    SetGpuReg(REG_OFFSET_BG3CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(22) | BGCNT_16COLOR | BGCNT_TXT256x512);
    SetGpuReg(REG_OFFSET_BG2CNT, BGCNT_PRIORITY(2) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(20) | BGCNT_16COLOR | BGCNT_TXT256x512);
    SetGpuReg(REG_OFFSET_BG1CNT, BGCNT_PRIORITY(1) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(18) | BGCNT_16COLOR | BGCNT_TXT256x512);
    SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(16) | BGCNT_16COLOR | BGCNT_TXT256x512);
    LoadCompressedSpriteSheet(&sSpriteSheet_WaterDropsAndLogo[0]); // WaterDropsAndLogo?
    LoadCompressedSpriteSheet(&sSpriteSheet_EonSilhouette[0]); // FlygonSilhouette?
    LoadSpritePalettes(sSpritePalettes_Intro1);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x1F0, 0x20);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x1E1, 0x1E);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x1D2, 0x1C);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x1C3, 0x1A);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x1B4, 0x18);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x1A5, 0x16);
    CpuCopy16(gPlttBufferUnfaded + 0x100, gPlttBufferUnfaded + 0x196, 0x14);
    gTasks[taskId].data[0] = CreateWaterDrop(236, -14, 0x200, 1, 0x78, FALSE);
    gTasks[taskId].func = Task_IntroFadeIn;
}

static void Task_IntroFadeIn(u8 taskId)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB(0, 0, 0));
    SetVBlankCallback(VBlankCB_RSIntro);
    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG_ALL_ON | DISPCNT_OBJ_ON;
    gTasks[taskId].func = Task_IntroWaterDrops;
    gRSIntroFrameCounter = 0;
    m4aSongNumStart(0x19E);
    ResetSerial();
}

static void Task_IntroWaterDrops(u8 taskId)
{
    //start moving rock
    if (gRSIntroFrameCounter == 76)
        gSprites[gTasks[taskId].data[0]].data[0] = 1;

    //drop rock
    if (gRSIntroFrameCounter == 251)
        gSprites[gTasks[taskId].data[0]].data[0] = 2;

    if (gRSIntroFrameCounter == 368)
        CreateWaterDrop(48, 0, 0x400, 5, 0x70, TRUE);
    if (gRSIntroFrameCounter == 384)
        CreateWaterDrop(200, 60, 0x400, 9, 0x80, TRUE);

    if (gRSIntroFrameCounter == 560)
        CreateGameFreakLogo(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, CreateTask(Task_CreateSparkles, 0));

    if (gRSIntroFrameCounter > 739)
    {
        gTasks[taskId].data[1] = 0x50;
        gTasks[taskId].data[2] = 0;
        gTasks[taskId].data[3] = 0x18;
        gTasks[taskId].data[4] = 0;
        gTasks[taskId].data[5] = 0x28;
        gTasks[taskId].data[6] = 0;
        gTasks[taskId].func = Task_IntroScrollDownAndShowEon;
    }
}

static void Task_IntroScrollDownAndShowEon(u8 taskId)
{
    if (gRSIntroFrameCounter < 904)
    {
        s32 r2;

        //slide backgrounds downward
        r2 = (gTasks[taskId].data[1] << 16) + (u16)gTasks[taskId].data[2] - 0xC000;
        gTasks[taskId].data[1] = r2 >> 16;
        gTasks[taskId].data[2] = r2;
        REG_BG2VOFS = gTasks[taskId].data[1];
        r2 = (gTasks[taskId].data[3] << 16) + (u16)gTasks[taskId].data[4] - 0x10000;
        gTasks[taskId].data[3] = r2 >> 16;
        gTasks[taskId].data[4] = r2;
        REG_BG1VOFS = gTasks[taskId].data[3];
        r2 = (gTasks[taskId].data[5] << 16) + (u16)gTasks[taskId].data[6] - 0x18000;
        gTasks[taskId].data[5] = r2 >> 16;
        gTasks[taskId].data[6] = r2;
        REG_BG0VOFS = gTasks[taskId].data[5];

        //show Lati@s sprite
        if (gRSIntroFrameCounter == 880)
        {
            u8 spriteId = CreateSprite(&gSpriteTemplate_EonSilhouette, 200, 160, 10);

            gSprites[spriteId].invisible = TRUE;
        }
    }
    else
    {
        //fade to white
        if (gRSIntroFrameCounter > 1007)
        {
            BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_WHITEALPHA);
            gTasks[taskId].func = Task_IntroWaitToSetupPart2;
        }
    }
}

static void Task_IntroWaitToSetupPart2(u8 taskId)
{
    if (gRSIntroFrameCounter > 1026)
        gTasks[taskId].func = Task_IntroLoadPart2Graphics;
}

static void Task_IntroLoadPart2Graphics(u8 taskId)
{
    IntroResetGpuRegs();
    SetVBlankCallback(NULL);
    ResetSpriteData();
    FreeAllSpritePalettes();
    gIntroCredits_RSTN_MovingSceneryVBase = 0;
    gIntroCredits_RSTN_MovingSceneryVOffset = 0;
#ifdef SAPPHIRE
    RSTN_LoadIntroPart2Graphics(0);
#else
    RSTN_LoadIntroPart2Graphics(1);
#endif
    gTasks[taskId].func = Task_IntroStartBikeRide;
}

static void Task_IntroStartBikeRide(u8 taskId)
{
    u8 spriteId;

    // TODO_RSTN check these for the look back sprites probably, other changes

    if (sIntroCharacterGender == 0)
        LoadCompressedSpriteSheet(gSpriteSheet_RSTN_IntroBrendan); // TODO_RSTN gIntro2BrendanSpriteSheet
    else
        LoadCompressedSpriteSheet(gSpriteSheet_RSTN_IntroMay); // TODO_RSTN gIntro2MaySpriteSheet
    LoadCompressedSpriteSheet(gSpriteSheet_RSTN_IntroBicycle); // TODO_RSTN gIntro2BicycleSpriteSheet
#ifdef SAPPHIRE
    LoadCompressedSpriteSheet(gSpriteSheet_RSTN_IntroFlygon); // TODO_RSTN gIntro2LatiasSpriteSheet
#else
    LoadCompressedSpriteSheet(gSpriteSheet_RSTN_IntroFlygon); // TODO_RSTN gIntro2LatiosSpriteSheet
#endif
    LoadSpritePalettes(gSpritePalettes_RSTN_IntroPlayerFlygon); // TODO_RSTN gIntro2SpritePalettes
    if (sIntroCharacterGender == 0)
        spriteId = RSTN_CreateIntroBrendanSprite(0x110, 100);
    else
        spriteId = RSTN_CreateIntroMaySprite(0x110, 100);
    gSprites[spriteId].callback = SpriteCB_PlayerOnBicycle;
    gSprites[spriteId].anims = gUnknown_0840AE80;
    gTasks[taskId].data[1] = spriteId;
#ifdef SAPPHIRE
    spriteId = RSTN_CreateIntroFlygonSprite_Unused(-0x40, 0x3C); // TODO_RSTN intro_create_latias_sprite
#else
    spriteId = RSTN_CreateIntroFlygonSprite(-0x40, 0x3C); // TODO_RSTN intro_create_latios_sprite
#endif
    gSprites[spriteId].callback = SpriteCB_Eon;
    gTasks[taskId].data[2] = spriteId;
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_WHITEALPHA);
    SetVBlankCallback(VBlankCB_RSIntro);
#ifdef SAPPHIRE
    gTasks[taskId].data[0] = RSTN_CreateBicycleBgAnimationTask(0, 0x4000, 0x40, 0x10);
    RSTN_SetIntroPart2BgCnt(0);
#else
    gTasks[taskId].data[0] = RSTN_CreateBicycleBgAnimationTask(1, 0x4000, 0x400, 0x10);
    RSTN_SetIntroPart2BgCnt(1);
#endif
    gTasks[taskId].func = Task_IntroHandleBikeAndEonMovement;
}

static void Task_IntroHandleBikeAndEonMovement(u8 taskId)
{
    s16 a;
    u16 sine;

    if (gRSIntroFrameCounter > 1823)
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 16, 0, 16, RGB_WHITEALPHA);
        gTasks[taskId].func = Task_IntroWaitToSetupPart3;
    }
    if (gRSIntroFrameCounter == 1109)
        gSprites[gTasks[taskId].data[1]].data[0] = 1;
    if (gRSIntroFrameCounter == 1214)
        gSprites[gTasks[taskId].data[1]].data[0] = 0;
    if (gRSIntroFrameCounter == 1394)
        gSprites[gTasks[taskId].data[2]].data[0] = 1;
    if (gRSIntroFrameCounter == 1398)
        gSprites[gTasks[taskId].data[1]].data[0] = 2;
    if (gRSIntroFrameCounter == 1586)
        gSprites[gTasks[taskId].data[1]].data[0] = 3;
    if (gRSIntroFrameCounter == 1727)
        gSprites[gTasks[taskId].data[1]].data[0] = 4;

    //TODO: Clean this up
    a = (((u16)gTasks[taskId].data[3] << 16) >> 18) & 0x7F;
    sine = Sin(a, 48);
    gIntroCredits_RSTN_MovingSceneryVOffset = sine;
    if (gTasks[taskId].data[3] < 512)
        gTasks[taskId].data[3]++;
#ifdef SAPPHIRE
    RSTN_CycleSceneryPalette(0);
#else
    RSTN_CycleSceneryPalette(1);
#endif
}

static void Task_IntroWaitToSetupPart3(u8 taskId)
{
    if (gRSIntroFrameCounter > 2068)
    {
        DestroyTask(gTasks[taskId].data[0]);
        gTasks[taskId].func = Task_IntroLoadPart3Graphics;
        
    }
}

static void Task_IntroLoadPart3Graphics(u8 taskId)
{
    IntroResetGpuRegs();
    LZ77UnCompVram(gIntroPokeball_Gfx, (void *)VRAM);
    LZ77UnCompVram(gIntroPokeball_Tilemap, (void *)(BG_CHAR_ADDR(1)));
    LoadPalette(gIntroPokeball_Pal, BG_PLTT_ID(0), 0x200);
    gTasks[taskId].data[0] = 0;
    gTasks[taskId].data[1] = 0;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[3] = 0;
    PanFadeAndZoomScreen(0x78, 0x50, 0, 0);
    ResetSpriteData();
    FreeAllSpritePalettes();
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_WHITEALPHA);
    REG_BG2CNT = BGCNT_PRIORITY(3) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(8) | BGCNT_256COLOR | BGCNT_AFF256x256;
    REG_DISPCNT = DISPCNT_MODE_1 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG2_ON | DISPCNT_OBJ_ON;
    gTasks[taskId].func = Task_IntroSpinAndZoomPokeball;
    gRSIntroFrameCounter = 0;
    m4aSongNumStart(0x1BA);
}

static void Task_IntroSpinAndZoomPokeball(u8 taskId)
{
    gTasks[taskId].data[0] += 0x400;
    if (gTasks[taskId].data[1] <= 0x6BF)
    {
        gTasks[taskId].data[1] += gTasks[taskId].data[2];
        gTasks[taskId].data[2]++; // * += 2 in emerald?
    }
    else
    {
        // TODO_RSTN: go to intro 3
        gTasks[taskId].func = Task_GoToTitleScreen; // * Task_Scene3_WaitGroudon
    }

    PanFadeAndZoomScreen(0x78, 0x50, 0x10000 / gTasks[taskId].data[1], gTasks[taskId].data[0]);
    
    if (gRSIntroFrameCounter == 44) // * TIMER_POKEBALL_FADE, 28 instead
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
}

static void Task_GoToTitleScreen(u8 taskId)
{
    DestroyTask(taskId);
    SetMainCallback2(MainCB2_RSEndIntro);
}

static void IntroResetGpuRegs(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3HOFS, 0);
    SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    SetGpuReg(REG_OFFSET_BG2HOFS, 0);
    SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    SetGpuReg(REG_OFFSET_BG1HOFS, 0);
    SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    SetGpuReg(REG_OFFSET_BG0HOFS, 0);
    SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

// sub_813CCE8
static void Task_CreateSparkles(u8 taskId)
{
    switch (gTasks[taskId].data[0])
    {
    default:
    case 0:
        SetGpuReg(REG_OFFSET_BLDCNT, 0x3F50);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0x1000);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        gTasks[taskId].data[1] = 0x40;
        gTasks[taskId].data[0] = 1;
        break;
    case 1:
        if (gTasks[taskId].data[1] != 0)
        {
            u8 foo;

            gTasks[taskId].data[1]--;
            foo = gTasks[taskId].data[1] / 2;
            SetGpuReg(REG_OFFSET_BLDALPHA, gTitleScreenAlphaBlend[foo]);
        }
        else
        {
            SetGpuReg(REG_OFFSET_BLDALPHA, gTitleScreenAlphaBlend[0]);
            gTasks[taskId].data[1] = 0x80;
            gTasks[taskId].data[0]++;
        }
        break;
    case 2:
        if (gTasks[taskId].data[1] != 0)
        {
            //tail merge at _0813CE0E
            gTasks[taskId].data[1]--;
        }
        else
        {
            gTasks[taskId].data[1] = 0;  //redundant?
            gTasks[taskId].data[0]++;
        }
        break;
    case 3:
        if (gTasks[taskId].data[1] <= 0x3D)
        {
            u8 foo;

            gTasks[taskId].data[1]++;
            foo = gTasks[taskId].data[1] / 2;
            SetGpuReg(REG_OFFSET_BLDALPHA, gTitleScreenAlphaBlend[foo]);
        }
        else
        {
            //_0813CDE0
            SetGpuReg(REG_OFFSET_BLDALPHA, gTitleScreenAlphaBlend[0x1F]);
            gTasks[taskId].data[1] = 0x10;
            gTasks[taskId].data[0]++;
        }
        break;
    case 4:
        if (gTasks[taskId].data[1] != 0)
        {
            gTasks[taskId].data[1]--;
        }
        else
        {
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            DestroyTask(taskId);
        }
        break;
    }
}

static const union AnimCmd gSpriteAnim_81E7C44[] =
{
    ANIMCMD_FRAME(0, 0),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_81E7C4C[] =
{
    ANIMCMD_FRAME(1, 0),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_81E7C54[] =
{
    ANIMCMD_FRAME(2, 0),
    ANIMCMD_END,
};
static const union AnimCmd gSpriteAnim_81E7C5C[] =
{
    ANIMCMD_FRAME(3, 0),
    ANIMCMD_END,
};

const union AnimCmd *const gSpriteAnimTable_81E7C64[] =
{
    gSpriteAnim_81E7C44,
    gSpriteAnim_81E7C4C,
    gSpriteAnim_81E7C54,
    gSpriteAnim_81E7C5C
};

static void SpriteCB_WaterDrop_Ripple(struct Sprite *sprite)
{
    u8 r0;

    if (sprite->data[2] >= 192)
    {
        if (sprite->data[3] != 0)
        {
            sprite->data[3]--;
        }
        else
        {
            sprite->invisible = FALSE;
            SetOamMatrix(sprite->data[1], sprite->data[2], 0, 0, sprite->data[2]);
            sprite->data[2] = (sprite->data[2] * 95) / 100;
            r0 = (sprite->data[2] - 192) / 128 + 9;
            if (r0 > 15)
                r0 = 15;
            sprite->oam.paletteNum = r0;
        }
    }
    else
    {
        DestroySprite(sprite);
    }
}

// sub_813D158
static void SpriteCB_WaterDropHalf(struct Sprite *sprite)
{
    if (gSprites[sprite->data[7]].data[7] != 0)
    {
        sprite->invisible = TRUE;
        sprite->x += sprite->x2;
        sprite->y += sprite->y2;
        StartSpriteAnim(sprite, 3);
        sprite->data[2] = 1024;
        sprite->data[3] = 8 * (sprite->data[1] & 3);
        sprite->callback = SpriteCB_WaterDrop_Ripple;
        sprite->oam.shape = 1;
        sprite->oam.size = 3;
        CalcCenterToCornerVec(sprite, 1, 3, 2);
    }
    else
    {
        sprite->x2 = gSprites[sprite->data[7]].x2;
        sprite->y2 = gSprites[sprite->data[7]].y2;
        sprite->x = gSprites[sprite->data[7]].x;
        sprite->y = gSprites[sprite->data[7]].y;
    }
}

// sub_813D208
static void SpriteCB_WaterDrop(struct Sprite *sprite)
{
    if (sprite->data[0] != 0)
        sprite->callback = SpriteCB_WaterDrop_Slide;
}

// sub_813D220
static void SpriteCB_WaterDrop_Slide(struct Sprite *sprite)
{
    if (sprite->x <= 116)
    {
        sprite->y += sprite->y2;
        sprite->y2 = 0;
        sprite->x += 4;
        sprite->x2 = -4;
        sprite->data[4] = 128;
        sprite->callback = SpriteCB_WaterDrop_ReachLeafEnd;
    }
    else
    {
        u16 data2;
        u16 data3;
        u16 data4;
        s16 sin1;
        s16 sin2;
        s16 sin3;
        s16 sin4;
        s16 var1;
        s16 var2;
        s16 var3;
        s16 var4;
        s16 temp;

        data4 = sprite->data[4];
        sin1 = gSineTable[(u8)data4];
        sin2 = gSineTable[(u8)(data4 + 64)];
        sprite->data[4] += 2;
        sprite->y2 = sin1 / 32;
        sprite->x--;
        if (sprite->x & 1)
            sprite->y++;
        temp = -sin2 / 16;
        data2 = sprite->data[2];
        data3 = sprite->data[3];
        sin3 = gSineTable[(u8)(temp - 16)];
        sin4 = gSineTable[(u8)(temp + 48)];
        var1 = sin4 * data2 / 256;
        var2 = -sin3 * data3 / 256;
        var3 = sin3 * data2 / 256;
        var4 = sin4 * data3 / 256;
        SetOamMatrix(sprite->data[1], data2, 0, 0, data3);
        SetOamMatrix(sprite->data[1] + 1, var1, var3, var2, var4);
        SetOamMatrix(sprite->data[1] + 2, var1, var3, var2 * 2, var4 * 2);
    }
}

// sub_813D368
static void SpriteCB_WaterDrop_ReachLeafEnd(struct Sprite *sprite)
{
    SetOamMatrix(sprite->data[1], sprite->data[6] + 64, 0, 0, sprite->data[6] + 64);
    SetOamMatrix(sprite->data[1] + 1, sprite->data[6] + 64, 0, 0, sprite->data[6] + 64);
    SetOamMatrix(sprite->data[1] + 2, sprite->data[6] + 64, 0, 0, sprite->data[6] + 64);
    if (sprite->data[4] != 64)
    {
        u16 data4;

        sprite->data[4] -= 8;
        data4 = sprite->data[4];
        sprite->x2 = gSineTable[(u8)(data4 + 64)] / 64;
        sprite->y2 = gSineTable[(u8)data4] / 64;
    }
    else
    {
        sprite->data[4] = 0;
        sprite->callback = SpriteCB_WaterDrop_DangleFromLeaf;
    }
}

// sub_813D414
static void SpriteCB_WaterDrop_DangleFromLeaf(struct Sprite *sprite)
{
    if (sprite->data[0] != 2)
    {
        s16 r2;

        sprite->data[4] += 8;
        r2 = gSineTable[(u8)sprite->data[4]] / 16 + 64;
        sprite->x2 = gSineTable[(u8)(r2 + 64)] / 64;
        sprite->y2 = gSineTable[(u8)r2] / 64;
    }
    else
    {
        sprite->callback = SpriteCB_WaterDrop_Fall;
    }
}

static void SpriteCB_WaterDrop_Fall(struct Sprite *sprite)
{
    if (sprite->y < sprite->data[5])
    {
        sprite->y += 4;
    }
    else
    {
        sprite->data[7] = 1;
        sprite->invisible = TRUE;
        sprite->x += sprite->x2;
        sprite->y += sprite->y2;
        StartSpriteAnim(sprite, 3);
        sprite->data[2] = 1024;
        sprite->data[3] = 8 * (sprite->data[1] & 3);
        sprite->callback = SpriteCB_WaterDrop_Ripple;
        sprite->oam.shape = 1;
        sprite->oam.size = 3;
        CalcCenterToCornerVec(sprite, 1, 3, 2);
    }
}

static u8 CreateWaterDrop(s16 x, s16 y, u16 c, u16 d, u16 e, u8 fallImmediately)
{
    u8 spriteId;
    u8 oldSpriteId;

    spriteId = CreateSprite(&gSpriteTemplate_WaterDrop, x, y, 0);
    gSprites[spriteId].data[0] = 0;
    gSprites[spriteId].data[7] = 0;
    gSprites[spriteId].data[1] = d;
    gSprites[spriteId].data[2] = c;
    gSprites[spriteId].data[3] = c;
    gSprites[spriteId].data[5] = e;
    gSprites[spriteId].data[6] = c;
    gSprites[spriteId].oam.affineMode = 3;
    gSprites[spriteId].oam.matrixNum = d;
    CalcCenterToCornerVec(&gSprites[spriteId], 0, 2, 2);
    StartSpriteAnim(&gSprites[spriteId], 2);
    if (!fallImmediately)
        gSprites[spriteId].callback = SpriteCB_WaterDrop; // Do full anim, for 1st drop that slides along the leaf
    else
        gSprites[spriteId].callback = SpriteCB_WaterDrop_Fall; // Skip to drop falling into the water, for 2nd and 3rd drops
    oldSpriteId = spriteId;

    spriteId = CreateSprite(&gSpriteTemplate_WaterDrop, x, y, 0);
    gSprites[spriteId].data[7] = oldSpriteId;
    gSprites[spriteId].data[1] = d + 1;
    gSprites[spriteId].oam.affineMode = 3;
    gSprites[spriteId].oam.matrixNum = d + 1;
    CalcCenterToCornerVec(&gSprites[spriteId], 0, 2, 2);
    gSprites[spriteId].callback = SpriteCB_WaterDropHalf;

    spriteId = CreateSprite(&gSpriteTemplate_WaterDrop, x, y, 0);
    gSprites[spriteId].data[7] = oldSpriteId;
    gSprites[spriteId].data[1] = d + 2;
    StartSpriteAnim(&gSprites[spriteId], 1);
    gSprites[spriteId].oam.affineMode = 3;
    gSprites[spriteId].oam.matrixNum = d + 2;
    CalcCenterToCornerVec(&gSprites[spriteId], 0, 2, 2);
    gSprites[spriteId].callback = SpriteCB_WaterDropHalf;

    SetOamMatrix(d, c + 32, 0, 0, c + 32);
    SetOamMatrix(d + 1, c + 32, 0, 0, c + 32);
    SetOamMatrix(d + 2, c + 32, 0, 0, 2 * (c + 32));

    return oldSpriteId;
}

// sub_813D788
static void SpriteCB_PlayerOnBicycle(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        StartSpriteAnimIfDifferent(sprite, 0);
        sprite->x--;
        break;
    case 1:
        StartSpriteAnimIfDifferent(sprite, 0);
        if (gRSIntroFrameCounter & 7)
            return;
        sprite->x++;
        break;
    case 2:
        StartSpriteAnimIfDifferent(sprite, 2);
        if (sprite->x <= 120 || (gRSIntroFrameCounter & 7))
            sprite->x++;
        break;
    case 3:
        StartSpriteAnimIfDifferent(sprite, 3);
        break;
    case 4:
        StartSpriteAnimIfDifferent(sprite, 0);
        if (sprite->x > -32)
            sprite->x -= 2;
        break;
    }
    if (gRSIntroFrameCounter & 7)
        return;
    if (sprite->y2 != 0)
    {
        sprite->y2 = 0;
    }
    else
    {
        switch (Random() & 3)
        {
        case 0:
            sprite->y2 = -1;
            break;
        case 1:
            sprite->y2 = 1;
            break;
        case 2:
        case 3:
            sprite->y2 = 0;
            break;
        }
    }
}

static void SpriteCB_Eon(struct Sprite *sprite)
{
    switch (sprite->data[0])
    {
    case 0:
        break;
    case 1:
        if (sprite->x2 + sprite->x < 304)
            sprite->x2 += 8;
        else
            sprite->data[0] = 2;
        break;
    case 2:
        if (sprite->x2 + sprite->x > 120)
            sprite->x2 -= 1;
        else
            sprite->data[0] = 3;
        break;
    case 3:
        if (sprite->x2 > 0)
            sprite->x2 -= 2;
        break;
    }
    sprite->y2 = Sin((u8)sprite->data[1], 8) - gIntroCredits_RSTN_MovingSceneryVOffset;
    sprite->data[1] += 4;
}

static void SpriteCB_LogoLetter(struct Sprite *sprite)
{
    if (gTasks[sprite->data[0]].data[0] == 0)
    {
        sprite->invisible = TRUE;
    }
    else if (gTasks[sprite->data[0]].data[0] != 4)
    {
        sprite->invisible = FALSE;
    }
    else
    {
        DestroySprite(sprite);
    }
}

static u8 CreateGameFreakLogo(s16 a, s16 b, u8 c)
{
    u8 spriteId;
    u16 i;

    for (i = 0; i < 9; i++)
    {
        spriteId = CreateSprite(&gSpriteTemplate_GameFreakLetter, gUnknown_0840AF50[i][1] + a, b - 4, 0);
        gSprites[spriteId].data[0] = c;
        StartSpriteAnim(&gSprites[spriteId], gUnknown_0840AF50[i][0]);
    }
    for (i = 0; i < 8; i++)
    {
        spriteId = CreateSprite(&gSpriteTemplate_PresentsLetter, gUnknown_0840AF74[i][1] + a, b + 12, 0);
        gSprites[spriteId].data[0] = c;
        StartSpriteAnim(&gSprites[spriteId], gUnknown_0840AF74[i][0]);
    }
    spriteId = CreateSprite(&gSpriteTemplate_GameFreakLogo, 120, b - 4, 0);
    gSprites[spriteId].data[0] = c;

    return spriteId;
}

// sub_813DA64
static void SpriteCB_EonSilhouette(struct Sprite *sprite)
{
    sprite->data[7]++;

    switch (sprite->data[0])
    {
    case 0:
    default:
        sprite->oam.affineMode = 3;
        sprite->oam.matrixNum = 1;
        CalcCenterToCornerVec(sprite, 1, 3, 3);
        sprite->invisible = FALSE;
        sprite->data[0] = 1;
        sprite->data[1] = 128;
        sprite->data[2] = -24;
        sprite->data[3] = 0;
        break;
    case 1:
    {
        s16 sin;
        s16 cos;
        s16 a;
        s16 b;
        s16 c;
        s16 d;

        if (sprite->data[3] < 0x50)
        {
            sprite->y2 = -Sin((u8)sprite->data[3], 0x78);
            sprite->x2 = -Sin((u8)sprite->data[3], 0x8C);
            if (sprite->data[3] > 64)
                sprite->oam.priority = 3;
        }
        sin = gSineTable[(u8)sprite->data[2]];
        cos = gSineTable[(u8)(sprite->data[2] + 64)];
        d =  cos * sprite->data[1] / 256;
        c = -sin * sprite->data[1] / 256;
        b =  sin * sprite->data[1] / 256;
        a  = cos * sprite->data[1] / 256;

        SetOamMatrix(1, a, b, c, d);

        if (sprite->data[1] < 0x100)
            sprite->data[1] += 8;
        else
            sprite->data[1] += 32;
        if (sprite->data[2] < 0x18)
            sprite->data[2] += 1;
        if (sprite->data[3] < 64)
            sprite->data[3] += 2;
        else if (!(sprite->data[7] & 3))
            sprite->data[3] += 1;
        break;
    }
    }
}