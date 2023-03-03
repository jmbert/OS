#ifndef _PIC__H
#define _PIC__H
#include "../lib/types.h"

#define PIC_1 0x20 // master PIC
#define PIC_2 0xa0 // slave PIC
#define PIC_1_COMMAND	PIC_1 // Master PIC command
#define PIC_1_DATA	    (PIC_1+1) // Master PIC data
#define PIC_2_COMMAND	PIC_2 // Slave PIC command
#define PIC_2_DATA	    (PIC_2+1) // Slave PIC data

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */
 
/**
 * Gets an interrupt register
 * 
 * @param ocw3 Either PIC_READ_IRR or PIC_READ_ISR
 * @return Contents of either register
 */
uint16_t __pic_get_irq_reg(int ocw3);
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr();
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr();
 
/**
 * Sets the interrupt mask on the PIC
 * 
 * @param bitmask Binary, 1 represents masked, 0 unmasked
 * @param chip Chip to set mask of
 */
void IRQ_set_mask(uint8_t bitmask, int chip);

#define EOI 0x20  // End of interrupt command

/**
 * Sends an EOI to the PIC, allowing the PIC to send another interrupt
 * 
 * @param irq 
 */
void PIC_send_eoi(uint8_t irq);

/**
 * Remap the PIC irq vectors
 * 
 * @param offset1 Master offset
 * @param offset2 Slave offset
 */
void PIC_remap(int offset1, int offset2);

#endif // _PIC__H