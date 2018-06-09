#include <hw/interruptmanager.h>

extern "C" void activateInterrupts();
extern "C" void loadIdt(hw::InterruptManager::IdtPointer*);
extern "C" void ignoreInterrupt();

#define DEFINE_INTERRUPT(x)                                     \
    extern "C" void interrupt##x();                             \
    extern "C" void handleInterrupt##x() {                      \
        hw::InterruptManager::instance()->handleInterrupt(x);   \
    }

DEFINE_INTERRUPT(0x20)
DEFINE_INTERRUPT(0x21)
DEFINE_INTERRUPT(0x22)
DEFINE_INTERRUPT(0x23)
DEFINE_INTERRUPT(0x24)
DEFINE_INTERRUPT(0x25)
DEFINE_INTERRUPT(0x26)
DEFINE_INTERRUPT(0x27)
DEFINE_INTERRUPT(0x28)
DEFINE_INTERRUPT(0x29)
DEFINE_INTERRUPT(0x2A)
DEFINE_INTERRUPT(0x2B)
DEFINE_INTERRUPT(0x2C)
DEFINE_INTERRUPT(0x2D)
DEFINE_INTERRUPT(0x2E)
DEFINE_INTERRUPT(0x2F)
DEFINE_INTERRUPT(0x51)
DEFINE_INTERRUPT(0xA0)

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

void hw::InterruptManager::handleInterrupt(uint16 interrupt) {
    if (_callbacks[interrupt]) {
        _callbacks[interrupt]();
    }
}

hw::InterruptManager::InterruptManager(uint16 offset) :
    std::Singleton<hw::InterruptManager>(this),
    _pic_master(PIC_MASTER, offset),
    _pic_slave(PIC_SLAVE, offset + 8) {

    for (uint32 i = 0; i < IDT_SIZE; i++) {
        setCallback(i, NULL);
        setIdtEntry(i, ignoreInterrupt);
    }
    setIdtEntry(0x20, interrupt0x20);
    setIdtEntry(0x21, interrupt0x21);
    setIdtEntry(0x22, interrupt0x22);
    setIdtEntry(0x23, interrupt0x23);
    setIdtEntry(0x24, interrupt0x24);
    setIdtEntry(0x25, interrupt0x25);
    setIdtEntry(0x26, interrupt0x26);
    setIdtEntry(0x27, interrupt0x27);
    setIdtEntry(0x28, interrupt0x28);
    setIdtEntry(0x29, interrupt0x29);
    setIdtEntry(0x2A, interrupt0x2A);
    setIdtEntry(0x2B, interrupt0x2B);
    setIdtEntry(0x2C, interrupt0x2C);
    setIdtEntry(0x2D, interrupt0x2D);
    setIdtEntry(0x2E, interrupt0x2E);
    setIdtEntry(0x2F, interrupt0x2F);
    setIdtEntry(0x51, interrupt0x51);
    setIdtEntry(0xA0, interrupt0xA0);

    IdtPointer idtptr;
    idtptr.size = sizeof(GateDescriptor) * IDT_SIZE;
    idtptr.offset = (uint32) _idt;
    loadIdt(&idtptr);
}

void hw::InterruptManager::setCallback(uint16 interrupt, void (*callback)()) {
    _callbacks[interrupt] = callback;
}

void hw::InterruptManager::setIdtEntry(uint16 i, void (*callback)()) {
    _idt[i] = GateDescriptor(
                  callback,
                  0x08,
                  GateDescriptor::TYPE_INTERRUPT_32,
                  0);
}

