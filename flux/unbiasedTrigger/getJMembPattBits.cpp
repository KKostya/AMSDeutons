#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <bitset>

using namespace std;

int main( int argc, char** argv){
    ifstream f("treeAll.log");
    std::string line;
    std::getline(f,line);
    int PhysBPatt, JMembPatt;
    std::map<int, std::map<int,int>* > m;
    int i = 0;
    int max = 0;
    while(!f.eof() && i++ < 1000000){
        f >> JMembPatt >> PhysBPatt;
        if( max < PhysBPatt ) max = PhysBPatt;
        
        
        for(int j = 0;j<=16;j+=2){
            if( (bitset<16>(PhysBPatt) == bitset<16>(j))  ){
                if( m[j] == NULL){
                    m[j] = new std::map<int,int>;
                }
                (*(m[j]))[JMembPatt]++;
            }
	}
    }

    for(std::map<int, std::map<int,int>*>::iterator it = m.begin();it!=m.end();it++){
        std::cout << "Map for PhysBPatt : " << it -> first << std::endl;
        std::bitset<16> b = ~0;
        for(std::map<int,int>::iterator it2 = it->second->begin();it2!=it->second->end();it2++){
            std::cout << "n[" << std::bitset<16>(it2->first) << "] = " << it2 -> second << std::endl;
            b&= ~std::bitset<16>(it2->first);
        }
        std::cout << "b : " << b << std::endl;
        std::cout << std::endl;
    }

    std::cout << "max : " << max << std::endl;
}
