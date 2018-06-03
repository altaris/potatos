#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT16_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT16_H_

#include <io/port.h>

namespace io {

/*!
 * \brief 16 bit port
 */
class Port16 : public io::Port {

public:

    Port16(uint16 port);

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

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT16_H_
