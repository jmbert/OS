#ifndef _IO__H
#define _IO__H

#include "types.h"

/**
 * Printf to vga screen.
 * 
 * Takes %s, %c, %x, %d, %b
 * 
 * @param fmt Format text
 * @param ... List of values to load into format
 */
void printk(char *fmt, ...);

/**
 * Print string primitive,
 * 
 * only used by higher-level print functions.
 * 
 * @param string String to print. 
 */
void print(char *string);

/**
 * Print denary primitive,
 * 
 * only used by higher-level print functions.
 * 
 * @param n Number to print. 
 */
void print_number(int n);

/**
 * Print binary primitive,
 * 
 * only used by higher-level print functions.
 * 
 * @param n Number to print. 
 */
void print_binary(int n);

/**
 * Print hex primitive,
 * 
 * only used by higher-level print functions.
 * 
 * @param n Number to print. 
 */
void print_hex(int n);

/**
 * Writes character to vga text buffer.
 * 
 * @param chr Char to write
 */
void write_to_buffer(uint8_t chr);

/**
 * Get the address of the vga text buffer.
 * 
 * @return Pointer to the text buffer.
 */
uint8_t *get_buffer();

/**
 * Initialises IO variables.
 * 
 * Only called by init.
 */
void init_io();

/**
 * Clears text buffer.
 */
void clear_buffer();

/**
 * Set the cursor position.
 * 
 * @param x Set cursor x-position.
 * @param y Set cursor y-position.
 */
void set_cursor(uint32_t x, uint32_t y);

/**
 * Get the cursor x-position
 * 
 * @return x Position 
 */
uint32_t get_cursor_x();

/**
 * Get the cursor y-position
 * 
 * @return y Position 
 */
uint32_t get_cursor_y();

#endif // _IO__H