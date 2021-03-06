#ifndef _DST__CPP_
#define _DST__CPP_

#include "dst.hpp"

using namespace rootUtils;

#define LAMBDA(expr) [this](){return expr;}

Dst::CodeTrackId Dst::codeTrackId = {
    {"Up",   111},
    {"Down", 121},
    {"",     131},
    {"L1",   151}
};

Dst::Selections Dst::selections = {
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

void Dst::registerVariables() {
    // HEADER
    add<unsigned int>("Run",            LAMBDA( ev   ? ev -> Run()                   : -1));
    add<unsigned int>("Event",          LAMBDA( ev   ? ev -> Event()                 : -1));
    add<unsigned int>("UTime",          LAMBDA( ev   ? ev -> UTime()                 : -1));
    add<float>("ThetaS",                LAMBDA( ev   ? ev -> fHeader.ThetaS          :  0));
    add<float>("PhiS",                  LAMBDA( ev   ? ev -> fHeader.PhiS            :  0));
    add<float>("Livetime",              LAMBDA( ev   ? ev -> LiveTime()              :  0));
    add<float>("Latitude",              LAMBDA( ev   ? ev -> fHeader.ThetaM          :  0));
    add<unsigned long long>("fStatus",  LAMBDA( ev   ? ev -> fStatus                 :  0));
    add<float>("Rcutoff",               LAMBDA( part ? part -> Cutoff                : -1));
                                                                       
    // Triggers                                                    
    add<int>("PhysBPatt", LAMBDA( level ? level -> PhysBPatt           : -1));
    add<int>("JMembPatt", LAMBDA( level ? level -> JMembPatt           : -1));
                                                                                                  
    // TOF                                                                                        
    add<float>("BetaTOF",         LAMBDA( beta         ? beta  -> Beta                : -1));
    add<float>("BetaTOFH",        LAMBDA( betaH        ? betaH -> GetBeta()           : -1));
    add<float>("ChargeTOF",       LAMBDA( betaH        ? betaH->GetQ(nlay,qrms)       : -1));

    for(int iLayer: {0,1,2,3})
        add<float>(Form("TimeTof_L%i",iLayer),   [this,iLayer]{return clusterHL[iLayer] ? clusterHL[iLayer] -> Time         : -1;});

    add<int>("NTofClustersH",     LAMBDA( ev           ? ev     -> NTofClusterH()     : -1));
    add<int>("NTofClusters",      LAMBDA( ev           ? ev     -> NTofCluster()      : -1));
    add<int>("NTofClustersHUsed", LAMBDA( betaH        ? betaH ->  NTofClusterH()     : -1));
    add<int>("NTofClustersUsed",  LAMBDA( beta         ? beta  ->  NTofCluster()      : -1));
    add<int>("TofTrackPatt",      LAMBDA( tofTrack     ? tofTrack -> GetPatternInsideTracker(0) : 0));
    
    // Tracker                                                                                  
    add<int>("NTrackHits",   LAMBDA( tr ? tr -> NTrRecHit()               : 0));
    add<float>("Q_all",      LAMBDA( tr ? tr -> GetQ_all().Mean           : 0));
    add<float>("InnerQ_all", LAMBDA( tr ? tr -> GetInnerQ_all().Mean      : 0));

    
    std::map<std::string, int> axis = { {"X", 0}, {"Y", 1}, {"Z", 2}};

    for( auto const &it: axis )
        for(int iLayer: {1,2})
            add<float>("L"+std::to_string(iLayer)+"_Hit_"+it.first,   [this,iLayer,it](){return  tr ? tr -> GetHitCooLJ(iLayer)[it.second]         : 0;});

    for( auto const &it: codeTrackId ){
        add<float>("ChiQ"+it.first, [this,it]{return tr && tr -> ParExists(trackFitId[it.second])   ? tr -> GetChisq(trackFitId[it.second])  : 0;});
        add<float>("R"   +it.first, [this,it]{return tr && tr -> GetRigidity(trackFitId[it.second]) ? tr -> GetRigidity(trackFitId[it.second])  : 0;});
    }

    add<std::vector<float>, 9>("EDepLayerX", LAMBDA( edepLayer<0>();));
    add<std::vector<float>, 9>("EDepLayerY", LAMBDA( edepLayer<1>();));
    add<std::vector<float>, 9>("EDepTrackX", LAMBDA( edepTrack<0>();));
    add<std::vector<float>, 9>("EDepTrackY", LAMBDA( edepTrack<1>();));
    add<std::vector<float>, 9>("LayerJQ",    LAMBDA( LayerJQ();));

    // Rich
    add<float>("BetaRICH",            LAMBDA( rich ? rich -> getBeta()               : 0));
    add<float>("RichBetaConsistency", LAMBDA( rich ? rich -> getBetaConsistency()    : 0));

    // // MC
    add<float>("GenMomentum", LAMBDA( mc ? mc -> Momentum          : -999));

    for(int iCoo=0;iCoo<3;iCoo++){
        add<float>(Form("GenCoo%i",iCoo), [this, iCoo](){return mc ? mc -> Coo[iCoo]  : -999;});
        add<float>(Form("GenDir%i",iCoo), [this, iCoo](){return mc ? mc -> Dir[iCoo]  : -999;});
    }    

    add<double>("DistanceTOF_P",       LAMBDA( distanceMinimizer -> protonDists.TOF;      ));
    add<double>("DistanceTRD_P",       LAMBDA( distanceMinimizer -> protonDists.TRD;      ));
    add<double>("DistanceTracker_P",   LAMBDA( distanceMinimizer -> protonDists.Track;    ));
    add<double>("MLRigidityTOF_P",     LAMBDA( distanceMinimizer -> protonDists.rMinTOF;  ));
    add<double>("MLRigidityTRD_P",     LAMBDA( distanceMinimizer -> protonDists.rMinTRD;  ));
    add<double>("MLRigidityTracker_P", LAMBDA( distanceMinimizer -> protonDists.rMinTrack;));

    add<double>("DistanceTOF_D",       LAMBDA( distanceMinimizer -> deutonDists.TOF;      ));
    add<double>("DistanceTRD_D",       LAMBDA( distanceMinimizer -> deutonDists.TRD;      ));
    add<double>("DistanceTracker_D",   LAMBDA( distanceMinimizer -> deutonDists.Track;    ));
    add<double>("MLRigidityTOF_D",     LAMBDA( distanceMinimizer -> deutonDists.rMinTOF;  ));
    add<double>("MLRigidityTRD_D",     LAMBDA( distanceMinimizer -> deutonDists.rMinTRD;  ));
    add<double>("MLRigidityTracker_D", LAMBDA( distanceMinimizer -> deutonDists.rMinTrack;));

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
    std::vector<std::string>  files;

    int smearing = 0;
    int timingOffset = 0;
    OutFileType outFileType = kBinaryFile;

    if (argc==1){
        std::cout
            << "Simple example:  ./bin/dst -o outputFolder -n 10000 -f ${HOME}/eos/ams/Data/AMS02/2014/ISS.B900/std/1439205227.00000001.root"
            << "\n\nUsage:"
            << "\n\t-f: input AMS Root file"
            << "\n\t    support multiples files, ex: ./bin/dst -f \"file1.root file2.root\""
            << "\n\t                               : ./bin/dst -f file1.root -f file2.root"
            << "\n\t                               : ./bin/dst -f file1.root,file2.root\n"
            << "\n\t-o: output file name\n"
            << "\n\t-n: number of events\n"
            << "\n\t-s: smearing, gaussian width:  TofMCPar::MCtuneDT\n"
            << "\n\t-z: smearing, gaussian offset: TofMCPar::MCtuneST\n"
            << "\n\t-m: mode for output file"
            << "\n\t    bin = binary format (default)"
            << "\n\t    txt = text file with one file per variable"
            << "\n\t    csv = csv file (all variables in same file)"
            << "\n\t    zip = zipped csv file (BigQuery compatible)\n"
            << "\n\t-v: git version"
            << std::endl;
        exit(-1);
    }

    while((c = getopt(argc, argv, "vm:o:n:s:f:z:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        else if(c == 'n') entries = atoi(optarg);
        else if(c == 'v'){
            std::cout << gitversion << std::endl;
            return 0;
        }
        else if(c == 's'){
            smearing = atoi(optarg);
            if( smearing > 0 ) smearing = -smearing;
        }
        else if(c == 'z'){
            timingOffset = atoi(optarg);
        }
        else if(c == 'f'){
            std::vector< std::string > f = generalUtils::split(optarg, " ,");
            std::copy(f.begin(), f.end(), std::back_inserter(files));
        }
        else if(c == 'm'){
            std::map<std::string, OutFileType> outFileDict = { {"bin", kBinaryFile},
                                                               {"txt", kTextFile},
                                                               {"csv", kCsvForBigQuery},
                                                               {"zip", kZippedCsvForBigQuery}
            };
            
            if( outFileDict.find(optarg) == outFileDict.end() ){
                std::cout << "This file format does not exist !\nPlease choose between c, b or t" << std::endl;
                exit(-1);
            }
            outFileType = outFileDict[optarg];
        } 
    }

    if(files.size() == 0) files.push_back("/afs/cern.ch/work/b/bcoste/protonB800.root");
    
    Dst t( files );
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

    for( auto &it: trackFitId) it.second = 0;

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

        for( auto &it: trackFitId ){
            int algo = it.first/100;
            int pattern = (it.first-100*algo)/10;
            int refit = it.first-100*algo-10*pattern;
            it.second = tr -> iTrTrackPar(algo,pattern,refit);
        }
    }

    if (betaH){
        if( smearing != 0 || timingOffset != 0) betaH->DoMCtune(); //Active smearing
        for(int iLayer = 0;iLayer<4;iLayer++) clusterHL[iLayer] = betaH -> GetClusterHL(iLayer);
    }

    mc = ev->GetPrimaryMC();

    distanceMinimizer -> reset(this);
    distanceMinimizer -> CalculateDistances();

    if(level){
        TofRecon::BuildTofTracks(ev);
        tofTrack = TofRecon::pTofTrack(0);
    }
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

