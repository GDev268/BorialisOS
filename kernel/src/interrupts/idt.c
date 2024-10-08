extern void idt_exception_handle() {
    asm volatile("cli; hlt"); //Hangs the computer
}