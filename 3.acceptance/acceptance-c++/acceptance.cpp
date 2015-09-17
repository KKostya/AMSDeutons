#ifndef _ACCEPTANCE__CPP_
#define _ACCEPTANCE__CPP_

#include "acceptance.hpp"

using namespace rootUtils;

void Acceptance::init(){
    maxRootFiles = 2;
    maxEntries = 10000000;
    //maxEntries = 100;

    setOutputFileName( "ana_" + generalUtils::getFileName(data[0]) );

    Loop::init();
    TH1::SetDefaultSumw2();
    
    h["raw"] = new TH1F("hraw","hraw",100,1,101);
    
    biggest = 0;
    smallest = INT_MAX;

}



bool Acceptance::process(){
    
    int num =  ev -> Event();
    if( num > biggest ) biggest = num;
    if( num < smallest ) smallest = num;
    
    if (ev==NULL) return false;
    int nBetaH = ev->nBetaH();
    if (nBetaH == 0) return false;
    BetaHR* betaH = ev->pBetaH(0);
    if ( !betaH ) return false;
    if ( betaH -> NTofClusterH() < 3) return false;
    if ( betaH -> GetBeta() <= 0 ) return false;

    h["raw"] -> Fill( ev -> GetPrimaryMC() -> Momentum);
}

void Acceptance::write(){
    (TParameter<int>("nGen",biggest - smallest)).Write();
}

void Acceptance::draw(){
    h["acc"] = (TH1F*)h["raw"]->Clone("hacc");
    h["acc"] -> SetTitle("hacc");
    
    std::cout << "smallest : " << smallest << std::endl;
    std::cout << "biggest : " << biggest << std::endl;

    for(int i = 1; i <= h["acc"]->GetNbinsX();i++){
        float nGenPerBin = (log10(h["acc"]->GetBinLowEdge(i+1)) - log10(h["acc"]->GetBinLowEdge(i))) / (log10(200) - log10(1)) * (biggest-smallest);
        float content = h["acc"] -> GetBinContent(i);
        float error = h["acc"] -> GetBinError(i);
        h["acc"] -> SetBinError(i, error / nGenPerBin  * pow(3.9,2) * TMath::Pi() );
        h["acc"] -> SetBinContent(i, content / nGenPerBin  * pow(3.9,2) * TMath::Pi() );
    }
}

int Acceptance::cutEvent(){

    return 0;
}

int main(int argc, char **argv){
    std::vector< std::string > data;

    if(argc < 2){
        data.push_back("/afs/cern.ch/work/b/bcoste/protonB800.root");
    }else{
        data.push_back( argv[1] );
    }
    
    Acceptance t( data );
    t.go();

    return 0;
}

#endif

