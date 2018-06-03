#include <io/port32.h>

io::Port32::Port32(uint16 port) :
    Port(port) {
}

uint32 io::Port32::read() {
    uint32 result;
    asm volatile("inl %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

void io::Port32::write(uint32 data) {
    asm volatile("outl %0, %1" : : "a" (data), "Nd" (_port));
}
