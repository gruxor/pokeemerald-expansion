#ifndef GUARD_RSTN_CONFIG
#define GUARD_RSTN_CONFIG

/*
    NOTE: All options default to FALSE.
    Some features only differ from Emerald and are the same between Ruby/Sapphire.
    Changes that only differ in Emerald are marked with an EM comment
    while all three-version-differences are marked with an RS comment.
    Any options that are not yet implemented are marked with a TODO in their description.
*/

// Boolean for swapping game versions. No effect if options are FALSE.
// 0 = Ruby; 1 = Sapphire
#define RSTN_VERSION 0

// TODO Intro cutscenes
#define RSTN_INTRO_GFX /*RS*/ TRUE

// Sets the color of the player's attire in the intro scenes. Also affects credits sequence.
// 0 = Emerald Green, 1 = R/S Red, 2 = Mandela Blue
#define RSTN_INTRO_PLAYER_GFX /*--*/ 1
// TODO might need a rival color for credits, i forget

// TODO The general graphics used for the main menu, i.e. Rayquaza/Groudon/Kyogre
#define RSTN_MENU_GFX /*RS*/ FALSE

// TODO Which version text to use on the main menu
#define RSTN_MENU_LOGO /*RS*/ FALSE

// TODO Brendan/May Overworld Sprite Colors
// 0 = Emerald Green, 1 = R/S Red, 2 = Mandela Blue
// NOTE: Blue was never an outfit color in any of the 3 games, but many people misremember Sapphire as 
// having blue outfits for the player/rival. Setting either option to 2 will use a custom blue outfit.
#define RSTN_PLAYER_OW_COLOR /*--*/ 1
#define RSTN_RIVAL_OW_COLOR /*--*/ 1

// TODO Vigoroth/Machoke Movers
// Ruby/Sapphire's moving crew in the opening sequence were Machokes, rather than Emerald's Vigoroth.
#define RSTN_MACHOKE_MOVERS /*EM*/ FALSE

// TODO Zigzagoon/Poochyena Birch Chase
// This also swaps the first trainer (after the rival battle) to have a Zigzagoon instead.
#define RSTN_BIRCH_POOCHYENA /*EM*/ FALSE

// TODO Contest/Quiz/Favor Lady in Lilycove?

// TODO "New Move Tutors added, including most of the ones in FireRed and LeafGreen
// might need to add an option here to undo the map swap killing these guys?
// per map?
// fuck thats gonna be a lot of maps idk

// TODO Main Story
// If RSTN_OTHER_CAVE is TRUE, the mon not caught during the story can be found 
// in Terra Cave/Marine Cave (as in Emerald) after becoming Champion.
#define RSTN_STORY /*RS*/ FALSE
#define RSTN_OTHER_CAVE /*RS*/ FALSE

// TODO Hideouts? In general?
// TODO Magma Hideout
// TODO Hideout seal entrances
// add option for other team to show up in magma hideout, if RS behavior is enabled

// TODO Roaming Latias/Latios (hall of fame?)

// TODO Legendary titans puzzles

/* ### Gyms ### */

// TODO Gym Leader Teams (excluding 8)

// TODO Juan vs Wallace, Steven vs. Wallace
// allow for Juan + Steven combo? Can't have Wallace BOTH champ and gym leader right?
// Steven encounter in meteor falls - def remove for RS, but maybe optional replacement? Wallace?

// TODO Gym Layout Changes
// map switch may just automatically handle this

// TODO Scott

// TODO Cave floor design?
// "The cave floor design has slightly changed."

// TODO Animated battler sprites

// TODO Rugs
// "Brendan's house has blue rugs, while May's has pink rugs. In Ruby and Sapphire, both houses had red rugs."
// add option for "reverse" colored rugs for RS

// TODO Champion room colors
// map swap

// TODO Legendary intro anims?
// "The Legendary Pokémon battle intros include a different animation before moving into the battle scene. 
// This animation involves the body patterns of the super-ancient Pokémon and the Legendary titans's braille eye patterns.""
// these seem objectively cool, idk

// TODO Caught Pokemon fanfare
// this was changed to the one from FRLG? what? WHAT

// TODO Route 101 blocker kid gender

// TODO Trick room puzzles

// TODO Fossils

// TODO Battle Tents

// TODO Verdanturf

// random notes below
// gen 2 starters after regional dex - map swap might break
// pokemon contests vs. battle tents (map swap might handle automatically, but options are nice)
// steven multi-battle at mossdeep
// battle tower multi-battles (probably not touching these)


// ### Changes Not Implemented ###

/*
    These are changes that either aren't substantial enough, are bugs/buggy behavior,
    or are not worth implementing for technical reasons. This list is probably not
    entirely exhaustive and is naturally subject to my own opinions.
*/

//* E-Reader support (unchanged from pokeemerald and RHH, so whatever form it takes there)
//  I don't want to dive in technically, and I honestly think no one gives a shit.
//* Trainer's Eyes
//  Match Call is just a direct upgrade, I'm pretty sure. Way less creepy name too.
//* Deoxys + Mew related stuff
//  For event ROMs/cheats, the events are good enough.
//* Removing ability field effects + Pickup ability changes + female ditto everstone breeding
//  Doubt anyone cares about this stuff. Direct upgrades. Probably supereseded by the expansion too, I'd guess.
//* Trade restrictions
//  Probably trade compatible with any other Emerald + RHH project? Don't count on old RS behavior, probably.
//* Carryovers from FRLG (Union Room, Mystery Gift, PP color (lol), other stuff if not mentioned elsewhere)
//  Some stuff won't be used often with romhacks anyways. For PP text color, it's just a direct upgrade imo.

#endif // GUARD_RSTN_CONFIG