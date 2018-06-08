#ifndef SRC_STD_STRING_H_
#define SRC_STD_STRING_H_

#include <global.h>

namespace std {

/*!
 * \brief Represents strings
 *
 * Internally uses char*
 */
class String {

public:

    /*!
     * \todo Length control
     * \todo Terminator control
     * \todo const char version
     */
    explicit String(const char* str);

    /*!
     * \brief Returns character at index
     * \param i Index
     * \warning No check in i
     */
    char at(uint16 i) const;

    /*!
     * \brief Length of the string
     *
     * Index of the first occurence of '\0'.
     */
    unsigned int length() const;

    /*!
     * \brief Returns character at index
     * \param i Index
     *
     * Calls str::String::at
     */
    char operator[](uint16 i) const;

    operator const char*() const;

private:

    /*!
     * \brief Internal char array
     */
    const char* _str = NULL;

};

}  // namespace std

#endif  // SRC_STD_STRING_H_

