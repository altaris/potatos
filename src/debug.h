#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_

#include <std/string.h>

namespace debug {

void clear();

void print(char c);

void print(const char* str);

void print(const std::String& str);

void print(uint32 n);

}  // namespace debug

#endif  // SRC_DEBUG_H_
