#ifndef _VGA__H // Header guard
#define _VGA__H
#include "../lib/types.h"

#define VIDEO_MEMORY 0xa0000 // Start of video memory

#define FONTLOC 0x5000 // Location the bootloader saves the VGA BIOS font in

#define SCREEN_WIDTH 320 // Number of pixels across the screen
#define SCREEN_HEIGHT 200 // Number of pixels down the screen

#define CHAR_HEIGHT 16 // Number of y pixels each character uses
#define CHAR_WIDTH 8 // Number of x pixels each character uses

#define BUFFER_SIZE (SCREEN_HEIGHT/16)*(SCREEN_WIDTH/8) // Length of VGA text buffer

#define EOS '\0' // End of string

/**
 * Set a pixel of video memory
 * 
 * @param colour Colour to set
 * @param offset Offset from VIDEO_MEMORY
 */
void set_video_memory(uint8_t colour, int offset);

/**
 * Read a pixel of video memory
 * 
 * @param offset Offset from VIDEO_MEMORY 
 * @return colour at pixel offset
 */
uint8_t get_video_memory(int offset);

/**
 * Set a pixel on vga screen
 * 
 * @param colour Colour to set pixel
 * @param x X-Coordinate
 * @param y Y-Coordinate
 */
void set_pixel(uint8_t colour, int x, int y);

/**
 * Get a pixel on vga screen
 * 
 * @param x X-Coordinate
 * @param y Y-Coordinate
 * @return colour 
 */
uint8_t get_pixel(int x, int y);

/**
 * Fill the screen with a colour
 * 
 * @param colour Colour to fill the screen with
 */
void fill_screen(uint8_t colour);

/**
 * Draw a character to the vga screen
 * 
 * @param chr Character to draw
 * @param x_offset X offset to draw at (left)
 * @param y_offset Y offset to draw at (top)
 */
void draw_char(char chr, int *x_offset, int *y_offset);

/**
 * Draws the text buffer
 * 
 * @param textBuffer Pointer to a text buffer
 */
void draw_buffer(uint8_t *textBuffer);


#endif // _VGA__H