#ifndef KEYBOARD_STATE
#define KEYBOARD_STATE

#include "KeyDefinitions.h"
#include "InputEvent.h"
#include "InputEventPool.h"
#include "board/board.h"

class KeyboardState {
    public:
        KeyboardState(uint8_t keymaps[1][NUM_ROWS][NUM_COLS], int nKeymaps);
        void clearKeyStates();
        void resetKeyStates(uint8_t fromKeymap[NUM_ROWS][NUM_COLS], uint8_t toKeymap[NUM_ROWS][NUM_COLS]);
        void raise();
        void lower();
        uint16_t getScancode(int row, int col);
        uint16_t getScancode(uint8_t keymap[NUM_ROWS][NUM_COLS], int row, int col);
        void inputEvent(InputEvent *event);
        unsigned char keyIterCount[NUM_ROWS][NUM_COLS];
        uint8_t keyState[NUM_ROWS][NUM_COLS]; 
        uint8_t (*keymaps)[NUM_ROWS][NUM_COLS];
        int nKeymaps;
        int activeKeymapIndex = 0;

        InputEventPool inputEventPool;
};

#endif