#include <hw/programmableinterruptcontroller.h>
#include <io/port8.h>

#include <debug.h>

hw::ProgrammableInterruptController::ProgrammableInterruptController(
        hw::ProgrammableInterruptController::Type type,
        uint16 port,
        uint8 offset) :
    _commandPort(port, true),
    _dataPort(port + 1, true) {
    uint8 masks = _dataPort.read();             // Save masks

    debug::print("PIC at port ");
    debug::print((uint32) port);
    debug::print(" (cmd), and ");
    debug::print((uint32) port + 1);
    debug::print(" (data). Offset = ");
    debug::print((uint32) offset);
    debug::print('\n');

    _commandPort.write(PIC_INIT);               // Initialization
    _dataPort.write(offset);                    // Set offset
    _dataPort.write(0x00);                      // Cascading
    _dataPort.write(0x01);                      // Env. info
    /*
    switch (type) {
        default:
        case hw::ProgrammableInterruptController::Master:
            _dataPort.write(PIC_SET_MASTER);    // Set master
            break;
        case hw::ProgrammableInterruptController::Slave:
            _dataPort.write(PIC_SET_SLAVE);     // Set slave
            break;
    }
    _dataPort.write(PIC_8086_MODE);             // Set 8086/88 (MCS-80/85) mode
    */
    //_dataPort.write(0xFF);                      // Mask interrupts
    //_dataPort.write(masks);                     // Restore masks
    _dataPort.write(0xFD); // only keyboard interrupts
}

