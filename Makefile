CFLAGS=
ROOTINC=`root-config --cflags`
ROOTLIB=`root-config --libs`
AMSINC=-I$(AMSSRC)/include

selTable: SelectionsTable.o Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) SelectionsTable.o  Selections/selections.a

ntuplesData: Data.o CreateDataTree.o Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) Data.o CreateDataTree.o  Selections/selections.a

ntupleData: ntupleData.o Data Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) ntupleData.o Data/data.a  Selections/selections.a

Data:
	make --directory=$@

Selections:
	make --directory=$@

Data.o: Data.cxx Data.h
CreateDataTree.o: CreateDataTree.cxx  Data.h 
SelectionsTable.o: SelectionsTable.cxx 

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: Selections
