#ifndef SRC_IO_PORT8_H_
#define SRC_IO_PORT8_H_

#include <io/port.h>

namespace io {

/*!
 * \brief 8 bit port
 */
class Port8 : public io::Port {

public:

    explicit Port8(uint16 port, bool slow = false);

    /*!
     * \brief Reads data from the port
     */
    uint8 read();

    /*!
     * \brief Writes data to the port
     */
    void write(uint8 data);

private:

    /*!
     * \brief If the port is slow
     *
     * A slow port waits for io to complete until returning from the write()
     * method.
     */
    bool _slow;

};

}  // namespace io

#endif  // SRC_IO_PORT8_H_
