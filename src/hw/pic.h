#ifndef SRC_HW_PIC_H_
#define SRC_HW_PIC_H_

#include <global.h>

#include <io/port8.h>

namespace hw {

/*!
 * \brief Represents a PIC
 * \see https://wiki.osdev.org/PIC
 */
class Pic {

public:

    /*!
     * \brief Constructor
     * \param port
     * \param offset Offset for the PIC remap
     *
     * Vectors on the PIC become offset..offset+7
     *
     * The command port is `port`, whereas the data port is `port + 1`
     */
    Pic(uint16 port, uint8 offset);

private:

    /*!
     * \brief ICW1: Begin initialization
     */
    static constexpr uint8 PIC_INIT             = 0x11;
    /*!
     * \brief ICW3: Setup cascading
     */
    static constexpr uint8 PIC_SET_CASCADE      = 0x00;
    /*!
     * \brief ICW4: Set environment infos
     */
    static constexpr uint8 PIC_SET_ENV          = 0x01;

private:

    /*!
     * \brief Command port
     *
     * This is an 8 bits slow port
     */
    io::Port8 _commandPort;

    /*!
     * \brief Data port
     *
     * This is an 8 bits slow port
     */
    io::Port8 _dataPort;

};

}  // namespace hw

#endif  // SRC_HW_PIC_H_
