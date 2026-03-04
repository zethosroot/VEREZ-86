bits 32 ; This file contains 32 bit instructions

global start ; Global symbol for linker

extern kernel_main ; External reference that kernel_main exists in kernel.c

section .text

start:
    mov esp, stack_top ; Set up the stack
    call kernel_main ; Call the C kernel

.halt:
    cli ; disable interrupts
    hlt ; halt the processor
    jmp .halt ; if somehow resumed, halt again

section .bss
align 16 ; stack should start at a memory address divisible by 16
stack_bottom:
    resb 4096 * 4 ; Reserve 16KB of stack space
stack_top:
