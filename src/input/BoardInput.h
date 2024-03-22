#ifndef BOARD_INPUT
#define BOARD_INPUT
#include "KeyboardState.h"
#include "InputEvent.h"
#include "InputDevice.h"
#include "board/board.h"

class BoardInput: public InputDevice {
    public:
        BoardInput();
        virtual bool scan(KeyboardState* keyboardState);
};

#endif