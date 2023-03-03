#ifndef _ISR__H
#define _ISR__H

/**
 * Regular interrupt handler, should only be called from isr_asm.
 */
void extern irq_handler();

/**
 * Handler for INT 32, aka PIT interrupt timer.
 * 
 * Also currently manages process switching.
 */
void handle_timer();

/**
 * Handler for INT 33, aka PS2 keypress.
 */
void handle_keypress();

#endif // _ISR__H