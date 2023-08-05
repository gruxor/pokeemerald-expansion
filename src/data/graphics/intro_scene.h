const u16 gIntroGameFreakTextFade_Pal[] = INCBIN_U16("graphics/intro/scene_1/text.gbapal"); // game freak text blue fade
const u16 gIntroPlayer_Pal[] = INCBIN_U16("graphics/intro/scene_2/player.gbapal");
const u16 gIntro3Bg_Pal[] = INCBIN_U16("graphics/intro/scene_3/bg.gbapal");
const u16 gIntroVolbeat_Pal[] = INCBIN_U16("graphics/intro/scene_2/volbeat.gbapal");
const u16 gIntroTorchic_Pal[] = INCBIN_U16("graphics/intro/scene_2/torchic.gbapal");
const u16 gIntroManectric_Pal[] = INCBIN_U16("graphics/intro/scene_2/manectric.gbapal");
const u16 gIntroFlygon_Pal[] = INCBIN_U16("graphics/intro/scene_2/flygon.gbapal");

const u32 gIntroVolbeat_Gfx[] = INCBIN_U32("graphics/intro/scene_2/volbeat.4bpp.lz");
const u32 gIntroTorchic_Gfx[] = INCBIN_U32("graphics/intro/scene_2/torchic.4bpp.lz");
const u32 gIntroManectric_Gfx[] = INCBIN_U32("graphics/intro/scene_2/manectric.4bpp.lz");
const u32 gIntroFlygon_Gfx[] = INCBIN_U32("graphics/intro/scene_2/flygon.4bpp.lz");
const u32 gIntroBrendan_Gfx[] = INCBIN_U32("graphics/intro/scene_2/brendan.4bpp.lz");
const u32 gIntroMay_Gfx[] = INCBIN_U32("graphics/intro/scene_2/may.4bpp.lz");

const u32 gIntroGroudon_Gfx[] = INCBIN_U32("graphics/intro/scene_3/groudon.8bpp.lz");
const u32 gIntroGroudon_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/groudon.bin.lz");

const u32 gIntroKyogre_Gfx[] = INCBIN_U32("graphics/intro/scene_3/kyogre.8bpp.lz");
const u32 gIntroKyogre_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/kyogre.bin.lz");

const u32 gIntroLegendBg_Gfx[] = INCBIN_U32("graphics/intro/scene_3/legend_bg.4bpp.lz"); // groudon/kyogre bg
const u32 gIntroGroudonBg_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/groudon_bg.bin.lz");
const u32 gIntroKyogreBg_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/kyogre_bg.bin.lz");

const u32 gIntroClouds_Gfx[] = INCBIN_U32("graphics/intro/scene_3/clouds.4bpp.lz");
const u32 gIntroCloudsLeft_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/clouds_left.bin.lz");
const u32 gIntroCloudsRight_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/clouds_right.bin.lz");
const u32 gIntroCloudsSun_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/clouds_sun.bin.lz");

const u32 gIntroLightning_Gfx[] = INCBIN_U32("graphics/intro/scene_3/lightning.4bpp.lz");
const u16 gIntroLightning_Pal[] = INCBIN_U16("graphics/intro/scene_3/lightning.gbapal");

const u32 gIntroRayquaza_Gfx[] = INCBIN_U32("graphics/intro/scene_3/rayquaza.4bpp.lz");
const u32 gIntroRayquaza_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/rayquaza.bin.lz");

const u32 gIntroUnused1_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/unused_1.bin.lz");
const u32 gIntroUnused2_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/unused_2.bin.lz");

const u32 gIntroRayquazaClouds_Gfx[] = INCBIN_U32("graphics/intro/scene_3/rayquaza_clouds.4bpp.lz");
const u32 gIntroRayquazaClouds_Tilemap[] = INCBIN_U32("graphics/intro/scene_3/rayquaza_clouds.bin.lz");

const u32 gIntroBubbles_Gfx[] = INCBIN_U32("graphics/intro/scene_3/bubbles.4bpp.lz");
const u16 gIntroBubbles_Pal[] = INCBIN_U16("graphics/intro/scene_3/bubbles.gbapal");

const u32 gIntroFlygonSilhouette_Gfx[] = INCBIN_U32("graphics/intro/scene_1/flygon.4bpp.lz");
const u32 gIntroSparkle_Gfx[] = INCBIN_U32("graphics/intro/scene_1/sparkle.4bpp.lz");

// TODO_RSTN clean up comments so these don't get accidentally remove, also refine config bc testing
// These are exposed by RSTN so that the variable names can be shared between both
// and for configuration purposes.
const u16 gIntroDrops_Pal[]            = INCBIN_U16("graphics/intro/scene_1/drops.gbapal");
const u16 gIntroLogo_Pal[]             = INCBIN_U16("graphics/intro/scene_1/logo.gbapal");
const u32 gIntroDropsLogo_Gfx[]        = INCBIN_U32("graphics/intro/scene_1/drops_logo.4bpp.lz");
const u16 gIntro1Bg_Pal[16][16]        = INCBIN_U16("graphics/intro/scene_1/bg.gbapal");
const u32 gIntro1Bg0_Tilemap[]         = INCBIN_U32("graphics/intro/scene_1/bg0_map.bin.lz");
const u32 gIntro1Bg1_Tilemap[]         = INCBIN_U32("graphics/intro/scene_1/bg1_map.bin.lz");
const u32 gIntro1Bg2_Tilemap[]         = INCBIN_U32("graphics/intro/scene_1/bg2_map.bin.lz");
const u32 gIntro1Bg3_Tilemap[]         = INCBIN_U32("graphics/intro/scene_1/bg3_map.bin.lz");
const u32 gIntro1Bg_Gfx[]              = INCBIN_U32("graphics/intro/scene_1/bg.4bpp.lz");
const u16 gIntroPokeball_Pal[]         = INCBIN_U16("graphics/intro/scene_3/pokeball.gbapal");
const u32 gIntroPokeball_Tilemap[]     = INCBIN_U32("graphics/intro/scene_3/pokeball_map.bin.lz");
const u32 gIntroPokeball_Gfx[]         = INCBIN_U32("graphics/intro/scene_3/pokeball.8bpp.lz");
const u16 gIntroStreaks_Pal[]          = INCBIN_U16("graphics/intro/scene_3/streaks.gbapal"); // Unused
const u32 gIntroStreaks_Gfx[]          = INCBIN_U32("graphics/intro/scene_3/streaks.4bpp.lz"); // Unused
const u32 gIntroStreaks_Tilemap[]      = INCBIN_U32("graphics/intro/scene_3/streaks_map.bin.lz"); // Unused
const u16 gIntroRayquzaOrb_Pal[]       = INCBIN_U16("graphics/intro/scene_3/rayquaza_orb.gbapal");
const u16 gIntroMisc_Pal[]             = INCBIN_U16("graphics/intro/scene_3/misc.gbapal"); // Unused
const u32 gIntroMisc_Gfx[]             = INCBIN_U32("graphics/intro/scene_3/misc.4bpp.lz"); // Rayquza orb, and misc unused gfx
const u16 gIntroFlygonSilhouette_Pal[] = INCBIN_U16("graphics/intro/scene_1/flygon.gbapal");
const u32 gIntroLati_Gfx[]             = INCBIN_U32("graphics/intro/scene_1/lati.4bpp.lz"); // Unused
