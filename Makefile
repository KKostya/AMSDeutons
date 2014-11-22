CFLAGS=
ROOTINC=`root-config --cflags`
ROOTLIB=`root-config --libs`
AMSINC=-I$(AMSSRC)/include

ntuplesData: Data.o CreateDataTree.o Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) Data.o CreateDataTree.o  Selections/selections.a

Selections:
	make --directory=$@

Data.o: Data.cxx Data.h
CreateDataTree.o: CreateDataTree.cxx  Data.h 

%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: Selections
