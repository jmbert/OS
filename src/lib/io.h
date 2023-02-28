#ifndef _IO__H
#define _IO__H

#include "types.h"

void printf(char *fmt, ...);

void print(char *string);

void print_number(int n);
void print_binary(int n);

void print_hex(int n);

void init_io();

uint8_t *get_buffer();

#endif