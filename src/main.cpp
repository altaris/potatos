#include <global.h>

#include <mem/globaldescriptortable.h>

#include <io/screen.h>
#include <std/string.h>

typedef void (*Constructor)();

/*!
 * \brief Pointer to the begening of the constructor array
 */
extern "C"
Constructor start_ctors;

/*!
 * \brief Pointer to the end of the constructor array
 */
extern "C"
Constructor end_ctors;

/*!
 * \brief Calls all constructors
 *
 * That is, constructs all global objects. This is called before kernelMain
 */
extern "C"
void callConstructors() {
    for (Constructor* i = &start_ctors; i != &end_ctors; i++) {
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

    mem::GlobalDescriptorTable gdt;

    io::Screen scr;
    scr.clear();
    scr.print(1, 1,
              std::String("Hello World! This is my OS!"),
              io::Screen::Blue,
              io::Screen::Red);

    while (1) {
    }
}
