# Change the two first lines

EXEC = compareAmsChains
ADDCLASS= 

CLASSES = $(ADDCLASS) $(ADDCLASS:include/%.h=src/%.cpp)

BIN    =$(EXEC:%=bin/%)
SRC    =$(EXEC:%=./%.cpp)
OBJECTS=$(EXEC:%=./%.o)


### Options
LIBS	      := -L${HOME}/utils/lib/ -lLoop -L${HOME}/utils/Stack/lib -lStack
INCLUDES      := -I. -I$(AMSROOTLIBS) -Iinclude/ -I${HOME}/utils/ -I${HOME}/utils/Stack
DEBUG	      := -g

#Ca va chier dans le compilo
ROOTCFG  := root-config
CXXFLAGS :=$(DEBUG) -O2 $(shell $(ROOTCFG) --cflags) -D_PGTRACK_ -Wno-write-strings # TH1F...


#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


all :$(BIN)

$(BIN) : $(OBJECTS) $(CLASSES)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ $^  $(AMSSTATICLIBS) $(ROOTLIBS) $(LIBS)


$(OBJECTS): $(SRC)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ -c $^

clean:
	rm -rf $(OBJECTS)
