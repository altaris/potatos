#include <io/port16.h>

io::Port16::Port16(uint16 port) :
    Port(port) {
}

uint16 io::Port16::read() {
    uint16 result;
    asm volatile("inw %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

void io::Port16::write(uint16 data) {
    asm volatile("outw %0, %1" : : "a" (data), "Nd" (_port));
}
