#include "terminal.h"
#include "gdt.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

void kernel_main()
{
    terminal_initialize();
    terminal_write("Hello World from OSDev84!\n");

    gdt_init();
    terminal_write("GDT initialized successfully.\n");

    while (1)
    {
        __asm__ volatile("hlt");
    }
}
