#ifndef _KEYBOARD__H
#define _KEYBOARD__H

#include "../lib/types.h"

/**
 * Type that getKey will return
 * 
 */
typedef struct keyReturn {
    uint8_t chr; // Character to print
    int print; // Whether to print this character (e.g. if it is a key release)
} keyReturn;

#define ACK 0xfa // Acknowledge (sent by keyboard)
#define RESEND 0xfe // Resend (sent by keyboard)

#define ECHO 0xee // Acknowledge (sent by user and keyboard)

#define ENABLESCANNING 0xf4 // Enable scanning (sent by user)
#define DISABLESCANNING 0xf5 // Disable scanning (sent by user)

/**
 * Receive a byte from the keyboard
 * 
 * @return Byte from keyboard
 */
uint8_t receive_byte();

/**
 * Sets the normal (unshifted) keymap
 * 
 */
void set_keymap();

/**
 * Sets the shifted keymap
 * 
 */
void set_keymap_shift();

/**
 * Initialises keyboard
 * 
 */
void init_keyboard();

/**
 * Returns a keyreturn for a given scancode
 * 
 * @param scancode 
 * @return keyReturn 
 */
keyReturn get_key(int scancode);

#endif // _KEYBOARD__H