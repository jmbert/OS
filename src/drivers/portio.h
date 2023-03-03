#ifndef _PORTIO__H
#define _PORTIO__H

#include "../lib/types.h"

/**
 * Sends a byte to a port
 * 
 * @param data Byte to send
 * @param port Port to send byte to
 */
void outb(uint8_t data, uint8_t port);

/**
 * Reads a byte form a port
 * 
 * @param port Port to read byte from
 * @return Contents of read port 
 */
uint8_t inb(uint8_t port);

/**
 * Short wait time
 * 
 * Done by sending hex 80 to port 0
 */
void io_wait();

#endif // _PORTIO__H