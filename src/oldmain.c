#include <pico/stdlib.h>
#include <pico/stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"


enum {
    BLINK_UNMOUNTED = 250,
    BLINK_MOUNTED = 750,
    BLINK_SUSPENDED = 1500
};

static uint32_t blinkIntervalMs = BLINK_UNMOUNTED;


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

// device callbacks
void tusbMountCallback(void) {
    blinkIntervalMs = BLINK_MOUNTED;
}

void tusbUnmountCallback(void) { 
    blinkIntervalMs = BLINK_UNMOUNTED;
}

void tusbSuspendedCallback (void) {
    blinkIntervalMs = BLINK_SUSPENDED;
}

void tusbResumeCallback (void) {
    blinkIntervalMs = BLINK_MOUNTED;
}

// tinyusb callbacks

// invoked whenever a report is successfully sent to the host
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len) {
    // suppress unused variable message
    (void) instance;
    (void) len;

    uint8_t nextReportId = report[0] + 1;
    if (nextReportId < REPORT_ID_COUNT) {
        send_hid_report(nextReportId, board_button_read());
    }
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t reportId, hid_report_type_t reportType, uint8_t* buffer, uint16_t reqlen) {
    // suppress unused variable message
    (void) instance;
    (void) reportId;
    (void) reportType;
    (void) buffer;
    (void) reqlen;

    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t reportId, hid_report_type_t reportType, uint8_t const* buffer, uint16_t bufsize) {
    // suppress unused variable message
    (void) instance;

    if(reportType == HID_REPORT_TYPE_OUTPUT) {
        if (reportId == REPORT_ID_KEYBOARD) {
            if (bufsize < 1) return;

            uint8_t const keyboardLeds = buffer[0];

            if(keyboardLeds & KEYBOARD_LED_CAPSLOCK) {
                blinkIntervalMs = 0;
                board_led_write(true);
            } else {
                board_led_write(false);
                blinkIntervalMs = BLINK_MOUNTED;
            }
        }
    }
}

// usb hid
static void send_hid_report(uint8_t reportId, uint32_t btn) {
    // check if hid is ready, if not ready then skip it
    if (!tud_hid_ready() ) {
        return;
    }

    switch(reportId) {
        case REPORT_ID_KEYBOARD: {
            // used to avoid sending multiple consecutive zero reports
            static bool hasKeyboardKey = false;

            if (btn) {
                uint8_t keycode[6] = { 0 };
                keycode[0] = HID_KEY_A; //sends "A" 

                tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
                hasKeyboardKey = true;
            } else {
                if (hasKeyboardKey) {
                    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
                    hasKeyboardKey = false;
                }
            }
        }
        break;

        default: break;
    }
}

// send a HID report every 10ms
void hid_task(void) {
    const uint32_t intervalMs = 10;
    static uint32_t startMs = 0;

    if (board_millis() - startMs < intervalMs) {
        return;
    }

    startMs += intervalMs;

    uint32_t const btn = board_button_read();

    if (tud_suspended() && btn) {
        // wake up host if we are in a suspended mode
        tud_remote_wakeup();
    } else {
        send_hid_report(REPORT_ID_KEYBOARD, btn);
    }
}

int main(void) {
    board_init();
    tusb_init();

    while (1)
    {
        tud_task();
        ledBlinkTask();
        hid_task();
    }
}