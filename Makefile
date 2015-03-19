CFLAGS=
ROOTINC=`root-config --cflags`
ROOTLIB=`root-config --libs`
AMSINC=-I$(AMSSRC)/include

selTable: SelectionsTable.o Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) SelectionsTable.o  Selections/selections.a

ntupleData: ntupleData.o Data Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) ntupleData.o Data/data.a  Selections/selections.a

Data:
	make --directory=$@

Selections:
	make --directory=$@

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: Selections Data
