#ifndef _PS2__H
#define _PS2__H

#define IO_PORT 0x60
#define STATUS_CMD_PORT 0x64

#define TEST_CONTROLLER 0xaa

#define ENABLE_PORT1 0xae
#define DISABLE_PORT1 0xad

#define ENABLE_PORT2 0xa8
#define DISABLE_PORT2 0xa7

#define TEST_PORT1 0xab
#define TEST_PORT2 0xa9

#define READ_CCB 0x20
#define WRITE_CCB 0x60

#define READ_OUTPUT 0xD0
#define WRITE_OUTPUT 0xD1

#define RESET_CMD 0xff

int write_ps2_io(unsigned char data);

unsigned short read_ps2_io();

unsigned char get_status();

void send_cmd(unsigned char cmd);

void send_device_byte(unsigned char cmd, int device);

unsigned short get_response();

int test_ps2();

int init_ps2();

#endif