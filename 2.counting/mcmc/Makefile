INCLUDE=-I./utils -I../../utils/include -I.
LIBS=`root-config --cflags --libs | sed 's/-lPhysics//g' | sed 's/-lGraf3d//g' | sed 's/-lPostscript//g' ` -lMathMore -L../../utils/lib
#LIBS=`root-config --cflags --libs`
OPTIMIZATION=-O3
CXXFLAGS=-Wall -pedantic -Wno-sign-compare -Wno-unused-variable -Wno-unused-parameter\
    -pedantic-errors -Wextra -Wcast-align \
    -Wcast-qual  -Wchar-subscripts  -Wcomment \
    -Wdisabled-optimization \
    -Werror -Wfloat-equal  -Wformat  -Wformat=2 \
    -Wformat-nonliteral -Wformat-security  \
    -Wformat-y2k \
    -Wimport  -Winit-self  -Winline \
    -Winvalid-pch   \
    # -Wunsafe-loop-optimizations
-Wlong-long -Wmissing-braces \
    -Wmissing-field-initializers -Wmissing-format-attribute   \
    -Wmissing-include-dirs -Wmissing-noreturn \
    -Wparentheses  -Wpointer-arith \
    -Wredundant-decls -Wreturn-type \
    -Wsequence-point  -Wshadow -Wstack-protector \
    -Wstrict-aliasing -Wstrict-aliasing=2 -Wswitch  -Wswitch-default \
    -Wswitch-enum -Wtrigraphs  -Wuninitialized \
    -Wunknown-pragmas  -Wunreachable-code -Wunused \
    -Wunused-function  -Wunused-label  -Wunused-parameter \
    -Wunused-value  -Wunused-variable  -Wvariadic-macros \
    -Wvolatile-register-var  -Wwrite-strings

all: mcmc

mcmc:	mcmc.cpp libpd_model.so generalUtils.o
	$(CXX) ${OPTIMIZATION} $(CXXFLAGS) ${INCLUDE} $(LIBS) $^ -o mcmc -std=c++11

reader:	reader.cpp
	$(CXX) ${OPTIMIZATION} -std=c++11  -L${amsUtils}/lib ${INCLUDE} reader.cpp -o reader  ${LIBS} -lRootUtils  -lStack -lGeneralUtils

generalUtils.o: utils/generalUtils.cpp utils/generalUtils.hpp 
	$(CXX) ${OPTIMIZATION} ${INCLUDE} -c $< -std=c++11 

libpd_model.so: pd_model.o
	$(CXX) -shared $< -o $@ 

pd_model.o: pd_model.cpp  pd_model.hpp
	$(CXX) ${OPTIMIZATION} $(CXXFLAGS) ${INCLUDE} -c -fPIC $< -std=c++11 

test_matrix: tests/test_matrix.cpp utils/Matrix.hpp  generalUtils.o
	$(CXX) ${INCLUDE} $(CXXFLAGS) -o $@ $< -std=c++11 

test_model: tests/test_model.cpp pd_model.o generalUtils.o
	$(CXX) ${INCLUDE} $(CXXFLAGS) -o $@ $^ -std=c++11

gui: gui.cpp gui.hpp libpd_model.so
	rootcint -f guiLinkDef.cpp -c ${INCLUDE} gui.hpp guiLinkDef.hpp
	$(CXX) ${INCLUDE} `root-config --cflags --glibs` -lMathMore gui.cpp guiLinkDef.cpp -o gui `root-config --glibs` -L../../utils/lib -lGeneralUtils -L. -lpd_model -lStack

sigma: sigma.cpp sigma.hpp pd_model.o generalUtils.o gui.hpp
	$(CXX) ${INCLUDE} sigma.cpp -o sigma pd_model.o generalUtils.o  -lGraphFromHistos -lStack $(LIBS)

mask:
	$(CXX) -o makeMask makeMask.cpp -L../../utils/lib -I../../utils/include -lGeneralUtils -std=c++11

clean:
	rm -f mcmc reader test_model test_matrix *.o guiLinkDef.cpp guiLinkDef_rdict.pcm

