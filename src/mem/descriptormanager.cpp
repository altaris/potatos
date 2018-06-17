#include <mem/descriptormanager.h>
#include <mem/selector.h>

#include <debug.h>

extern "C" void loadGdt(mem::DescriptorManager::GdtPointer*);

mem::Selector mem::DescriptorManager::codeSegmentSelector() const {
    return mem::Selector(0, mem::Selector::GDT, CODE_SEGMENT_INDEX);
}

mem::DescriptorManager::DescriptorManager() {
    _gdt[UNUSED_SEGMENT_INDEX] = SegmentDescriptor(
        0x0,
        0_MB,
        SegmentDescriptor::Access{
            .accessed   = 0x0,
            .rw         = 0x0,
            .dc         = 0x0,
            .executable = 0x0,
            .privilege  = 0x0,
            .present    = 0x0});
    _gdt[CODE_SEGMENT_INDEX] = SegmentDescriptor(
        0,
        4_MB,
        SegmentDescriptor::Access{
            .accessed   = 0x0,
            .rw         = 0x1,
            .dc         = 0x0,
            .executable = 0x1,
            .privilege  = 0x0,
            .present    = 0x1});
    _gdt[DATA_SEGMENT_INDEX] = SegmentDescriptor(
        0,
        4_MB,
        SegmentDescriptor::Access{
            .accessed   = 0x0,
            .rw         = 0x1,
            .dc         = 0x0,
            .executable = 0x0,
            .privilege  = 0x0,
            .present    = 0x1});

    GdtPointer gdtptr{
        .size = sizeof(mem::DescriptorManager::SegmentDescriptor) * GDT_SIZE,
        .offset = (uint32) _gdt     // NOLINT
    };
    loadGdt(&gdtptr);
}

uint32 mem::DescriptorManager::SegmentDescriptor::access() const {
    return _access_accessed             +
            (_access_rw << 1)           +
            (_access_dc << 2)           +
            (_access_executable << 3)   +
            (_access_unused << 4)       +
            (_access_privilege << 5)    +
            (_access_present << 7);
}

mem::DescriptorManager::SegmentDescriptor::SegmentDescriptor() :
    _limit_low          (0x0),
    _base_low           (0x0),
    _access_accessed    (0x0),
    _access_rw          (0x0),
    _access_dc          (0x0),
    _access_executable  (0x0),
    _access_unused      (0x1),
    _access_privilege   (0x0),
    _access_present     (0x0),
    _limit_high         (0x0),
    _flags_unused       (0x0),
    _flags_size         (0x0),
    _flags_granularity  (0x0),
    _base_high          (0x0) {

}

mem::DescriptorManager::SegmentDescriptor::SegmentDescriptor(
        uint32 base,
        uint32 limit,
        Access access) {

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
    _access_unused      = 0x1;
    _access_privilege   = access.privilege;
    _access_present     = access.present;
    _limit_high         = (limit >> 16) & 0xF;
    _flags_unused       = 0x00;
    _flags_size         = 0x1;
    _flags_granularity  = granularity;
    _base_high          = (base >> 24) & 0xFF;
}

uint32 mem::DescriptorManager::SegmentDescriptor::limit() const {
    uint32 result = (_limit_high << 16) + _limit_low;
    if (_flags_granularity && _flags_size) {
        result = (result << 12) | 0xFFF;
    }
    return result;
}
