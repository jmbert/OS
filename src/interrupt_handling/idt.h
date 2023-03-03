#ifndef _IDT__H
#define _IDT__H

#define IDT_MAX_DESCRIPTORS 256


/**
 * IDT gate entry type.
 * 
 * 32 bit
 */
typedef struct {
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     zero;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high; // The higher 16 bits of the ISR's address
}__attribute__((packed)) gate_entry_t;

/**
 * IDT register type.
 * 
 * 32 bit
 */
typedef struct {
	uint16_t size; // Size of IDT in bytes
	uint32_t start; // Location of IDT
}__attribute__((packed)) idtr_t;

/**
 * Set IDT descriptor
 * 
 * @param vector Interrupt vector to load into idt 
 * @param isr Pointer to the interrupt location
 * @param flags Flags to load
 */
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

/**
 * Initalise IDT
 * 
 */
void idt_init();

#endif // _IDT__H