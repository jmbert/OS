extern exception_handler

extern inc_timer

extern irq_handler

extern PIC_send_eoi

extern advance_next_process

%macro interrupt 1
isr_stub_%+%1:
    pusha
    mov ecx, %1
    mov [0x8000], ecx
    call irq_handler
    popa
    iret
%endmacro

%macro timer_int 1
isr_stub_%+%1:

    pusha
    
    call advance_next_process

    mov [0x8006], eax

    mov [0x8004], esp
    mov esp, ebp

    mov eax, [0x8006]

    pop word [0x9000] ; ret ip
    pop word [0x9002] ; ret cs
    pop word [0x9004] ; flags
    pop word [0x9006] ; esp
    pop word [0x9008] ; ss
 
    mov eax, [0x8006]
    mov [0x9000], eax

    mov esp, [0x8004]

    push word [0x9000] ; ret ip
    push word [0x9002] ; ret cs
    push word [0x9004] ; flags
    push word [0x9006] ; esp
    push word [0x9008] ; ss

    mov esp, [0x8004]

    popa

    call inc_timer

    call PIC_send_eoi
    iret
%endmacro

%macro exception 1
isr_stub_%+%1:
    pusha
    mov ecx, %1
    mov [0x8000], ecx
    call exception_handler  
    hlt
    popa
    iret
%endmacro


exception 0
interrupt 1
interrupt 2
interrupt 3
interrupt 4
interrupt 5
interrupt 6
interrupt 7
exception 8
interrupt 9
exception 10
exception 11
exception 12
exception 13
exception 14
interrupt 15
interrupt 16
exception 17
interrupt 18
interrupt 19
interrupt 20
interrupt 21
interrupt 22
interrupt 23
interrupt 24
interrupt 25
interrupt 26
interrupt 27
interrupt 28
interrupt 29
exception 30
interrupt 31

; PIC interrupts 32-47
timer_int 32
interrupt 33
interrupt 34
interrupt 35
interrupt 36
interrupt 37
interrupt 38
interrupt 39
interrupt 40
interrupt 41
interrupt 42
interrupt 43
interrupt 44
interrupt 45
interrupt 46
interrupt 47


interrupt 48
interrupt 49
interrupt 50
interrupt 51
interrupt 52
interrupt 53
interrupt 54
interrupt 55
interrupt 56
interrupt 57
interrupt 58
interrupt 59
interrupt 60
interrupt 61
interrupt 62
interrupt 63

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    64 
    dd isr_stub_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep