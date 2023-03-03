#ifndef _PS2__H
#define _PS2__H

#define IO_PORT 0x60 // PS2 IO poret
#define STATUS_CMD_PORT 0x64 // PS2 port to get status from, and send cmds to

#define TEST_CONTROLLER 0xaa // Command to test if controller is on

#define ENABLE_PORT1 0xae // Enables device 1
#define DISABLE_PORT1 0xad // Disables device 1

#define ENABLE_PORT2 0xa8 // Enables device 2
#define DISABLE_PORT2 0xa7 // Disables device 2

#define TEST_PORT1 0xab // Tests device 1
#define TEST_PORT2 0xa9 // Tests device 2

#define READ_CCB 0x20 // Read Controller Configuration Byte
#define WRITE_CCB 0x60 // Write Controller Configuration Byte

#define READ_OUTPUT 0xD0 // Read Controller Outport Byte
#define WRITE_OUTPUT 0xD1 // Write Controller Outport Byte

#define RESET_CMD 0xff // Reset Command (Send to device)

/**
 * Write to PS2 IOPort
 * 
 * @param data Byte to write
 * @return timed out
 */
int write_ps2_io(unsigned char data);

/**
 * Reads PS2 IOPort
 * 
 * @return First Byte: IOPort contents, Second Byte: 0x0f is timed out, 0x00 is a true response
 */
unsigned short read_ps2_io();

/**
 * Get PS2 status.
 * 
 * @return Status byte 
 */
unsigned char get_status();

/**
 * Send a cmd to the PS2
 * 
 * @param cmd Command byte to send
 */
void send_cmd(unsigned char cmd);

/**
 * Send a byte to a device
 * 
 * @param cmd Command to send
 * @param device Device to send it to (0 is device 1, 1 is device 2) 
 */
void send_device_byte(unsigned char cmd, int device);

/**
 * Reads ioport (wrapped by read_ps2_io, do not call)
 * 
 * @return response 
 */
unsigned short get_response();

/**
 * Tests PS2 Controller
 * 
 * @return 0 for success, 1 for failure 
 */
int test_ps2();

/**
 * Initialises PS2 Controller (called by init, do not call)
 * 
 * @return 0 for success, 1 for failure
 */
int init_ps2();

#endif // _PS2__H