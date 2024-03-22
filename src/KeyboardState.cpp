#include <pico/stdio.h>
#include "tusb.h"

#include "board/board.h"
#include "KeyboardState.h"

int pressed[256] = {0};

KeyboardState::KeyboardState(uint8_t keymaps[1][NUM_ROWS][NUM_COLS], int nKeymaps) {
    this->keymaps = keymaps;
    this->nKeymaps = nKeymaps;

    // set initial values on iteration count and state arrays
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            keyIterCount[row][col] = DEBOUNCE_ITR + 1;
            keyState[row][col] = KEY_RELEASED;
        }
    }
}

void KeyboardState::raise() {
    if (activeKeymapIndex < (nKeymaps - 1)) {
        activeKeymapIndex++;
        resetKeyStates(keymaps[activeKeymapIndex - 1], keymaps[activeKeymapIndex]);
    }
}

void KeyboardState::lower() {
    if (activeKeymapIndex > 0) {
        activeKeymapIndex--;
        resetKeyStates(keymaps[activeKeymapIndex + 1], keymaps[activeKeymapIndex]);
    }
}

// get scancode from the current active keymap
uint16_t KeyboardState::getScancode(int row, int col) {
    return getScancode(keymaps[activeKeymapIndex], row, col);
}

uint16_t KeyboardState::getScancode(uint8_t keymap[NUM_ROWS][NUM_COLS], int row, int col) {
    uint16_t scancode = keymap[row][col];
    int trnsIndex = activeKeymapIndex;
    while(scancode == TRNS && trnsIndex >= 0) {
        scancode = keymaps[trnsIndex--][row][col];
    }
    return scancode;
}

void KeyboardState::clearKeyStates() {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            keyIterCount[row][col] = DEBOUNCE_ITR + 1;
            keyState[row][col] = KEY_RELEASED;
        }
    }
}

void KeyboardState::resetKeyStates(uint8_t fromKeymap[NUM_ROWS][NUM_COLS], uint8_t toKeymap[NUM_ROWS][NUM_COLS]) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if(fromKeymap[row][col] != TRNS && toKeymap[row][col] != TRNS && toKeymap[row][col] != fromKeymap[row][col]) {
                keyIterCount[row][col] = DEBOUNCE_ITR + 1;
                //if it's currently PRESSED then we have to 'release' the 'from' map keycode, and 'press' the 'to' keycode
                if(keyState[row][col] == KEY_PRESSED) {
                    uint8_t fromKeyCode = getScancode(fromKeymap,row,col);
                    uint8_t toKeyCode =   getScancode(toKeymap,row,col);
                }       
            }
        }
    }
}