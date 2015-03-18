ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include
CFLAGS=

data.a: Geo.o Provenance.o Tracker.o RootWriter.o
	ar rvs $@ $?

Geo.o: Geo.cxx  Geo.h
Provenance.o: Provenance.cxx  Provenance.h
Tracker.o: Tracker.cxx  Tracker.h
RootWriter.o:  RootWriter.cxx RootWriter.hpp Geo.o Provenance.o Tracker.o

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
