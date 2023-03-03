#include "../drivers/vga.h"
#include "../lib/types.h"
#include "../interrupt_handling/idt.h"
#include "../drivers/pic.h"
#include "../drivers/keyboard.h"
#include "../common/variables.h"
#include "../lib/io.h"
#include "process_switching/processes.h"
#include "process_switching/std_processes.h"

/**
 * Call all different init functions as well as setting IRQ masks and loading processes.
 * 
 * Called from kernel_entry;
 */
void extern init() {
    initVGA();
    init_io();

    PIC_remap(0x20, 0x28);
    init_keyboard();

    init_vars();

    IRQ_set_mask(0b00010000, 0);
    IRQ_set_mask(0b00000000, 1);

    load_process(idle);

    idt_init();
    main();
    return;
}

void prt_a() {
    for (;;) {
        if (get_timer() % 10) {
            printk("a");
        }   
    }
    return;
}

void prt_b() {
    for (;;) {
        if (get_timer() % 13) {
            printk("b");
        }  
    }
    return;
}

/**
 * Main kernel function.
 * 
 * Called after end of initialisation.
 * 
 */
void main() {

    load_process(prt_a);
    load_process(prt_b);
    
    switch_process();
    
    end();
    return;
}


/**
 * Halts CPU and disables interrupts.
 */
void end() {
    __asm__("cli; hlt");
}