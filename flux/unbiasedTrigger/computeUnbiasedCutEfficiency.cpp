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


enum TriggerState {
    kPhysics,
    kUnbiasedOnlyTofFlag,
    kUnbiasedOnlyEcalFlag,
    kUnbiasedTofAndEcalFlags,
    kNotSupposedToHappen
};

typedef std::tuple<TriggerState, float, float, float > Tuple;


template<int N> void printEfficienciesTuple(const std::vector< Tuple > &tree, const Binning &binning){
    int bin;
    float val;
    int nBins = binning.size();
    std::vector<int> nUnbiasedTofNoEcal(nBins,0); // All unbiased events with a FTC1 flag (JMembPatt == 4) but no Ecal flag (JMembPatt != 11 )
    std::vector<int> nUnbiasedEcal(nBins,0); // All unbiased events with an EcalF flag (JMembPatt == 11) 
    std::vector<int> nPhysics(nBins, 0);

    for(int i = 0;i<tree.size();i++){
        val = std::get<N>(tree[i]);
        bin = binning.findBin(val);
        if( bin > -1 ){
            TriggerState triggerState = std::get<0>(tree[i]);
            
            switch( triggerState ){
            case kPhysics:
                nPhysics[bin]++;
                break;

            case kUnbiasedTofAndEcalFlags:
                nUnbiasedEcal[bin]++;
                break;

            case kUnbiasedOnlyEcalFlag:
                nUnbiasedEcal[bin]++;
                break;

            case kUnbiasedOnlyTofFlag:
                nUnbiasedTofNoEcal[bin]++;
                break;

            default:
                std::cout << "Not supposed to happen" << std::endl;
                break;
            }
        }
    }

    TFile* file = new TFile(Form("unbiasedCutEfficiency_%i.root",N),"recreate");
    TGraphErrors gr;
    
    for(int i = 0;i<binning.size();i++){
        double error = 0;
        double efficiency = 0;
        double Ntot = nPhysics[i] + 100. * nUnbiasedTofNoEcal[i] + 1000. * nUnbiasedEcal[i];
        if(Ntot > 0){
            efficiency = nPhysics[i] / (double)(nPhysics[i] + 100. * nUnbiasedTofNoEcal[i] + 1000. * nUnbiasedEcal[i]);
            // error = pow(100/pow(nPhysics[i] + 100 * nUnbiased[i],2),2) * (nPhysics[i] * pow(nUnbiased[i],2) + nUnbiased[i] * pow(nPhysics[i],2) + 2*nPhysics[i]*nUnbiased[i]*sqrt(nPhysics[i]*nUnbiased[i]));
            error = sqrt( pow(100/Ntot,2) * nUnbiasedTofNoEcal[i] + pow(1000/Ntot,2) * nUnbiasedEcal[i]) ;
         }
        
        std::cout << rootUtils::redFontBegin << "Unbiased trigger efficiency for bin [" << binning[i]->inf << "," << binning[i]->sup << "] : " << efficiency * 100 << "+/- " << error * 100. << "%  -   Nunb : " <<  nUnbiasedEcal[i] + nUnbiasedTofNoEcal[i] << "    nPhys : " << nPhysics[i] << rootUtils::redFontEnd << std::endl;
        gr.SetPoint(i, binning[i]->center, efficiency );
        gr.SetPointError(i,binning[i]->center - binning[i]->inf, error);
    }

    gr.Write("gr");
    
    std::cout << std::endl;

}

void computeUnbiasedCutEfficiency(const std::vector<Binning> &binning, TTree* selectionTree ){
    
    int PhysBPatt, JMembPatt;

    double Rfull;
    double Latitude;
    double BetaTOF;
    unsigned int UTime;
    unsigned long long int selStatus, fStatus;
    selectionTree -> SetBranchAddress("JMembPatt",  &JMembPatt );
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
    int p = 0;
    //    for(int i = 100000000;i<nEntries;i++){
    for(int i = 0;i<nEntries;i++){
        //        if(p++ > 14000000 ) break;
        if( i%50000 == 0 ) std::cout << "entry : "  << i << std::endl;
	selectionTree -> GetEntry(i);

        mass = Rfull * sqrt(1 - pow(BetaTOF,2)) / BetaTOF;

        //        std::cout << "(selStatus^preselMask) : " << std::bitset<64>(selStatus^preselMask) << std::endl;
        if( (selStatus&preselMask) != preselMask || Rfull <= 0 || mass < 0.8 || mass > 1.3 ) {
            preselCuts++;
            continue;
        }

        std::bitset<16> JMembPattBit(JMembPatt);
        bool isEcalF = JMembPattBit.test(11);
        bool isTof = JMembPattBit.test(4);

        TriggerState theTriggerState;
        if( ((PhysBPatt >> 1)&0b11111) != 0 ) theTriggerState = kPhysics;
        else if( isTof && !isEcalF ) theTriggerState = kUnbiasedOnlyTofFlag;
        else if( !isTof && isEcalF ) theTriggerState = kUnbiasedOnlyEcalFlag;
        else if( isTof && isEcalF ) theTriggerState = kUnbiasedTofAndEcalFlags;
        else theTriggerState = kNotSupposedToHappen;

        tree.push_back( Tuple(theTriggerState, Rfull, Latitude*180./TMath::Pi(), UTime) );
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
    // std::vector< std::string > files;
    // files.push_back("ntuple.root");
    firstTree = files[0];

    for(int i = 0;i<files.size();i++){
        //for(int i = 0;i<1;i++){
        chain -> Add( (files[i] + "/selections").c_str() );
    }

    std::cout << "chain -> GetEntries() : " << chain -> GetEntries() << std::endl;
    
    computeUnbiasedCutEfficiency(binning, chain);

    return 1;
}
