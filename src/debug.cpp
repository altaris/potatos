#include <debug.h>

#include <io/screen.h>

io::Screen screen;
uint8 currentLine = 0;
uint8 currentColumn = 0;

void newLine() {
    currentLine++;
    if (currentLine >= io::Screen::HEIGHT) {
        currentLine = 0;
    }
    currentColumn = 0;
}

void debug::clear() {
    screen.clear();
}

void debug::print(char c) {
    if (c == '\n') {
        newLine();
    } else {
        screen.print(
                    currentColumn,
                    currentLine,
                    c,
                    io::Screen::Black,
                    io::Screen::Green);
        currentColumn++;
        if (currentColumn >= io::Screen::WIDTH) {
            newLine();
        }
    }
}

void debug::print(const char* str) {
    for (uint16 i = 0; str[i] != '\0'; i++) {
        debug::print((char) str[i]);
    }
}

void debug::print(const std::String& str) {
    debug::print((const char*) str);
}

void debug::print(uint32 n) {
    static const char* HEX = "0123456789ABCDEF";
    debug::print("0x");
    for (int i = 7; i >= 0; i--) {
        debug::print((char) HEX[(n >> (4 * i)) & 0xF]);
    }
}
