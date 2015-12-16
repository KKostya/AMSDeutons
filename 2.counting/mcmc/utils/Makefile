INCLUDE=-I./utils -I$(amsUtils)/include -I.
LIBS=`root-config --cflags --libs | sed 's/-lPhysics//g' | sed 's/-lGraf3d//g' | sed 's/-lPostscript//g' `  -L$(amsUtils)/lib
#LIBS=`root-config --cflags --libs`
OPTIMIZATION=-g
CXXFLAGS=-Wall -Weffc++ -pedantic -Wno-sign-compare -Wno-unused-variable -Wno-unused-parameter\
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

all: mcmc test_model test_matrix

mcmc:	mcmc.cpp pd_model.o generalUtils.o
	$(CXX) ${OPTIMIZATION} $(CXXFLAGS) ${INCLUDE} $(LIBS) $^ -o mcmc -std=c++11

reader:	reader.cpp
	$(CXX) ${OPTIMIZATION} -std=c++11  -L${amsUtils}/lib ${INCLUDE} reader.cpp -o reader  ${LIBS} -lRootUtils  -lStack -lGeneralUtils

generalUtils.o: utils/generalUtils.cpp utils/generalUtils.hpp 
	$(CXX) ${OPTIMIZATION} ${INCLUDE} -c $< -std=c++11 

pd_model.o: pd_model.cpp  pd_model.hpp
	$(CXX) ${OPTIMIZATION} $(CXXFLAGS) ${INCLUDE} -c $< -std=c++11 

test_matrix: tests/test_matrix.cpp utils/Matrix.hpp  generalUtils.o
	$(CXX) ${INCLUDE} $(CXXFLAGS) -o $@ $< -std=c++11 

test_model: tests/test_model.cpp pd_model.o generalUtils.o
	$(CXX) ${INCLUDE} $(CXXFLAGS) -o $@ $^ -std=c++11 

clean:
	rm -f mcmc reader test_model test_matrix *.o

