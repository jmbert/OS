#ifndef _IDT__H
#define _IDT__H

#define IDT_MAX_DESCRIPTORS 256

typedef struct {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     zero;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;
}__attribute__((packed)) gate_entry_t;

typedef struct {
	uint16_t size;
	uint32_t start;
}__attribute__((packed)) idtr_t;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

void idt_init();

#endif