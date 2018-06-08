#include <global.h>
#include <debug.h>

#include <io/screen.h>
#include <std/string.h>

/*!
 * \brief Kernel's main function
 */
extern "C"
void kernelMain() {
    io::Screen scr;
    scr.clear();

    debug::print("Welcome to POTATOS!\nMah dudes");

    while (true) {
    }
}
