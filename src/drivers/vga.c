#include "vga.h"
#include "../../config.h"
#include "io.h"
#include "../../lib/vzstring.h"

static struct Char* buffer = (struct Char*) 0xb8000;

static size_t col = 0;
static size_t row = 0;
static uint8_t color = VGA_COLOR_GREEN | VGA_COLOR_BLACK << 4;

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
        if (row >= NUM_ROWS) vga_scroll();
        vga_update_cursor(row * NUM_COLS + col);
        return;
    }

    if (c == '\b') {
        if (col > 0) col--;
        buffer[col + NUM_COLS * row] = (struct Char){ .character = ' ', .color = color };
        vga_update_cursor(row * NUM_COLS + col);
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

    if (row >= NUM_ROWS) vga_scroll();

    uint16_t pos = row * NUM_COLS + col;

    vga_update_cursor(pos);
}

void vga_print(const char* str) {
    
    if (!str) return; // If no input, return
    
    for (int i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}

void vga_print_centered(const char* str) {
    int indent = (NUM_COLS - vzstrlen(str)) / 2;

    for (int i = 0; i < indent; i++) {
        vga_putchar(' ');
    }

    vga_print(str);
}

void vga_set_color(uint8_t fg, uint8_t bg) {
    color = fg | bg << 4;
}

void vga_update_cursor(uint16_t pos) {
    outb(0x3D4, 0x0E);
    outb(0x3D5, pos >> 8);

    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
}

void vga_scroll() {
    
    for (size_t i = 1; i < NUM_ROWS; i++) {
        for (size_t j = 0; j < NUM_COLS; j++) {
            buffer[j + NUM_COLS * (i-1)] = buffer[j + NUM_COLS * i];
        }
    }
    // clear last row
    for (size_t j = 0; j < NUM_COLS; j++) {
        buffer[j + NUM_COLS * (NUM_ROWS - 1)] = (struct Char){ .character = ' ', .color = color };
    }
    row = NUM_ROWS - 1;
}