# Change the two first lines

EXEC = computeExposureTime
ADDCLASS= 

CLASSES = $(ADDCLASS) $(ADDCLASS:include/%.h=src/%.cpp)

SRC    =$(EXEC:%=./%.cpp)
OBJECTS=$(EXEC:%=./%.o)


### Options
AMSROOTLIBS   :=$(AMSWD)/include # amschain.h
AMSSTATICLIBS := -L$(AMSWD)/lib/linuxx8664gcc5.34 -lntuple_slc6_PG
LIBS	      := -L${HOME}/utils/lib/ -lRootUtils
INCLUDES      := -I. -I$(AMSROOTLIBS) -Iinclude/ -I${HOME}/utils/include
DEBUG	      := -O3

#Ca va chier dans le compilo
ROOTCFG  := root-config
CXX      :=$(shell $(ROOTCFG) --cxx)   #g++
CXXFLAGS :=$(DEBUG) $(shell $(ROOTCFG) --cflags) -D_PGTRACK_ -Wno-write-strings # TH1F...
ROOTLIBS :=$(shell $(ROOTCFG) --libs) -lTMVA -lNetx -lNet -lRFIO


#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


all :$(EXEC)

$(EXEC) : $(OBJECTS) $(CLASSES)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(ROOTLIBS) $(LIBS) $(AMSSTATICLIBS)


$(OBJECTS): $(SRC)
	$(CXX)  $(CXXFLAGS) $(INCLUDES) -o $@ -c $^

clean:
	rm -rf $(OBJECTS)
