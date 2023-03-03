#ifndef _PROCESSES__H
#define _PROCESSES__H

#include "../../lib/types.h"

/**
 *  Process type used for handling processes. 
 */
typedef struct {
    /**
     * Stack pointer for this process.
     */
    uint8_t *esp;
    /**
     * Pointer to start of process execeutable
     */
    uint8_t *exec;


    /**
     * Indicator as to whether this process has begun execeution.
     */
    uint8_t fresh;
}process_t;

/** 
 * Function for loading processes into the queue.
 * 
 * @param exec Pointer to start of execeutable
 */
void load_process(uint8_t *exec);

/**
 * Advances the current process
 * 
 * @return Pointer to the new process in queue.
 */
process_t *advance_next_process();

/**
 * Ends process from running |||WIP|||
 * 
 * @param proc Process to end
 */
void end_process(process_t* proc);

/**
 * Get the currently running process in the queue.
 * 
 * @return Pointer to the currently running process.
 */
process_t *get_current_process();

/**
 * Switches to the current process.
 * 
 * Call advance_next_process before calling.
 * 
 * Dangerous to call outside of the PIT interrupt handler.
 */
void switch_process();

#endif // _PROCESSES__H