# HEPL - 2 - CPP Statistics

A simple applied statistics course in cpp.

## Build instructions

Clone this directory and clone the lib directory to the src/lib/ subfolder, typically from the root of this repository:

    git clone https://github.com/wget/hepl-2-cpp-lib src/lib/utils

Then, still from the root of this repository:

    make

To clean objs and executables:

    make mrproper

Requires a C++11 compiler. Only tested with GNU GCC.

To debug: [src.](https://stackoverflow.com/a/6121299/3514658)

    gdb --args ./dist/main arg1 arg2 arg3

Out of bound and parsing debug issue:

    ./dist/main ./data/DonneeNbEnf.txt

Or if you prefer valgrind:

    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose dist/main data/Donnee.dat

