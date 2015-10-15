ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include
CFLAGS= -g

selections.a: Geo.o Golden.o MinBias.o Preselect.o RICH.o 
	ar rvs $@ $?

Geo.o: Geo.cxx  Geo.h
Golden.o: Golden.cxx  Golden.h
MinBias.o: MinBias.cxx  MinBias.h
Preselect.o: Preselect.cxx Preselect.h
RICH.o: RICH.cxx RICH.h

clean:
	rm -rf *.o *.a

%.o: %.cxx
	g++ -D_PGTRACK_ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
