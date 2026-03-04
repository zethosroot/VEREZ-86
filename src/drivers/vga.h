#pragma once

#include <stdint.h>
#include <stddef.h>

// Define colors
enum {
    VGA_COLOR_BLACK       = 0,
    VGA_COLOR_BLUE        = 1,
    VGA_COLOR_GREEN       = 2,
    VGA_COLOR_CYAN        = 3,
    VGA_COLOR_RED         = 4,
    VGA_COLOR_MAGENTA     = 5,
    VGA_COLOR_BROWN       = 6,
    VGA_COLOR_LIGHT_GRAY  = 7,
    VGA_COLOR_DARK_GRAY   = 8,
    VGA_COLOR_WHITE       = 15,
};


// Declare struct. Each cell on vga screen is 2 bytes. 
// One byte for ascii and one for color.
struct Char {
    uint8_t character;
    uint8_t color;
};

void vga_init();
void vga_clear();
void vga_putchar(char c);
void vga_print(const char* str);
void vga_set_color(uint8_t fg, uint8_t bg);