ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include
CFLAGS= -g

all: utils.a

utils.a: rootUtils.o
	ar rvs $@ $?

rootUtils.o: rootUtils.cxx  rootUtils.hpp

clean:
	rm -f *.o *.a

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
