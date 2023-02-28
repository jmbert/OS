#include "isr.h"
#include "../lib/types.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../drivers/pic.h"
#include "../common/variables.h"
#include "../kernel/processes.h"

uint32_t IDT_desc;

void extern irq_handler() {
    int irq;
    irq = *(uint8_t*)0x8000;
    switch (irq)
    {
    case 32:
        handle_timer();
        break;
    case 33:
        handle_keypress();
        break;
    default:
        int x = 0;
        int y = 16;
        print("Unhandled Interrupt", &x, &y);
        x = 176;
        print_number(irq, &x, &y);
        break;
    }
    PIC_send_eoi(irq);
    return;
}

void extern exception_handler()  {
    int irq;
    irq = *(uint8_t*)0x8000;
    int x = 0;
    int y = 0;
    print("Exception", &x, &y);
    x = 88;
    print_number(irq, &x, &y);
    return;
}

void handle_timer() {

    uint16_t ip;
    __asm__("popw %0" : "m="(ip));
    uint16_t cs;
    __asm__("popw %0" : "m="(cs));
    uint16_t Rflags;
    __asm__("popw %0" : "m="(Rflags));
    uint16_t sp;
    __asm__("popw %0" : "m="(sp));
    uint16_t ss;
    __asm__("popw %0" : "m="(ss));

    process_t *proc = advance_next_process();

    __asm__("movl %0, %%esp" :: "m"(proc->stack));

    ip = proc->exec;

    __asm__("pushw %0" :: "m"(ss));
    __asm__("pushw %0" :: "m"(sp));
    __asm__("pushw %0" :: "m"(Rflags));
    __asm__("pushw %0" :: "m"(cs));
    __asm__("pushw %0" :: "m"(ip));

    inc_timer();
    
    return;
}

void handle_keypress() {
    uint8_t scancode = receive_byte();
    keyReturn keyRet = get_key(scancode);
    if (keyRet.print) {
        printf("%c", keyRet.chr);
    }
    return;
}