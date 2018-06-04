#include <hw/programmableinterruptcontroller.h>
#include <io/port8.h>

hw::ProgrammableInterruptController::ProgrammableInterruptController(
        hw::ProgrammableInterruptController::Type type,
        uint16 port,
        uint8 offset) :
    _commandPort(port, true),
    _dataPort(port + 1, true) {
    uint8 masks = _dataPort.read();             // Save masks
    _commandPort.write(PIC_INIT);               // Initialization
    _dataPort.write(offset);                    // Set offset
    switch (type) {
        default:
        case hw::ProgrammableInterruptController::Master:
            _dataPort.write(PIC_SET_MASTER);    // Set master
            break;
        case hw::ProgrammableInterruptController::Slave:
            _dataPort.write(PIC_SET_SLAVE);     // Set slave
            break;
    }
    _dataPort.write(PIC_8086_MODE);             // Set 8086/88 (MCS-80/85) mode (???)
    _dataPort.write(masks);                     // Restore masks
}

