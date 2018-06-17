#ifndef SRC_MEM_SELECTOR_H_
#define SRC_MEM_SELECTOR_H_

#include <global.h>

namespace mem {

/*!
 * \brief Represents a selector
 * \see https://wiki.osdev.org/Selector
 */
class __ATTRIBUTE____PACKED__ Selector {

public:

    /*!
     * \brief Type of the table the selector is referencing to
     */
    enum TableType {
        GDT,
        LDT
    };

public:

    Selector(uint8 priviledge, TableType type, uint16 offset);

    operator uint16() const;

private:

    /*!
     * \brief Requested Privilege Level
     *
     * The CPU checks these bits before any selector is changed.
     */
    uint8 _priviledge : 2;

    /*!
     * \brief Type
     * \see TableType
     *
     * - `0` : GDT
     * - `1` : LDT
     */
    uint8 _type : 1;

    /*!
     * \brief Index (offset) of the descriptor in the table
     */
    uint16 _index : 13;

};

}  // namespace mem

#endif // SRC_MEM_SELECTOR_H_
