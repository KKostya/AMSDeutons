# Change the two first lines

### Options
LIBS	      := -L../utils/lib -lRootUtils -lGeneralUtils $(shell root-config --libs) $(AMSLIBso) 
INCLUDES      := -I. -Iselections/ -I$(AMSWD)/include -Iinclude/ -I../utils/include $(shell root-config --cflags) 
FLAGS         := -O3 -std=c++11 -D_PGTRACK_ -Wno-write-strings -fPIC


#$?  List of dependencies changed more recently than current target.
#$^  List of dependencies.
#$@  Name of current target.
#$<  Name of current dependency.
#$*  Name of current dependency without extension.


all :bin/dst bin/to_root

gitversion.hpp: ../.git/HEAD ../.git/index
	echo "const char *gitversion = \"$(shell git rev-parse HEAD)\";" > $@

selections/selections.a:
	make --directory=selections

utils:
	make --directory=../utils

bin/dst: dst.o selections/selections.a utils
	$(CXX)  $(FLAGS) $(INCLUDES) -o $@  dst.o $(LIBS) selections/selections.a -lDstAmsBinary

bin/to_root: to_root.cpp 
	$(CXX) $(FLAGS) $(INCLUDES) -o $@ $(LIBS)$^

dst.o: dst.cpp dst.hpp gitversion.hpp
	$(CXX) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(OBJECTS) bin/dst
	rm -f selections/selections.a
	rm -f gitversion.hpp
	rm -f ../utils/lib/libGeneralUtils.so
