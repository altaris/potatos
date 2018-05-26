#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_MEM_GLOBALDESCRIPTORTABLE_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_MEM_GLOBALDESCRIPTORTABLE_H_

#include <global.h>

namespace mem {

class GlobalDescriptorTable {

public:

    /*!
     * \brief An entry of the GDT
     *
     * The attributes of this class are layed out in memory as explained here
     * https://wiki.osdev.org/Global_Descriptor_Table .
     */
    class Entry {

    public:

        /*!
         * \brief Bit field representing the access 8 bits of a segment
         * descriptor
         */
        struct AccessBlock {

            /*!
             * \brief Accessed bit
             *
             * Ac: Accessed bit. Just set to 0. The CPU sets this to 1 when the
             * segment is accessed.
             */
            uint8 accessed : 1;

            /*!
             * \brief Readable bit / Writable bit
             *
             * * Readable bit for code selectors: Whether read access for this
             * segment is allowed. Write access is never allowed for code
             * segments.
             *
             * * Writable bit for data selectors: Whether write access for this
             * segment is allowed. Read access is always allowed for data
             * segments.
             */
            uint8 rw : 1;

            /*!
             * \brief Direction bit / Conforming bit
             *
             * Direction bit for data selectors: Tells the direction. 0 the
             * segment grows up. 1 the segment grows down, i.e. the offset has
             * to be greater than the limit.
             *
             * Conforming bit for code selectors:
             * * If 1 code in this segment can be executed from an equal or
             * lower privilege level. For example, code in ring 3 can far-jump
             * to conforming code in a ring 2 segment. The privl-bits represent
             * the highest privilege level that is allowed to execute the
             * segment. For example, code in ring 0 cannot far-jump to a
             * conforming code segment with `privledge == 0x2`, while code in
             * ring 2 and 3 can. Note that the privilege level remains the same,
             * i.e. a far-jump form ring 3 to a `privledge == 2`-segment remains
             * in ring 3 after the jump.
             * * If 0 code in this segment can only be executed from the ring
             * set in `privledge`.
             */
            uint8 dc : 1;

            /*!
             * \brief Executable bit
             *
             * If 1 code in this segment can be executed, i.e. a code selector.
             * If 0 it is a data selector.
             */
            uint8 executable : 1;

            /*!
             * \brief This bit is always 1
             */
            uint8 unused : 1;

            /*!
             * \brief Privilege, 2 bits
             *
             * Contains the ring level, 0 = highest (kernel), 3 = lowest
             * (user applications).
             */
            uint8 privilege : 2;

            /*!
             * \brief Present bit
             *
             * This must be 1 for all valid selectors.
             */
            uint8 present : 1;

        };

        /*!
         * \brief Bit field representing the flags 4 bits of the segment
         * descriptor
         */
        struct FlagsBlock {
            /*!
             * \brief Always 0
             */
            uint8 unused : 2;

            /*!
             * \brief Size bit
             *
             * If 0 the selector defines 16 bit protected mode. If 1 it defines
             * 32 bit protected mode. You can have both 16 bit and 32 bit
             * selectors at once.
             */
            uint8 size : 1;

            /*!
             * \brief Granularity bit
             *
             * If 0 the limit is in 1 B blocks (byte granularity), if 1 the
             * limit is in 4 KiB blocks (page granularity).
             */
            uint8 granularity : 1;
        };

    public:

        /*!
         * \brief Constructor
         * \param base 32 base bits
         * \param limit 32 limit bits
         * \param access 8 access bits, described by an AccessBlock struct
         */
        Entry(uint32 base, uint32 limit, AccessBlock access);

        /*!
         * \brief Returns the 8 access bits
         */
        AccessBlock access() const;

        /*!
         * \brief Returns the 32 base bits
         */
        uint32 base() const;

        /*!
         * \brief Returns the 4 flag bits padded in 8 bits (4 high 0s)
         */
        FlagsBlock flags() const;

        /*!
         * \brief Returns the 32 limit bits
         */
        uint32 limit() const;

        /*!
         * \brief Sets access 8 bits in segment descriptor
         */
        void setAccess(AccessBlock access);

        /*!
         * \brief Sets base 32 bits in segment descriptor
         */
        void setBase(uint32 base);

        /*!
         * \brief Sets the 4 flag bits
         * \param flags Only the lower 4 bits are considered
         */
        void setFlags(FlagsBlock flags);

        /*!
         * \brief Set limits 32 bits in segment descriptor
         *
         * There are two cases:
         * * If \p limit `<= 65536`, then we use 16 bits address space. The
         * granularity bit (mem::GlobalDescriptorTable::Entry::_flags)
         * is set to `0`.
         * * Otherwise, we have to squeeze the 32 bits limit into 20 bits, hence
         * discard 12 bits. The CPU will pad the 20 bits limit in the segment
         * descriptor with 1s.
         *      - Case 1: If not all of those lower 12 bits are 0, then
         * discarding them looses information. We still have to do that, but
         * then the CPU will compute a limit that is higher than the one we
         * really have, so we compensate by decreasing a higher bit. This trick
         * yields at most 4095 wasted bytes in memory.
         *      - Case 2: If the 12 least significant bits are all 1, then we
         * just discard them, and the CPU will add them back later.
         */
        void setLimit(uint32 limit);

    private:

        /*!
         * \brief Low 16 bits of limit
         */
        uint16 _limit_low : 16;

        /*!
         * \brief Low 24 bits of base
         */
        uint32 _base_low : 24;

        /*!
         * \brief Access 8 bits
         * \see mem::GlobalDescriptorTable::SegmentDescriptor::AccessBlock
         */
        AccessBlock _access;

        /*!
         * \brief High 4 bits of limit combined
         */
        uint8 _limit_high : 4;

        /*!
         * \brief Flags 4 bits
         * \see mem::GlobalDescriptorTable::SegmentDescriptor::FlagsBlock
         */
        FlagsBlock _flags;

        /*!
         * \brief High 8 bits of base
         */
        uint8 _base_high : 8;

    };

public:

    GlobalDescriptorTable();

private:

    Entry _nullSegmentSelector;
    Entry _unusedSegmentSelector;
    Entry _codeSegmentSelector;
    Entry _dataSegmentSelector;

};

}  // namespace mem

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_MEM_GLOBALDESCRIPTORTABLE_H_
