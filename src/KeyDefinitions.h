#ifndef KEY_DEFINITIONS
#define KEY_DEFINITIONS

#define KEY_RELEASED 1
#define KEY_PRESSED 0

// number of iterations of identical keyscan values before a keypress is triggered
#define DEBOUNCE_ITR 5

// microseconds between each scan
#define SCAN_PERIOD 4000            // equal to 5ms 
#define TIMER_TICK_PERIOD 20000     // equal to 20ms

#define MKC_SPECIAL 0xFC
#define MKC_REBOOT (MKC_SPECIAL + 1)
#define TRNS (MKC_SPECIAL + 2)
#define MKC_FUNCTION (MKC_SPECIAL + 3)

// macropad specific keycodes
#ifndef MKC_NONE
    #define MKC_NONE    0x0000
    #define MKC_1       0xA000
    #define MKC_2       0xA001
    #define MKC_3       0xA002
    #define MKC_4       0xA003
    #define MKC_5       0xA004
    #define MKC_6       0xA005
    #define MKC_7       0xA006
    #define MKC_8       0xA007
    #define MKC_9       0xA008
    #define MKC_10      0xA009
    #define MKC_11      0xA00A 
    #define MKC_12      0xA00B
    #define MKC_13      0xA00C
    #define MKC_14      0xA00D
    #define MKC_15      0xA00E
    #define MKC_16      0xA00F
    #define MKC_17      0xA010
    #define MKC_18      0xA011
    #define MKC_19      0xA012
    #define MKC_20      0xA013
    #define MKC_21      0xA014
#endif // macropad keycode defines

#endif // KEY_DEFINITIONS