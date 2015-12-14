# Change the two first lines

EXEC = dst
ADDCLASS= 

CLASSES = $(ADDCLASS) $(ADDCLASS:include/%.h=src/%.cpp)

BIN    =$(EXEC:%=bin/%)
SRC    =$(EXEC:%=./%.cpp)
HEADER =$(EXEC:%=./%.hpp)
OBJECTS=$(EXEC:%=./%.o)


### Options
AMSROOTLIBS   :=$(AMSWD)/include # amschain.h
LIBS	      := -L../utils/lib -lRootUtils -lGeneralUtils
INCLUDES      := -I. -Iselections/ -I$(AMSROOTLIBS) -Iinclude/ -I../utils/include
DEBUG	      := -O3

#Ca va chier dans le compilo
ROOTCFG  := root-config
CXXFLAGS :=$(DEBUG) $(shell $(ROOTCFG) --cflags) -std=c++11 -D_PGTRACK_ -Wno-write-strings -Wno-unknown-pragmas # TH1F...


#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


all :$(BIN)

gitversion.hpp: ../.git/HEAD ../.git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

selections/selections.a:
	make --directory=selections

utils:
	make --directory=../utils

$(BIN) : $(OBJECTS) $(CLASSES) selections/selections.a utils
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@  dst.o $(AMSSTATICLIBS) $(ROOTLIBS) $(LIBS) selections/selections.a -lDstAmsBinary


$(OBJECTS): $(SRC) $(HEADER)
	make -B gitversion.hpp
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJECTS) bin/dst
	rm -f selections/selections.a selections/*.o
	rm -f gitversion.hpp
