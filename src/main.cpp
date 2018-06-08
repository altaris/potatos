#include <global.h>

#include <mem/globaldescriptortable.h>
#include <hw/interruptmanager.h>

#include <io/screen.h>

#include <debug.h>

/*!
 * \brief PIC offset
 * \see hw::ProgrammableInterruptController
 */
constexpr uint8 PIC_OFFSET = 0x20;

/*!
 * \brief Pointer to the begening of the constructor array
 */
extern "C" void (*start_ctors)();

/*!
 * \brief Pointer to the end of the constructor array
 */
extern "C" void (*end_ctors)();

/*!
 * \brief Calls all constructors
 *
 * That is, constructs all global objects. This is called before kernelMain
 */
extern "C"
void callConstructors() {
    for (void (**i)() = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

/*!
 * \brief Kernel's main function
 * \param multibootStructure Pointer to the multiboot structure
 * \param multibootMagic Value of the magic number (?)
 */
extern "C"
void kernelMain(const void* multibootStructure, unsigned int multibootMagic) {
    UNUSED(multibootStructure);
    UNUSED(multibootMagic);

    io::Screen scr;
    scr.clear();

    mem::GlobalDescriptorTable gdt;
    hw::InterruptManager im(0x20, &gdt);

    im.activate();

    while (true) {
    }
}
