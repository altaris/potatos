TARGET          = potatos
VERSION         = alpha

CONFIG          =
TEMPLATE        =

QMAKE_CXX       = gcc
QMAKE_CXXFLAGS  = -m32 -std=c++11 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
QMAKE_LINK      = ld
QMAKE_LFLAGS    = -m elf_i386 -T $${PWD}/linker.ld
QMAKE_LFLAGS_DEBUG   =
QMAKE_LFLAGS_RELEASE =
QMAKE_AS        = nasm
QMAKE_ASFLAGS   = -f elf32

SOURCES_ASM    += \
    src/loader.asm

asm.input       = SOURCES_ASM
asm.output      = ${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
asm.commands    = $${QMAKE_AS} $${QMAKE_ASFLAGS} ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += asm

INCLUDEPATH     = \
    src

SOURCES        += \
    src/main.cpp \
    src/io/port.cpp \
    src/io/port8.cpp \
    src/io/port16.cpp \
    src/io/port32.cpp \
    src/io/screen.cpp \
    src/std/string.cpp \
    src/debug.cpp

HEADERS        += \
    src/global.h \
    src/io/port.h \
    src/io/port8.h \
    src/io/port16.h \
    src/io/port32.h \
    src/io/screen.h \
    src/std/string.h \
    src/debug.h

DISTFILES += \
    readme.md \
    makefile \
    linker.ld



