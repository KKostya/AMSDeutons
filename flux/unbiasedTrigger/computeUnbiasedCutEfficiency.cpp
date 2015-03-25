#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TKey.h"
#include "TROOT.h"
#include "TChain.h"
#include "TF1.h"

#include <bitset>

#include "../../utils/rootUtils.hpp"
#include "../../utils/Binning.hpp"

void computeUnbiasedCutEfficiency(const Binning &binning, TTree* selectionTree ){
    
    TObjString* selectionBitsObjStr = (TObjString*) gFile -> Get("infos/selectionBits");

    std::string selectionBits( selectionBitsObjStr -> GetString() );
    std::vector< std::string > selectionBitsVec = rootUtils::split( selectionBits, ",");

    int lastMinimumBiasCut = -1;
    
    for(int i = 0;i<selectionBitsVec.size();i++){
        std::cout << "selectionBitsVec[i] : " << selectionBitsVec[i] << std::endl;
        
        if( selectionBitsVec[i].find("minimumbias") != std::string::npos ){
            lastMinimumBiasCut = i;
        }
    }
    std::cout << "lastMinimumBiasCut : " << lastMinimumBiasCut << std::endl;
    
    unsigned long long selStatus;
    int isUnbiased;
    float R;
    selectionTree -> SetBranchAddress("selStatus",  &selStatus );
    selectionTree -> SetBranchAddress("Unbias",  &isUnbiased );
    selectionTree -> SetBranchAddress("R",  &R );

    int nBins = binning.size();
    std::vector<int> passUnbias(nBins,0);
    std::vector<int> totalUnbiased(nBins, 0);

    long int nEntries = selectionTree->GetEntries();
    for(int i = 0;i<nEntries;i++){
	selectionTree -> GetEntry(i);

        // testing workaround since rigidity is not in the selections tree yet;
        R = 10 + i%100;

        if( isUnbiased == false ) continue;

        int mask = 1;
        for(int i = 0; i<lastMinimumBiasCut+1; i++) mask *= 2;
        mask -= 1;

        int maskedSelStatus = selStatus & mask;
        int thebit = maskedSelStatus >> lastMinimumBiasCut;

        int bin = binning.findBin(R);

        if( bin > -1){
            if( thebit ) passUnbias[bin]++;
            totalUnbiased[bin]++;
        }
        
    }

    for(int i = 0;i<binning.size();i++){
        if(totalUnbiased[i] > 0){
            std::cout << rootUtils::redFontBegin << "Unbiased trigger efficiency for bin [" << binning[i]->inf << "," << binning[i]->sup << "] : " << passUnbias[i] << "/" << totalUnbiased[i] << " = " << 100 * passUnbias[i]/(double)totalUnbiased[i] << " %" << rootUtils::redFontEnd << std::endl;
        }
    }
    
}

int main(){
    Binning dummyBinning;
    dummyBinning.createLogarithmicBinning(0.5,1.2,30);

    TTree* selectionTree = (TTree*)rootUtils::root::get("1386007353.00000001.ntuple.root","selections");

    computeUnbiasedCutEfficiency(dummyBinning, selectionTree);

    return 1;
}
