#include "TreeReader.hpp"



int main(){
    std::vector< std::string > data;
    data.push_back("ntuple.root/data");

    TreeReader reader(data);
    reader.go();
}


