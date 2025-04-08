#include "gba.h"
#include "sprites.h"
#include "Console_Input.h"

#define MAX_SNAKE_LENGTH 100

// Snake segment positions
int snakeLength = 3;
int snakeX[MAX_SNAKE_LENGTH] = {80, 76, 72};
int snakeY[MAX_SNAKE_LENGTH] = {80, 80, 80};

// Prey position
int preyX = 120;
int preyY = 80;

// Snake movement direction
int dx = 4;
int dy = 0;

// Game state flag
int gameRunning = 1;

// Delay to control game speed (waits for vertical blanking)
void waitFrames(int frames) {
    for (int i = 0; i < frames; i++) {
        while (REG_VCOUNT >= 160);
        while (REG_VCOUNT < 160);
    }
}

// Moves the snake and checks for prey collision
void updateSnake() {
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }
    snakeX[0] += dx;
    snakeY[0] += dy;

    // Wrap around screen boundaries
    if (snakeX[0] >= SCREEN_WIDTH) snakeX[0] = 0;
    if (snakeX[0] < 0) snakeX[0] = SCREEN_WIDTH - 8;
    if (snakeY[0] >= SCREEN_HEIGHT) snakeY[0] = 0;
    if (snakeY[0] < 0) snakeY[0] = SCREEN_HEIGHT - 8;

    // If snake head touches prey, grow snake and relocate prey
    if (snakeX[0] == preyX && snakeY[0] == preyY && snakeLength < MAX_SNAKE_LENGTH) {
        snakeLength++;
        preyX = (rand() % 28) * 8;
        preyY = (rand() % 18) * 8;
    }
}

// Draws each segment of the snake using sprite slots
void drawSnakeBody() {
    for (int i = 0; i < snakeLength; i++) {
        drawSprite(SNAKE_BODY, i, snakeX[i], snakeY[i]);
    }
}

// Draws the prey sprite on screen
void drawPrey() {
    drawSprite(PREY, 127, preyX, preyY);
}

// Game entry point
int main(void) {
    // Set video mode to Mode 2, enable sprites, use 1D mapping
    REG_DISPCNT = MODE2 | OBJ_ENABLE | OBJ_MAP_1D;

    // Load palette and sprite graphics
    fillPalette();
    fillSprites();

    // Game loop
    while (1) {
        if (gameRunning) {
            checkInput();       // handle player input
            updateSnake();      // move the snake
            fillSprites();      // clear all sprite positions
            drawSnakeBody();    // draw updated snake
            drawPrey();         // draw the prey
        }
        waitFrames(10);         // control game speed
    }
    return 0;
}
