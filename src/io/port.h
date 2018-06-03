#ifndef SRC_IO_PORT_H_
#define SRC_IO_PORT_H_

#include <global.h>

namespace io {

/*!
 * \brief An abstract port
 */
class Port {

protected:

    explicit Port(uint16 port);

protected:

    /*!
     * \brief Port number
     */
    uint16 _port;

};

}  // namespace io

#endif  // SRC_IO_PORT_H_
