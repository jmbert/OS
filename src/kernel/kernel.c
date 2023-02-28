#include "../drivers/vga.h"
#include "../lib/types.h"
#include "../interruptHandling/idt.h"
#include "../drivers/pic.h"
#include "../drivers/keyboard.h"
#include "../common/variables.h"
#include "../lib/io.h"
#include "processes.h"

void extern init() {
    initVGA();
    init_io();
    PIC_remap(0x20, 0x28);
    idt_init();
    init_keyboard();

    init_vars();
    
    
    IRQ_set_mask(0b00010000, 0);
    IRQ_set_mask(0b00000000, 1);
    

    main();
    return;
}

void prt_a() {
    for (;;) {
        if (get_timer() % 10 == 0) {
            printf("a");
        }
    }
}

void prt_b() {
    for (;;) {
        if (get_timer() % 13 == 0) {
            printf("b");
        }
    }
}

void main() {

    process_t *a = load_process(&prt_a);
    process_t *b = load_process(&prt_b);

    for (;;)
    {
        printf("%d ", get_timer());
        __asm__("int $32");
    }
    

    end();
    return;
}



void end() {
    __asm__("cli; hlt");
}