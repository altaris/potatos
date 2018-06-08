#include <mem/globaldescriptortable.h>
#include <mem/selector.h>

mem::GlobalDescriptorTable::GlobalDescriptorTable() :
    _codeSegmentSelector(0, 4_MB, {
                         .accessed = 0,
                         .rw = 0x1,
                         .dc = 0,
                         .executable = 1,
                         .unused = 0x1,
                         .privilege = 0,
                         .present = 0x1}),
    _dataSegmentSelector(0, 4_MB, {
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
    mem::Selector s(0, mem::Selector::GDT, (uint8*) &_codeSegmentSelector - (uint8*) this); // NOLINT
    return * (uint16*) &s;
    // return (uint8*) &_codeSegmentSelector - (uint8*) this;  // NOLINT
}

uint16 mem::GlobalDescriptorTable::dataSegmentSelector() const {
    return (uint8*) &_dataSegmentSelector - (uint8*) this;  // NOLINT
}

mem::GlobalDescriptorTable::Entry::Entry(
        uint32 base,
        uint32 limit,
        AccessBlock access) {

    uint8 granularity = 0;
    if (limit <= 65536) {   // 16-bit address space
        granularity = 0x0;
    } else {                // 32-bit address space
        granularity = 0x1;
        if ((limit & 0xFFF) != 0xFFF) {
            // Case 1: If not all of those lower 12 bits are 0.
            limit = (limit >> 12) - 1;
        } else {
            // Case 2: All 12 least significant bits are all 1.
            limit = limit >> 12;
        }
    }

    _limit_low          = limit & 0xFFFF;
    _base_low           = base & 0xFFFFFF;
    _access_accessed    = access.accessed;
    _access_rw          = access.rw;
    _access_dc          = access.dc;
    _access_executable  = access.executable;
    _access_unused      = access.unused;
    _access_privilege   = access.privilege;
    _access_present     = access.present;
    _limit_high         = (limit >> 16) & 0xF;
    _flags_unused       = 0x00;
    _flags_size         = 0x1;
    _flags_granularity  = granularity;
    _base_high          = (base >> 24) & 0xFF;
}

uint32 mem::GlobalDescriptorTable::Entry::limit() const {
    uint32 result = (_limit_high << 16) + _limit_low;
    if (_flags_granularity && _flags_size) {
        result = (result << 12) | 0xFFF;
    }
    return result;
}

uint16 mem::GlobalDescriptorTable::nullSegmentSelector() const {
    return (uint8*) &_nullSegmentSelector - (uint8*) this;  // NOLINT
}

uint16 mem::GlobalDescriptorTable::unusedSegmentSelector() const {
    return (uint8*) &_unusedSegmentSelector - (uint8*) this;    // NOLINT
}
