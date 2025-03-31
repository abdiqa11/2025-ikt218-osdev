extern kernel_main

global _start

section .multiboot_header
header_start:
    dd 0xe85250d6               ; Multiboot2 magic
    dd 0                        ; Architecture (i386)
    dd header_end - header_start
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start)) ; Checksum

align 8
    ; Required end tag
    dw 0
    dw 0
    dd 8
header_end:

section .text
bits 32

_start:
    cli
    mov esp, stack_top

    push ebx
    push eax
    call kernel_main

    hlt  ; hang if returned

section .bss
align 16
stack_bottom:
    resb 4096 * 16
stack_top:
