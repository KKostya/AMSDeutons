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
#include <tuple>

#include "../../utils/rootUtils.hpp"
#include "../../utils/Binning.hpp"

std::string firstTree;

typedef std::tuple<bool, float, float, float > Tuple;

template<int N> void printEfficienciesTuple(const std::vector< Tuple > &tree, const Binning &binning){
    int bin;
    float val;
    int nBins = binning.size();
    std::vector<int> nUnbiased(nBins,0);
    std::vector<int> nPhysics(nBins, 0);
    
    for(int i = 0;i<tree.size();i++){
        val = std::get<N>(tree[i]);
        bin = binning.findBin(val);
        if( bin > -1 ){
            if( std::get<0>(tree[i]) == 0 ) nUnbiased[bin]++;
            else nPhysics[bin]++;
        }
    }

    for(int i = 0;i<binning.size();i++){
        if(nPhysics[i] + 100. * nUnbiased[i] > 0){
            double efficiency = nPhysics[i] / (double)(nPhysics[i] + 100. * nUnbiased[i]);
            double error = pow(100/pow(nPhysics[i] + 100 * nUnbiased[i],2),2) * (nPhysics[i] * pow(nUnbiased[i],2) + nUnbiased[i] * pow(nPhysics[i],2) + 2*nPhysics[i]*nUnbiased[i]*sqrt(nPhysics[i]*nUnbiased[i]));
            
            std::cout << rootUtils::redFontBegin << "Unbiased trigger efficiency for bin [" << binning[i]->inf << "," << binning[i]->sup << "] : " << efficiency * 100 << "+/- " << error * 100. << "%  -   Nunb : " << nUnbiased[i]  << "    nPhys : " << nPhysics[i] << rootUtils::redFontEnd << std::endl;
        }
    }
    std::cout << std::endl;

}

void computeUnbiasedCutEfficiency(const std::vector<Binning> &binning, TTree* selectionTree ){
    
    int PhysBPatt, physicsTrigger;
    double Rfull;
    double Latitude;
    double BetaTOF;
    unsigned int UTime;
    unsigned long long int selStatus, fStatus;
    selectionTree -> SetBranchAddress("PhysBPatt",  &PhysBPatt );
    selectionTree -> SetBranchAddress("Rfull",  &Rfull );
    selectionTree -> SetBranchAddress("UTime",  &UTime );
    selectionTree -> SetBranchAddress("Latitude",  &Latitude );
    selectionTree -> SetBranchAddress("selStatus",  &selStatus );
    selectionTree -> SetBranchAddress("fStatus",  &fStatus );
    selectionTree -> SetBranchAddress("BetaTOF",  &BetaTOF );


    long int nEntries = selectionTree->GetEntries();

    std::vector< std::string > masks;
    masks.push_back("notFirstTwo");
    masks.push_back("notInSaaCut");
    masks.push_back("zenithCut");
    masks.push_back("runtypeCut");
    masks.push_back("oneTRDTrack");
    masks.push_back("goldenTRACKER");
    masks.push_back("oneTrack");
    masks.push_back("chargeOne");
    masks.push_back("downGoing");
    masks.push_back("betaNotCrazy");
    
    int preselMask = 0;
    for(int i = 0; i<masks.size(); i++){
        int theMask = rootUtils::selectionMask(firstTree, masks[i]);
        preselMask |= theMask;
    }

    std::bitset<30> theMaskBitset(preselMask);
    std::cout << "theMask : " << theMaskBitset << std::endl;
    
    int preselCuts = 0;
    std::vector< Tuple > tree;
    float mass;
    
    for(int i = 0;i<nEntries;i++){
        //        if(i > 10000000 ) break;
        if( i%50000 == 0 ) std::cout << "entry : "  << i << std::endl;
	selectionTree -> GetEntry(i);

        mass = Rfull * sqrt(1 - pow(BetaTOF,2)) / BetaTOF;
            
        if( (selStatus&preselMask) != preselMask || Rfull <= 0 || mass < 0.8 || mass > 1.3 ) {
            preselCuts++;
            continue;
        }

        physicsTrigger = (PhysBPatt >> 1)&0b11111;

        if( PhysBPatt == 0 || physicsTrigger ){
            tree.push_back( Tuple((PhysBPatt!=0), Rfull, Latitude*180./TMath::Pi(), UTime) );
        }
    }

    printEfficienciesTuple<1>(tree, binning[0]);
    printEfficienciesTuple<2>(tree, binning[1]);
    //    printEfficienciesTuple<3>(tree, binning[2]);
}

int main(){

    std::vector<Binning> binning;
    
    Binning binningRigidity;
    binningRigidity.createLogarithmicBinning(0.5,1.2,30);
    binning.push_back(binningRigidity);
    
    Binning binningLatitude;
    binningLatitude.createUniformBinning(0,90,9);
    binning.push_back(binningLatitude);

    //    TTree* selectionTree = (TTree*)rootUtils::root::get("ntuple.root","selections");

    TChain* chain = new TChain();
    std::vector< std::string > files = rootUtils::getFilesInDirWithPattern("/afs/cern.ch/user/b/bcoste/eos/ams/user/k/kostams/DeuteronNtuples/production","ntuple.root");
    firstTree = files[0];

    for(int i = 0;i<files.size();i++){
        //for(int i = 0;i<1;i++){
        chain -> Add( (files[i] + "/selections").c_str() );
    }

    std::cout << "chain -> GetEntries() : " << chain -> GetEntries() << std::endl;
    
    computeUnbiasedCutEfficiency(binning, chain);

    return 1;
}
