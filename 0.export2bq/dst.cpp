#ifndef _DST__CPP_
#define _DST__CPP_

#include "dst.hpp"

using namespace rootUtils;

void Dst::registerSelStatus(){
    std::map<std::string, bool(*)(AMSEventR*)> cuts = {
        {"notFirstTwo", notFirstTwo},
        {"notInSaaCut", notInSaaCut},
        {"zenithCut", zenithCut},
        {"runtypeCut", runtypeCut},
        {"minimumbiasTOF", minimumbiasTOF},
        {"minimumbiasTRIGG", minimumbiasTRIGG},
        {"minimumbiasTRD", minimumbiasTRD},
        {"minimumbiasTRACKER", minimumbiasTRACKER},
        {"goldenTOF", goldenTOF},
        {"goldenTRD", goldenTRD},
        {"goldenTRACKER", goldenTRACKER},
        {"aParticle", aParticle},
        {"aTrack", aTrack},
        {"aTRDTrack", aTRDTrack},
        {"oneParticle", oneParticle},
        {"oneTrack", oneTrack},
        {"oneTRDTrack", oneTRDTrack},
        {"chargeOne", chargeOne},
        {"downGoing", downGoing},
        {"betaNotCrazy", betaNotCrazy},
        {"physicsTrigger", physicsTrigger},
        {"basicBetaH", basicBetaH},
        {"isolatedBetaH", isolatedBetaH},
        {"tofTrackInsideInnerTracker", tofTrackInsideInnerTracker},
        {"tofTrackInsideFullSpan", tofTrackInsideFullSpan},
        {"aRing", aRing},
        {"oneRing", oneRing},
        {"noNaF", noNaF},
        {"photFracG04", photFracG04},
        {"photFracL2", photFracL2},
        {"betaDisp", betaDisp},
        {"counts5", counts5},
        {"aRing", aRing},
        {"oneRing", oneRing},
        {"noNaF", noNaF},
        {"ringGood",  ringGood},
        {"ringClean", ringClean},
        {"ringProb",  ringProb},
        {"ringPMTs",  ringPMTs},
        {"ringChargeConsistency", ringChargeConsistency},
        {"ringPhotoElectrons",    ringPhotoElectrons},
        {"ringExpPhe", ringExpPhe},
        {"ringBetaCons", ringBetaCons},
        {"ringNoNaFBorder", ringNoNaFBorder}
    };
}

template <typename T> void Dst::add(std::string name, std::function<T()> lambda){
    variables.push_back(new Container<T>(name, lambda));
}

template <typename T, int SIZE> void Dst::add(std::string name, std::function<T()> lambda){
    variables.push_back(new Container<T,SIZE>(name, lambda));
}

void Dst::registerVariables() {

    registerSelStatus();

    // HEADER
    add<unsigned int>("Run", [this](){return ev ? ev -> Run() : -1;});
    add<unsigned int>("Event",           [this](){return ev ? ev -> Event()                   : -1;});
    add<unsigned int>("UTime",           [this](){return ev ? ev -> UTime()                   : -1;});
    add<float>("ThetaS",                 [this](){return ev ? ev -> fHeader.ThetaS            :  0;});
    add<float>("PhiS",                   [this](){return ev ? ev -> fHeader.PhiS              :  0;});
    add<float>("Livetime",               [this](){return ev ? ev -> LiveTime()                :  0;});
    add<float>("Latitude",               [this](){return ev ? ev -> fHeader.ThetaM            :  0;});
    add<unsigned long long>("fStatus",   [this](){return ev ? ev -> fStatus                   :  0;});
    add<float>("Rcutoff",                [this](){return part ? part -> Cutoff                : -1;});
                                                                       
    // Triggers                                                    
    add<int>("PhysBPatt",                [this](){return level ? level -> PhysBPatt           : -1;});
    add<int>("JMembPatt",                [this](){return level ? level -> JMembPatt           : -1;});
                                                                                                  
    // TOF                                                                                        
    add<float>("BetaTOF",                [this](){return beta  ? beta  -> Beta                : -1;});
    add<float>("BetaTOFH",               [this](){return betaH ? betaH -> GetBeta()           : -1;});
    add<float>("ChargeTOF",              [this](){return betaH       ? betaH->GetQ(nlay,qrms) : -1; });
    add<float>("TimeTof_L0",             [this](){return clusterHL[0] ? clusterHL[0] -> Time : 0;});
    add<float>("TimeTof_L1",             [this](){return clusterHL[1] ? clusterHL[1] -> Time : 1;});
    add<float>("TimeTof_L2",             [this](){return clusterHL[2] ? clusterHL[2] -> Time : 2;});
    add<float>("TimeTof_L3",             [this](){return clusterHL[3] ? clusterHL[3] -> Time : 3;});
    add<int>("NTofClustersH",            [this](){return ev    ? ev     -> NTofClusterH()     : -1;});
    add<int>("NTofClusters",             [this](){return ev    ? ev     -> NTofCluster()      : -1;});
    add<int>("NTofClustersHUsed",        [this](){return betaH ? betaH ->  NTofClusterH()     : -1;});
    add<int>("NTofClustersUsed",         [this](){return beta  ? beta  ->  NTofCluster()      : -1;});
    add<int>("TofTrackPatt",             [this](){return tofTrack    ? tofTrack -> GetPatternInsideTracker(0) : 0; });
    
    // Tracker                                                                                  
    add<int>("NTrackHits",   [this](){return tr ? tr -> NTrRecHit()               : 0;});
    add<float>("Q_all",      [this](){return tr ? tr -> GetQ_all().Mean           : 0;});
    add<float>("InnerQ_all", [this](){return tr ? tr -> GetInnerQ_all().Mean      : 0;});
    add<float>("L1_Hit_X",   [this](){return tr ? tr -> GetHitCooLJ(1)[0]         : 0;});
    add<float>("L1_Hit_Y",   [this](){return tr ? tr -> GetHitCooLJ(1)[1]         : 0;});
    add<float>("L1_Hit_Z",   [this](){return tr ? tr -> GetHitCooLJ(1)[2]         : 0;});
    add<float>("L2_Hit_X",   [this](){return tr ? tr -> GetHitCooLJ(2)[0]         : 0;});
    add<float>("L2_Hit_Y",   [this](){return tr ? tr -> GetHitCooLJ(2)[1]         : 0;});
    add<float>("L2_Hit_Z",   [this](){return tr ? tr -> GetHitCooLJ(2)[2]         : 0;});
    add<float>("ChiQUp",     [this](){return tr && tr -> ParExists(trackFitId_111) ? tr -> GetChisq(trackFitId_111)  : 0;});
    add<float>("ChiQDown",   [this](){return tr && tr -> ParExists(trackFitId_121) ? tr -> GetChisq(trackFitId_121)  : 0;});
    add<float>("ChiQ",       [this](){return tr && tr -> ParExists(trackFitId_131) ? tr -> GetChisq(trackFitId_131)  : 0;});
    add<float>("ChiQL1",     [this](){return tr && tr -> ParExists(trackFitId_151) ? tr -> GetChisq(trackFitId_151)  : 0;});
    add<float>("RUp",        [this](){return tr && tr -> ParExists(trackFitId_111) ? tr -> GetRigidity(trackFitId_111)  : 0;});
    add<float>("RDown",      [this](){return tr && tr -> ParExists(trackFitId_121) ? tr -> GetRigidity(trackFitId_121)  : 0;});
    add<float>("R",          [this](){return tr && tr -> ParExists(trackFitId_131) ? tr -> GetRigidity(trackFitId_131)  : 0;});
    add<float>("RL1",        [this](){return tr && tr -> ParExists(trackFitId_151) ? tr -> GetRigidity(trackFitId_151)  : 0;});

    add<std::vector<float>, 9>("EDepLayerX", [this](){return edepLayer<0>(); });
    add<std::vector<float>, 9>("EDepLayerY", [this](){return edepLayer<1>(); });
    add<std::vector<float>, 9>("EDepTrackX", [this](){return edepTrack<0>(); });
    add<std::vector<float>, 9>("EDepTrackY", [this](){return edepTrack<1>(); });
    add<std::vector<float>, 9>("LayerJQ",    [this](){return LayerJQ(); });

    // Rich
    add<float>("BetaRICH",            [this](){return rich ? rich -> getBeta()               : 0;});
    add<float>("RichBetaConsistency", [this](){return rich ? rich -> getBetaConsistency()    : 0;});

    // // MC
    add<float>("GenMomentum", [this](){return mc ? mc -> Momentum          : -999;});

    for(int iCoo=0;iCoo<3;iCoo++){
        add<float>(Form("GenCoo%i",iCoo), [this, iCoo](){return mc ? mc -> Coo[iCoo]  : -999;});
        add<float>(Form("GenDir%i",iCoo), [this, iCoo](){return mc ? mc -> Dir[iCoo]  : -999;});
    }    

    add<double>("DistanceTOF_P", [this](){return distanceMinimizer -> protonDists.TOF;       });
    add<double>("DistanceTRD_P", [this](){return distanceMinimizer -> protonDists.TRD;       });
    add<double>("DistanceTracker_P", [this](){return distanceMinimizer -> protonDists.Track;     });
    add<double>("MLRigidityTOF_P", [this](){return distanceMinimizer -> protonDists.rMinTOF;   });
    add<double>("MLRigidityTRD_P", [this](){return distanceMinimizer -> protonDists.rMinTRD;   });
    add<double>("MLRigidityTracker_P", [this](){return distanceMinimizer -> protonDists.rMinTrack; });

    add<double>("DistanceTOF_D", [this](){return distanceMinimizer -> deutonDists.TOF;       });
    add<double>("DistanceTRD_D", [this](){return distanceMinimizer -> deutonDists.TRD;       });
    add<double>("DistanceTracker_D", [this](){return distanceMinimizer -> deutonDists.Track;     });
    add<double>("MLRigidityTOF_D", [this](){return distanceMinimizer -> deutonDists.rMinTOF;   });
    add<double>("MLRigidityTRD_D", [this](){return distanceMinimizer -> deutonDists.rMinTRD;   });
    add<double>("MLRigidityTracker_D", [this](){return distanceMinimizer -> deutonDists.rMinTrack; });

    variables.push_back(new Container<unsigned long long>("selStatus", [this](){
                unsigned long long selStatus = 0;
                int nsel=0;
                if(!ev) return selStatus;
                for(auto const &it : selections){
                    if(it.second(ev)) selStatus += 1LLU << nsel;
                    nsel++;
                }
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

// TOF energy deposit
std::vector<float> EdepTOF(AMSEventR * ev)
{
    std::vector<float> ret(4,0);

    if(ev == NULL) return ret;
    for(int j=0; j< ev -> NTofCluster(); j++)
        ret[(ev->pTofCluster(j)->Layer)-1] = ev->pTofCluster(j)->Edep;
    return ret;
}

int NTRDclusters(AMSEventR * ev)
{
    if( ev -> pTrdTrack(0) == NULL ) return -1;
    int ret = 0;
    for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
        {
            TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
            for(int i = 0;i < trdSegment->NTrdCluster(); i++) ret++;
        }
    return ret;
}

double EdepTRD(AMSEventR * ev)
{
    if( ev -> pTrdTrack(0) == NULL ) return -1;
    double ret = 0;
    for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
        {
            TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
            for(int i = 0;i < trdSegment->NTrdCluster(); i++) 
                ret += trdSegment->pTrdCluster(i)->EDep;
        }
    return ret;
}

int main(int argc, char **argv){
    //Processing input options
    int c;
    int entries = 0;
    std::string outFname;
    std::string  inFname = "/afs/cern.ch/work/b/bcoste/protonB800.root";
    int smearing = 0;
    int timingOffset = 0;
    OutFileType outFileType = kBinaryFile;

    if (argc==1){
        std::cout
            << "Simple example:  ./dst -o output.root -n 10000 -f ${HOME}/eos/ams/Data/AMS02/2014/ISS.B900/std/1439205227.00000001.root"
            << "\n\nUsage:"
            << "\n\t-f: input AMS Root file"
            << "\n\t-o: output file name"
            << "\n\t-n: number of events"
            << "\n\t-s: smearing, gaussian width:  TofMCPar::MCtuneDT"
            << "\n\t-z: smearing, gaussian offset: TofMCPar::MCtuneST"
            << "\n\t-t: change output format to text file (default is binary)"
            << std::endl;
        exit(-1);
    }

    while((c = getopt(argc, argv, "to:n:s:f:z:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        else if(c == 'n') entries = atoi(optarg);
        else if(c == 's'){
            smearing = atoi(optarg);
            if( smearing > 0 ) smearing = -smearing;
        }
        else if(c == 'z'){
            timingOffset = atoi(optarg);
        }
        else if(c == 'f') inFname = optarg;
        else if(c == 't'){
            outFileType = kTextFile;
        } 
    }
    
    std::cout << "inFname : " << inFname << std::endl;
    Dst t( inFname );
    t.setSmearing(smearing);
    t.setTimingOffset(timingOffset);
    t.setMaxEntries(entries);
    t.setOutFileType(outFileType);
    if(!outFname.empty()) t.setOutputFileName(outFname);
    t.go();
    return 0;
}


void Dst::initPointers(){
    beta = NULL;
    betaH = NULL;
    part = NULL;
    tr = NULL;
    level = NULL;
    for(int iLayer = 0;iLayer<4;iLayer++) clusterHL[iLayer] = NULL;
    mc = NULL;
    rich = NULL;
    tofTrack = NULL;

    trackFitId_111 = 0;
    trackFitId_121 = 0;
    trackFitId_131 = 0;
    trackFitId_151 = 0;

    trackRawClusters.clear();
    trackHitToClusterMap.clear();

    if(ev == NULL) return;

    level = ev->pLevel1(0);
    rich = ev->pRichRing(0);

    if (ev->nBetaH() > 0)     betaH = ev->pBetaH(0);
    if (ev->nBeta() > 0)      beta = ev -> pBeta(0);
    if (ev->nParticle() > 0 ) part = ev->pParticle(0);
    
    if (part) tr = (TrTrackR*) part->pTrTrack();

    for (int i = 0; i < ev -> NTrCluster(); i++) trackRawClusters.push_back( ev->pTrCluster(i) );

    if(tr){
        for (int i = 0; i < tr -> GetNhits(); i++){
            TrRecHitR* hit = tr -> GetHit(i);
            TrClusterR* yCluster = hit -> GetYCluster();
            TrClusterR* xCluster = hit->OnlyY() ? NULL : hit -> GetXCluster();
            trackHitToClusterMap[hit] = make_pair(xCluster, yCluster);
        }

        trackFitId_111 = tr -> iTrTrackPar(1,1,1);
        trackFitId_121 = tr -> iTrTrackPar(1,2,1);
        trackFitId_131 = tr -> iTrTrackPar(1,3,1);
        trackFitId_151 = tr -> iTrTrackPar(1,5,1);
    }

    if (betaH){
        if( smearing != 0 || timingOffset != 0) betaH->DoMCtune(); //Active smearing
        for(int iLayer = 0;iLayer<4;iLayer++) clusterHL[iLayer] = betaH -> GetClusterHL(iLayer);

    }

    mc = ev->GetPrimaryMC();

    distanceMinimizer -> reset(this);
    distanceMinimizer -> CalculateDistances();

    TofRecon::BuildTofTracks(ev);
    tofTrack = TofRecon::pTofTrack(0);
}

void Dst::init(){
    DstAmsBinary::init();
    if( smearing != 0 || timingOffset != 0 ){
        TofMCPar::MCtuneDT=smearing;
        TofMCPar::MCtuneST=timingOffset;
        std::cout << "Smearing activated and set to : " << smearing << std::endl;
        std::cout << "Timing offset activated and set to : " << timingOffset << std::endl;
    }
    distanceMinimizer = new DistanceMinimizer();
}

#endif

