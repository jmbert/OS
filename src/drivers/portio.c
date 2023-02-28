#include "portio.h"
#include "../lib/types.h"

void outb(uint8_t data, uint8_t port) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint8_t inb(uint8_t port) {
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void io_wait() {
    outb(0x80, 0);
}