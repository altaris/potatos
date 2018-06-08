#ifndef SRC_IO_PORT8_H_
#define SRC_IO_PORT8_H_

#include <global.h>

namespace io {

/*!
 * \brief 8 bit port
 */
class Port8 {

public:

    explicit Port8(uint16 port);

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
     * \brief Port number
     */
    uint16 _port;

};

}  // namespace io

#endif  // SRC_IO_PORT8_H_
