ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include

selections: Geo.o Golden.o MinBias.o Preselect.o

Geo.o: Geo.cxx  Geo.h SubSelection.hpp
Golden.o: Golden.cxx  Golden.h  SubSelection.hpp
MinBias.o: MinBias.cxx  MinBias.h SubSelection.hpp
Preselect.o: Preselect.cxx Preselect.h SubSelection.hpp

%.o: %.cxx
	g++ -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
