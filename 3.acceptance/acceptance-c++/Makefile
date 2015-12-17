# Change the two first lines

EXEC = main
ADDCLASS= 

CLASSES = $(ADDCLASS) $(ADDCLASS:include/%.h=src/%.cpp)

BIN    =$(EXEC:%=bin/%)
SRC    =$(EXEC:%=./%.cpp)
OBJECTS=$(EXEC:%=./%.o)


### Options
LIBS	      := -L../../utils/lib/ -lRootUtils -lGeneralUtils
INCLUDES      := -I. -I$(AMSROOTLIBS) -Iinclude/ -I../../utils/include
DEBUG	      := -O3

#Ca va chier dans le compilo
ROOTCFG  := root-config 
CXXFLAGS :=$(DEBUG)  $(shell $(ROOTCFG) --cflags) -D_PGTRACK_ -Wno-write-strings # TH1F...


#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


all :$(BIN) result

$(BIN) : $(OBJECTS) $(CLASSES) ../../utils/Loop.o
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ $^  $(AMSSTATICLIBS) $(ROOTLIBS)  $(LIBS)  -lStack

result : result.cpp
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o result result.cpp  $(AMSSTATICLIBS) $(ROOTLIBS)  $(LIBS) 


$(OBJECTS): $(SRC)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ -c $^

clean:
	rm -rf *.o bin/*
