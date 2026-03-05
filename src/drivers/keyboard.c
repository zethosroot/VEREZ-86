#include "kbd_map.h"
#include "keyboard.h"
#include "io.h"

static unsigned int shift_held = 0;

void kbd_init() {
    inb(0x60);
}

char kbd_getchar() {
    
    while (1) {
        
        while (!(inb(0x64) & 0x01)); // Wait till there is data ready
        uint8_t scancode = inb(0x60);

        if (scancode == 0x2A || scancode == 0x36) {
            shift_held = 1;
            continue;  // loop again, don't return a character
        }
        if (scancode == 0xAA || scancode == 0xB6) {
            shift_held = 0;
            continue;
        }
        
        char ret = 0;

        // Make code?
        if (!(scancode & 0x80)) {
            return shift_held ? kbd_map_shift[scancode] : kbd_map[scancode];
        } 
    }

}