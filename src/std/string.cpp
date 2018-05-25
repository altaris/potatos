#include <std/string.h>

std::String::String(char* str) :
    _str(str) {
}

char std::String::at(unsigned int i) const {
    return _str[i];
}

unsigned int std::String::length() const {
    unsigned int i = 0;
    while (_str[i] != '\0') {
        i++;
    }
    if (_next) {
        return i + _next->length();
    } else {
        return i;
    }
}

char std::String::operator[](unsigned int i) const {
    return at(i);
}
