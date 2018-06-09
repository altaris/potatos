#ifndef SRC_HW_KEYBOARD_H_
#define SRC_HW_KEYBOARD_H_

#include <global.h>

#include <hw/interruptmanager.h>

#include <io/port8.h>

#include <std/singleton.h>

namespace hw {

class Keyboard : public std::Singleton<Keyboard> {

    SINGLETON(Keyboard)

public:

    static constexpr uint16 PORT_DATA   = 0x60;
    static constexpr uint16 PORT_STATUS = 0x64;

public:

    Keyboard(hw::InterruptManager* interruptManager);

    /*!
     * \brief Called whenever a key is pressed
     */
    void handleKeypress();

private:

    /*!
     * \brief Data port
     */
    io::Port8 _port_data;

    /*!
     * \brief Status port
     */
    io::Port8 _port_status;

};

}  // namespace hw

#endif  // SRC_HW_KEYBOARD_H_
