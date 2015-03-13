ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include
CFLAGS=

selections.a: Geo.o Golden.o MinBias.o Preselect.o RICH.o SelectionLists.o
	ar rvs $@ $?

Geo.o: Geo.cxx  Geo.h
Golden.o: Golden.cxx  Golden.h
MinBias.o: MinBias.cxx  MinBias.h
Preselect.o: Preselect.cxx Preselect.h
RICH.o: RICH.cxx RICH.h
SelectionLists.o:  SelectionLists.cxx SelectionLists.hpp

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
