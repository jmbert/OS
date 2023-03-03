#ifndef _PIT__H
#define _PIT__H

#include "portio.h"

#define CHANNEL_0 0x40 // CHannel 0 of the PIT
#define CHANNEL_1 0x41 // Channel 1 of the PIT
#define CHANNEL_2 0x42 // CHannel 2 of the PIT

#define CMD 0x43 // Prepare PIT for command



/**
 * Set the PIT frequency
 * 
 * @param set_frequency Frequency in hertz
 */
void set_frequency(uint16_t set_frequency);


#endif // _PIT__H