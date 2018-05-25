#include <io/screen.h>
#include <std/string.h>

void io::Screen::clear() const {
    for (unsigned int i = 0; i < io::Screen::height * io::Screen::width; i++) {
        _videoMemory[i] = 0x0000;
    }
}

void io::Screen::print(
        unsigned int x,
        unsigned int y,
        char c,
        io::Screen::Color bg,
        io::Screen::Color fg) const {
    if (x < io::Screen::width && y < io::Screen::height) {
        print(y * io::Screen::width + x, c, bg, fg);
    }
}

void io::Screen::print(
        unsigned int x,
        unsigned int y,
        std::String str,
        io::Screen::Color bg,
        io::Screen::Color fg) const {
    if (x < io::Screen::width
            && y < io::Screen::height
            && y * io::Screen::width + x + str.length() - 1
            <= io::Screen::height * io::Screen::width
    ) {
        for (unsigned int i = 0; i < str.length(); i++) {
            print(y * io::Screen::width + x + i, str[i], bg, fg);
        }
    }
}

void io::Screen::print(
        unsigned int i,
        char c,
        io::Screen::Color bg,
        io::Screen::Color fg) const {
    _videoMemory[i] = (bg << 12) | (fg << 8) | c;
}
