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


template <typename T> struct Container{
    Container<T>(std::string _name, std::function<T()> _f): name(_name), f(_f){

    }

    std::string name;
    std::function<T()> f;
    T *var;

    void assign(int i){
        var[i] = f();
    }

    // void save(){
    //     for(auto it = var.begin(); it != var.end() ;it++){
    //         std::cout << "outputFileName : " << outputFileName << std::endl;
    //         std::stringstream fname;
    //         fname << outputFileName <<"/" << it->first << "_chunk" << chunkNumber << ".bin";
    //         std::cout << "fname.str() : " << fname.str() << std::endl;
    //         std::ofstream myfile( fname.str(), std::ios::out | std::ios::binary);

    //         // myfile.write((char*)&chunkStepNumber, sizeof(int));
    //         myfile.write((char*)&(it->second[0]), sizeof(float)*chunkStepNumber);
    //         myfile.close();
    //     }
    // }
};

void Dst::registerVariables(){

    registerSelStatus();

    variables = std::make_tuple
        (
         // HEADER
         Container<unsigned int>("Run", [this](){return ev ? ev -> Run()                     : -1;}),
         Container<unsigned int>("Event", [this](){return ev ? ev -> Event()                   : -1;}),
         Container<unsigned int>("UTime", [this](){return ev ? ev -> UTime()                   : -1;}),
         Container<double>("ThetaS", [this](){return ev ? ev -> fHeader.ThetaS             : 0;}),
         Container<double>("PhiS", [this](){return ev ? ev -> fHeader.PhiS               : 0;}),
         Container<double>("Livetime", [this](){return ev ? ev -> LiveTime()                 : 0;}),
         Container<double>("Latitude", [this](){return ev ? ev -> fHeader.ThetaM             : 0;}),
         Container<unsigned long long>("fStatus", [this](){return ev ? ev -> fStatus                    : 0;}),
         Container<double>("Rcutoff", [this](){return part ? part -> Cutoff                   : -1;}),
                                                     
         // Triggers                                      
         Container<int>("PhysBPatt", [this](){return level ? level -> PhysBPatt               : -1;}),
         Container<int>("JMembPatt", [this](){return level ? level -> JMembPatt               : -1;}),
                                                                                                
         // TOF                                                                                      
         Container<double>("BetaTOF", [this](){return beta  ? beta  -> Beta                : -1;}),
         Container<double>("BetaTOFH", [this](){return betaH  ? betaH -> GetBeta()           : -1;}),
         Container<int>("NTofClustersH", [this](){return ev ? ev     -> NTofClusterH()     : -1;}),
         Container<int>("NTofClusters", [this](){return ev ? ev     -> NTofCluster()      : -1;}),
         Container<int>("NTofClustersHUsed", [this](){return betaH  ? betaH ->  NTofClusterH()     : -1;}),
         Container<int>("NTofClustersUsed", [this](){return beta   ? beta  ->  NTofCluster()      : -1;}),
         Container<float>("Time_L0",    [this](){return clusterHL0  ? clusterHL0 -> Time              : -999;}),
         Container<float>("Time_L1",    [this](){return clusterHL1  ? clusterHL1 -> Time              : -999;}),
         Container<float>("Time_L2",    [this](){return clusterHL2  ? clusterHL2 -> Time              : -999;}),
         Container<float>("Time_L3",    [this](){return clusterHL3  ? clusterHL3 -> Time              : -999;}),
    
         // Tracker                                                                                  
         Container<int>("NTrackHits",   [this](){return tr ? tr -> NTrRecHit()               : 0;}),
         Container<double>("R",         [this](){return tr ? tr -> GetRigidity()             : 0;}),
         Container<float>("Q_all",      [this](){return tr ? tr -> GetQ_all().Mean           : 0;}),
         Container<float>("InnerQ_all", [this](){return tr ? tr -> GetInnerQ_all().Mean      : 0;}),
         Container<float>("L1_Hit_X",   [this](){return tr ? tr -> GetHitCooLJ(1)[0]         : 0;}),
         Container<float>("L1_Hit_Y",   [this](){return tr ? tr -> GetHitCooLJ(1)[1]         : 0;}),
         Container<float>("L1_Hit_Z",   [this](){return tr ? tr -> GetHitCooLJ(1)[2]         : 0;}),
         Container<float>("L2_Hit_X",   [this](){return tr ? tr -> GetHitCooLJ(2)[0]         : 0;}),
         Container<float>("L2_Hit_Y",   [this](){return tr ? tr -> GetHitCooLJ(2)[1]         : 0;}),
         Container<float>("L2_Hit_Z",   [this](){return tr ? tr -> GetHitCooLJ(2)[2]         : 0;}),
         Container<float>("ChiQUp",     [this](){return tr && tr -> ParExists(trackFitId_111) ? tr -> GetChisq(trackFitId_111)  : 0;}),
         Container<float>("ChiQDown",   [this](){return tr && tr -> ParExists(trackFitId_121) ? tr -> GetChisq(trackFitId_121)  : 0;}),
         Container<float>("ChiQ",       [this](){return tr && tr -> ParExists(trackFitId_131) ? tr -> GetChisq(trackFitId_131)  : 0;}),
         Container<float>("ChiQL1",     [this](){return tr && tr -> ParExists(trackFitId_151) ? tr -> GetChisq(trackFitId_151)  : 0;}),

         // Rich
         Container<double>("BetaRICH", [this](){return rich ? rich -> getBeta()               : 0;}),
         Container<float>("RichBetaConsistency", [this](){return rich ? rich -> getBetaConsistency()    : 0;}),

         // // MC
         Container<double>("GenMomentum", [this](){return mc ? mc -> Momentum          : -999;}),
         Container<float>("GenCoo0", [this](){return mc ? mc -> Coo[0]            : -999;}),
         Container<float>("GenCoo1", [this](){return mc ? mc -> Coo[1]            : -999;}),
         Container<float>("GenCoo2", [this](){return mc ? mc -> Coo[2]            : -999;}),
         Container<float>("GenDir0", [this](){return mc ? mc -> Dir[0]            : -999;}),
         Container<float>("GenDir1", [this](){return mc ? mc -> Dir[1]            : -999;}),
         Container<float>("GenDir2", [this](){return mc ? mc -> Dir[2]            : -999;}),
         Container<unsigned long long>("selStatus", [this](){
                 if(!ev) return float(0);
                 unsigned long long selStatus = 0;
                 for(int nsel=0; nsel<selections.size(); nsel++)
                     if(selections[nsel].second(ev))
                         selStatus += 1LLU << nsel;
                 return float(selStatus);
             })
         );

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

