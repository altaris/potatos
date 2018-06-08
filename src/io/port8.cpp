#include <io/port8.h>

extern "C" uint8 read_port8(uint16 port);
extern "C" void write_port8(uint16 port, uint8 data);

io::Port8::Port8(uint16 port) :
    _port(port) {
}

uint8 io::Port8::read() {
    return read_port8(_port);
}

void io::Port8::write(uint8 data) {
    write_port8(_port, data);
}
