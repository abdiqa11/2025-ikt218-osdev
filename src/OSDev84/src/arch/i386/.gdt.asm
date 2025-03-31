section .text
global gdt_flush

gdt_flush:
    mov eax, [esp + 4]     ; Load the address of the GDT pointer
    lgdt [eax]             ; Load GDT

    ; Reload segment registers
    mov ax, 0x10           ; Data segment selector (2nd GDT entry)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush        ; Far jump to reload CS (code segment selector)
.flush:
    ret
