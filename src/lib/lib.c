#include "lib.h"

uint8_t *next_addr = START_ADDR;

void *malloc(uint32_t size) {
    void *_return = (void*)next_addr;
    next_addr += size;
    return _return;
}   