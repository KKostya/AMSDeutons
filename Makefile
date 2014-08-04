
maindatatree: maindatatree.C
	g++ -o$@ `root-config --ldflags` $(CXXFLAGS) -I$(ROOTSYS)/include $^

