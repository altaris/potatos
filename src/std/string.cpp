#include <std/string.h>

std::String::String(const char* str) :
    _str(str) {

}

char std::String::at(uint16 i) const {
    return _str[i];
}

unsigned int std::String::length() const {
    uint16 i = 0;
    while (_str[i] != '\0') {
        i++;
    }
}

char std::String::operator[](uint16 i) const {
    return at(i);
}

std::String::operator const char*() const {
    return _str;
}
