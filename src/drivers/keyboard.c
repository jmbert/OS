#include "keyboard.h"
#include "ps2.h"
#include "../lib/types.h"

command echoCmd;
command enableScanningCmd;
command disableScanningCmd;

uint8_t *keymap;
void set_keymap() {
    uint8_t keymapInit[90] =
    {
        0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
      '9', '0', '-', '=', '\b',	/* Backspace */
      '\t',			/* Tab */
      'q', 'w', 'e', 'r',	/* 19 */
      't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
        0,			/* 29   - Control */
      'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
     '\'', '#',   0,		/* Left shift */
     '#', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
      'm', ',', '.', '/',   0,				/* Right shift */
      '*',
        0,	/* Alt */
      ' ',	/* Space bar */
        0,	/* Caps lock */
        0,	/* 59 - F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,	/* < ... F10 */
        0,	/* 69 - Num lock*/
        0,	/* Scroll Lock */
        0,	/* Home key */
        0,	/* Up Arrow */
        0,	/* Page Up */
      '-',
        0,	/* Left Arrow */
        0,
        0,	/* Right Arrow */
      '+',
        0,	/* 79 - End key*/
        0,	/* Down Arrow */
        0,	/* Page Down */
        0,	/* Insert Key */
        0,	/* Delete Key */
        0,   0,  '\\',
        0,	/* F11 Key */
        0,	/* F12 Key */
       0,	/* All other keys are undefined */
    };

    for (int i = 0; i < 90; i++)
    {
        keymap[i] = keymapInit[i];
    }
}

void set_keymap_shift() {
    uint8_t keymap_shift[90] =
    {
        0,  27, '!', '\"', '£', '$' /* shift+4 */, '%', '^', '&', '*',	/* 9 */
      '(', ')', '_', '+', '\b',	/* Backspace */
      '\t',			/* Tab */

     'Q', 'W', 'E', 'R',   /* 19 */
      'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
        0,          /* 29   - Control */
      'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
     '@', '~',   0,        /* Left shift */
     '~', 'Z', 'X', 'C', 'V', 'B', 'N',            /* 49 */
      'M', '<', '>', '?',   0,              /* Right shift */

      '*',
        0,	/* Alt */
      ' ',	/* Space bar */
        0,	/* Caps lock */
        0,	/* 59 - F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,	/* < ... F10 */
        0,	/* 69 - Num lock*/
        0,	/* Scroll Lock */
        0,	/* Home key */
        0,	/* Up Arrow */
        0,	/* Page Up */
      '-',
        0,	/* Left Arrow */
        0,
        0,	/* Right Arrow */
      '+',
        0,	/* 79 - End key*/
        0,	/* Down Arrow */
        0,	/* Page Down */
        0,	/* Insert Key */
        0,	/* Delete Key */
        0,   0,   '|',
        0,	/* F11 Key */
        0,	/* F12 Key */
        0,	/* All other keys are undefined */
    };

    for (int i = 0; i < 90; i++)
    {
        keymap[i] = keymap_shift[i];
    }
}
void init_keyboard() {
    echoCmd.cmdByte = ECHO;
    enableScanningCmd.cmdByte = ENABLESCANNING;
    disableScanningCmd.cmdByte = DISABLESCANNING;
    
    set_keymap();
}

void send_command(command cmd) {
    int retry = 1;
    for (int i = 0; i < 4; i++)
    {
        if (!retry) {
            break;
        }
        send_device_byte(cmd.cmdByte, 0);
        uint16_t response = read_ps2_io();
        if (response == ACK || (response == ECHO && cmd.cmdByte == ECHO)) {
            retry = 0;
        }
    }
    
    if (!retry) {
        send_device_byte(cmd.argByte, 0);
    }
    
}

uint8_t receive_byte() {
    return read_ps2_io();
}

command echo() {
    return echoCmd;
}

command enable_scanning() {
    return enableScanningCmd;
}

command disable_scanning() {
    return disableScanningCmd;
}


keyReturn get_key(int scancode) {
    keyReturn key;
	uint8_t c = 0;

    if (scancode == 0x2a) {
        set_keymap_shift();
        key.print = 0;
        return key;
    } else if (scancode == 0xaa) {
        set_keymap();
        key.print = 0;
        return key;
    }

    if (scancode < 0x80) {
        c = keymap[scancode];
        key.print = 1;
        key.chr = c;
    } else {
        key.print = 0;
    }

    return key;
}