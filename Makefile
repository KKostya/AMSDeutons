maindatatree: selezioni.o maindatatree.o
	g++ -o maindatatree $(AMSLIBso) `root-config --libs` selezioni.o maindatatree.o 


selezioni.o: selezioni.h selezioni.C
	g++ -c selezioni.C `root-config --cflags` -I$(AMSSRC)/include

maindatatree.o: maindatatree.C selezioni.h
	g++ -c maindatatree.C `root-config --cflags` -I$(AMSSRC)/include


