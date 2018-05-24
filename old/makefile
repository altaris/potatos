NAME		= potatos
VERSION		= alpha
TARGET 		= $(NAME)-$(VERSION)

GCCPARAMS 	= -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS 	= --32
LDPARAMS 	= -melf_i386

OBJECTS 	= build/obj/*.o

.PHONY: clean

all: clean build/$(TARGET).bin 

clean:
	rm -rf build/obj build/$(TARGET).bin

doc:
	doxygen doxyfile

build/obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

build/obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

run: build/$(TARGET).bin
	qemu-system-i386 -kernel build/$(TARGET).bin

build/$(TARGET).bin: linker.ld $(OBJECTS)
	ld $(LDPARAMS) -T $< -o $@ $(OBJECTS)
