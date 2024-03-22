#include <pico/stdio.h>
#include <pico/stdlib.h>
#include "BoardInput.h"

extern uint8_t boardLayout[NUM_ROWS][NUM_COLS];

BoardInput::BoardInput() {
    // initialize all the gpio pins
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            gpio_init(boardLayout[row][col]);
            gpio_set_dir(boardLayout[row][col], GPIO_IN);
            gpio_pull_up(boardLayout[row][col]);
        }
    }
}

bool BoardInput::scan(KeyboardState* keyboardState) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            gpio_set_dir(boardLayout[row][col], GPIO_OUT);
            gpio_put(boardLayout[row][col], false);

            bool boolVal = gpio_get(boardLayout[row][col]);
            unsigned char value = boolVal ? KEY_RELEASED : KEY_PRESSED;

            if (value == KEY_PRESSED && keyboardState->keyState[row][col] == KEY_RELEASED) {
                keyboardState->keyState[row][col] = KEY_PRESSED;
                keyboardState->keyIterCount[row][col] = 0;
            } else if (value == KEY_RELEASED && keyboardState->keyState[row][col] == KEY_PRESSED) {
                keyboardState->keyState[row][col] = KEY_RELEASED;
                keyboardState->keyIterCount[row][col] = 0;
            } else {
                if (keyboardState->keyIterCount[row][col] < DEBOUNCE_ITR) {
                    keyboardState->keyIterCount[row][col]++;
                } else if (keyboardState->keyIterCount[row][col] == DEBOUNCE_ITR){
                    keyboardState->keyState[row][col]++;
                    uint16_t scancode = keyboardState->getScancode(row, col);
                    InputEvent* inputEvent = keyboardState->inputEventPool.getInputEvent(SCANCODE);
                    inputEvent->scancode = scancode;
                    inputEvent->state = keyboardState->keyState[row][col];
                    keyboardState->inputEvent(inputEvent);
                }
            }
            gpio_set_dir(boardLayout[row][col], GPIO_IN);
        }
    }
    return true;
}