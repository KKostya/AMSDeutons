#ifndef _DST__CPP_
#define _DST__CPP_

#include "dst.hpp"

using namespace rootUtils;

#define ADD_VARIABLE(name, lambda) fill[name] =  [this](){ var[name][chunkStepNumber] = lambda }

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

void Dst::registerVariables(){
    // HEADER
    ADD_VARIABLE("Run",                                    ev  ? ev -> Run()                     : -1;     );
    ADD_VARIABLE("Event",                                  ev  ? ev -> Event()                   : -1;     );
    ADD_VARIABLE("UTime",                                  ev  ? ev -> UTime()                   : -1;     );
    ADD_VARIABLE("ThetaS",                                 ev ? ev -> fHeader.ThetaS             : 0;     );
    ADD_VARIABLE("PhiS",                                   ev ? ev -> fHeader.PhiS               : 0;     );
    ADD_VARIABLE("Livetime",                               ev ? ev -> LiveTime()                 : 0;     );
    ADD_VARIABLE("Latitude",                               ev ? ev -> fHeader.ThetaM             : 0;     );
    ADD_VARIABLE("fStatus",                                ev ? ev -> fStatus                    : 0;     );
    ADD_VARIABLE("Rcutoff",                              part ? part -> Cutoff                   : -1;    );

    // Triggers
    ADD_VARIABLE("PhysBPatt",                           level ? level -> PhysBPatt               : -1;    );
    ADD_VARIABLE("JMembPatt",                           level ? level -> JMembPatt               : -1;    );
                                                                                                
    // TOF                                                                                      
    ADD_VARIABLE("BetaTOF",                                 beta  ? beta  -> Beta                : -1;     );
    ADD_VARIABLE("BetaTOFH",                               betaH  ? betaH -> GetBeta()           : -1;     );
    ADD_VARIABLE("NTofClustersH",                              ev ? ev     -> NTofClusterH()     : -1;     );
    ADD_VARIABLE("NTofClusters",                               ev ? ev     -> NTofCluster()      : -1;     );
    ADD_VARIABLE("NTofClustersHUsed",                      betaH  ? betaH ->  NTofClusterH()     : -1;     );
    ADD_VARIABLE("NTofClustersUsed",                       beta   ? beta  ->  NTofCluster()      : -1;     );
    ADD_VARIABLE("Time_L0",                        clusterHL0  ? clusterHL0 -> Time              : -999;     );
    ADD_VARIABLE("Time_L1",                        clusterHL1  ? clusterHL1 -> Time              : -999;     );
    ADD_VARIABLE("Time_L2",                        clusterHL2  ? clusterHL2 -> Time              : -999;     );
    ADD_VARIABLE("Time_L3",                        clusterHL3  ? clusterHL3 -> Time              : -999;     );
    
    // Tracker                                                                                  
    ADD_VARIABLE("NTrackHits",                               tr ? tr -> NTrRecHit()               : 0;  );
    ADD_VARIABLE("R",                                        tr ? tr -> GetRigidity()             : 0;  );
    ADD_VARIABLE("Q_all",                                    tr ? tr -> GetQ_all().Mean           : 0;  );
    ADD_VARIABLE("InnerQ_all",                               tr ? tr -> GetInnerQ_all().Mean      : 0;  );
    ADD_VARIABLE("L1_Hit_X",                                 tr ? tr -> GetHitCooLJ(1)[0]         : 0;  );
    ADD_VARIABLE("L1_Hit_Y",                                 tr ? tr -> GetHitCooLJ(1)[1]         : 0;  );
    ADD_VARIABLE("L1_Hit_Z",                                 tr ? tr -> GetHitCooLJ(1)[2]         : 0;  );
    ADD_VARIABLE("L2_Hit_X",                                 tr ? tr -> GetHitCooLJ(2)[0]         : 0;  );
    ADD_VARIABLE("L2_Hit_Y",                                 tr ? tr -> GetHitCooLJ(2)[1]         : 0;  );
    ADD_VARIABLE("L2_Hit_Z",                                 tr ? tr -> GetHitCooLJ(2)[2]         : 0;  );
    ADD_VARIABLE("ChiQUp",  tr && tr -> ParExists(trackFitId_111) ? tr -> GetChisq(trackFitId_111)  : 0;  );
    ADD_VARIABLE("ChiQDown",tr && tr -> ParExists(trackFitId_121) ? tr -> GetChisq(trackFitId_121)  : 0;  );
    ADD_VARIABLE("ChiQ",    tr && tr -> ParExists(trackFitId_131) ? tr -> GetChisq(trackFitId_131)  : 0;  );
    ADD_VARIABLE("ChiQL1",  tr && tr -> ParExists(trackFitId_151) ? tr -> GetChisq(trackFitId_151)  : 0;  );

    // Rich
    ADD_VARIABLE("BetaRICH",                               rich ? rich -> getBeta()               : 0;  );
    ADD_VARIABLE("RichBetaConsistency",                    rich ? rich -> getBetaConsistency()    : 0;  );

    // MC
    ADD_VARIABLE("GenMomentum",          mc ? mc -> Momentum          : -999;  );
    ADD_VARIABLE("GenCoo0",              mc ? mc -> Coo[0]            : -999;  );
    ADD_VARIABLE("GenCoo1",              mc ? mc -> Coo[1]            : -999;  );
    ADD_VARIABLE("GenCoo2",              mc ? mc -> Coo[2]            : -999;  );
    ADD_VARIABLE("GenDir0",              mc ? mc -> Dir[0]            : -999;  );
    ADD_VARIABLE("GenDir1",              mc ? mc -> Dir[1]            : -999;  );
    ADD_VARIABLE("GenDir2",              mc ? mc -> Dir[2]            : -999;  );

    registerSelStatus();
    fill["selStatus"] = [this](){
        if(!ev) return float(0);
        unsigned long long selStatus = 0;
        for(int nsel=0; nsel<selections.size(); nsel++)
            if(selections[nsel].second(ev))
                selStatus += 1LLU << nsel;
        return float(selStatus);
    };
}



int main(int argc, char **argv){
    //Processing input options
    int c;
    int entries = 0;
    std::string outFname;
    std::string  inFname = "/afs/cern.ch/work/b/bcoste/protonB800.root";

    if (argc==1) std::cout
                     << "Example:  ./dst -o test.root -n 10000 $EOSPATH/ams/Data/AMS02/2014/ISS.B900/std/1439205227.00000001.root"
                     << std::endl;

    while((c = getopt(argc, argv, "o:n:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        else if(c == 'n') entries = atoi(optarg);
    }

    if (optind < argc) inFname = std::string(argv[optind++]); 
    
    Dst t( inFname );
    t.setMaxEntries(entries);
    if(!outFname.empty()) t.setOutputFileName(outFname);
    t.go();
    return 0;
}

#endif

