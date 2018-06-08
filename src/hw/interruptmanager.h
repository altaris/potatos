#ifndef SRC_HW_INTERRUPTMANAGER_H_
#define SRC_HW_INTERRUPTMANAGER_H_

#include <global.h>
#include <hw/programmableinterruptcontroller.h>
#include <mem/globaldescriptortable.h>

namespace hw {

class InterruptManager {

public:

    /*!
     * \brief Describes an entry in the IDT
     *
     * See https://wiki.osdev.org/IDT
     */
    class GateDescriptor {

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


    } __attribute__((packed));

public:

    /*!
     * \brief Size of the IDT
     */
    static constexpr uint16 IDT_SIZE = 256;

public:

    /*!
     * \brief Activates the interrupt manager
     *
     * Must be called after hardware initializations
     */
    void activate();

    /*!
     * \brief Handles an interrupt
     * \param interrupt Interrupt number
     * \param esp Stack pointer
     * \return A new stack pointer
     */
    uint32 handleInterrupt(uint8 interrupt, uint32 esp);

    /*!
     * \brief InterruptManager
     * \param picOffset Offset for the PIC
     * \see hw::ProgrammableInterruptController
     * \param gdt Pointer to the GDT
     */
    InterruptManager(uint8 picOffset, mem::GlobalDescriptorTable* gdt);

    /*!
     * \brief Sets an entry in the IDT
     * \param entry Must be `<` IDT_SIZE
     * \param descriptor The gate descriptor
     * \see GateDescriptor
     */
    void setInterruptDescriptorTableEntry(
            uint8 entry,
            GateDescriptor descriptor);

public:

    static InterruptManager* instance;

private:

    /*!
     * \brief IDT Descriptor structure
     *
     * Used for the `lidt` asm instruction. https://wiki.osdev.org/IDT
     */
    struct Descriptor {
        uint16 size;
        uint32 offset;
    } __attribute__((packed));

private:

    /*!
     * \brief Port of the master PIC
     */
    static constexpr uint16 PIC_MASTER_PORT = 0x20;

    /*!
     * \brief Port of the slave PIC
     */
    static constexpr uint16 PIC_SLAVE_PORT  = 0xA0;

private:

    /*!
     * \brief Fills the IDT
     * \see _interruptDescriptorTable
     */
    void populateIdt(uint8 picOffset, mem::GlobalDescriptorTable* gdt);

private:

    /*!
     * \brief The actual IDT
     */
    static GateDescriptor _interruptDescriptorTable[IDT_SIZE];

    /*!
     * \brief Master PIC
     */
    ProgrammableInterruptController _pic_master;

    /*!
     * \brief Slave PIC
     */
    ProgrammableInterruptController _pic_slave;

};

}  // namespace hw

#endif  // SRC_HW_INTERRUPTMANAGER_H_
