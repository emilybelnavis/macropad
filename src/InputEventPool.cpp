#include <pico/stdio.h>
#include <pico/stdlib.h>
#include "InputEventPool.h"

InputEventPool::InputEventPool() { }

InputEvent* InputEventPool::getInputEvent(InputEvent inputEvent) {
    InputEvent* poolEvent = getInputEvent(inputEvent.type);
    poolEvent->source = inputEvent.source;
    poolEvent->state = inputEvent.state;
    poolEvent->scancode = inputEvent.scancode;
    poolEvent->timestamp = inputEvent.timestamp;
    return poolEvent;
}

InputEvent* InputEventPool::getInputEvent(InputEventType inputEventType) {
    for (int pool = 0; pool < INPUT_EVENT_POOL_SIZE; pool++) {
        if (inputEvents[pool].type == FREE) {
            inputEvents[pool].type = inputEventType;
            inputEvents[pool].timestamp = time_us_64();

            return &inputEvents[pool];
        }
    }
    return nullptr;
}