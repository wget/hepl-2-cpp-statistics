# HEPL - 2 - CPP Statistics

A simple applied statistics course in C++.

## Build instructions

0. Make sure you have a C++11 capable compiler. This project has only been tested with GNU GCC. The Makefile ensures the code is compiled in 2011 mode.

   If you are using an old machine and you are unsure of the version of C++ being available, you can display the value of the `__cplusplus` keyword.
    ```
    #include <iostream>

    int main(void) {
        std::cout << __cplusplus << std::endl;
        return 0;
    }
    ```

    To force the compilation in C++11, compile with `g++ -std=gnu++11 test_cpp_standard.cpp  -o test_cpp_standard`, execute the binary produced. It should return `201103`. If C++11 is not supported, you should have something like `g++: error: unrecognized command-line option ‘-std=gnu++11’; did you mean 'XXX'?`


1. Clone this repository:
    ```
    $ git clone https://github.com/wget/hepl-2-cpp-statistics
    $ cd hepl-2-cpp-statistics
    ```
2. from the root of the directory where you cloned this repository, clone the library to `src/lib/`:
    ```
    $ git clone https://github.com/wget/hepl-2-cpp-lib src/lib/utils
    ```

3. This project is built with Qt and requires to have MOC files (`.cpp` usually beginning with the `moc_` prefix). Generating moc files is only needed on Qt files containing Qt classes making use of the `Q_OBJECT` macro. While our Makefile is taking care of regenerating these moc files for you, you may want to regenerate them manually with:
    ```
    $ moc ./src/lib/graph/Graph1DContinu/graphstat1dcontinue.h > ./src/lib/graph/Graph1DContinu/moc_graphstat1dcontinue.cpp
    $ moc ./src/lib/graph/Graph1DDiscret/graphstat1ddiscrete.h > ./src/lib/graph/Graph1DDiscret/moc_graphstat1ddiscrete.cpp
    $ moc ./src/lib/graph/Graph2D/graphstat2d.h > ./src/lib/graph/Graph2D/moc_graphstat2d.cpp
    ```

   The moc files are tighly coupled to the version of the Qt library being installed on the system. Therefore they need to be regenerated each time the Qt library is being updated on the system.

4. Still from the root of this repository, build the project with:
    ```
    $ make
    ```

## Debugging

* To clean objs and executables:
    ```
    $ make mrproper
    ```

* We have written a special rule called `debug`. The latter is compiling the code in debug mode (with debugging symbols) and add an additional debug flag understood by the util library to add more traces on stdout.

  That debug rule is also running the `mrproper` rule for you.

  To run the debug rule, just type:
  ```
  $ make debug
  ```

* To debug: [src.](https://stackoverflow.com/a/6121299/3514658)
    ```
    $ gdb --args ./dist/main arg1 arg2 arg3
    ```

* When debugging this project we realized that some files were malformed due to the fact the teachers edited the data alternatively the data files from UNIxX or Windows. Some lines were using the UNIX EOL and some the Windows EOL characters which broke our parsing. To find out the reason we had to debug this issue carefully and `valgrind` came to the help:

  Out of bound and parsing debug issue:
    ```
    $ ./dist/main ./data/DonneeNbEnf.txt
    ```

  Or if you prefer valgrind:
    ```
    $ valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose dist/main data/Donnee.dat
    ```

* In the Makefile, we defined a custom rule beginning with `print-`. When calling your Makefile, you just need to suffix that rule by the name of the variable you want to display to display the content of that variable. Imagine you want to display what the `OBJ` variable is containing, just type `make print-OBJ` and you get the content displayed on your terminal:

    ```
    $ make print-OBJ
    OBJ = dist/obj/Data1D.o dist/obj/Data2D.o dist/obj/DataSource2D.o dist/obj/DataSource.o dist/obj/DataSourceSerie2D.o dist/obj/DataSourceSerieContinue.o dist/obj/DataSourceSerieDiscrete.o dist/obj/Sample.o dist/obj/Stat1DStudy.o dist/obj/Stat2DStudy.o dist/obj/lib/graph/Graph1DContinu/graphstat1dcontinue.o dist/obj/lib/graph/Graph1DDiscret/graphstat1ddiscrete.o dist/obj/lib/graph/Graph2D/graphstat2d.o dist/obj/lib/utils/src/HeplBaseException.o dist/obj/lib/utils/src/HeplString.o dist/obj/lib/utils/src/HeplStringOutOfRangeException.o
    ```