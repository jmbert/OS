#ifndef _PORTIO__H // Header guard
#define _PORTIO__H

#include "../lib/types.h"

void outb(uint8_t data, uint8_t port);
uint8_t inb(uint8_t port);
void io_wait();

#endif // _PORTIO__H