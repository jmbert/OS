#include "vga.h"
#include "../lib/types.h"

uint8_t bg_colour;
uint8_t text_colour;

void initVGA() {
    bg_colour = 0x20;
    text_colour = 0x40;
    fill_screen(bg_colour);
}

void set_video_memory(uint8_t colour, int offset) {
    *(uint8_t*)(VIDEO_MEMORY+offset) = colour;
}

uint8_t get_video_memory(int offset) {
    return *(uint8_t*)(VIDEO_MEMORY+offset);
}

void set_pixel(uint8_t colour, int x, int y) {
    set_video_memory(colour, y*SCREEN_WIDTH + x);
}

uint8_t get_pixel(int x, int y) {
    return get_video_memory(y*SCREEN_WIDTH + x);
}

void fill_screen(uint8_t colour) {
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            set_pixel(colour, x, y);
        }        
    }
}

void draw_char(char chr, int *x_offset, int *y_offset) {
    switch (chr)
    {
    case '\n':
        *x_offset = 0;
        *y_offset += 16;
        return;
    case '\t':
        for (int i = 0; i < 4; i++)
        {
            draw_char(' ', x_offset, y_offset);
        }
        return;
    case '\r':
        *y_offset += 16;
        return; 
    }

    for (int x = 0; x < CHAR_WIDTH; x++)
    {
        for (int y = 0; y < CHAR_HEIGHT; y++)
        {
            if((*(uint8_t*)(0x5000 + chr*16+y)) & 1 << x) {        
                set_pixel(text_colour, *x_offset+7-x, *y_offset+y);
            } else {
                set_pixel(bg_colour, *x_offset+7-x, *y_offset+y);
            }
        }        
    }
    if (*x_offset + 8 < SCREEN_WIDTH) {
        *x_offset += 8;
    } else {
        *x_offset = 0;
        *y_offset += 16;
    }  
    
}

void draw_buffer(uint8_t *text_buffer) {
    int x = 0;
    int y = 0;
    for (int chr_offset = 0; chr_offset < BUFFER_SIZE; chr_offset++)
    {
        uint8_t chr = text_buffer[chr_offset];
        switch (chr)
        {
        case '\n':
            for (int i = 0; i < SCREEN_WIDTH/8 - x/8; i++)
            {
                int x_tmp = x;
                int y_tmp = y;
                draw_char(' ', &x_tmp, &y_tmp);
            }
            break;

        case '\r':
            for (int i = 0; i < SCREEN_WIDTH/8; i++)
            {
                int x_tmp = x;
                int y_tmp = y;
                draw_char(' ', &x_tmp, &y_tmp);
            }
            break;
        
        default:
            break;
        }
        draw_char(chr, &x, &y);
    }
    
}