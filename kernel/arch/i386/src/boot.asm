MBALIGN  equ 1 << 0            ; align loaded modules on page boundries
MEMINFO  equ 1 << 1            ; provide memory map
FLAGS    equ MBALIGN | MEMINFO ; multiboot 'flag' field
MAGIC    equ 0x1BADB002        ; grub magic number
CHECKSUM equ -(MAGIC + FLAGS)  ; multiboot checksum

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; The mutiboot sepcfication does not define a value for the stack pointer
; so it is up to the kernel to provide a stack.
; The stack must be 16-byte aligned by the System V ABI standard, as the 
; compiler expectes the stack to be configured that way.
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB of stack
stack_top:


section .text
global _start:function (_start.end - _start)
_start:
    ; The bootloader has loaded the kernel into 32-bit protected mode.
    ;  - Interrupts are disabled
    ;  - Paging is disabled
    ;  - Kernel has full control (on Ring 0)
    
    ; Setup the stack
    ; Since the stack grows downwards, we need to provide the highest 
    ; address in the stack memory area
    mov esp, stack_top

    ; Call the global constructors
    ;##call _init 

    ; Transfer control to the main kernel
    ; TODO: supply provided multiboot things as parameters to kernel main 
    ;       function
    extern kernel_main
    call kernel_main

    ; If the kernel_main function unexpectedly returns put the processor 
    ; into an infinite loop
    ;  - disable interrupts
    ;  - wait for next interrupt with hlt instruction, but interrupts are 
    ;    disabled, so it will hang forever
    ;  - if an non-maskable interrupt occurres jump back to waiting

    cli
.hang:  
    hlt
    jmp .hang
    
.end:

