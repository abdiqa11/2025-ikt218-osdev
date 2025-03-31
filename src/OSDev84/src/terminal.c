#include <stdint.h>
#include <stddef.h>

#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define DEFAULT_COLOR 0x07 // Light grey on black

static volatile uint16_t *const vga = (uint16_t *)VGA_ADDRESS;
static size_t terminal_row = 0;
static size_t terminal_column = 0;

static void put_char_at(char c, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    vga[index] = ((uint16_t)DEFAULT_COLOR << 8) | c;
}

void terminal_initialize()
{
    for (size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
        {
            put_char_at(' ', x, y);
        }
    }
}

void terminal_write(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == '\n')
        {
            terminal_column = 0;
            terminal_row++;
        }
        else
        {
            put_char_at(str[i], terminal_column, terminal_row);
            terminal_column++;
            if (terminal_column >= VGA_WIDTH)
            {
                terminal_column = 0;
                terminal_row++;
            }
        }

        if (terminal_row >= VGA_HEIGHT)
        {
            terminal_row = 0; // Or implement scrolling if you want
        }
    }
}
