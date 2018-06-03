#ifndef SRC_IO_PORT16_H_
#define SRC_IO_PORT16_H_

#include <io/port.h>

namespace io {

/*!
 * \brief 16 bit port
 */
class Port16 : public io::Port {

public:

    explicit Port16(uint16 port);

    /*!
     * \brief Reads data from the port
     */
    virtual inline uint16 read();

    /*!
     * \brief Writes data to the port
     */
    virtual inline void write(uint16 data);

};

}  // namespace io

#endif  // SRC_IO_PORT16_H_
