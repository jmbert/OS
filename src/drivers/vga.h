#ifndef _VGA__H // Header guard
#define _VGA__H
#include "../lib/types.h"

#define VIDEO_MEMORY 0xa0000

#define FONTLOC 0x5000

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define CHAR_HEIGHT 16
#define CHAR_WIDTH 8

#define CHAR_SPACING 1

#define BUFFER_SIZE (SCREEN_HEIGHT/16)*(SCREEN_WIDTH/8)

#define EOS '\0'

void set_video_memory(uint8_t colour, int offset);

uint8_t get_video_memory(int offset);

void set_pixel(uint8_t colour, int x, int y);

uint8_t get_pixel(int x, int y);


void fill_screen(uint8_t colour);

void draw_char(char chr, int *x_offset, int *y_offset);

void draw_buffer(uint8_t *textBuffer);

#endif // _VGA__H