#include <stdbool.h>
#include "gdt/gdt.h"
#include "shell/shell.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

GDTR gdt;

//Need to make extern "C" because of name mangling
extern "C" void kernel_main() {
    initialize_terminal();

    //terminal_color = vga_entry_color(VGA,VGA_COLOR_LIGHT_RED);
    
    terminal_write_string("                            Welcome to Borialis OS!\n");
}