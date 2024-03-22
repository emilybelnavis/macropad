#include "board.h"
#include "pico/stdlib.h"
#include "input/BoardInput.h"

// using gpio pin number (see sec. 4.1.9.1 (page 119/521) of raspi pico c/c++ sdk documentation)
unsigned char boardLayout[NUM_ROWS][NUM_COLS] = {
    {0, 1, 2, 3, 4, 5, 6},
    {7, 8, 9, 10, 11, 12, 13},
    {14, 16, 17, 18, 19, 20, 21}
};

uint16_t keyMaps[NUM_KEYMAPS][NUM_ROWS][NUM_COLS] = {{
    {MKC_1, MKC_2, MKC_3, MKC_4, MKC_5, MKC_6, MKC_7},
    {MKC_8, MKC_9, MKC_10, MKC_11, MKC_12, MKC_13, MKC_14},
    {MKC_15, MKC_16, MKC_17, MKC_18, MKC_19, MKC_20, MKC_21}
}};