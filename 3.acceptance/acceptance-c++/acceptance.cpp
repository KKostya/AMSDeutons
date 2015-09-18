#ifndef _ACCEPTANCE__CPP_
#define _ACCEPTANCE__CPP_

#include "acceptance.hpp"

using namespace rootUtils;

// Search for line containing the given substring 
std::string extractFromDatacard(std::string datacards, std::string sub)
{
    vector<size_t> positions; // holds all the positions that sub occurs within str

    size_t pos = datacards.find(sub, 0);
    size_t pos2 = datacards.find('\n', pos+1);
    return datacards.substr( pos+sub.length(), pos2-(pos+sub.length()) );
}

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

    TObjString* d = (TObjString*)rootUtils::get(data[0],"DataCards");
    std::string datacards( d->GetString() );

    pMin = generalUtils::stringTo<float>( extractFromDatacard(datacards,"\nPMIN=") );
    pMax = generalUtils::stringTo<float>( extractFromDatacard(datacards,"\nPMAX=") );

    if( pMin <= 0 || pMin > 1e10){
        std::cerr << "Wrong value for pMin : " << pMin << std::endl;
    }

    if( pMax <= 0 || pMax > 1e10){
        std::cerr << "Wrong value for pMax : " << pMax << std::endl;
    }
}

// Laurent Derome's stuff
// the array IsTrkLayer[9] tells which tracker layer is crossed by the track
// void LxPart::SetTrackerLayersCrossedByTofTrack(AMSPoint pnt, AMSDir dir, float margin,bool EcalWindow0,bool* IsTrkLayer) {
//     for(int ilayer=0;ilayer<9;ilayer++){
//         AMSPoint pint = pnt+dir*(tracker_layers_z[ilayer]-pnt.z())/dir.z();
//         // rectangle & circle
//         IsTrkLayer[ilayer] = false;
//         if(ilayer==8 && EcalWindow0) {
//             if( (pint.x()>tracker_planes_edges[ilayer+1][0]+margin)&&
//                 (pint.x()<tracker_planes_edges[ilayer+1][2]-margin)&&
//                 (pint.y()>tracker_planes_edges[ilayer+1][1]+margin)&&
//                 (pint.y()<tracker_planes_edges[ilayer+1][3]-margin)
//                 ) IsTrkLayer[ilayer] = true;
//         } else {
//             if( (pint.x()>tracker_planes_edges[ilayer][0]+margin)&&
//                 (pint.x()<tracker_planes_edges[ilayer][2]-margin)&&
//                 (pint.y()>tracker_planes_edges[ilayer][1]+margin)&&
//                 (pint.y()<tracker_planes_edges[ilayer][3]-margin)&&
//                 (sqrt(pint.x()*pint.x()+pint.y()*pint.y())<tracker_planes_edges[ilayer][2]-margin)
//                 ){
//                 IsTrkLayer[ilayer] = true;
//             }
//         }
//     }
// }

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

    TofRecon::BuildTofTracks(ev);
    if( TofRecon::TofTracksList.size() == 0) return false;

    // Ask that extrapolation crosses Tracker layers L2 to L8 with a safety margin of 0
    int isInsideBit = TofRecon::TofTracksList[0] -> GetPatternInsideTracker(0);
    
    if( (isInsideBit&0b011111110) != 0b011111110 ) return false;

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
        float nGenPerBin = (log10(h["acc"]->GetBinLowEdge(i+1)) - log10(h["acc"]->GetBinLowEdge(i))) / (log10(pMax) - log10(pMin)) * (biggest-smallest);
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

