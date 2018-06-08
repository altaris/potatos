#include <hw/interruptmanager.h>
#include <hw/programmableinterruptcontroller.h>
#include <io/screen.h>
#include <std/string.h>

#include <debug.h>

constexpr uint8 TYPE_TASK_32         = 0x5;
constexpr uint8 TYPE_INTERRUPT_16    = 0x6;
constexpr uint8 TYPE_TRAP_16         = 0x7;
constexpr uint8 TYPE_INTERRUPT_32    = 0xE;
constexpr uint8 TYPE_TRAP_32         = 0xF;

hw::InterruptManager::GateDescriptor
hw::InterruptManager::_interruptDescriptorTable[hw::InterruptManager::IDT_SIZE];

hw::InterruptManager* hw::InterruptManager::instance = NULL;

extern "C"
uint32 handleInterrupt(uint8 interrupt, uint32 esp) {
    debug::print("INTERRUPT ");
    debug::print((uint32) interrupt);
    debug::print('\n');
    return hw::InterruptManager::instance->handleInterrupt(interrupt, esp);
}

extern "C" void handleException0x00();
extern "C" void handleException0x01();
extern "C" void handleException0x02();
extern "C" void handleException0x03();
extern "C" void handleException0x04();
extern "C" void handleException0x05();
extern "C" void handleException0x06();
extern "C" void handleException0x07();
extern "C" void handleException0x08();
extern "C" void handleException0x09();
extern "C" void handleException0x0A();
extern "C" void handleException0x0B();
extern "C" void handleException0x0C();
extern "C" void handleException0x0D();
extern "C" void handleException0x0E();
extern "C" void handleException0x0F();
extern "C" void handleException0x10();
extern "C" void handleException0x11();
extern "C" void handleException0x12();
extern "C" void handleException0x13();
extern "C" void handleInterrupt0x00();
extern "C" void handleInterrupt0x01();
extern "C" void handleInterrupt0x02();
extern "C" void handleInterrupt0x03();
extern "C" void handleInterrupt0x04();
extern "C" void handleInterrupt0x05();
extern "C" void handleInterrupt0x06();
extern "C" void handleInterrupt0x07();
extern "C" void handleInterrupt0x08();
extern "C" void handleInterrupt0x09();
extern "C" void handleInterrupt0x0A();
extern "C" void handleInterrupt0x0B();
extern "C" void handleInterrupt0x0C();
extern "C" void handleInterrupt0x0D();
extern "C" void handleInterrupt0x0E();
extern "C" void handleInterrupt0x0F();
extern "C" void handleInterrupt0x31();
extern "C" void handleInterrupt0x80();
extern "C" void ignoreInterrupt();

hw::InterruptManager::GateDescriptor::GateDescriptor() {
    _present = 0x0;
}

hw::InterruptManager::GateDescriptor::GateDescriptor(
        void (*handler)(),
        uint16 codeSegmentSelector,
        uint8 type,
        uint8 priviledge) {
    _offset_low = ((uint32) handler) & 0xFFFF;              // NOLINT
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
    _offset_high = (((uint32) handler) >> 16) & 0xFFFF;     // NOLINT
}

void hw::InterruptManager::activate() {
    asm volatile("sti");
}

hw::InterruptManager::InterruptManager(
        uint8 picOffset,
        mem::GlobalDescriptorTable* gdt) :
    _pic_master(
        hw::ProgrammableInterruptController::Master,
        PIC_MASTER_PORT,
        picOffset),
    _pic_slave(
        hw::ProgrammableInterruptController::Slave,
        PIC_SLAVE_PORT,
        picOffset + 8) {
    instance = this;

    populateIdt(picOffset, gdt);

    Descriptor idtr;
    idtr.size = hw::InterruptManager::IDT_SIZE * sizeof(GateDescriptor);
    idtr.offset = (uint32) _interruptDescriptorTable;                           // NOLINT
    asm volatile("lidt %0" : : "m" (idtr));
}

uint32 hw::InterruptManager::handleInterrupt(uint8 interrupt, uint32 esp) {
    UNUSED(interrupt);
    return esp;
}

void hw::InterruptManager::populateIdt(
        uint8 picOffset,
        mem::GlobalDescriptorTable* gdt) {
    // uint16 codeSegment = gdt->codeSegmentSelector();
    uint16 codeSegment = 0x08;

    for (uint16 i = 0; i < IDT_SIZE; i++) {
        setInterruptDescriptorTableEntry(
            i,
            GateDescriptor(
                &ignoreInterrupt,
                codeSegment,
                TYPE_INTERRUPT_32,
                0));
    }

    setInterruptDescriptorTableEntry(
        0x00,
        GateDescriptor(
            &handleException0x00,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x01,
        GateDescriptor(
            &handleException0x01,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x02,
        GateDescriptor(
            &handleException0x02,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x03,
        GateDescriptor(
            &handleException0x03,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x04,
        GateDescriptor(
            &handleException0x04,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x05,
        GateDescriptor(
            &handleException0x05,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x06,
        GateDescriptor(
            &handleException0x06,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x07,
        GateDescriptor(
            &handleException0x07,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x08,
        GateDescriptor(
            &handleException0x08,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x09,
        GateDescriptor(
            &handleException0x09,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x0A,
        GateDescriptor(
            &handleException0x0A,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x0B,
        GateDescriptor(
            &handleException0x0B,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x0C,
        GateDescriptor(
            &handleException0x0C,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x0D,
        GateDescriptor(
            &handleException0x0D,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x0E,
        GateDescriptor(
            &handleException0x0E,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x0F,
        GateDescriptor(
            &handleException0x0F,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x10,
        GateDescriptor(
            &handleException0x10,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x11,
        GateDescriptor(
            &handleException0x11,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x12,
        GateDescriptor(
            &handleException0x12,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x13,
        GateDescriptor(
            &handleException0x13,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));

    setInterruptDescriptorTableEntry(
        picOffset + 0x00,
        GateDescriptor(
            &handleInterrupt0x00,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x01,
        GateDescriptor(
            &handleInterrupt0x01,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x02,
        GateDescriptor(
            &handleInterrupt0x02,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x03,
        GateDescriptor(
            &handleInterrupt0x03,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x04,
        GateDescriptor(
            &handleInterrupt0x04,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x05,
        GateDescriptor(
            &handleInterrupt0x05,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x06,
        GateDescriptor(
            &handleInterrupt0x06,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x07,
        GateDescriptor(
            &handleInterrupt0x07,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x08,
        GateDescriptor(
            &handleInterrupt0x08,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x09,
        GateDescriptor(
            &handleInterrupt0x09,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x0A,
        GateDescriptor(
            &handleInterrupt0x0A,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x0B,
        GateDescriptor(
            &handleInterrupt0x0B,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x0C,
        GateDescriptor(
            &handleInterrupt0x0C,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x0D,
        GateDescriptor(
            &handleInterrupt0x0D,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x0E,
        GateDescriptor(
            &handleInterrupt0x0E,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        picOffset + 0x0F,
        GateDescriptor(
            &handleInterrupt0x0F,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
    setInterruptDescriptorTableEntry(
        0x80,
        GateDescriptor(
            &handleInterrupt0x80,
            codeSegment,
            TYPE_INTERRUPT_32,
            0));
}

void hw::InterruptManager::setInterruptDescriptorTableEntry(
        uint8 entry,
        GateDescriptor descriptor) {
    _interruptDescriptorTable[entry] = descriptor;
}
