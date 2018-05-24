potatos
=======

This is a personal OS experiment. Some code is largely copypasta'd from various "Make your own OS" tutorials such as [this](https://arjunsreedharan.org/post/82710718100/kernel-101-lets-write-a-kernel) and [this](https://www.youtube.com/watch?v=1rnA6wpF0o4&list=PLHh55M_Kq4OApWScZyPl5HhgsTJS9MZ6M&index=2&t=0s).

# Tools

* `as` (assembler compiler)
* `ld` (linker)
* `gcc` (c++ compiler)
* `qmake`, `make`
* `qemu-system-i386`

# Build

Instead of the traditional `makefile`, this projects uses a QT Creator `pro` file.

# Run

```
qemu-system-i386 -kernel potatos
```

This can be configured in Qt Creator (Projects -> Build & Run -> Run -> Add new run configuration).
