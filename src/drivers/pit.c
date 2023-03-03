#include "pit.h"

void set_frequency(uint16_t frequency) {
    outb(CMD, 0x36);

    uint16_t freqDivider = 1193182/frequency;

    outb(CHANNEL_0, 11931 % 256);

    outb(CHANNEL_0, 11931 >> 8);
}