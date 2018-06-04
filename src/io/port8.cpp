#include <io/port8.h>

io::Port8::Port8(uint16 port, bool slow) :
    Port(port),
    _slow(slow) {
}

uint8 io::Port8::read() {
    uint8 result;
    asm volatile("inb %1, %0" : "=a" (result) : "Nd" (_port));
    return result;
}

void io::Port8::write(uint8 data) {
    if (_slow) {
        asm volatile("outb %0, %1\n\t"
                     "jmp 1f\n\t"
                     "1:jmp 2f\n\t"
                     "2:" : : "a" (data), "Nd" (_port));
    } else {
        asm volatile("outb %0, %1" : : "a" (data), "Nd" (_port));
    }
}
