#ifndef _DST__CPP_
#define _DST__CPP_

#include "dst.hpp"

using namespace rootUtils;

//#define ADD_VARIABLE(name, lambda) fill[name] =  [this](){ var[name][chunkStepNumber] = lambda }

// #define ADD_VARIABLE(name, lambda) fill[  [this](){ var[name][chunkStepNumber] = lambda }


void Dst::registerSelStatus(){
    selections.push_back( std::make_pair("notFirstTwo", notFirstTwo) );
    selections.push_back( std::make_pair("notInSaaCut", notInSaaCut) );
    selections.push_back( std::make_pair("zenithCut", zenithCut) );
    selections.push_back( std::make_pair("runtypeCut", runtypeCut) );
    selections.push_back( std::make_pair("minimumbiasTOF", minimumbiasTOF) );
    selections.push_back( std::make_pair("minimumbiasTRIGG", minimumbiasTRIGG) );
    selections.push_back( std::make_pair("minimumbiasTRD", minimumbiasTRD) );
    selections.push_back( std::make_pair("minimumbiasTRACKER", minimumbiasTRACKER) );
    selections.push_back( std::make_pair("goldenTOF", goldenTOF<0,3>) );
    selections.push_back( std::make_pair("goldenTRD", goldenTRD<0,3>) );
    selections.push_back( std::make_pair("goldenTRACKER", goldenTRACKER<0,3>) );
    selections.push_back( std::make_pair("aParticle", aParticle) );
    selections.push_back( std::make_pair("aTrack", aTrack) );
    selections.push_back( std::make_pair("aTRDTrack", aTRDTrack) );
    selections.push_back( std::make_pair("oneParticle", oneParticle) );
    selections.push_back( std::make_pair("oneTrack", oneTrack) );
    selections.push_back( std::make_pair("oneTRDTrack", oneTRDTrack) );
    selections.push_back( std::make_pair("chargeOne", chargeOne) );
    selections.push_back( std::make_pair("downGoing", downGoing) );
    selections.push_back( std::make_pair("betaNotCrazy", betaNotCrazy) );
    selections.push_back( std::make_pair("physicsTrigger", physicsTrigger) );
    selections.push_back( std::make_pair("basicBetaH", basicBetaH) );
    selections.push_back( std::make_pair("isolatedBetaH", isolatedBetaH) );
    selections.push_back( std::make_pair("tofTrackInsideInnerTracker", tofTrackInsideInnerTracker) );
    selections.push_back( std::make_pair("tofTrackInsideFullSpan", tofTrackInsideFullSpan) );
    selections.push_back( std::make_pair("aRing", aRing) );
    selections.push_back( std::make_pair("oneRing", oneRing) );
    selections.push_back( std::make_pair("noNaF", noNaF) );
    selections.push_back( std::make_pair("photFracG04", photFracG04) );
    selections.push_back( std::make_pair("photFracL2", photFracL2) );
    selections.push_back( std::make_pair("betaDisp", betaDisp) );
    selections.push_back( std::make_pair("counts5", counts5) );
    selections.push_back( std::make_pair("aRing", aRing) );
    selections.push_back( std::make_pair("oneRing", oneRing) );
    selections.push_back( std::make_pair("noNaF", noNaF) );
    selections.push_back( std::make_pair("ringGood",  ringGood) );
    selections.push_back( std::make_pair("ringClean", ringClean) );
    selections.push_back( std::make_pair("ringProb",  ringProb) );
    selections.push_back( std::make_pair("ringPMTs",  ringPMTs) );
    selections.push_back( std::make_pair("ringChargeConsistency", ringChargeConsistency) );
    selections.push_back( std::make_pair("ringPhotoElectrons",    ringPhotoElectrons) );
    selections.push_back( std::make_pair("ringExpPhe", ringExpPhe) );
    selections.push_back( std::make_pair("ringBetaCons", ringBetaCons) );
    selections.push_back( std::make_pair("ringNoNaFBorder", ringNoNaFBorder) );
}

void Dst::registerVariables() {

    registerSelStatus();

    // HEADER
    variables.push_back(new Container<unsigned int>("Run", [this](){return ev ? ev -> Run()                     : -1;}));
    variables.push_back(new Container<unsigned int>("Event", [this](){return ev ? ev -> Event()                   : -1;}));
    variables.push_back(new Container<unsigned int>("UTime", [this](){return ev ? ev -> UTime()                   : -1;}));
    variables.push_back(new Container<double>("ThetaS", [this](){return ev ? ev -> fHeader.ThetaS             : 0;}));
    variables.push_back(new Container<double>("PhiS", [this](){return ev ? ev -> fHeader.PhiS               : 0;}));
    variables.push_back(new Container<double>("Livetime", [this](){return ev ? ev -> LiveTime()                 : 0;}));
    variables.push_back(new Container<double>("Latitude", [this](){return ev ? ev -> fHeader.ThetaM             : 0;}));
    variables.push_back(new Container<unsigned long long>("fStatus", [this](){return ev ? ev -> fStatus                    : 0;}));
    variables.push_back(new Container<double>("Rcutoff", [this](){return part ? part -> Cutoff                   : -1;}));
                                                     
        // Triggers                                      
    variables.push_back(new Container<int>("PhysBPatt", [this](){return level ? level -> PhysBPatt               : -1;}));
    variables.push_back(new Container<int>("JMembPatt", [this](){return level ? level -> JMembPatt               : -1;}));
                                                                                                
        // TOF                                                                                      
    variables.push_back(new Container<double>("BetaTOF", [this](){return beta  ? beta  -> Beta                : -1;}));
    variables.push_back(new Container<double>("BetaTOFH", [this](){return betaH  ? betaH -> GetBeta()           : -1;}));
    variables.push_back(new Container<int>("NTofClustersH", [this](){return ev ? ev     -> NTofClusterH()     : -1;}));
    variables.push_back(new Container<int>("NTofClusters", [this](){return ev ? ev     -> NTofCluster()      : -1;}));
    variables.push_back(new Container<int>("NTofClustersHUsed", [this](){return betaH  ? betaH ->  NTofClusterH()     : -1;}));
    variables.push_back(new Container<int>("NTofClustersUsed", [this](){return beta   ? beta  ->  NTofCluster()      : -1;}));
    variables.push_back(new Container<float>("Time_L0",    [this](){return clusterHL0  ? clusterHL0 -> Time              : -999;}));
    variables.push_back(new Container<float>("Time_L1",    [this](){return clusterHL1  ? clusterHL1 -> Time              : -999;}));
    variables.push_back(new Container<float>("Time_L2",    [this](){return clusterHL2  ? clusterHL2 -> Time              : -999;}));
    variables.push_back(new Container<float>("Time_L3",    [this](){return clusterHL3  ? clusterHL3 -> Time              : -999;}));
    
        // Tracker                                                                                  
    variables.push_back(new Container<int>("NTrackHits",   [this](){return tr ? tr -> NTrRecHit()               : 0;}));
    variables.push_back(new Container<float>("Q_all",      [this](){return tr ? tr -> GetQ_all().Mean           : 0;}));
    variables.push_back(new Container<float>("InnerQ_all", [this](){return tr ? tr -> GetInnerQ_all().Mean      : 0;}));
    variables.push_back(new Container<float>("L1_Hit_X",   [this](){return tr ? tr -> GetHitCooLJ(1)[0]         : 0;}));
    variables.push_back(new Container<float>("L1_Hit_Y",   [this](){return tr ? tr -> GetHitCooLJ(1)[1]         : 0;}));
    variables.push_back(new Container<float>("L1_Hit_Z",   [this](){return tr ? tr -> GetHitCooLJ(1)[2]         : 0;}));
    variables.push_back(new Container<float>("L2_Hit_X",   [this](){return tr ? tr -> GetHitCooLJ(2)[0]         : 0;}));
    variables.push_back(new Container<float>("L2_Hit_Y",   [this](){return tr ? tr -> GetHitCooLJ(2)[1]         : 0;}));
    variables.push_back(new Container<float>("L2_Hit_Z",   [this](){return tr ? tr -> GetHitCooLJ(2)[2]         : 0;}));
    variables.push_back(new Container<float>("ChiQUp",     [this](){return tr && tr -> ParExists(trackFitId_111) ? tr -> GetChisq(trackFitId_111)  : 0;}));
    variables.push_back(new Container<float>("ChiQDown",   [this](){return tr && tr -> ParExists(trackFitId_121) ? tr -> GetChisq(trackFitId_121)  : 0;}));
    variables.push_back(new Container<float>("ChiQ",       [this](){return tr && tr -> ParExists(trackFitId_131) ? tr -> GetChisq(trackFitId_131)  : 0;}));
    variables.push_back(new Container<float>("ChiQL1",     [this](){return tr && tr -> ParExists(trackFitId_151) ? tr -> GetChisq(trackFitId_151)  : 0;}));

    variables.push_back(new Container<float>("RUp",     [this](){return tr && tr -> ParExists(trackFitId_111) ? tr -> GetRigidity(trackFitId_111)  : 0;}));
    variables.push_back(new Container<float>("RDown",   [this](){return tr && tr -> ParExists(trackFitId_121) ? tr -> GetRigidity(trackFitId_121)  : 0;}));
    variables.push_back(new Container<float>("R",       [this](){return tr && tr -> ParExists(trackFitId_131) ? tr -> GetRigidity(trackFitId_131)  : 0;}));
    variables.push_back(new Container<float>("RL1",     [this](){return tr && tr -> ParExists(trackFitId_151) ? tr -> GetRigidity(trackFitId_151)  : 0;}));

    variables.push_back(new Container<std::vector<float>, 9 >("EDepLayerX", [this](){return edepLayer<0>(); }));
    variables.push_back(new Container<std::vector<float>, 9>("EDepLayerY", [this](){return edepLayer<1>(); }));
    variables.push_back(new Container<std::vector<float>, 9>("EDepTrackX", [this](){return edepTrack<0>(); }));
    variables.push_back(new Container<std::vector<float>, 9>("EDepTrackY", [this](){return edepTrack<1>(); }));
    variables.push_back(new Container<std::vector<float>, 9>("LayerJQ", [this](){return LayerJQ(); }));

        // Rich
    variables.push_back(new Container<double>("BetaRICH", [this](){return rich ? rich -> getBeta()               : 0;}));
    variables.push_back(new Container<float>("RichBetaConsistency", [this](){return rich ? rich -> getBetaConsistency()    : 0;}));

        // // MC
    variables.push_back(new Container<double>("GenMomentum", [this](){return mc ? mc -> Momentum          : -999;}));
    variables.push_back(new Container<float>("GenCoo0", [this](){return mc ? mc -> Coo[0]            : -999;}));
    variables.push_back(new Container<float>("GenCoo1", [this](){return mc ? mc -> Coo[1]            : -999;}));
    variables.push_back(new Container<float>("GenCoo2", [this](){return mc ? mc -> Coo[2]            : -999;}));
    variables.push_back(new Container<float>("GenDir0", [this](){return mc ? mc -> Dir[0]            : -999;}));
    variables.push_back(new Container<float>("GenDir1", [this](){return mc ? mc -> Dir[1]            : -999;}));
    variables.push_back(new Container<float>("GenDir2", [this](){return mc ? mc -> Dir[2]            : -999;}));
    variables.push_back(new Container<unsigned long long>("selStatus", [this](){
            unsigned long long selStatus = 0;
            if(!ev) return selStatus;
            for(int nsel=0; nsel<selections.size(); nsel++)
                if(selections[nsel].second(ev))
                    selStatus += 1LLU << nsel;
            return selStatus;
            }));
}


//////////////////////////////////////////
// Total energy deposited in each layer //
//////////////////////////////////////////

template<int SIDE>
std::vector<float> Dst::edepLayer()
{
    std::vector<float> ret(9, 0);
    for (int i = 0; i < trackRawClusters.size(); i++){
        if (trackRawClusters[i]->GetSide() != SIDE) continue;
        int ilay = trackRawClusters[i]->GetLayerJ()-1;
        ret[ilay] += trackRawClusters[i]->GetEdep();
    }
    return ret;
}

//////////////////////////////////////////
//  Energy deposited along the track    //
//////////////////////////////////////////

template<int SIDE>
std::vector<float> Dst::edepTrack()
{
    std::vector<float> ret(9, 0);
    for (auto it = trackHitToClusterMap.begin(); it != trackHitToClusterMap.end(); it++){
        const TrRecHitR* hit = it -> first;
        const int ilay = hit->GetLayerJ()-1;
        const std::pair<TrClusterR*, TrClusterR*> xyClusters = it -> second;
        if(SIDE == 0) ret[ilay] = xyClusters.first ? xyClusters.first -> GetEdep() : 0;
        if(SIDE == 1) ret[ilay] = xyClusters.second -> GetEdep();
    }
    return ret;
}

std::vector<float> Dst::LayerJQ()
{
    std::vector<float> ret(9, 0);
    if(!tr) return ret;

    for (int j = 0; j < 9; j++) 
        ret[j] = tr -> GetLayerJQ(j+1);
    return ret; 
}

int main(int argc, char **argv){
    //Processing input options
    int c;
    int entries = 0;
    std::string outFname;
    std::string  inFname = "/afs/cern.ch/work/b/bcoste/protonB800.root";
    int smearing = 0;

    if (argc==1) std::cout
                     << "Example:  ./dst -o test.root -n 10000 -f $EOSPATH/ams/Data/AMS02/2014/ISS.B900/std/1439205227.00000001.root"
                     << std::endl;

    while((c = getopt(argc, argv, "o:n:s:f:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        else if(c == 'n') entries = atoi(optarg);
        else if(c == 's') smearing = atoi(optarg);
        else if(c == 'f') inFname = optarg;
    }
    
    std::cout << "inFname : " << inFname << std::endl;
    Dst t( inFname );
    t.setSmearing(smearing);
    t.setMaxEntries(entries);
    if(!outFname.empty()) t.setOutputFileName(outFname);
    t.go();
    return 0;
}

#endif

