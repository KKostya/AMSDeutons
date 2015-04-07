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
    
    int PhysBPatt;
    double R;
    selectionTree -> SetBranchAddress("PhysBPatt",  &PhysBPatt );
    selectionTree -> SetBranchAddress("R",  &R );

    int nBins = binning.size();
    std::vector<int> nUnbiased(nBins,0);
    std::vector<int> nPhysics(nBins, 0);

    long int nEntries = selectionTree->GetEntries();
    for(int i = 0;i<nEntries;i++){
	selectionTree -> GetEntry(i);

        // testing workaround since rigidity is not in the selections tree yet;
        // R = 10 + i%100;

        

        int bin = binning.findBin(R);

        if( bin > -1){
            if( PhysBPatt == 0 ) nUnbiased[bin]++;
            else nPhysics[bin]++;
        }
        
    }

    for(int i = 0;i<binning.size();i++){
        if(nPhysics[i] + 100. * nUnbiased[i] > 0){
            double error = pow(100/pow(nPhysics[i] + 100 * nUnbiased[i],2),2) * (nPhysics[i] * pow(nUnbiased[i],2) + nUnbiased[i] * pow(nPhysics[i],2) + 2*nPhysics[i]*nUnbiased[i]*sqrt(nPhysics[i]*nUnbiased[i]));
            std::cout << rootUtils::redFontBegin << "Unbiased trigger efficiency for bin [" << binning[i]->inf << "," << binning[i]->sup << "] : " << nPhysics[i] / (double)(nPhysics[i] + 100. * nUnbiased[i]) * 100 << "+/- " << error * 100. << "%  -   Nunb : " << nUnbiased[i]  << "    nPhys : " << nPhysics[i] << rootUtils::redFontEnd << std::endl;
            //            std::cout << nUnbiased[i]*pow(nPhysics[i],2) << "\t"  <<  nPhysics[i] * pow(nUnbiased[i],2) << "\t" <<  200 * sqrt(nPhysics[i]* nUnbiased[i]) * nPhysics[i] * nUnbiased[i]
        }
    }
    
}

int main(){
    Binning dummyBinning;
    dummyBinning.createLogarithmicBinning(0.5,1.2,30);

    TTree* selectionTree = (TTree*)rootUtils::root::get("ntuple.root","selections");

    computeUnbiasedCutEfficiency(dummyBinning, selectionTree);

    return 1;
}
