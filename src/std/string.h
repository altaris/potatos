#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_STD_STRING_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_STD_STRING_H_

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
    explicit String(char* str);

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

private:

    /*!
     * \brief Pointer to next string
     */
    String* _next = NULL;

    /*!
     * \brief Internal char array
     */
    char* _str = NULL;

};

}  // namespace std

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_STD_STRING_H_

