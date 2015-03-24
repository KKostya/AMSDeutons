CFLAGS= -g
ROOTINC=`root-config --cflags`
ROOTLIB=`root-config --libs`
AMSINC=-I$(AMSSRC)/include

ntupleData: ntupleData.o Data Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) ntupleData.o Data/data.a  Selections/selections.a

selTable: SelectionsTable.o Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) SelectionsTable.o  Selections/selections.a

<<<<<<< HEAD
=======
ntuplesData: Data.o CreateDataTree.o Selections
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) Data.o CreateDataTree.o  Selections/selections.a

ntupleData: ntupleData.o Data Selections gitversion.c rootUtils.o
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) ntupleData.o rootUtils.o Data/data.a  Selections/selections.a gitversion.c 
>>>>>>> benoit

Data:
	make --directory=$@

Selections:
	make --directory=$@

<<<<<<< HEAD
%.o: %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

.PHONY: Selections Data
=======
Data.o: Data.cxx Data.h
CreateDataTree.o: CreateDataTree.cxx  Data.h 
SelectionsTable.o: SelectionsTable.cxx 

%.o : %.cxx
	g++ $(CFLAGS) -o $@ -c $< $(ROOTINC) $(AMSINC)

gitversion.c: .git/HEAD .git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

clean:
	rm -f *.o *.a ntupleData ntuplesData
	make --directory=Data clean
	make --directory=Selections clean

.PHONY: Selections
>>>>>>> benoit
