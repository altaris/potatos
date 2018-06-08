#ifndef SRC_IO_SCREEN_H_
#define SRC_IO_SCREEN_H_

#include <global.h>

namespace std {

class String;

}  // namespace std

namespace io {

/*!
 * \brief Handles text based display
 *
 * Default dimensions: 80 cols, 25 rows
 */
class Screen {

public:

    /*!
     * \brief Default width
     *
     * Default width of the screen (in characters)
     */
    static constexpr uint16 WIDTH  = 80;
    /*!
     * \brief Default height
     *
     * Default height of the screen (in characters)
     */
    static constexpr uint16 HEIGHT = 25;

    /*!
     * \brief Available colors
     */
    enum Color {
        Black           = 0x0,
        Blue            = 0x1,
        Green           = 0x2,
        Cyan            = 0x3,
        Red             = 0x4,
        Magenta         = 0x5,
        Brown           = 0x6,
        LightGrey       = 0x7,
        DarkGrey        = 0x8,
        LightBlue       = 0x9,
        LightGreen      = 0xa,
        LightCyan       = 0xb,
        LightRed        = 0xc,
        LightMagenta    = 0xd,
        LightBrown      = 0xe,
        White           = 0xf
    };

public:

    Screen() {}

    /*!
     * \brief Clears the screen
     *
     * Writes a bunch of 0s in _videoMemory.
     */
    void clear() const;

    /*!
     * \brief Prints a character on screen
     * \param x Column number (between 0 and 79)
     * \param y Row number (between 0 and 24)
     * \param c Character to print
     * \param bg Background color
     * \param fg Foreground color
     */
    void print(uint16 x,
               uint16 y,
               char c,
               Color bg = Black,
               Color fg = LightGrey) const;

    /*!
     * \brief Prints a string on screen
     * \param x Column number (between 0 and 79)
     * \param y Row number (between 0 and 24)
     * \param str String to print
     * \param bg Background color
     * \param fg Foreground color
     *
     * Checks that str isn't too long
     */
    void print(uint16 x,
               uint16 y,
               std::String str,
               Color bg = Black,
               Color fg = LightGrey) const;

private:

    /*!
     * \brief Pointer to video memory
     */
    static constexpr uint16* _videoMemory = (uint16*) 0xb8000;

private:

    /*!
     * \brief Prints a character at a given index
     * \param i Index in video memory
     * \param c Character to print
     * \param bg Background color
     * \param fg Foreground color
     */
    void print(uint16 i,
               char c,
               Color bg = Black,
               Color fg = LightGrey) const;

};

}  // namespace io

#endif  // SRC_IO_SCREEN_H_

