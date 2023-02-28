#ifndef _KEYBOARD__H
#define _KEYBOARD__H

#include "../lib/types.h"

typedef struct command {
    uint8_t cmdByte;
    uint8_t argByte;
    int arg;
} command;

typedef struct keyReturn {
    uint8_t chr;
    int print;
} keyReturn;

#define ACK 0xfa
#define RESEND 0xfe

#define ECHO 0xee

#define ENABLESCANNING 0xf4
#define DISABLESCANNING 0xf5

void send_command(command cmd);

uint8_t receive_byte();

command echo();

command enable_scanning();

command disable_scanning();

void set_keymap();

void set_keymap_shift();

void init_keyboard();

keyReturn get_key(int scancode);
#endif