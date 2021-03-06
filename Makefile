.SILENT:
# If we define in the current directory a file named clean or mrproper, this
# will break this Makefile. As these targets do not have any dependencies, the
# target will always be more recent and will never be evaluated. The PHONY
# directive avoids this issue.
.PHONY: clean mrproper debug

################################################################################
# Custom Makefile functions (GNU Make specific)
################################################################################
# If used like "make print-MYVAR", allow to print a target/variable directly
# when calling the Makefile, e.g.:
# src.: https://stackoverflow.com/a/25817631
print-%: ; @echo $* = $($*)
# Recursive wildcard because the default wildcard is not recursive
rwildcard = $(wildcard $1$2) $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2))

################################################################################
# Compiler settings
################################################################################
CC = g++
# -fPIC -fPIE for position independant code is required by Qt
CFLAGS = -std=gnu++11 -W -Wall -I/usr/include -I. -I/usr/include/qt/QtWidgets -I/usr/include/qt -fPIC
# For other GNU/Linux distributions, the location of the lib Qt differs. May be wise to use pkgconf.
LDFLAGS = -lQt5Core -lQt5Widgets -lQt5Gui

################################################################################
# Gathering files
################################################################################
SRC_PATH = src
DIST_PATH = dist
OBJ_PATH = $(DIST_PATH)/obj

# From all the .cpp files we have, replace the .cpp extension by .hpp and remove
# the file main.hpp since it does not exist and make might complain there is no
# rule for this file.
# HEADERS=$(filter-out $(SRC_PATH)/main.hpp, $(SRC:.cpp=.hpp))

# Search for all .cpp files recursively starting from the directory specified
# by SRC_PATH.
SRC := $(call rwildcard,$(SRC_PATH),*.cpp)

# Search for all .cpp files recursively starting from the test directory
# specified by SRC_TEST.
SRC_TEST = $(call rwildcard,$(TEST_PATH),*.cpp)

EXECS = main
# Among all the EXECS, search for % (which means a wildcard) and prefix it by
# the path specified by DIST_PATH.
# Syntax: in each space separated words in 'text', search for a 'pattern' and
# replace it by 'replacement'. The usual widlcard star is a percentage '%' in
# the GNU Make syntax.
# $(patsubst pattern,replacement,text)
EXECS_WITH_PATH = $(patsubst %,$(DIST_PATH)/%, $(EXECS))
# 1. $(SRC:$(SRC_PATH)/%.cpp=%)): take all the sources specified by 'SRC' and
#    remove the prefix SRC_PATH and .cpp file existension
# 2. filter-out: remove the execs and all the files located at 'dist/obj/tests/'
# 3. prefix the result by the object path specified by 'OBJ_PATH' and add the
#    .o file extension
OBJ = $(patsubst %, $(OBJ_PATH)/%.o, $(filter-out dist/obj/tests/%,$(filter-out $(EXECS),$(SRC:$(SRC_PATH)/%.cpp=%))))

################################################################################
# Rules
################################################################################
# Syntax:
# target: prerequisites/dependencies
# 		recipe/instructions
# Note: In the tech litterature, prerequisites and dependencies are
# interchangeably used and qualify the same thing.
all: $(EXECS_WITH_PATH)

debug: CFLAGS+=-DWITH_DEBUG
debug: mrproper
debug: CC+=-ggdb
debug: all

# Instead of repeating the same dependencies over and over again, GNU Make does
# support the following shortcuts. These also avoid some burden when we want to
# change the destination name of executables/targets for example as they allow
# to change what we want eveywhere at once.
#$@ : Target name;
#$< : First dependency;
#$? : More recent dependencies than the target;
#$^ : All the dependencies;
#$* : All wildcard character, same as * but syntax interpreted by Make
$(DIST_PATH)/main: $(OBJ_PATH)/main.o $(OBJ)
	echo "[+] Building $@"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	echo "[+] Building $@"
	# Create parent directory on the fly to store objects. We are making use of
	# the make's internal variable $(@D) which means "the directory the current
	# target resides in". Needed to have our directory hierarchy created.
	# src.: https://stackoverflow.com/a/1951111/3514658
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -r $(OBJ_PATH)

mrproper: clean
	$(RM) $(EXECS_WITH_PATH) $(TESTS_WITH_PATH)
