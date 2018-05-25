#ifndef DOCUMENTS_PROJECTS_POTATOS_SRC_GLOBAL_H_
#define DOCUMENTS_PROJECTS_POTATOS_SRC_GLOBAL_H_

// NOLINTNEXTLINE
#define UNUSED(x) (void) x

#define NULL 0

typedef char                    int8;
typedef unsigned char           uint8;
typedef short                   int16;
typedef unsigned short          uint16;
typedef int                     int32;
typedef unsigned int            uint32;
typedef long long int           int64;
typedef unsigned long long int  uint64;

/*!
 * \brief Literal operator for bytes
 *
 * Doesn nothing (1_B = 1)
 */
constexpr uint32 operator"" _B (unsigned long long int n) {
    return n;
}

/*!
 * \brief Literal operator for kilobytes
 *
 * 1_kB = 1024
 */
constexpr uint32 operator"" _kB (unsigned long long int n) {
    return 1024 * n;
}

/*!
 * \brief Literal operator for megabytes
 *
 * 1_MB = 1024 * 1024
 */
constexpr uint32 operator"" _MB (unsigned long long int n) {
    return 1024 * 1024 * n;
}

/*!
 * \brief Literal operator for gigabytes
 *
 * 1_GB = 1024 * 1024 * 1024
 */
constexpr uint32 operator"" _GB (unsigned long long int n) {
    return 1024 * 1024 * 1024 * n;
}

#endif  // DOCUMENTS_PROJECTS_POTATOS_SRC_GLOBAL_H_
