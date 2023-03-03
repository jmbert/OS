#include "portio.h"
#include "ps2.h"

int ps2Working; // Bool to check if the PS2 works

int ps2Device2Enabled; // Bool to check if the PS2 can handle 2 devices
int ps2Device1Working; // Bool to check if the first device is working
int ps2Device2Working; // Bool to check if the second device is working

unsigned short device1Type; // First device type (unused)
unsigned short device2Type; // Second device type (unused)

unsigned char get_status() {
    return inb(STATUS_CMD_PORT);
}

void send_cmd(unsigned char cmd) {
    unsigned char status = get_status();
    if (!(status & 0b10)) {
        outb(cmd, STATUS_CMD_PORT);
    }
}

int write_ps2_io(unsigned char data) {
    for (int i = 0; i < 100 ;i++)
    {
        unsigned char status = get_status();
        if (!(status & 1)) {
            outb(data, IO_PORT);
            return 0;
        }
    }
    return 1;
}

unsigned short get_response() {
    unsigned char status = get_status();
    if (status & 1) {
        return inb(IO_PORT);
    } else {
        return 0xf00;
    }
}

unsigned short read_ps2_io() {
    for (int i = 0; i < 100 ;i++)
    {
        unsigned short response = get_response();
        if (response != 0xf00) {
            return response;
        } 
    }
    return 0xf00;
    
}


int test_ps2() {
    send_cmd(READ_CCB);
    unsigned short response = get_response();
    unsigned char ccb = response%256;
    ps2Device2Enabled = (ccb >> 5) & 1U;

    send_cmd(TEST_CONTROLLER);
    response = get_response();
    if (response == 0x55) {
        ps2Working = 1;
    } else if (response == 0xfc) {
        ps2Working = 0;
        return 1;
    }

    send_cmd(TEST_PORT1);
    response = get_response();
    if (response == 0x00) {
        ps2Device1Working = 1;
    } else {
        ps2Device1Working = 0;
    }
    if (ps2Device2Enabled) {
        send_cmd(TEST_PORT2);
        response = get_response();
        if (response == 0x00) {
            ps2Device2Working = 1;
        } else {
            ps2Device2Working = 0;
        }
    } else {
        ps2Device2Working = 0;
    }

    write_ps2_io(RESET_CMD);
    read_ps2_io();

    if (ps2Device1Working || ps2Device2Working) {
        return 0;
    } else {
        return 1;
    }
}

int init_ps2() {
    unsigned char status; 
    unsigned short response; 
    send_cmd(DISABLE_PORT1);
    send_cmd(DISABLE_PORT2);

    send_cmd(READ_CCB);
    response = get_response();
    unsigned char ccb = response%256;
    ccb &= ~(1UL << 0);
    ccb &= ~(1UL << 1);
    ccb &= ~(1UL << 6);
    ps2Device2Enabled = (ccb >> 5) & 1U;

    if (test_ps2()) {
        return 1;
    }

    if (ps2Device1Working) {
        send_cmd(ENABLE_PORT1);
    } 
    if (ps2Device2Working) {
        send_cmd(ENABLE_PORT2);
    }

    return 0;
}

void send_device_byte(unsigned char cmd, int device) {
   if (device == 0) {
        write_ps2_io(cmd);
   }
}