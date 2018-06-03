#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT8_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT8_H_

#include <io/port.h>

namespace io {

/*!
 * \brief 8 bit port
 */
class Port8 : public io::Port {

public:

    Port8(uint16 port);

    /*!
     * \brief Reads data from the port
     */
    virtual inline uint8 read();

    /*!
     * \brief Writes data to the port
     */
    virtual inline void write(uint8 data);

};

}  // namespace io

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT8_H_
