#include <mem/selector.h>

mem::Selector::Selector(
        uint8 priviledge,
        mem::Selector::TableType type,
        uint16 offset) :
    _priviledge(priviledge & 0x3),
    _type(type == mem::Selector::GDT ? 0x0 : 0x1),
    _index(offset & 0x1FFF) {
}

mem::Selector::operator uint16() const {
    return _priviledge + (_type << 2) + (_index << 3);
}
