#ifndef SRC_HW_INTERRUPTMANAGER_H_
#define SRC_HW_INTERRUPTMANAGER_H_

#include <global.h>

#include <hw/pic.h>

namespace hw {

class InterruptManager {

public:

    static constexpr uint16 IDT_SIZE    = 256;

    static constexpr uint16 PIC_MASTER  = 0x20;
    static constexpr uint16 PIC_SLAVE   = 0xA0;

public:

    class __attribute__((__packed__)) GateDescriptor {

    public:

        static constexpr uint8 TYPE_TASK_32         = 0x5;
        static constexpr uint8 TYPE_INTERRUPT_16    = 0x6;
        static constexpr uint8 TYPE_TRAP_16         = 0x7;
        static constexpr uint8 TYPE_INTERRUPT_32    = 0xE;
        static constexpr uint8 TYPE_TRAP_32         = 0xF;

    public:

        /*!
         * \brief Creates an invalid gate descriptor
         *
         * Sets _present to `0`
         */
        GateDescriptor();

        /*!
         * \brief Creates a valid gate descriptor
         */
        GateDescriptor(
                void (*handler)(),
                uint16 codeSegmentSelector,
                uint8 type,
                uint8 priviledge);

    private:

        /*!
         * \brief Low 16 bits of the offset
         *
         * The offset is the address of the function that should be called upon
         * this interrupt
         */
        uint16 _offset_low : 16;

        /*!
         * \brief A code segment selector
         * \todo Add documentation here
         */
        uint16 _selector : 16;

        /*!
         * \brief Must be 0
         */
        uint8 _zero : 8;

        /*!
         * \brief Gate type
         *
         * Possible IDT gate types :
         * - `0x5` : 32 bit task gate
         * - `0x6` : 16-bit interrupt gate
         * - `0x7` : 16-bit trap gate
         * - `0xE` : 32-bit interrupt gate
         * - `0xF` : 32-bit trap gate
         */
        uint8 _type : 4;

        /*!
         * \brief Storage segment
         *
         * Set to 0 for interrupt and trap gates. See _type
         */
        uint8 _storageSegment : 1;

        /*!
         * \brief Descriptor privilege level
         *
         * Gate call protection. Specifies which privilege Level the calling
         * descriptor minimum should have. So hardware and CPU interrupts can be
         * protected from being called out of userspace
         */
        uint8 _priviledge : 2;

        /*!
         * \brief Present
         *
         * Set to 0 for unused interrupts
         */
        uint8 _present : 1;

        /*!
         * \brief High 16 bits of the offset
         * \see _offset_low
         */
        uint16 _offset_high : 16;

    };

    struct __attribute__((__packed__)) IdtPointer {
        uint16 size : 16;
        uint32 offset : 32;
    };

public:

    /*!
     * \brief Activates interrupts
     *
     * Issues the asm `sti` instruction
     */
    void activate();

    explicit InterruptManager(uint16 offset);

    void setIdtEntry(uint16 i, GateDescriptor gate);

private:

    GateDescriptor _idt[IDT_SIZE];

    hw::Pic _pic_master;
    hw::Pic _pic_slave;

};

}  // namespace hw

#endif  // SRC_HW_INTERRUPTMANAGER_H_
