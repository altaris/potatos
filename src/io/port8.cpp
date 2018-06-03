#include <io/port8.h>

io::Port8::Port8(uint16 port) :
    Port(port) {
}

uint8 io::Port8::read() {
    uint8 result;
    asm volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

void io::Port8::write(uint8 data) {
    asm volatile("outb %0, %1" : : "a" (data), "Nd" (_port));
}
