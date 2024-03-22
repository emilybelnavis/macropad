#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

#include "KeyDefinitions.h"
#include "KeyboardState.h"
#include "input/InputDevice.h"
#include "board/board.h"

KeyboardState *keyboardState;

extern uint8_t keymaps[NUM_KEYMAPS][NUM_ROWS][NUM_COLS];
extern InputDevice* inputDevices[];

enum {
    BLINK_UNMOUNTED = 25,
    BLINK_MOUNTED = 750,
    BLINK_SUSPENDED = 1500
};

static uint32_t blinkIntervalMs = BLINK_UNMOUNTED;


void doInputs() {
    for(int inputDevice = 0; inputDevice < NUM_INPUT_DEVICES; inputDevice++) {
        if(!inputDevices[inputDevice]->scan(keyboardState)) {
            return;
        }
    }
}

unsigned long long getMicros(){
    return time_us_64();
}

void doTimerTick() {
    InputEvent* timerEvent = keyboardState->inputEventPool.getInputEvent(TIMER);
    timerEvent->timestamp = getMicros();
    keyboardState->inputEvent(timerEvent);
}

void setup() {
    keyboardState = new KeyboardState(keymaps, NUM_KEYMAPS);
}

void loop() {
    static unsigned long long scanTick = getMicros();
    static unsigned long long timerTick = getMicros();

    unsigned long long elapsed = getMicros() - timerTick;
    if (elapsed >= TIMER_TICK_PERIOD) {
        timerTick = getMicros() - (elapsed - TIMER_TICK_PERIOD);
        doTimerTick();
    }

    elapsed = getMicros() - scanTick;
    if (elapsed >= SCAN_PERIOD) {
        scanTick = getMicros() - (elapsed - SCAN_PERIOD);
        doInputs();
    }
}

// tinyusb callbacks
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t reportId, hid_report_type_t reportType, uint8_t* buffer, uint16_t reqlen) {
    (void) instance;
    (void) reportId;
    (void) reportType;
    (void) buffer;
    (void) reqlen;

    return 0;
}


void tud_hid_set_report_cb(uint8_t instance, uint8_t reportId, hid_report_type_t reportType, uint8_t const* buffer, uint16_t bufsize) {
    (void) instance;
    (void) reportId;
    (void) reportType;
    (void) buffer;
    (void) bufsize;
}

// device callbacks
void tusb_mount_callback(void) {
    blinkIntervalMs = BLINK_MOUNTED;
}

void tusb_unmount_callback(void) { 
    blinkIntervalMs = BLINK_UNMOUNTED;
}

void tusb_suspended_callback (void) {
    blinkIntervalMs = BLINK_SUSPENDED;
}

void tusb_resume_callback (void) {
    blinkIntervalMs = BLINK_MOUNTED;
}

void ledBlinkTask(void) {
    static uint32_t startMs = 0;
    static bool ledState = false;
    
    // blink is disabled
    if (!blinkIntervalMs) return;

    // blink every [interval] ms
    if (board_millis() - startMs < blinkIntervalMs) return;
    startMs += blinkIntervalMs;

    board_led_write(ledState);

    ledState = 1 - ledState;

}

// void hid_task(void) {
//     const uint64_t intervalMicros = 10000;
//     static uint64_t startMicros = 0;
// }

int main() {
    stdio_init_all();
    board_init();
    tusb_init();

    while(1) {
        tud_task();
        ledBlinkTask();
        //hid_task();
    }
}