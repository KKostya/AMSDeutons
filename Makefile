all: TIsotopesMCMC.so tensor_test root_test model_test grad_test

RCC=$(shell root-config --cxx --cflags) 

TIsotopesMCMC.so: TIsotopesMCMC.cpp TIsotopesMCMC.hpp RootUtils.hpp Model.hpp LinkDef.h GradOptimizer.hpp
	$(RCC) --std=c++11 -fPIC -c -I. TIsotopesMCMC.cpp
	rootcint -f TIsotopesMCMC_Dict.cpp -c -p TIsotopesMCMC.hpp LinkDef.h
	$(RCC) -fPIC -c TIsotopesMCMC_Dict.cpp
	$(RCC) -fPIC -shared -o TIsotopesMCMC.so TIsotopesMCMC.o TIsotopesMCMC_Dict.o


tensor_test: tensor_test.cpp 
	g++ -I. --std=c++11 tensor_test.cpp -o tensor_test

root_test: root_test.cpp RootUtils.hpp 
	g++ root_test.cpp --std=c++11 $(shell root-config --cflags --libs) -I.  -o root_test

model_test: model_test.cpp Model.hpp
	g++ -I. --std=c++11 model_test.cpp -o model_test

grad_test: grad_test.cpp GradOptimizer.hpp Model.hpp
	g++ -I. --std=c++11 grad_test.cpp -o grad_test

