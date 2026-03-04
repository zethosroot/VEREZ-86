#include "vga.h"
#include "../config.h"

static struct Char* buffer = (struct Char*) 0xb8000;

static size_t col = 0;
static size_t row = 0;
static uint8_t color = VGA_COLOR_WHITE | VGA_COLOR_BLACK << 4;

void vga_init(){
    col = 0;
    row = 0;
    vga_clear();
}

void vga_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {
            buffer[j + NUM_COLS * i] = (struct Char) {
                .character = ' ',
                .color = color,
            };
        }
    }
    col = 0;
    row = 0;
}

void vga_putchar(char c) {
    if (c == '\n') {
        col = 0;
        row++;
        return;
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        .character = (uint8_t) c,
        .color = color,
    };

    col++;
    if (col >= NUM_COLS) {
        col = 0;
        row++;
    }
}

void vga_print(const char* str) {
    
    if (!str) return; // If no input, return
    
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}

void vga_set_color(uint8_t fg, uint8_t bg) {
    color = fg | bg << 4;
}