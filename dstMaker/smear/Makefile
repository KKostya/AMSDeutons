# Change the two first lines

EXEC = compare
ADDCLASS= 

CLASSES = $(ADDCLASS) $(ADDCLASS:include/%.h=src/%.cpp)

BIN    =$(EXEC:%=bin/%)
SRC    =$(EXEC:%=./%.cpp)
OBJECTS=$(EXEC:%=./%.o)


### Options
LIBS	      := -L../../utils/lib -lRootUtils -lGeneralUtils -lStack
INCLUDES      := -I. -I$(AMSROOTLIBS) -Iinclude/ -I../../utils/include
#DEBUG	      := -g

#Ca va chier dans le compilo
ROOTCFG  := root-config
CXXFLAGS :=$(DEBUG) -O2 $(shell $(ROOTCFG) --cflags) -std=c++11 -D_PGTRACK_ -Wno-write-strings # TH1F...


#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


all : bin/compare bin/smear

bin/compare : compare.o $(CLASSES)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ $^  $(AMSSTATICLIBS) $(ROOTLIBS) $(LIBS) ../../utils/Loop.o

bin/smear : smear.o $(CLASSES)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ $^  $(AMSSTATICLIBS) $(ROOTLIBS) $(LIBS) ../../utils/Loop.o


%.o: %.cpp
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ -c $^

clean:
	rm -rf $(OBJECTS)
