#ifndef _ISR__H
#define _ISR__H

#include "../lib/types.h"

typedef struct {
    uint8_t aligment_len;
    uint16_t ss;
    uint32_t esp;

}int_stack_frame;

void dummy_interrupt_handler();

void div0_handler();

void pg_fault_handler();

void gpf_handler();

void systimer_handler();

void keyboard_handler();

#endif // _ISR__H