// sprites.h - Contains color palette and sprite tile data for the GBA Snake game
#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h" // Include GBA macro and register definitions

// Total number of colors in the sprite palette
#define NCOLS 20

// Sprite identifiers (used by drawSprite)
#define SNAKE_BODY 0  // ID for snake body sprite
#define PREY 1        // ID for prey/food sprite

//-----------------------------------------------
// Color Palette (20 total entries)
// Each entry is a 15-bit GBA RGB value
// Use RGB(r, g, b) macro: r, g, b ? [0, 31]
// These are indexed colors used by your sprite tiles
//-----------------------------------------------
int palette[] = {
    RGB(0, 0, 0),       // 0 - Black
    RGB(31, 31, 31),    // 1 - White
    RGB(0, 31, 31),     // 2 - Light Blue
    RGB(26, 26, 26),    // 3 - Light Grey
    RGB(9, 9, 9),       // 4 - Darkest Grey
    RGB(31, 31, 0),     // 5 - Yellow
    RGB(31, 0, 0),      // 6 - Red
    RGB(0, 0, 31),      // 7 - Blue
    RGB(11, 8, 3),      // 8 - Dark Brown
    RGB(27, 27, 27),    // 9 - Lightest Grey
    RGB(16, 16, 16),    // 10 - Dark Grey
    RGB(31, 17, 17),    // 11 - Light Red
    RGB(31, 24, 24),    // 12 - Lighter Red
    RGB(27, 0, 0),      // 13 - Dark Red
    RGB(0, 16, 0),      // 14 - Darkest Green
    RGB(0, 31, 0),      // 15 - Pure Green
    RGB(16, 31, 16),    // 16 - Light Green
    RGB(23, 31, 23),    // 17 - Lightest Green
    RGB(31, 26, 28),    // 18 - Light Pink
    RGB(31, 0, 15)      // 19 - Bright Pink
};

//-------------------------------------------------------------
// Sprite tile data (indexed color values that map to palette[])
// Each sprite here is 16x16 pixels = 256 pixels = 256 bytes
// We use color indices 18 (light pink) for the snake
// and 19 (bright pink) for the prey
//-------------------------------------------------------------
u16 sprites[] = {
    // -------- SNAKE_BODY sprite --------
    // Uses color index 18 for all pixels
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,
    18,18,18,18,18,18,18,18,

    // -------- PREY sprite --------
    // Uses color index 19 for all pixels
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19,
    19,19,19,19,19,19,19,19
};

#endif // SPRITES_H
