#include <global.h>
#include <debug.h>

#include <hw/interruptmanager.h>
#include <io/screen.h>

/*!
 * \brief Kernel's main function
 */
extern "C"
void kernelMain() {
    io::Screen scr;
    scr.clear();

    hw::InterruptManager interruptManager(0x20);

    debug::print("Welcome to POTATOS!\nMah dudes\n");
    debug::print((uint32) sizeof(hw::InterruptManager::GateDescriptor));

    interruptManager.activate();

    while (true) {
    }
}
