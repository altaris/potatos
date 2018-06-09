#ifndef SRC_STD_SINGLETON_H_
#define SRC_STD_SINGLETON_H_

#include <global.h>

namespace std {

/*!
 * \brief A typical singleton class.
 *
 * Usage:
 * - The class pust publicly inherit from std::Singleton<TheClass>
 * - Use the SINGLETON macro withing the definition of the class (.h)
 * - In the constructor, call the std::Singleton<TheClass> constructor passing
 * `this` as argument.
 */
template<typename T> class Singleton {

public:

    /*!
     * \brief Instanciates if need be.
     */
    static T* instance() {
        return __instance;
    }

protected:

    Singleton(T* instance) {
        __instance = instance;
    }

private:

    static T* __instance;

};

template<typename T> T* Singleton<T>::__instance = NULL;

}  // namespace std

/*!
 * \brief This macro is necessary for every subclass of Singleton.
 */
#define SINGLETON(T) friend class Singleton<T>;

#endif  // SRC_STD_SINGLETON_H_

