#ifndef GUARD_RSTN_CONFIG
#define GUARD_RSTN_CONFIG

/*
    NOTE: All options default to FALSE.

    Some features only differ from Emerald and are the same between Ruby/Sapphire.
    Changes that only differ in Emerald are marked with an EM comment
    while three-version-differences are marked with an RS comment.
    Any options that are not yet implemented are marked with a TODO in their description.

    If your editor supports extensions that color-code comment tags such as TODO, !/?/*, etc.
    then I recommend using them. I use "Better Comments" for VSCode, but many editors have analogues.
*/

// Boolean for swapping game versions. No effect if options are FALSE.
// 0 = Ruby; 1 = Sapphire
#define RSTN_VERSION 0

// TODO Brendan/May Overworld Sprite Colors
// 0 = Emerald Green, 1 = R/S Red, 2 = Mandela Blue
// NOTE: Blue was never an outfit color in any of the 3 games, but many people misremember Sapphire as 
// having blue outfits for the player/rival. Setting either option to 2 will use a custom blue palette.
#define RSTN_PLAYER_OW_COLOR /*--*/ 1
#define RSTN_RIVAL_OW_COLOR /*--*/ 1

// TODO Intro cutscenes
#define RSTN_INTRO_GFX /*RS*/ TRUE

// Sets the color of the player's attire in the intro scenes. Also affects credits sequence.
// 0 = Emerald Green, 1 = R/S Red, 2 = Mandela Blue
#define RSTN_INTRO_PLAYER_GFX /*--*/ 1
// TODO probably need a rival color setting here for credits. will need to investigate further

// TODO The general graphics used for the main menu, i.e. Rayquaza/Groudon/Kyogre
#define RSTN_MENU_GFX /*RS*/ FALSE

// TODO Which version text to use on the main menu
#define RSTN_MENU_LOGO /*RS*/ FALSE

// TODO Vigoroth/Machoke Movers
// Ruby/Sapphire's moving crew in the opening sequence were Machokes, rather than Emerald's Vigoroth.
#define RSTN_MACHOKE_MOVERS /*EM*/ FALSE

// TODO Zigzagoon/Poochyena Birch Chase
// This also swaps the first trainer (after the rival battle) to have a Zigzagoon instead.
#define RSTN_BIRCH_POOCHYENA /*EM*/ FALSE

// TODO Contest/Quiz/Favor Lady in Lilycove

// TODO New Move Tutors added, including most of the ones in FireRed and LeafGreen
// might need to add an option here to undo the map swap killing these guys?
// maybe config per map?
// fuck thats gonna be a lot of maps, idk maybe leave this one for hack authors to do themselves

// TODO Main Story
// If RSTN_OTHER_CAVE is TRUE, the mon not caught during the story can be found 
// in Terra Cave/Marine Cave (as in Emerald) after becoming Champion.
#define RSTN_STORY /*RS*/ FALSE
#define RSTN_OTHER_CAVE /*RS*/ FALSE

// TODO Hideouts? In general?
// TODO Magma Hideout
// TODO Hideout seal entrances
// add option for other team to show up in magma hideout, if RS behavior is enabled!

// TODO Roaming Latias/Latios (hall of fame?)

// TODO Legendary titans puzzles

/* ### Gyms ### */

// TODO Gym Leader Teams (excluding 8 obv)

// TODO Juan/Wallace for 8
// TODO Steven/Wallace for champ
// allow for Juan 8 + Steven champ combo?
// if above is allowed, ensure that having Wallace as both gym 8 and champ is checked
// or don't check, fuck it - it's their game

// TODO Steven encounter in meteor falls - remove for RS, BUT maybe optional replacement? Wallace?

// TODO Gym Layout Changes
// map swap may just automatically handle this

// TODO Scott lmao

// TODO Cave floor design?
// "The cave floor design has slightly changed." lol ok thanks bulbapedia guess i'll investigate

// TODO Animated/static battler sprites?

// TODO Rugs
// "Brendan's house has blue rugs, while May's has pink rugs. In Ruby and Sapphire, both houses had red rugs."
// add option for "reverse" colored rugs i suppose

// TODO Champion room colors
// map swap

// TODO Legendary intro anims?
// "The Legendary Pokémon battle intros include a different animation before moving into the battle scene. 
// This animation involves the body patterns of the super-ancient Pokémon and the Legendary titans's braille eye patterns.""
// these seem objectively cool, this may be able to be written off into the "direct upgrade" category

// TODO Caught Pokemon fanfare
// this was changed to the one from FRLG? what? WHAT. my life is a lie

// TODO Route 101 blocker kid sprite/gender

// TODO Trick room puzzles

// TODO Fossils

// TODO Battle Tents

// TODO Verdanturf stuff

// random notes below
// gen 2 starters after regional dex - map swap might break, probably reinstate as an optional toggle?
// pokemon contests vs. battle tents (map swap might handle automatically, but options are nice)
// steven multi-battle at mossdeep
// battle tower multi-battles (probably not touching these)


// ### Changes Not Implemented ###

/*
    These are changes that either aren't substantial or beneficial enough, are bugs/buggy behavior,
    or are not worth implementing for technical reasons. This list is not
    entirely exhaustive (yet) and is naturally subject to opinion.
*/

//* E-Reader support (unchanged from pokeemerald and RHH, so whatever form it takes there)
//  I don't want to dive in technically, and I honestly think no one gives a shit.
//* Trainer's Eyes
//  Match Call is just a direct upgrade, I'm pretty sure. Way less creepy name too.
//* Deoxys + Mew related stuff
//  For event ROMs/cheats, the events are fine.
//* Removing ability field effects + Pickup ability changes + female ditto everstone breeding
//  Doubt anyone cares about this stuff. Direct upgrades. Probably supereseded by the expansion too, I'd guess.
//* Trade restrictions
//  Probably trade compatible with any other Emerald + RHH project? Don't count on old RS behavior, probably.
//* Carryovers/upgrades from FRLG (Union Room, Mystery Gift, PP color (lol), other stuff if not mentioned elsewhere)
//  Some stuff won't be used often with romhacks anyways. For PP text color, it's just a direct upgrade. Other stuff
//  has little effect on actual gameplay/nostalgia/etc.

#endif // GUARD_RSTN_CONFIG