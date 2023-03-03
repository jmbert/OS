#include "processes.h"
#include "../../lib/lib.h"
#include "../../drivers/pic.h"

process_t *proc_queue; // Process queue.
process_t *current_proc; // Currently running process. 

int processes = -1; // Number of processes.

void load_process(uint8_t *exec) {

    process_t proc;
    proc.exec = exec;
    proc.esp = (uint8_t*)malloc(0x1000);
    proc.fresh = 1;

    processes++;
    proc_queue[processes] = proc;
    
    return;
}

process_t *advance_next_process() {
    process_t *lastProc = current_proc;
    proc_queue[processes+1] = *lastProc;

    for (int i = 0; i <= processes; i++)
    {
        proc_queue[i] = proc_queue[i+1];
    }

    *current_proc = proc_queue[0];
    
    return current_proc;
}

void switch_process() {
    __asm__("mov %0, %%esp" :: "m"(current_proc->esp));

    if (current_proc->fresh) {
        __asm__("sti");
        __asm__("jmp %0" :: "m"(current_proc->exec));
    }

    return;
}

void end_process(process_t* proc) {
    processes--;
    return;
}

process_t *get_current_process() {
    return current_proc;
}