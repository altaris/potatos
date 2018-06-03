#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT32_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT32_H_

#include <io/port.h>

namespace io {

/*!
 * \brief 32 bit port
 */
class Port32 : public io::Port {

public:

    Port32(uint16 port);

    /*!
     * \brief Reads data from the port
     */
    virtual inline uint32 read();

    /*!
     * \brief Writes data to the port
     */
    virtual inline void write(uint32 data);

};

}  // namespace io

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT32_H_
