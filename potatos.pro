TARGET          = potatos
VERSION         = alpha

CONFIG          =
TEMPLATE        =

QMAKE_CXX       = gcc
QMAKE_CXXFLAGS  = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
QMAKE_LINK      = ld
QMAKE_LFLAGS    = -melf_i386 -T $${PWD}/linker.ld
QMAKE_LFLAGS_DEBUG   =
QMAKE_LFLAGS_RELEASE =
QMAKE_AS        = as
QMAKE_ASFLAGS   = --32

SOURCES_ASM    += \
    src/loader.s

asm.input       = SOURCES_ASM
asm.output      = ${QMAKE_FILE_IN_BASE}$${first(QMAKE_EXT_OBJ)}
asm.commands    = $${QMAKE_AS} $${QMAKE_ASFLAGS} ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
QMAKE_EXTRA_COMPILERS += asm

INCLUDEPATH     = \
    include

SOURCES        += \
    src/main.cpp

HEADERS        += \
    include/utils.h

DISTFILES += \
    readme.md



