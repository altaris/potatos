#ifndef SRC_MEM_DESCRIPTORMANAGER_H_
#define SRC_MEM_DESCRIPTORMANAGER_H_

#include <global.h>

#include <mem/selector.h>

namespace mem {

class DescriptorManager {

public:

    /*!
     * \brief Size of the GDT
     */
    static constexpr uint16 GDT_SIZE = 256;

public:

    /*!
     * \brief An SegmentDescriptor of the GDT
     *
     * The attributes of this class are layed out in memory as explained here
     * https://wiki.osdev.org/Global_Descriptor_Table .
     */
    class __ATTRIBUTE____PACKED__ SegmentDescriptor {

    public:

        struct Access {
            /*!
             * \see mem::DescriptorManager::SegmentDescriptor::_access_accessed
             */
            uint8 accessed : 1;
            /*!
             * \see mem::DescriptorManager::SegmentDescriptor::_access_rw
             */
            uint8 rw : 1;
            /*!
             * \see mem::DescriptorManager::SegmentDescriptor::_access_dc
             */
            uint8 dc : 1;
            /*!
             * \see mem::DescriptorManager::SegmentDescriptor::_access_executable
             */
            uint8 executable : 1;
            /*!
             * \see mem::DescriptorManager::SegmentDescriptor::_access_privilege
             */
            uint8 privilege : 2;
            /*!
             * \see mem::DescriptorManager::SegmentDescriptor::_access_present
             */
            uint8 present : 1;
        };

    public:

        /*!
         * \brief Return the access code
         */
        uint32 access() const;

        /*!
         * \brief Default constructor
         *
         * Constructs a null segment
         */
        SegmentDescriptor();

        /*!
         * \brief Constructor
         * \param base 32 base bits
         * \param limit 32 limit bits
         * \param access 8 access bits, described by an
         * mem::DescriptorManager::SegmentDescriptor::Access struct
         */
        SegmentDescriptor(uint32 base, uint32 limit, Access access);

        /*!
         * \brief Returns the 32 limit bits
         */
        uint32 limit() const;


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
         * \brief Accessed bit
         *
         * Ac: Accessed bit. Just set to 0. The CPU sets this to 1 when the
         * segment is accessed.
         */
        uint8 _access_accessed : 1;

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
        uint8 _access_rw : 1;

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
        uint8 _access_dc : 1;

        /*!
         * \brief Executable bit
         *
         * If 1 code in this segment can be executed, i.e. a code selector.
         * If 0 it is a data selector.
         */
        uint8 _access_executable : 1;

        /*!
         * \brief This bit is always 1
         */
        uint8 _access_unused : 1;

        /*!
         * \brief Privilege, 2 bits
         *
         * Contains the ring level, 0 = highest (kernel), 3 = lowest
         * (user applications).
         */
        uint8 _access_privilege : 2;

        /*!
         * \brief Present bit
         *
         * This must be 1 for all valid selectors.
         */
        uint8 _access_present : 1;

        /*!
         * \brief High 4 bits of limit combined
         */
        uint8 _limit_high : 4;

        /*!
         * \brief Always 0
         */
        uint8 _flags_unused : 2;

        /*!
         * \brief Size bit
         *
         * If 0 the selector defines 16 bit protected mode. If 1 it defines
         * 32 bit protected mode. You can have both 16 bit and 32 bit
         * selectors at once.
         */
        uint8 _flags_size : 1;

        /*!
         * \brief Granularity bit
         *
         * If 0 the limit is in 1 B blocks (byte granularity), if 1 the
         * limit is in 4 KiB blocks (page granularity).
         */
        uint8 _flags_granularity : 1;

        /*!
         * \brief High 8 bits of base
         */
        uint8 _base_high : 8;

    };

    /*!
     * \brief GDT pointer
     *
     * Used for the `lgdt` instruction.
     */
    struct __ATTRIBUTE____PACKED__ GdtPointer {
        uint16 size;
        uint32 offset;
    };

public:

    mem::Selector codeSegmentSelector() const;

    /*!
     * \brief Constructor
     *
     * Loads the GDT using the asm `lgdt` instruction
     */
    DescriptorManager();

private:

    static constexpr uint16 UNUSED_SEGMENT_INDEX   = 0x0;
    static constexpr uint16 CODE_SEGMENT_INDEX     = 0x1;
    static constexpr uint16 DATA_SEGMENT_INDEX     = 0x2;

private:

    SegmentDescriptor _gdt[GDT_SIZE];

};

}  // namespace mem

#endif  // SRC_MEM_DESCRIPTORMANAGER_H_
