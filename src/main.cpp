#include <debug.h>
#include <global.h>

#include <hw/interruptmanager.h>
#include <hw/keyboard.h>

#include <mem/descriptormanager.h>

/*!
 * \brief Kernel's main function
 */
extern "C"
void kernelMain() {

    debug::clear();
    debug::print("Welcome to POTATOS mah dudes!\n");

    mem::DescriptorManager descriptorManager;

    hw::InterruptManager interruptManager(&descriptorManager, 0x20);
    hw::Keyboard kbd(&interruptManager);

    interruptManager.activate();

    while (true) {
    }
}
