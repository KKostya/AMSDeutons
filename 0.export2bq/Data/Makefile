ROOTINC=`root-config --cflags`
AMSINC=-I$(AMSSRC)/include
CFLAGS= -g

all: data.a

data.a: Geo.o Provenance.o Tracker.o Ecal.o RootWriter.o TRD.o TOF.o SelectionStatus.o MC.o RICH.o
	ar rvs $@ $?

Geo.o: Geo.cxx  Geo.h
Provenance.o: Provenance.cxx  Provenance.h
Tracker.o: Tracker.cxx  Tracker.h
Ecal.o: Ecal.cxx  Ecal.h
TRD.o: TRD.cxx  TRD.h
TOF.o: TOF.cxx  TOF.h
RICH.o: RICH.cxx  RICH.h
SelectionStatus.o: SelectionStatus.cxx  SelectionStatus.h
RootWriter.o:  RootWriter.cxx RootWriter.hpp Geo.o Provenance.o Tracker.o Ecal.o TRD.o TOF.o MC.o

clean:
	rm -f *.o *.a

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: selections
