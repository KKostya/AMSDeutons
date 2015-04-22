// macro
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TKey.h"
#include "TROOT.h"
#include "TChain.h"
#include "TF1.h"

#include "../../utils/rootUtils.hpp"

void triggerBits(){
    TChain* chain = new TChain();
    std::vector< std::string > files = rootUtils::getFilesInDirWithPattern("/afs/cern.ch/user/b/bcoste/eos/ams/user/k/kostams/DeuteronNtuples/production","ntuple.root");

    //    for(int i = 0;i<files.size();i++){
    for(int i = 0;i<1;i++){
        chain -> Add( (files[i] + "/selections").c_str() );
    }

    std::cout << "chain -> GetEntries() : " << chain -> GetEntries() << std::endl;

    
    int PhysBPatt;
    chain -> SetBranchAddress("PhysBPatt",  &PhysBPatt );
    long int nEntries = chain -> GetEntries();

    for(int i = 0;i<nEntries;i++){
        if(i > 100000 ) break;
        if( i%50000 == 0 ) std::cout << "entry : "  << i << std::endl;
	chain -> GetEntry(i);
        std::cout << "PhysBPatt : " << PhysBPatt << std::endl;
    }
    
}
