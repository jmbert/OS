#include "../lib/types.h"
#include "idt.h"

gate_entry_t idt[256]; // IDT to fill

idtr_t idtr; // IDT register

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    gate_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->zero       = 0;
}

extern void* isr_stub_table[]; // Reference to the stub table located in isr_asm

void idt_init() {
    idtr.start = (uint32_t)&idt[0];
    idtr.size = (uint16_t)sizeof(gate_entry_t) * IDT_MAX_DESCRIPTORS - 1;
 
    for (uint8_t vector = 0; vector < 64; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    }
 
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}