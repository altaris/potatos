#include <hw/pic.h>
#include <io/port8.h>

hw::Pic::Pic(uint16 port, uint8 offset) :
    _commandPort(port),
    _dataPort(port + 1) {
    _commandPort.write(PIC_INIT);       // Initialization
    _dataPort.write(offset);            // Set offset
    _dataPort.write(PIC_SET_CASCADE);   // Cascading
    _dataPort.write(PIC_SET_ENV);       // Env. info
    _dataPort.write(0xFD);
}

