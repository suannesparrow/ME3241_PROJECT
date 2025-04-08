// Console_Input.h
#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "gba.h"       // GBA hardware register definitions and helper macros
#include "sprites.h"   // Game sprite and palette definitions

// Macro to read current button inputs (0 = pressed)
#define INPUT (KEY_MASK & (~REG_KEYS))

// These extern variables are declared in main.c
extern int gameRunning;  // Boolean flag for game state
extern int dx, dy;       // Snake direction: delta x and delta y

//-----------------------------------------------
// Game control functions (triggered by buttons)
//-----------------------------------------------

// Start the game (set running flag to true)
void startGame() { gameRunning = 1; }

// Quit the game (set running flag to false)
void quitGame() { gameRunning = 0; }

// Change direction to UP if not moving vertically
void moveUp() {
    if (dy == 0) {
        dx = 0;
        dy = -4;
    }
}

// Change direction to DOWN if not moving vertically
void moveDown() {
    if (dy == 0) {
        dx = 0;
        dy = 4;
    }
}

// Change direction to LEFT if not moving horizontally
void moveLeft() {
    if (dx == 0) {
        dx = -4;
        dy = 0;
    }
}

// Change direction to RIGHT if not moving horizontally
void moveRight() {
    if (dx == 0) {
        dx = 4;
        dy = 0;
    }
}

//--------------------------------------------------
// Check button inputs and call corresponding logic
//--------------------------------------------------
void checkInput(void) {
    u16 buttons = INPUT;

    if ((buttons & KEY_UP) == KEY_UP)       moveUp();
    if ((buttons & KEY_DOWN) == KEY_DOWN)   moveDown();
    if ((buttons & KEY_LEFT) == KEY_LEFT)   moveLeft();
    if ((buttons & KEY_RIGHT) == KEY_RIGHT) moveRight();
    if ((buttons & KEY_START) == KEY_START) startGame();
    if ((buttons & KEY_SELECT) == KEY_SELECT) quitGame();
}

//------------------------------------------------------
// Fill GBA sprite palette memory with defined palette
//------------------------------------------------------
void fillPalette(void) {
    for (int i = 0; i < NCOLS; i++) {
        spritePal[i] = palette[i];  // Copy each color to GBA OBJ palette
    }
}

//------------------------------------------------------
// Load sprite data into GBA sprite tile memory
// Then initialize all 128 sprites off-screen
//------------------------------------------------------
void fillSprites(void) {
    // Load tile data (GBA uses 16-bit tile format)
    for (int i = 0; i < 128 * 16 * 16; i++) {
        spriteData[i] = (sprites[i * 2 + 1] << 8) + sprites[i * 2];
    }

    // Hide all sprites by drawing them off-screen
    for (int i = 0; i < 128; i++) {
        drawSprite(0, i, 240, 160);  // (240,160) is bottom-right corner, off-screen
    }
}

//------------------------------------------------------
// Draw a single sprite at (x, y) using sprite index `numb`
// `N` is the sprite slot (0 to 127)
//------------------------------------------------------
void drawSprite(int numb, int N, int x, int y) {
    // Set Y position and enable 16x16 object shape
    *(unsigned short *)(0x7000000 + 8 * N) = y | 0x2000;

    // Set X position and enable 1D mapping
    *(unsigned short *)(0x7000002 + 8 * N) = x | 0x4000;

    // Set tile index for sprite graphics (numb * 8 in 1D mapping mode)
    *(unsigned short *)(0x7000004 + 8 * N) = numb * 8;
}

#endif // CONSOLE_INPUT_H
