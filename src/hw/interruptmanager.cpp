#include <hw/interruptmanager.h>
#include <io/port8.h>

#include <debug.h>

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',   /* Tab */
  'q', 'w', 'e', 'r', /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,   /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,  /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',   /* 49 */
  'm', ',', '.', '/',   0,    /* Right shift */
  '*',
    0, /* Alt */
  ' ', /* Space bar */
    0, /* Caps lock */
    0, /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
  '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
  '+',
    0, /* 79 - End key*/
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0,   0,   0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

extern "C" void activateInterrupts();
extern "C" void loadIdt(hw::InterruptManager::IdtPointer*);
extern "C" void ignoreInterrupt();
extern "C" void interrupt0x21();

extern "C" void handleInterrupt0x21() {
    io::Port8 kbd_status(0x64);
    io::Port8 kbd_data(0x60);

    uint8 status = kbd_status.read();

    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        char keycode = kbd_data.read();
        if (keycode <= 0) {
            return;
        }
        debug::print((char) keyboard_map[keycode]);
    }
}

hw::InterruptManager::GateDescriptor::GateDescriptor() {
    _present = 0x0;
}

hw::InterruptManager::GateDescriptor::GateDescriptor(
        void (*handler)(),
        uint16 codeSegmentSelector,
        uint8 type,
        uint8 priviledge) {
    _offset_low = ((uint32) handler) & 0xFFFF;
    _selector = codeSegmentSelector;
    _zero = 0x00;
    _type = type & 0xF;
    if (_type == TYPE_INTERRUPT_16 ||
        _type == TYPE_INTERRUPT_32 ||
        _type == TYPE_TRAP_16 ||
        _type == TYPE_TRAP_32) {
        _storageSegment = 0x0;
    } else {
        _storageSegment = 0x1;
    }
    _priviledge = priviledge & 0x3;
    _present = 0x1;
    _offset_high = (((uint32) handler) >> 16) & 0xFFFF;
}

void hw::InterruptManager::activate() {
    activateInterrupts();
}

hw::InterruptManager::InterruptManager(uint16 offset) :
    _pic_master(PIC_MASTER, offset),
    _pic_slave(PIC_SLAVE, offset + 8) {
    GateDescriptor ignoreGate(
                ignoreInterrupt,
                0x08,
                GateDescriptor::TYPE_INTERRUPT_32,
                0);
    for (uint32 i = 0; i < IDT_SIZE; i++) {
        setIdtEntry(i, ignoreGate);
    }

    setIdtEntry(0x21, GateDescriptor(
                    interrupt0x21,
                    0x08,
                    GateDescriptor::TYPE_INTERRUPT_32,
                    0));

    IdtPointer idtptr;
    idtptr.size = sizeof(GateDescriptor) * IDT_SIZE;
    idtptr.offset = (uint32) _idt;
    loadIdt(&idtptr);
}

void hw::InterruptManager::setIdtEntry(
        uint16 i,
        hw::InterruptManager::GateDescriptor gate) {
    _idt[i] = gate;
}

