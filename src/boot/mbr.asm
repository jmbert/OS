[bits 16]
[org 0x7c00]

KERNEL_OFFSET equ 0x1000

FONT_LOC equ 0x5000

STACK_BASE equ 0x10000

BOOT_DISK db 0
mov [BOOT_DISK], dl

CODESEG equ code_descriptor - GDT_Start
DATASEG equ data_descriptor - GDT_Start

; Set data and extended segment registers to zero
xor ax, ax
mov ds, ax
mov ax, 0x1000
mov es, ax

; Initialise Stack
mov bp, STACK_BASE
mov sp, bp

; Load kernel segment
mov ah, 2
mov al, 100 ; If unexpectadly crashing, increase this
mov ch, 0
mov cl, 2
mov dh, 0
xor bx, bx
mov ds, bx
mov es, bx
mov bx, KERNEL_OFFSET
int 0x13

mov di, FONT_LOC
push ds
push es
;ask BIOS to return VGA bitmap fonts
mov	ax, 1130h
mov	bh, 6
int	0x10
;copy charmap
push es
pop	ds
pop	es
mov	si, bp
mov	cx, 0x1000/2
rep	movsd
pop	ds

; change into graphics mode
mov ah,0x0
mov al,0x13
int 0x10

; disable cursor
mov ah, 0x01
mov ch, 0x3f
int 0x10

cli
lgdt [GDT_Descriptor]

; Set the last bit of control register 0 to 1 using eax to enable protected mode
mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODESEG:protected_mode ; Perform a long jump into the code segment, offset at the protected mode

jmp $

; GDT
%include "src/descriptors/gdt.asm"


; 32bit protected mode
[bits 32]
protected_mode:
    ; Set up segment registers and stack
    mov ax, DATASEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    jmp KERNEL_OFFSET ; Jump into kernel
    jmp $

times 510 - ($-$$) db 0x0
dw 0xaa55