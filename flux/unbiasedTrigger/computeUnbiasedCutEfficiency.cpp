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

std::string firstTree;

void printEfficiencies(const Binning &binning, std::vector<int> nUnbiased, std::vector<int> nPhysics){
    for(int i = 0;i<binning.size();i++){
        if(nPhysics[i] + 100. * nUnbiased[i] > 0){
            double efficiency = nPhysics[i] / (double)(nPhysics[i] + 100. * nUnbiased[i]);
            double error = pow(100/pow(nPhysics[i] + 100 * nUnbiased[i],2),2) * (nPhysics[i] * pow(nUnbiased[i],2) + nUnbiased[i] * pow(nPhysics[i],2) + 2*nPhysics[i]*nUnbiased[i]*sqrt(nPhysics[i]*nUnbiased[i]));
            
            std::cout << rootUtils::redFontBegin << "Unbiased trigger efficiency for bin [" << binning[i]->inf << "," << binning[i]->sup << "] : " << efficiency * 100 << "+/- " << error * 100. << "%  -   Nunb : " << nUnbiased[i]  << "    nPhys : " << nPhysics[i] << rootUtils::redFontEnd << std::endl;
            //            std::cout << nUnbiased[i]*pow(nPhysics[i],2) << "\t"  <<  nPhysics[i] * pow(nUnbiased[i],2) << "\t" <<  200 * sqrt(nPhysics[i]* nUnbiased[i]) * nPhysics[i] * nUnbiased[i]
        }
    }
}

void computeUnbiasedCutEfficiency(const Binning &binning, TTree* selectionTree ){
    
    int PhysBPatt, physicsTrigger;
    double R;
    double Latitude;
    long long int selStatus, fStatus;
    selectionTree -> SetBranchAddress("PhysBPatt",  &PhysBPatt );
    selectionTree -> SetBranchAddress("R",  &R );
    selectionTree -> SetBranchAddress("Latitude",  &Latitude );
    selectionTree -> SetBranchAddress("selStatus",  &selStatus );
    selectionTree -> SetBranchAddress("fStatus",  &fStatus );

    int nBins = binning.size();
    std::vector<int> nUnbiased(nBins,0);
    std::vector<int> nPhysics(nBins, 0);

    Binning binningLatitude;
    binningLatitude.createUniformBinning(0,90,9);
    int nBinsLatitude = binningLatitude.size();
    
    std::vector<int> nUnbiasedLatitude(nBinsLatitude,0);
    std::vector<int> nPhysicsLatitude(nBinsLatitude, 0);

    long int nEntries = selectionTree->GetEntries();

    std::vector< std::string > masks;
    masks.push_back("notFirstTwo");
    masks.push_back("notInSaaCut");
    masks.push_back("zenithCut");
    masks.push_back("runtypeCut");
    masks.push_back("oneTrack");
    masks.push_back("aTRDTrack");
    masks.push_back("goldenTRACKER");
    masks.push_back("chargeOne");
    masks.push_back("downGoing");
    masks.push_back("betaNotCrazy");
    
    int preselMask = 0;
    for(int i = 0; i<masks.size(); i++){
        int theMask = rootUtils::selectionMask(firstTree, masks[i]);
        preselMask |= theMask;
    }
    
    int preselCuts = 0;

    for(int i = 0;i<nEntries;i++){
        if(i > 1000000 ) break;
        if( i%50000 == 0 ) std::cout << "entry : "  << i << std::endl;
	selectionTree -> GetEntry(i);

        std::bitset<20> x(selStatus);
        if( (selStatus&preselMask) != preselMask  || ((fStatus >> 8) & 0b11) != 1) {
            //if( (selStatus&preselMask) != preselMask) {
            preselCuts++;
            continue;
        }
        
        int bin = binning.findBin(R);
        physicsTrigger = (PhysBPatt >> 1)&0b11111;


        if( bin > -1){
            if( PhysBPatt == 0 ) nUnbiased[bin]++;
            else{
                if( physicsTrigger != 0 ) {
                    nPhysics[bin]++;
                }else{
                    std::cout << "not physics :" << PhysBPatt << std::endl;
                }
            }
        }

        if( R > 0.5 ){
            int binLatitude = binningLatitude.findBin(Latitude*180/TMath::Pi());

            if( binLatitude > -1){
                if( PhysBPatt == 0 ) nUnbiasedLatitude[binLatitude]++;
                else{
                    if( physicsTrigger != 0 ) nPhysicsLatitude[binLatitude]++;
                }
            }
        }
    }

    printEfficiencies(binning, nUnbiased, nPhysics);

    std::cout << "\n\nLatitude dependance : "  << std::endl;
    printEfficiencies(binningLatitude, nUnbiasedLatitude, nPhysicsLatitude);

    std::cout << "preselCuts : " << preselCuts << std::endl;
}

int main(){
    Binning dummyBinning;
    dummyBinning.createLogarithmicBinning(0.5,1.2,30);

    //    TTree* selectionTree = (TTree*)rootUtils::root::get("ntuple.root","selections");

    TChain* chain = new TChain();
    std::vector< std::string > files = rootUtils::getFilesInDirWithPattern("/afs/cern.ch/user/b/bcoste/eos/ams/user/k/kostams/DeuteronNtuples/production","ntuple.root");
    firstTree = files[0];

    for(int i = 0;i<files.size();i++){
        chain -> Add( (files[i] + "/selections").c_str() );
    }

    std::cout << "chain -> GetEntries() : " << chain -> GetEntries() << std::endl;
    
    computeUnbiasedCutEfficiency(dummyBinning, chain);

    return 1;
}
