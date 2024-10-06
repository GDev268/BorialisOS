#include <stdbool.h>
#include "shell/shell.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

extern "C" void check_cpuid();
extern "C" void check_long_mode();
extern "C" void setup_page_tables();
extern "C" void enable_paging();

extern "C" void setup_kernel() {
    check_cpuid();
    check_long_mode();
    
    setup_page_tables();
    enable_paging();
}

extern "C" void kernel_main() {
    initialize_terminal();

    //terminal_color = vga_entry_color(VGA,VGA_COLOR_LIGHT_RED);
    
    terminal_write_string("                            Welcome to Borialis OS!\n");
}
