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

mem::GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(
        uint32 base,
        uint32 limit,
        AccessBlock access) {
    setAccess(access);
    setBase(base);
    setLimit(limit);
    _flags.unused = 0x00;
}

mem::GlobalDescriptorTable::SegmentDescriptor::AccessBlock
mem::GlobalDescriptorTable::SegmentDescriptor::access() const {
    return _access;
}

uint32 mem::GlobalDescriptorTable::SegmentDescriptor::base() const {
    return (_base_high << 24) + _base_low;
}

mem::GlobalDescriptorTable::SegmentDescriptor::FlagsBlock
mem::GlobalDescriptorTable::SegmentDescriptor::flags() const {
    return _flags;
}

uint32 mem::GlobalDescriptorTable::SegmentDescriptor::limit() const {
    uint32 result = (_limit_high << 16) + _limit_low;
    if (_flags.granularity && _flags.size) {
        result = (result << 12) | 0xFFF;
    }
    return result;
}

void mem::GlobalDescriptorTable::SegmentDescriptor::setAccess(
        mem::GlobalDescriptorTable::SegmentDescriptor::AccessBlock access) {
    _access = access;
}

void mem::GlobalDescriptorTable::SegmentDescriptor::setBase(uint32 base) {
    _base_low = base & 0xFFFFFF;
    _base_high = (base >> 24) & 0xFF;
}

void mem::GlobalDescriptorTable::SegmentDescriptor::setFlags(
        mem::GlobalDescriptorTable::SegmentDescriptor::FlagsBlock flags) {
    _flags = flags;
}

void mem::GlobalDescriptorTable::SegmentDescriptor::setLimit(uint32 limit) {
    _flags.size = 0x1;
    if (limit <= 65536) {   // 16-bit address space
        _flags.granularity = 0x0;
    } else {                // 32-bit address space
        _flags.granularity = 0x1;
        // Now we have to squeeze the 32 bits limit into 2.5 regiters (20 bits),
        // Hence discard 12 bits. The CPU will pad the 20 bits limit in the
        // segment descriptor with 1s.
        if ((limit & 0xFFF) != 0xFFF) {
            // Case 1: If not all of those lower 12 bits are 0, then discarding
            // them looses information. We still have to do that, but then the
            // CPU will compute a limit that is higher than the one we really
            // have, so we compensate by decreasing a higher bit. This trick
            // yields at most 4095 wasted bytes in memory.
            limit = (limit >> 12) - 1;
        } else {
            // Case 2: If the 12 least significan buts are all 1, then we just
            // discard them, and the CPU will add them back later.
            limit = limit >> 12;
        }
    }
    _limit_low = limit & 0xFFFF;
    _limit_high = (limit >> 16) & 0xF;
}
