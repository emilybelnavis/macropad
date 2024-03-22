#include <InputEvent.h>

InputEvent::InputEvent() {
    type = FREE;
}

InputEvent::InputEvent(const InputEvent& inputEvent) {
    source = inputEvent.source;
    state = inputEvent.state;
    scancode = inputEvent.scancode;
    type = inputEvent.type;
    timestamp = inputEvent.timestamp;
}

InputEvent::InputEvent(uint8_t state, uint16_t scancode) {
    type = SCANCODE;
    this->state = state;
    this->scancode = scancode;
}

InputEvent::InputEvent(uint8_t state, uint16_t scancode, uint8_t source) {
    this->source = source;
    InputEvent(state, scancode);
}

void InputEvent::clear() {
    this->type = FREE;
    this->scancode = MKC_NONE;
    this->source = 0;
}