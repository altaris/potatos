#include <debug.h>
#include <global.h>

#include <hw/interruptmanager.h>
#include <hw/keyboard.h>

/*!
 * \brief Kernel's main function
 */
extern "C"
void kernelMain() {
    hw::InterruptManager interruptManager(0x20);
    hw::Keyboard kbd(&interruptManager);

    debug::clear();
    debug::print("Welcome to POTATOS!\nMah dudes\n");

    interruptManager.activate();

    while (true) {
    }
}
