#ifndef INPUT_EVENT
#define INPUT_EVENT

#include "pico/stdlib.h"
#include "KeyDefinitions.h"

enum InputEventType {
    FREE,
    SCANCODE,
    TIMER
};

class InputEvent {
    public:
        InputEvent();
        InputEvent(const InputEvent& inputEvent);
        InputEvent(uint8_t state, uint16_t scancode);
        InputEvent(uint8_t state, uint16_t scancode, uint8_t source);
        void clear();

        uint16_t scancode = MKC_NONE;
        uint8_t state = 0;
        uint64_t timestamp;
        uint8_t source;

        InputEventType type = SCANCODE;
};

#endif