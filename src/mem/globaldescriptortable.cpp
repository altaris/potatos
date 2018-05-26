#include <src/mem/globaldescriptortable.h>

mem::GlobalDescriptorTable::GlobalDescriptorTable() :
    _nullSegmentSelector(0, 0, {.accessed = 0,
                         .rw = 0,
                         .dc = 0,
                         .executable = 0,
                         .unused = 0,
                         .privilege = 0,
                         .present = 0}),
    _unusedSegmentSelector(0, 0, {.accessed = 0,
                         .rw = 0,
                         .dc = 0,
                         .executable = 0,
                         .unused = 0,
                         .privilege = 0,
                         .present = 0}),
    _codeSegmentSelector(0, 64_MB, {.accessed = 0,
                         .rw = 1,
                         .dc = 0,
                         .executable = 1,
                         .unused = 1,
                         .privilege = 0,
                         .present = 1}),
    _dataSegmentSelector(0, 64_MB, {.accessed = 0,
                         .rw = 1,
                         .dc = 0,
                         .executable = 0,
                         .unused = 1,
                         .privilege = 0,
                         .present = 1}) {
    uint32 gdtDescriptor[2];
    gdtDescriptor[0] = sizeof(GlobalDescriptorTable) << 16;
    gdtDescriptor[1] = (uint32) this;           // NOLINT
    uint8* ptr = ((uint8*) gdtDescriptor) + 2;  // NOLINT
    asm volatile("lgdt %0": :"m" (ptr));
}

mem::GlobalDescriptorTable::Entry::Entry(
        uint32 base,
        uint32 limit,
        AccessBlock access) {
    setAccess(access);
    setBase(base);
    setLimit(limit);
    _flags.unused = 0x00;
}

mem::GlobalDescriptorTable::Entry::AccessBlock
mem::GlobalDescriptorTable::Entry::access() const {
    return _access;
}

uint32 mem::GlobalDescriptorTable::Entry::base() const {
    return (_base_high << 24) + _base_low;
}

mem::GlobalDescriptorTable::Entry::FlagsBlock
mem::GlobalDescriptorTable::Entry::flags() const {
    return _flags;
}

uint32 mem::GlobalDescriptorTable::Entry::limit() const {
    uint32 result = (_limit_high << 16) + _limit_low;
    if (_flags.granularity && _flags.size) {
        result = (result << 12) | 0xFFF;
    }
    return result;
}

void mem::GlobalDescriptorTable::Entry::setAccess(
        mem::GlobalDescriptorTable::Entry::AccessBlock access) {
    _access = access;
}

void mem::GlobalDescriptorTable::Entry::setBase(uint32 base) {
    _base_low = base & 0xFFFFFF;
    _base_high = (base >> 24) & 0xFF;
}

void mem::GlobalDescriptorTable::Entry::setFlags(
        mem::GlobalDescriptorTable::Entry::FlagsBlock flags) {
    _flags = flags;
}

void mem::GlobalDescriptorTable::Entry::setLimit(uint32 limit) {
    _flags.size = 0x1;
    if (limit <= 65536) {   // 16-bit address space
        _flags.granularity = 0x0;
    } else {                // 32-bit address space
        _flags.granularity = 0x1;
        if ((limit & 0xFFF) != 0xFFF) {
            // Case 1: If not all of those lower 12 bits are 0.
            limit = (limit >> 12) - 1;
        } else {
            // Case 2: All 12 least significant bits are all 1.
            limit = limit >> 12;
        }
    }
    _limit_low = limit & 0xFFFF;
    _limit_high = (limit >> 16) & 0xF;
}
