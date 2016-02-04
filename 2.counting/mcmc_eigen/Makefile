all: tensor_test root_test

tensor_test: tensor_test.cpp Utils.hpp
	g++ -I. --std=c++11 tensor_test.cpp -o tensor_test

root_test: root_test.cpp RootUtils.hpp Utils.hpp
	g++ root_test.cpp --std=c++11 $(shell root-config --cflags --libs) -I.  -o root_test

