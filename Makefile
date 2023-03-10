PROJROOT = ${CURDIR}

BUILD = $(PROJROOT)/build
SRC = $(PROJROOT)/src
BIN = $(PROJROOT)/bin

BOOT = $(SRC)/boot
KERNEL = $(SRC)/kernel
DESCRIPTORS = $(SRC)/descriptors

LIB = $(SRC)/lib
DRIVERS = $(SRC)/drivers
INT = $(SRC)/interrupt_handling
COMMON = $(SRC)/common

BUILDBOOT = $(BUILD)/boot
BUILDKERNEL = $(BUILD)/kernel
BUILDOBJECT = $(BUILD)/objects

KERNELOBJECTS = $(BUILDOBJECT)/kernel
DRIVEROBJECTS = $(BUILDOBJECT)/drivers
LIBOBJECTS = $(BUILDOBJECT)/lib
INTOBJECTS = $(BUILDOBJECT)/interrupt_handling
COMMONOBJECTS = $(BUILDOBJECT)/common

I386COMPILER = /usr/local/i386elfgcc/bin/i386-elf-gcc
I386LINKER = /usr/local/i386elfgcc/bin/i386-elf-ld

DRIVERFILES = $(DRIVERS)/*

all: init mbr process_switching drivers lib interrupts common kernel_entry kernel  link final

init: | $(BUILD) $(BIN) $(BUILDBOOT) $(BUILDKERNEL) $(BUILDOBJECT) $(KERNELOBJECTS) $(DRIVEROBJECTS) $(LIBOBJECTS) $(INTOBJECTS) $(COMMONOBJECTS)

$(BUILD):
	mkdir $@

$(BIN):
	mkdir $@

$(BUILDBOOT):
	mkdir $@

$(BUILDKERNEL):
	mkdir $@

$(BUILDOBJECT):
	mkdir $@ 

$(KERNELOBJECTS):
	mkdir $@ 

$(DRIVEROBJECTS):
	mkdir $@ 

$(LIBOBJECTS):
	mkdir $@ 

$(INTOBJECTS):
	mkdir $@ 

$(COMMONOBJECTS):
	mkdir $@

mbr: $(BOOT)/mbr.asm $(DESCRIPTORS)/gdt.asm 
	nasm $(BOOT)/mbr.asm -o $(BUILDBOOT)/mbr.bin -f bin

kernel_entry: $(KERNEL)/kernel_entry.asm
	nasm $(KERNEL)/kernel_entry.asm -o $(KERNELOBJECTS)/kernel_entry.o -f elf

kernel: $(KERNEL)/*.c
	@for f in $(notdir $(subst .c,, $^)) ; do \
		$(I386COMPILER) -ffreestanding -m32 -g -c $(KERNEL)/$${f}.c -o $(KERNELOBJECTS)/$${f}.o -w -fcompare-debug-second ; \
	done 

process_switching: process_switching_c process_switching_asm

process_switching_c: $(KERNEL)/process_switching/*.c
	@for f in $(notdir $(subst .c,, $^)) ; do \
		$(I386COMPILER) -ffreestanding -m32 -g -c $(KERNEL)/process_switching/*.c -o $(KERNELOBJECTS)/$${f}.o -w -fcompare-debug-second ; \
	done 

process_switching_asm: $(KERNEL)/process_switching/*.asm
	@for f in $(notdir $(subst .asm,, $^)) ; do \
		nasm $(KERNEL)/process_switching/$${f}.asm -o $(KERNELOBJECTS)/$${f}.o -f elf ; \
	done

drivers: $(DRIVERS)/*.c
	@for f in $(notdir $(subst .c,, $^)) ; do \
		$(I386COMPILER) -ffreestanding -m32 -g -c $(DRIVERS)/$${f}.c -o $(DRIVEROBJECTS)/$${f}.o -w -fcompare-debug-second ; \
	done

lib: $(LIB)/*.c
	@for f in $(notdir $(subst .c,, $^)) ; do \
		$(I386COMPILER) -ffreestanding -m32 -g -c $(LIB)/$${f}.c -o $(LIBOBJECTS)/$${f}.o -w -fcompare-debug-second ; \
	done

interrupts: $(INT)/*
	$(I386COMPILER) -ffreestanding -m32 -g -c $(INT)/idt.c -o $(INTOBJECTS)/idt.o -w -fcompare-debug-second
	$(I386COMPILER) -ffreestanding -m32 -g -c $(INT)/isr.c -o $(INTOBJECTS)/isr.o -w -fcompare-debug-second
	nasm $(INT)/isr_asm.asm -o $(INTOBJECTS)/isr_asm.o -f elf

common: $(COMMON)/*.c
	@for f in $(notdir $(subst .c,, $^)) ; do \
		$(I386COMPILER) -ffreestanding -m32 -g -c $(COMMON)/$${f}.c -o $(COMMONOBJECTS)/$${f}.o -w -fcompare-debug-second ; \
	done

link: $(BUILDBOOT)/* $(KERNELOBJECTS)/*  $(LIBOBJECTS)/* $(DRIVEROBJECTS)/* $(INTOBJECTS)/*
	$(I386LINKER) -o $(BUILDKERNEL)/linked_kernel.bin $(KERNELOBJECTS)/* $(LIBOBJECTS)/* $(DRIVEROBJECTS)/* $(INTOBJECTS)/* $(COMMONOBJECTS)/* --oformat binary -Tlinker/elf_i386.xc

final: $(BUILDKERNEL)/linked_kernel.bin
	cat $(BUILDBOOT)/mbr.bin $(BUILDKERNEL)/linked_kernel.bin > bin/os.bin
