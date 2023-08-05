#ifndef GUARD_RSTN_INTRO_CREDITS_GRAPHICS_H
#define GUARD_RSTN_INTRO_CREDITS_GRAPHICS_H

// States for gIntroCredits_MovingSceneryState
enum {
    INTROCRED_SCENERY_NORMAL,
    INTROCRED_SCENERY_DESTROY,
    INTROCRED_SCENERY_FROZEN,
};

// Scenes for the Credits sequence
enum {
    SCENE_OCEAN_MORNING,
    SCENE_OCEAN_SUNSET,
    SCENE_FOREST_RIVAL_ARRIVE,
    SCENE_FOREST_CATCH_RIVAL,
    SCENE_CITY_NIGHT,
};

extern u16 gIntroCredits_RSTN_MovingSceneryVBase;
extern s16 gIntroCredits_RSTN_MovingSceneryVOffset;
extern s16 gIntroCredits_RSTN_MovingSceneryState;

extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_IntroBrendan[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_IntroMay[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_IntroBicycle[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_IntroFlygon[];
extern const struct SpritePalette gSpritePalettes_RSTN_IntroPlayerFlygon[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_CreditsBrendan[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_CreditsMay[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_CreditsBicycle[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_CreditsRivalBrendan[];
extern const struct CompressedSpriteSheet gSpriteSheet_RSTN_CreditsRivalMay[];
extern const struct SpritePalette gSpritePalettes_RSTN_Credits[];

void RSTN_LoadIntroPart2Graphics(u8 scenery);
void RSTN_SetIntroPart2BgCnt(u8 scenery);
void RSTN_LoadCreditsSceneGraphics(u8);
void RSTN_SetCreditsSceneBgCnt(u8);
u8 RSTN_CreateBicycleBgAnimationTask(u8 mode, u16 bg1Speed, u16 bg2Speed, u16 bg3Speed);
void RSTN_CycleSceneryPalette(u8);
u8 RSTN_CreateIntroBrendanSprite(s16 x, s16 y);
u8 RSTN_CreateIntroMaySprite(s16 x, s16 y);
u8 RSTN_CreateIntroFlygonSprite(s16 x, s16 y);
u8 RSTN_CreateIntroFlygonSprite_Unused(s16 x, s16 y);

#endif // GUARD_RSTN_INTRO_CREDITS_GRAPHICS_H
