#include "pic.h"
#include "portio.h"
#include "../lib/types.h"

void PIC_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(EOI, PIC_2_COMMAND);
    }
    outb(EOI, PIC_1_COMMAND);
}

void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2;
 
	a1 = inb(PIC_1_DATA);                        // save masks
	a2 = inb(PIC_2_DATA);
 
	outb(ICW1_INIT | ICW1_ICW4, PIC_1_COMMAND);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(ICW1_INIT | ICW1_ICW4, PIC_2_COMMAND);
	io_wait();
	outb(offset1, PIC_1_DATA);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(offset2, PIC_2_DATA);               // ICW2: Slave PIC vector offset
	io_wait();
	outb(4, PIC_1_DATA);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(2, PIC_2_DATA);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(ICW4_8086, PIC_1_DATA);
	io_wait();
	outb(ICW4_8086, PIC_2_DATA);
	io_wait();
 
	outb(a1, PIC_1_DATA);   // restore saved masks.
	outb(a2, PIC_2_DATA);
}

void IRQ_set_mask(uint8_t bitmask, int chip) {
    uint16_t port;
 
    if (!chip) {
        port = PIC_1_DATA;
    } else {
        port = PIC_2_DATA;
    }
    outb(bitmask, port);        
}
 
/* Helper func */
uint16_t __pic_get_irq_reg(int ocw3) {
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(ocw3, PIC_1_COMMAND);
    outb(ocw3, PIC_2_COMMAND);
    return (inb(PIC_2_COMMAND) << 8) | inb(PIC_1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr(void) {
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr(void) {
    return __pic_get_irq_reg(PIC_READ_ISR);
}