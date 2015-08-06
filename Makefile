CFLAGS= -g

ROOTINC=`root-config --cflags`
ROOTLIB=`root-config --libs`
AMSINC=-I$(AMSSRC)/include

ntupleData: ntupleData.o Data Selections gitversion.c utils gitversion.c
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) ntupleData.o Data/data.a  Selections/selections.a utils/utils.a gitversion.c

selTable: SelectionsTable.o Selections 
	g++ -o $@ $(AMSLIBso) $(ROOTLIB) SelectionsTable.o  Selections/selections.a 


MyDict.cxx: $(HEADERS) Linkdef.h
	rootcint -f $@ -c $(CXXFLAGS) -p $^

libMyLib.so: MyDict.cxx $(SOURCES)
	g++ -shared -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^

Data:
	make --directory=$@

Selections:
	make --directory=$@

utils:
	make --directory=$@

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
	make --directory=utils clean

.PHONY: Selections Data utils

