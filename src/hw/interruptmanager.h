#ifndef SRC_HW_INTERRUPTMANAGER_H_
#define SRC_HW_INTERRUPTMANAGER_H_

#include <global.h>

#include <hw/pic.h>

#include <mem/descriptormanager.h>

#include <std/singleton.h>

namespace hw {

/*!
 * \brief Interrupt manager
 *
 * The main important method is hw::InterruptManager::setCallback to set a
 * function to be called upon interrupt
 */
class InterruptManager : public std::Singleton<InterruptManager> {

    SINGLETON(InterruptManager)

public:

    /*!
     * \brief Size of the IDT
     */
    static constexpr uint16 IDT_SIZE    = 256;

    /*!
     * \brief Port of master PIC
     */
    static constexpr uint16 PIC_MASTER  = 0x20;
    /*!
     * \brief Port of slave PIC
     */
    static constexpr uint16 PIC_SLAVE   = 0xA0;

public:

    /*!
     * \brief Gate descriptor
     * \see https://wiki.osdev.org/IDT#Structure_IA-32
     */
    class __ATTRIBUTE____PACKED__ GateDescriptor {

    public:

        /*!
         * \brief Type code for a 32 bit task gate
         * \see _type
         */
        static constexpr uint8 TYPE_TASK_32         = 0x5;
        /*!
         * \brief Type code for a 16 bit interrupt gate
         * \see _type
         */
        static constexpr uint8 TYPE_INTERRUPT_16    = 0x6;
        /*!
         * \brief Type code for a 16 bit trap gate
         * \see _type
         */
        static constexpr uint8 TYPE_TRAP_16         = 0x7;
        /*!
         * \brief Type code for a 32 bit interrupt gate
         * \see _type
         */
        static constexpr uint8 TYPE_INTERRUPT_32    = 0xE;
        /*!
         * \brief Type code for a 32 bit trap gate
         * \see _type
         */
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
         * \see hw::InterruptManager::TYPE_INTERRUPT_16
         * \see hw::InterruptManager::TYPE_INTERRUPT_32
         * \see hw::InterruptManager::TYPE_TASK_32
         * \see hw::InterruptManager::TYPE_TRAP_16
         * \see hw::InterruptManager::TYPE_TRAP_32
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

    /*!
     * \brief Pointer to the IDT
     *
     * Used in the asm `lidt` instruction
     */
    struct __ATTRIBUTE____PACKED__ IdtPointer {
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

    /*!
     * \brief Handles an interrupt
     */
    void handleInterrupt(uint16 interrupt);

    /*!
     * \brief Constructor
     * \param offset Remap offset \see hw::Pic
     */
    explicit InterruptManager(
            mem::DescriptorManager* descriptorManager,
            uint16 offset);

    /*!
     * \brief Sets a callback to be called on interrupt
     */
    void setCallback(uint16 interrupt, void (*callback)());

private:

    /*!
     * \brief Sets an entry in the IDT
     * \param i Interrupt number
     * \param callback Function to call upon interrupt
     */
    void setIdtEntry(uint16 i, void (*callback)());

private:

    /*!
     * \brief Callback table
     */
    void (*_callbacks[IDT_SIZE])();

    /*!
     * \brief Pointer to the descriptor manager
     * \see mem::DescriptorManager
     */
    mem::DescriptorManager* _descriptorManager;

    /*!
     * \brief The IDT
     */
    GateDescriptor _idt[IDT_SIZE];

    /*!
     * \brief Master PIC
     */
    hw::Pic _pic_master;

    /*!
     * \brief Slave PIC
     */
    hw::Pic _pic_slave;

};

}  // namespace hw

#endif  // SRC_HW_INTERRUPTMANAGER_H_
