all: TIsotopesMCMC.so 

test: tests/tensor_test tests/root_test tests/model_test tests/grad_test

RCC=$(shell root-config --cxx --cflags) 

TIsotopesMCMC.so: TIsotopesMCMC.cpp TIsotopesMCMC.hpp RootUtils.hpp Model.hpp LinkDef.h GradOptimizer.hpp
	$(RCC) --std=c++11 -fPIC -c -I. TIsotopesMCMC.cpp
	rootcint -f TIsotopesMCMC_Dict.cpp -c -p TIsotopesMCMC.hpp LinkDef.h
	$(RCC) -fPIC -c TIsotopesMCMC_Dict.cpp
	$(RCC) -fPIC -shared -o TIsotopesMCMC.so TIsotopesMCMC.o TIsotopesMCMC_Dict.o


tests/tensor_test: tests/tensor_test.cpp 
	g++ -I. --std=c++11 $< -o $@

tests/root_test: tests/root_test.cpp RootUtils.hpp 
	g++ $< --std=c++11 $(shell root-config --cflags --libs) -I.  -o $@

tests/model_test: tests/model_test.cpp Model.hpp
	g++ -I. --std=c++11 $< -o $@

tests/grad_test: tests/grad_test.cpp GradOptimizer.hpp Model.hpp
	g++ -I. --std=c++11 $< -o $@

