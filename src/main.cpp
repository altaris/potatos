#include <utils.h>

/*!
 * \brief printf
 * \param str
 */
void printf (
    char* str
) {
    static unsigned short * VideoMemory = (unsigned short *) 0xb8000;
    for (int i = 0; str[i] != '\0'; i++) {
        VideoMemory[i] = (VideoMemory[i] & 0xff00) | str[i];
    }
}

/*!
 * \brief Kernel's main function
 * \param multibootStructure Pointer to the multiboot structure
 * \param multibootMagic Value of the magic number (?)
 */
extern "C"
void kernelMain (
    const void * multibootStructure,
    unsigned int multibootMagic
) {
    UNUSED(multibootStructure);
    UNUSED(multibootMagic);


    printf("Hello World! This is my OS!");

    while(1);
}
