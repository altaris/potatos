#include <mem/selector.h>

mem::Selector::Selector(
        uint8 priviledge,
        mem::Selector::TableType type,
        uint16 index) :
    _priviledge(priviledge & 0x3),
    _type(type == mem::Selector::GDT ? 0x0 : 0x1),
    _index(index & 0x1FFF) {
}
