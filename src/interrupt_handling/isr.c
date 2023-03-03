#include "isr.h"
#include "../lib/types.h"
#include "../lib/io.h"
#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../drivers/pic.h"
#include "../common/variables.h"
#include "../kernel/process_switching/processes.h"

uint32_t IDT_desc;  // IDT descriptor


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
        if (irq < 32) {
            printf("Unhandled Exception #: %d\n", irq);
            break;
        }
        printf("Unhandled Interrupt #: %d\n", irq);
        PIC_send_eoi(irq);
        break;
    }
    return;
}


void handle_timer() {
    inc_timer();
    advance_next_process();
    PIC_send_eoi(32);
    switch_process();
    return;
}

void handle_keypress() {
    uint8_t scancode = receive_byte();
    keyReturn keyRet = get_key(scancode);
    if (keyRet.print) {
        printf("%c", keyRet.chr);
    }
    PIC_send_eoi(33);
    return;
}