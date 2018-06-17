#ifndef SRC_GLOBAL_H_
#define SRC_GLOBAL_H_

/*!
 * \brief Macro to avoid unused variable compiler warnings
 *
 * For example:
 *
 *      void return10 (int x) {
 *          UNUSED(x)
 *          return 10;
 *      }
 *
 */
#define UNUSED(x) (void) x;

/*!
 * \brief Macro for null pointer
 */
#define NULL 0

#ifdef DOXYGEN
/*!
 * \brief Macro to declare a class or structure packed
 *
 * Members of a packed class or structure are layed out contiguously in memory
 */
#define __ATTRIBUTE____PACKED__
#else
#define __ATTRIBUTE____PACKED__ __attribute__((__packed__))
#endif

/*!
 * \brief 8 bit integer
 */
typedef char                    int8;
/*!
 * \brief 8 bit unsigned integer
 */
typedef unsigned char           uint8;
/*!
 * \brief 16 bit integer
 */
typedef short                   int16;
/*!
 * \brief 16 bit unsigned integer
 */
typedef unsigned short          uint16;
/*!
 * \brief 32 bit integer
 */
typedef int                     int32;
/*!
 * \brief 32 bit unsigned integer
 */
typedef unsigned int            uint32;
/*!
 * \brief 64 bit integer
 */
typedef long long int           int64;
/*!
 * \brief 64 bit unsigned integer
 */
typedef unsigned long long int  uint64;

/*!
 * \brief Literal operator for bytes
 *
 * Does nothing:
 *
 *      x = 1_B; // x == 1
 */
constexpr uint32 operator"" _B (unsigned long long int n) {
    return n;
}

/*!
 * \brief Literal operator for kilobytes
 *
 * For example:
 *
 *      x = 1_kB; // x == 1024
 */
constexpr uint32 operator"" _kB (unsigned long long int n) {
    return 1024 * n;
}

/*!
 * \brief Literal operator for megabytes
 *
 * For example:
 *
 *      x = 1_MB; // x == 1024 * 1024
 */
constexpr uint32 operator"" _MB (unsigned long long int n) {
    return 1024 * 1024 * n;
}

/*!
 * \brief Literal operator for gigabytes
 *
 * For example:
 *
 *      x = 1_GB; // x == 1024 * 1024 * 1024
 */
constexpr uint32 operator"" _GB (unsigned long long int n) {
    return 1024 * 1024 * 1024 * n;
}

#endif  // SRC_GLOBAL_H_
