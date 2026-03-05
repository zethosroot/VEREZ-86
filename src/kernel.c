#include "drivers/vga.h"

void delay() {
    for (int i = 0; i < 10000000; i++); // Temporary solution for delay
}

void kernel_main() {
    vga_init();
    for (int i = 0; i < 11; i++) vga_print("\n");
    vga_print_centered("VEREZ/86");
    vga_print("\n");
    vga_print_centered("by zethosroot and technik7585");
    delay();
    vga_clear();
    vga_print_centered("**** VEREZ/86 BASIC V1.0 ****\n");
    vga_print_centered("128K RAM SYSTEM  32768 BASIC BYTES FREE"); // Placeholder numbers :) TODO: Read from multiboot memory map
    vga_print("\nREADY.\n");
}