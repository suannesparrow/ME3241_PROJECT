// Console_Input.h
#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "gba.h"
#include "sprites.h"

#define INPUT (KEY_MASK & (~REG_KEYS))

extern int gameRunning;
extern int dx, dy;

void startGame() { gameRunning = 1; }
void quitGame() { gameRunning = 0; }
void moveUp()    { if (dy == 0) { dx = 0; dy = -4; } }
void moveDown()  { if (dy == 0) { dx = 0; dy = 4; } }
void moveLeft()  { if (dx == 0) { dx = -4; dy = 0; } }
void moveRight() { if (dx == 0) { dx = 4; dy = 0; } }

void checkInput(void) {
    u16 buttons = INPUT;
    if ((buttons & KEY_UP) == KEY_UP) moveUp();
    if ((buttons & KEY_DOWN) == KEY_DOWN) moveDown();
    if ((buttons & KEY_LEFT) == KEY_LEFT) moveLeft();
    if ((buttons & KEY_RIGHT) == KEY_RIGHT) moveRight();
    if ((buttons & KEY_START) == KEY_START) startGame();
    if ((buttons & KEY_SELECT) == KEY_SELECT) quitGame();
}

void fillPalette(void) {
    for (int i = 0; i < NCOLS; i++) spritePal[i] = palette[i];
}

void fillSprites(void) {
    for (int i = 0; i < 128 * 16 * 16; i++) spriteData[i] = (sprites[i * 2 + 1] << 8) + sprites[i * 2];
    for (int i = 0; i < 128; i++) drawSprite(0, i, 240, 160); // hide all
}

void drawSprite(int numb, int N, int x, int y) {
    *(unsigned short *)(0x7000000 + 8 * N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8 * N) = x | 0x4000;
    *(unsigned short *)(0x7000004 + 8 * N) = numb * 8;
}

#endif
