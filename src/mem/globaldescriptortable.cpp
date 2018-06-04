#include <src/mem/globaldescriptortable.h>

mem::GlobalDescriptorTable::GlobalDescriptorTable() :
    _codeSegmentSelector(0, 64_MB, {
                         .accessed = 0,
                         .rw = 1,
                         .dc = 0,
                         .executable = 1,
                         .unused = 1,
                         .privilege = 0,
                         .present = 1}),
    _dataSegmentSelector(0, 64_MB, {
                         .accessed = 0,
                         .rw = 1,
                         .dc = 0,
                         .executable = 0,
                         .unused = 1,
                         .privilege = 0,
                         .present = 1}),
    _nullSegmentSelector(0, 0, {
                         .accessed = 0,
                         .rw = 0,
                         .dc = 0,
                         .executable = 0,
                         .unused = 1,
                         .privilege = 0,
                         .present = 0}),
    _unusedSegmentSelector(0, 0, {
                         .accessed = 0,
                         .rw = 0,
                         .dc = 0,
                         .executable = 0,
                         .unused = 1,
                         .privilege = 0,
                         .present = 0}) {
    Descriptor gdtr;
    gdtr.size = sizeof(mem::GlobalDescriptorTable) - 1;
    gdtr.offset = (uint32) this;                       // NOLINT
    asm volatile("lgdt %0" : : "m" (gdtr));
}

uint16 mem::GlobalDescriptorTable::codeSegmentSelector() const {
    return (uint8*) &_codeSegmentSelector - (uint8*) this;  // NOLINT
}

uint16 mem::GlobalDescriptorTable::dataSegmentSelector() const {
    return (uint8*) &_dataSegmentSelector - (uint8*) this;  // NOLINT
}

mem::GlobalDescriptorTable::Entry::Entry(
        uint32 base,
        uint32 limit,
        AccessBlock access) {
    setAccess(access);
    setBase(base);
    setLimit(limit);
    _flags_unused = 0x00;
}

mem::GlobalDescriptorTable::Entry::AccessBlock
mem::GlobalDescriptorTable::Entry::access() const {
    return AccessBlock{
        .accessed = _access_accessed,
        .rw = _access_rw,
        .dc = _access_dc,
        .executable = _access_executable,
        .unused = _access_unused,
        .privilege = _access_privilege,
        .present = _access_present
    };
}

uint32 mem::GlobalDescriptorTable::Entry::base() const {
    return (_base_high << 24) + _base_low;
}

mem::GlobalDescriptorTable::Entry::FlagsBlock
mem::GlobalDescriptorTable::Entry::flags() const {
    return FlagsBlock{
        .unused = _flags_unused,
        .size = _flags_size,
        .granularity = _flags_granularity
    };
}

uint32 mem::GlobalDescriptorTable::Entry::limit() const {
    uint32 result = (_limit_high << 16) + _limit_low;
    if (_flags_granularity && _flags_size) {
        result = (result << 12) | 0xFFF;
    }
    return result;
}

void mem::GlobalDescriptorTable::Entry::setAccess(
        mem::GlobalDescriptorTable::Entry::AccessBlock access) {
    _access_accessed   = access.accessed;
    _access_rw         = access.rw;
    _access_dc         = access.dc;
    _access_executable = access.executable;
    _access_unused     = access.unused;
    _access_privilege  = access.privilege;
    _access_present    = access.present;
}

void mem::GlobalDescriptorTable::Entry::setBase(uint32 base) {
    _base_low = base & 0xFFFFFF;
    _base_high = (base >> 24) & 0xFF;
}

void mem::GlobalDescriptorTable::Entry::setFlags(
        mem::GlobalDescriptorTable::Entry::FlagsBlock flags) {
    _flags_unused      = flags.unused;
    _flags_size        = flags.size;
    _flags_granularity = flags.granularity;
}

void mem::GlobalDescriptorTable::Entry::setLimit(uint32 limit) {
    _flags_size = 0x1;
    if (limit <= 65536) {   // 16-bit address space
        _flags_granularity = 0x0;
    } else {                // 32-bit address space
        _flags_granularity = 0x1;
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

uint16 mem::GlobalDescriptorTable::nullSegmentSelector() const {
    return (uint8*) &_nullSegmentSelector - (uint8*) this;  // NOLINT
}

uint16 mem::GlobalDescriptorTable::unusedSegmentSelector() const {
    return (uint8*) &_unusedSegmentSelector - (uint8*) this;    // NOLINT
}
