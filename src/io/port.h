#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT_H_

#include <global.h>

namespace io {

/*!
 * \brief An abstract port
 */
class Port {

protected:

    Port(uint16 port);

protected:

    /*!
     * \brief Port number
     */
    uint16 _port;

};

}  // namespace io

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_IO_PORT_H_
