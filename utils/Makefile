# Makefile template for shared library

INCLUDES      := $(shell root-config --cflags) -Iinclude -I$(AMSWD)/include
FLAGS  	      := -O3 -std=c++11 -D_PGTRACK_ -Wno-write-strings -fPIC

#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


SRCS = generalUtils.cpp rootUtils.cpp Stack.cpp GraphFromHistos.cpp Loop.cpp DstAmsBinary.cpp  # source files
OBJS = $(SRCS:.cpp=.o)

all: lib/libGeneralUtils.so  lib/libRootUtils.so lib/libStack.so lib/libDstAmsBinary.so  

lib/libGeneralUtils.so: generalUtils.o
	$(CXX) -shared -o $@ $^

lib/libRootUtils.so: rootUtils.o
	$(CXX) -shared -o $@ $^

lib/libStack.so: Stack.o
	$(CXX) -shared -o $@ $^ 

lib/libGraphFromHistos.so: GraphFromHistos.o
	$(CXX) -shared -o $@ $^

lib/libDstAmsBinary.so: DstAmsBinary.o Loop.o
	$(CXX) -shared -o $@ $^

$(SRCS:.cpp=.o):%.o:src/%.cpp include/%.hpp 
	$(CXX) $(FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f lib/*.so ${OBJS} lib/*.a
