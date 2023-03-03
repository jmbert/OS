#ifndef _LIB__H
#define _LIB__H

#include "types.h"

#define START_ADDR 0x10000 // First address to allocate to.

/**
 * Basic malloc implementation.
 * 
 * @param size Number of bytes to allocate
 * @return void* Void pointer to the beginning of the allocation
 */
void *malloc(uint32_t size);

#endif // _LIB__H