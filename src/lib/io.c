#include "io.h"
#include "arg.h"
#include "types.h"
#include "../drivers/vga.h"

int prt_cursor; // Whether to print an underscore at cursor location

uint8_t *text_buffer; // Pointer to the beginning of the vga text buffer

uint8_t *cursor_ptr; // Pointer to the cursor position in the text buffer

void printk(char *fmt, ...) {
    va_list args;

    va_start(args, 1);

    uint8_t chr;
    uint8_t fmtChr;

    int argNum;

    for (int i = 0;; i++)
    {
        chr = fmt[i];
        if (chr == '\0') {
            break;
        }

        if (chr == '%') {
            i++;
            fmtChr = fmt[i];
            switch (fmtChr)
            {
            case 's':
                uint8_t *arg_str;
                arg_str = va_arg(args, uint8_t*);
                print(arg_str);
                break;
            case 'd':
                int arg_int;
                arg_int = va_arg(args, int);
                print_number(arg_int);
                break;
            case 'x':
                arg_int = va_arg(args, int);
                print_hex(arg_int);
                break;
            case 'c':
                int arg_chr = va_arg(args, int);
                write_to_buffer(arg_chr);
                break;
            case 'b':
                arg_int = va_arg(args, int);
                print_binary(arg_int);
                break;
            }
            argNum++;
        } else {
            write_to_buffer(chr);
        }
    }

    va_end(args);

    if (prt_cursor) {
        *cursor_ptr = '_';
    }
    

    draw_buffer(text_buffer);   
}

void print(char *string) {
    char chr = string[0];
    for (int i = 0;chr != EOS;i++, chr = string[i])
    {
        write_to_buffer(chr);
    }
}

void print_number(int n) {
    int digits;
    int digit;

    int tmpN = n;

    for (int i = 1;; i++)
    {
        tmpN /= 10;
        if (tmpN == 0) {
            digits = i;
            break; 
        }
        
    }
    

    for (int i = 1;i <= digits;i++)
    {   
        digit = n/(exp(10, digits-i)) % 10;

        write_to_buffer(digit+0x30);
    }
}

void print_binary(int n) {
    int digits;
    int digit;

    int tmpN = n;

    for (int i = 1;; i++)
    {
        tmpN /= 2;
        if (tmpN == 0) {
            digits = i;
            break; 
        }
        
    }
    

    for (int i = 1;i <= digits;i++)
    {   
        digit = n/(exp(2, digits-i)) % 2;

        write_to_buffer(digit+0x30);
    }
}

void print_hex(int n) {
    int digits;
    uint8_t digit;

    int tmpN = n;

    for (int i = 1;; i++)
    {
        tmpN /= 16;
        if (tmpN == 0) {
            digits = i;
            break; 
        }
        
    }
    

    for (int i = 1;i <= digits;i++)
    {   
        digit = n/(exp(16, digits-i)) % 16;

        if (digit < 10) {
            write_to_buffer(digit+0x30);
        } else {
            write_to_buffer(digit+0x57);
        }
        
    }
}

void write_to_buffer(uint8_t chr) {
    if (chr == '\b') {
        *cursor_ptr = '\0';
        if (cursor_ptr > text_buffer) {
            cursor_ptr--;
        }
        *cursor_ptr = '\0';
    } else {
        if (cursor_ptr-text_buffer <= BUFFER_SIZE) {
            *cursor_ptr = chr;
            cursor_ptr++;
        }
        
    }
}

uint8_t *get_buffer() {
    return text_buffer;
}

void init_io() {
    text_buffer = 0x20000;
    prt_cursor = 0;

    clear_buffer();
}

void clear_buffer() {
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        text_buffer[i] = 0;
    }
    cursor_ptr = text_buffer;
}

void set_cursor(uint32_t x, uint32_t y) {
    cursor_ptr = text_buffer + x + y * SCREEN_WIDTH/8;
}

uint32_t get_cursor_x() {
    return (cursor_ptr - text_buffer) % SCREEN_WIDTH/8;
}

uint32_t get_cursor_y() {
    return (cursor_ptr - text_buffer) / SCREEN_WIDTH/8;
}