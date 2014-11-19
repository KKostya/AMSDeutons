ROOTINC=`root-config --cflags`
ROOTLIB=`root-config --libs`
AMSINC=-I$(AMSSRC)/include

Data.o: Data.cxx Data.h

%.o: %.cxx
	g++ -o $@ -c $< $(ROOTINC) $(AMSINC)


maindatatree: selezioni.o maindatatree.o
	g++ -o maindatatree $(AMSLIBso) `root-config --libs` selezioni.o maindatatree.o 

