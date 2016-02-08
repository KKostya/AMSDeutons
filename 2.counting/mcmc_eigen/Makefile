all: tensor_test root_test model_test

tensor_test: tensor_test.cpp 
	g++ -I. --std=c++11 tensor_test.cpp -o tensor_test

root_test: root_test.cpp RootUtils.hpp 
	g++ root_test.cpp --std=c++11 $(shell root-config --cflags --libs) -I.  -o root_test

model_test: model_test.cpp Model.hpp
	g++ -I. --std=c++11 model_test.cpp -o model_test

