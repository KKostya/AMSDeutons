#define compiler
Compiler = g++
#exe
exedue = Analisi
exetre = QualityLKLHOOD.exe
exequad = Preliminar.exe
exequint = TimeAnalysis.exe
exesex = MassWindow.exe
#file to compile
CCdue = Analisi.C
CCtre = QualityLKLHOOD.C
CCquad = Preliminar.C
CCquint = TimeAnalysis.C
CCsex = MassWindow.C

#root libs
rootlibs=`root-config --libs --cflags` 
all:
	$(Compiler) -o $(exedue) $(CCdue) $(rootlibs) -lTMVA 
	$(Compiler) -o $(exetre) $(CCtre) $(rootlibs) -lTMVA
	$(Compiler) -o $(exequad) $(CCquad) $(rootlibs) -lTMVA
	$(Compiler) -o $(exequint) $(CCquint) $(rootlibs) -lTMVA
	$(Compiler) -o $(exesex) $(CCsex) $(rootlibs) -lTMVA
