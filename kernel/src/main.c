#include <stdbool.h>
#include "shell/shell.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

extern void check_cpuid();
extern void check_long_mode();
extern void setup_page_tables();
extern void enable_paging();

extern void setup_kernel() {
    check_cpuid();
    check_long_mode();
    
    setup_page_tables();
    enable_paging();
}

void kernel_main() {
    initialize_terminal();

    //terminal_color = vga_entry_color(VGA,VGA_COLOR_LIGHT_RED);
    
    terminal_write_string("                            Welcome to Borialis OS!\n");
}
