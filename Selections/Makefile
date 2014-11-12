ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include

selections: Geo.o Golden.o MinBias.o

Geo.o: Geo.cxx  Geo.h  
Golden.o: Golden.cxx  Golden.h  
MinBias.o: MinBias.cxx  MinBias.h

%.o: %.cxx
	g++ -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
