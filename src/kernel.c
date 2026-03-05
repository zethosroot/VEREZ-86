#include "drivers/vga.h"
#include "drivers/keyboard.h"
#include "basic/basic.h"

void delay() {
    for (int i = 0; i < 10000000; i++); // Temporary solution for delay
}

void kernel_main() {
    
    char line[128];
    int pos = 0;
    
    vga_init();
    for (int i = 0; i < 11; i++) vga_print("\n");
    vga_print_centered("VEREZ/86");
    vga_print("\n");
    vga_print_centered("by zethosroot and technik7585");
    delay();
    vga_clear();
    vga_putchar('\n');
    vga_print_centered("**** VEREZ/86 BASIC V1.0 ****\n");
    vga_print_centered("128K RAM SYSTEM  32768 BASIC BYTES FREE"); // Placeholder numbers :) TODO: Read from multiboot memory map
    vga_print("\nREADY.\n");

    while (1) {
        char c = kbd_getchar();
        if (c == '\n') {
            vga_print("\n");
            line[pos] = '\0';
            basic_eval(line);
            vga_print("\nREADY.\n");
            pos = 0;
        } else if (c == '\b') {
            if (pos > 0) {
                pos--;
                vga_putchar('\b');
            }
        } else {
            if (c != 0) {  // only store valid characters
                line[pos++] = c;
                vga_putchar(c);
            }
        }
    }
}