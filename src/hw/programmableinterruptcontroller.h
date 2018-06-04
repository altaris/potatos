#ifndef SRC_HW_PROGRAMMABLEINTERRUPTCONTROLLER_H_
#define SRC_HW_PROGRAMMABLEINTERRUPTCONTROLLER_H_

#include <global.h>

#include <io/port8.h>

namespace hw {

/*!
 * \brief Represents a PIC
 * \see https://wiki.osdev.org/PIC
 */
class ProgrammableInterruptController {

public:

    enum Type {
        Master,
        Slave
    };

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
    ProgrammableInterruptController(Type type, uint16 port, uint8 offset);

private:

    static constexpr uint8 PIC_INIT        = 0x11;
    static constexpr uint8 PIC_SET_MASTER  = 0x04;
    static constexpr uint8 PIC_SET_SLAVE   = 0x02;
    static constexpr uint8 PIC_8086_MODE   = 0x01;

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

#endif  // SRC_HW_PROGRAMMABLEINTERRUPTCONTROLLER_H_
