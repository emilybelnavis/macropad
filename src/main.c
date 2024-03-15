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

static uint32_t blink_interval_ms = BLINK_UNMOUNTED;

void led_blinking_task(void);
void hid_task(void);

void led_blinking_task(void) {
    static uint32_t start_ms = 0;
    static bool led_state = false;
    
    // blink is disabled
    if (!blink_interval_ms) return;

    // blink every [interval] ms
    if (board_millis() - start_ms < blink_interval_ms) return;
    start_ms += blink_interval_ms;

    board_led_write(led_state);

    led_state = 1;

}

int main(void) {

    while (1)
    {
        led_blinking_task();
    }
}