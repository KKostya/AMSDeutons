ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include
CFLAGS=

selections.a: Geo.o Golden.o MinBias.o Preselect.o RICH.o
	ar rvs $@ $?

Geo.o: Geo.cxx  Geo.h SubSelection.hpp
Golden.o: Golden.cxx  Golden.h  SubSelection.hpp
MinBias.o: MinBias.cxx  MinBias.h SubSelection.hpp
Preselect.o: Preselect.cxx Preselect.h SubSelection.hpp
RICH.o: RICH.cxx RICH.h SubSelection.hpp

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
