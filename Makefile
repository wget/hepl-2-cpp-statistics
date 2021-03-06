.SILENT:
# If we define in the current directory a file named clean or mrproper, this
# will break this makefile as these target do not have any dependencies, the
# target will always be more recent and will never be evaluated. The PHONY
# directive avoids this issue.
.PHONY: clean mrproper debug test2

################################################################################
# Custom makefile functions (GNU Make)
################################################################################
# If used like "make print-MYVAR", allow to print a target/variable directly
# when calling the Makfile
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
# From all the cpp files we have, replace the cpp extension by hpp and remove
# the file main.hpp since it does not exist and make might complain there is no
# rule for this file.
# HEADERS=$(filter-out $(SRC_PATH)/main.hpp, $(SRC:.cpp=.hpp))
SRC := $(call rwildcard,$(SRC_PATH),*.cpp)
SRC_TEST = $(call rwildcard,$(TEST_PATH),*.cpp)
HEADERS = $(call rwildcard,$(SRC_PATH),*.hpp)

EXECS = main#  main
EXECS_WITH_PATH = $(patsubst %,$(DIST_PATH)/%, $(EXECS))
OBJ = $(patsubst %, $(OBJ_PATH)/%.o, $(filter-out dist/obj/tests/%,$(filter-out $(EXECS),$(SRC:$(SRC_PATH)/%.cpp=%))))

all: $(EXECS_WITH_PATH)

debug: CFLAGS+=-DWITH_DEBUG
debug: mrproper
debug: CC+=-ggdb
debug: all

# Instead of repeating dependencies over and over again, make does support the
# following shortcuts. These also allow to avoid burden when we want to change
# the destination name of executables/targets for example.
#$@ : Target name;
#$< : First dependency;
#$? : More recent dependencies than the target;
#$^ : All the dependencies;
#$* : All wildcard character, same as * but syntax interpreted by make
$(DIST_PATH)/main: $(OBJ_PATH)/main.o $(OBJ)
	echo "[+] Building $@"
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	echo "[+] Building $@"
	# Create parent directory on the fly to store objects.
	# We are making use of make's internal variable $(@D), that means "the
	# directory the current target resides in". Needed to have our directory
	# hierarchy created.
	# src.: https://stackoverflow.com/a/1951111/3514658
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) -r $(OBJ_PATH)

mrproper: clean
	$(RM) $(EXECS_WITH_PATH) $(TESTS_WITH_PATH)


# Makefile: teacher version
##.SILENT:
#UTILE=./Utile
#
#GRAPH1D=./Graph/Graph1DDiscret
#GRAPH1C=./Graph/Graph1DContinu
#GRAPH2D=./Graph/Graph2D
#
##GRAPH = $(GRAPH1D) 
#
#OBJS= Data1D.o Data2D.o EtudeStatDescriptive.o EtudeStat1D.o EtudeStat2D.o\
#	 DataSource.o DataSourceSerieDiscrete.o DataSourceSerieContinue.o\
#	DataSourceSerie2D.o Echantillon.o ListeBase.o Liste.o ListeTriee.o  BaseException.o \
#	graphstat1ddiscrete.o moc_graphstat1ddiscrete.o graphstat1dcontinue.o moc_graphstat1dcontinue.o\
#	graphstat2d.o moc_graphstat2d.o 
#
#QTLIB= -L/usr/lib/64 -L/usr/X11/lib/64 -L/opt/Qt4.8/lib -lQtGui -L/opt/Qt4.8/lib -L/usr/lib/64 \
#	-L/usr/X11/lib/64 -lQtCore -lpthread -lrt 
#
#QTINCLUDE=-I /opt/Qt4.8/mkspecs/solaris-g++-64 -I . -I /opt/Qt4.8/include/QtCore \
#	-I /opt/Qt4.8/include/QtGui -I/opt/Qt4.8/include -I /usr/include: -I usr/X11/include 
#
#GCC=g++ -m64 -Wall -I $(UTILE) $(QTINCLUDE) -I $(GRAPH1D) -I$(GRAPH1C) -I$(GRAPH2D) 
#
#QTGCC=$(GCC) -D_XOPEN_SOURCE=600 -D__EXTENSIONS__ -O2 -Wall -W -D_REENTRANT -DQT_NO_DEBUG \
#	-DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
#
#Applic:	Applic.cpp $(OBJS)
#	echo Creation de Applic
#	$(GCC) -o Applic Applic.cpp $(OBJS) $(QTLIB) -Wl,-R,/usr/local/Trolltech/Qt-4.8.6/lib
#
#EtudeStatDescriptive.o:	$(UTILE)/EtudeStatDescriptive.cpp $(UTILE)/EtudeStatDescriptive.h
#	echo Creation de EtudeStatDescriptive.o
#	$(GCC) $(UTILE)/EtudeStatDescriptive.cpp -c
#	
#BaseException.o:	$(UTILE)/BaseException.cpp $(UTILE)/BaseException.h
#	echo Creation de BaseException.o
#	$(GCC) $(UTILE)/BaseException.cpp -c
#	
#EtudeStat1D.o:	$(UTILE)/EtudeStat1D.cpp $(UTILE)/EtudeStat1D.h
#	echo Creation de EtudeStat1D.o
#	$(GCC) $(UTILE)/EtudeStat1D.cpp -c
#		
#EtudeStat2D.o:	$(UTILE)/EtudeStat2D.cpp $(UTILE)/EtudeStat2D.h
#	echo Creation de EtudeStat2D.o
#	$(GCC) $(UTILE)/EtudeStat2D.cpp -c
#	
#Echantillon.o:	$(UTILE)/Echantillon.cpp $(UTILE)/Echantillon.h
#	echo Creation de Echantillon.o
#	$(GCC) $(UTILE)/Echantillon.cpp -c
#
#Data1D.o:	$(UTILE)/Data1D.cpp $(UTILE)/Data1D.h
#	echo Creation de Data1D.o
#	$(GCC) $(UTILE)/Data1D.cpp -c
#		
#Data2D.o:	$(UTILE)/Data2D.cpp $(UTILE)/Data2D.h
#	echo Creation de Data2D.o
#	$(GCC) $(UTILE)/Data2D.cpp -c
#	
#DataSource.o:	$(UTILE)/DataSource.cpp $(UTILE)/DataSource.h
#	echo Creation de DataSource.o
#	$(GCC) $(UTILE)/DataSource.cpp -c
#
#DataSourceSerieDiscrete.o:	$(UTILE)/DataSourceSerieDiscrete.cpp $(UTILE)/DataSourceSerieDiscrete.h
#	echo Creation de DataSourceSerieDiscrete.o
#	$(GCC) $(UTILE)/DataSourceSerieDiscrete.cpp -c
#
#DataSourceSerieContinue.o:	$(UTILE)/DataSourceSerieContinue.cpp $(UTILE)/DataSourceSerieContinue.h
#	echo Creation de DataSourceSerieContinue.o
#	$(GCC) $(UTILE)/DataSourceSerieContinue.cpp -c
#	
#DataSourceSerie2D.o:	$(UTILE)/DataSourceSerie2D.cpp $(UTILE)/DataSourceSerie2D.h
#	echo Creation de DataSourceSerie2D.o
#	$(GCC) $(UTILE)/DataSourceSerie2D.cpp -c
#		
#Liste.o:	$(UTILE)/Liste.cpp $(UTILE)/Liste.h
#	echo Creation de Liste.o
#	$(GCC) $(UTILE)/Liste.cpp -c
#	
#ListeBase.o:	$(UTILE)/ListeBase.cpp $(UTILE)/ListeBase.h
#	echo Creation de ListeBase.o
#	$(GCC) $(UTILE)/ListeBase.cpp -c
#
#ListeTriee.o:	$(UTILE)/ListeTriee.cpp $(UTILE)/ListeTriee.h
#	echo Creation de ListeTriee.o
#	$(GCC) $(UTILE)/ListeTriee.cpp -c
#	
## creation des .o relatifs aux graphiques
#graphstat1ddiscrete.o: $(GRAPH1D)/graphstat1ddiscrete.cpp
#	echo creation de graphstat1ddiscrete.o
#	$(QTGCC)  $(GRAPH1D)/graphstat1ddiscrete.cpp -c
#
#moc_graphstat1ddiscrete.o: $(GRAPH1D)/moc_graphstat1ddiscrete.cpp
#	echo creation de moc_graphstat1ddiscrete.o
#	$(QTGCC)   $(GRAPH1D)/moc_graphstat1ddiscrete.cpp -c
#	
#graphstat1dcontinue.o: $(GRAPH1C)/graphstat1dcontinue.cpp
#	echo creation de graphstat1dcontinue.o
#	$(QTGCC)  $(GRAPH1C)/graphstat1dcontinue.cpp -c
#
#moc_graphstat1dcontinue.o: $(GRAPH1C)/moc_graphstat1dcontinue.cpp
#	echo creation de moc_graphstat1dcontinue.o
#	$(QTGCC)   $(GRAPH1C)/moc_graphstat1dcontinue.cpp -c
#
#graphstat2d.o: $(GRAPH2D)/graphstat2d.cpp $(GRAPH2D)/graphstat2d.h
#	echo creation de graphstat2d.o
#	$(QTGCC)   $(GRAPH2D)/graphstat2d.cpp -c
#
#moc_graphstat2d.o: $(GRAPH2D)/moc_graphstat2d.cpp
#	echo creation de moc_graphstat2d.o
#	$(QTGCC) $(GRAPH2D)/moc_graphstat2d.cpp -c
#
#
#

