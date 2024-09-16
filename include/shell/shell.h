#ifndef BORIS_SHELL
#define BORIS_SHELL

#include "utils/string.h"
#include "video/vga.h"
#include "utils/types.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_put_entry_at(char character, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(character,color);
}

void initialize_terminal(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_DARK_GREY,VGA_COLOR_CYAN);
    terminal_buffer = (uint16_t*) 0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            terminal_put_entry_at(' ', terminal_color, x, y);
        }
        
    }    
}

void terminal_set_color(vga_color color) {
    terminal_color = color;
}

void terminal_put_char(char character) {
    terminal_put_entry_at(character, terminal_color, terminal_column, terminal_row);
    if(++terminal_column == VGA_WIDTH) {
        terminal_column = 0;

        if(++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        terminal_put_char(data[i]);
    }
}

void terminal_write_string(const char* data) {
    terminal_write(data,strlen(data));
}


#endif