#include "gba.h"
#include "sprites.h"
#include "Inputs.h"

#define MAX_SNAKE_LENGTH 100

// Snake data
int snakeLength = 3;
int snakeX[MAX_SNAKE_LENGTH] = {80, 76, 72};
int snakeY[MAX_SNAKE_LENGTH] = {80, 80, 80};

// Prey data
int preyX = 120;
int preyY = 80;

// Snake direction
int dx = 4;
int dy = 0;

// Game state
int gameRunning = 1;

//======================================================
// Interrupt Handler (called on Timer 0 overflow)
//======================================================
void Handler(void) {
    REG_IME = 0; // Disable interrupts

    // Timer0 interrupt check
    if (REG_IF & INT_TIMER0) {
        if (gameRunning) {
            checkInput();
            updateSnake();
            fillSprites();
            drawSnakeBody();
            drawPrey();
        }

        REG_IF |= INT_TIMER0; // Acknowledge Timer0 interrupt
    }

    REG_IME = 1; // Re-enable interrupts
}

//======================================================
// Delay-free Game Update: Uses Timer for Timing
//======================================================
void setupTimerAndInterrupts() {
    // Set interrupt handler
    REG_INT = (unsigned int) &Handler;

    // Enable interrupt for Timer 0
    REG_IE = INT_TIMER0;
    REG_IME = 1;  // Enable global interrupt handling

    // Timer0 settings: overflow ~10 times/sec
    // 65536 - 62500 = 3036 (with 1024 prescaler)
    REG_TM0D = 3036; // Start value
    REG_TM0CNT = TIMER_FREQUENCY_1024 | TIMER_ENABLE | TIMER_INTERRUPTS;
}

//======================================================
// Update the snake's body and check for prey collision
//======================================================
void updateSnake() {
    // Move body
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Move head
    snakeX[0] += dx;
    snakeY[0] += dy;

    // Wrap around screen
    if (snakeX[0] >= SCREEN_WIDTH) snakeX[0] = 0;
    if (snakeX[0] < 0) snakeX[0] = SCREEN_WIDTH - 8;
    if (snakeY[0] >= SCREEN_HEIGHT) snakeY[0] = 0;
    if (snakeY[0] < 0) snakeY[0] = SCREEN_HEIGHT - 8;

    // Eat prey
    if (snakeX[0] == preyX && snakeY[0] == preyY && snakeLength < MAX_SNAKE_LENGTH) {
        snakeLength++;
        preyX = (rand() % 28) * 8;
        preyY = (rand() % 18) * 8;
    }
}

//======================================================
// Draw the snake's body
//======================================================
void drawSnakeBody() {
    for (int i = 0; i < snakeLength; i++) {
        drawSprite(SNAKE_BODY, i, snakeX[i], snakeY[i]);
    }
}

//======================================================
// Draw the prey
//======================================================
void drawPrey() {
    drawSprite(PREY, 127, preyX, preyY);
}

//======================================================
// Entry point
//======================================================
int main(void) {
    // Set video mode: Mode 2 + OBJ enabled + 1D mapping
    REG_DISPCNT = MODE2 | OBJ_ENABLE | OBJ_MAP_1D;

    // Load graphics
    fillPalette();
    fillSprites();

    // Set up interrupts and timer
    setupTimerAndInterrupts();

    // Main loop just idles; game runs in handler
    while (1);

    return 0;
}
