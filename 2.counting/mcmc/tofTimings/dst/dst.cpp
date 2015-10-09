#ifndef _DST__CPP_
#define _DST__CPP_

#include "dst.hpp"

using namespace rootUtils;

#define ADD_VARIABLE(name, lambda) fill[name] =  [this](){ var[name][chunkStepNumber] = lambda }


void Dst::registerVariables(){
    maxEntries = 100;

    //                              pointer        value              defaultValue
    // HEADER
    ADD_VARIABLE("run",                  ev ? ev -> Run()             : -1;     );
    ADD_VARIABLE("event",                ev ? ev -> Event()           : -1;     );
    ADD_VARIABLE("UTime",                ev ? ev -> UTime()           : -1;     );

    // TOF
    ADD_VARIABLE("beta",               beta ? beta  -> Beta           : -1;     );
    ADD_VARIABLE("betaH",             betaH ? betaH -> GetBeta()      : -1;     );
    ADD_VARIABLE("NTofClusterH",      betaH ? betaH -> NTofClusterH() : -1;     );
    ADD_VARIABLE("time_L0",      clusterHL0 ? clusterHL0 -> Time      : -999;     );
    ADD_VARIABLE("time_L1",      clusterHL1 ? clusterHL1 -> Time      : -999;     );
    ADD_VARIABLE("time_L2",      clusterHL2 ? clusterHL2 -> Time      : -999;     );
    ADD_VARIABLE("time_L3",      clusterHL3 ? clusterHL3 -> Time      : -999;     );

    // Tracker
    ADD_VARIABLE("R",                    tr ? tr -> GetRigidity()     : -999;  );

    // MC
    ADD_VARIABLE("GenMomentum",          mc ? mc -> Momentum          : -999;  );
    ADD_VARIABLE("GenCoo0",              mc ? mc -> Coo[0]            : -999;  );
    ADD_VARIABLE("GenCoo1",              mc ? mc -> Coo[1]            : -999;  );
    ADD_VARIABLE("GenCoo2",              mc ? mc -> Coo[2]            : -999;  );
    ADD_VARIABLE("GenDir0",              mc ? mc -> Dir[0]            : -999;  );
    ADD_VARIABLE("GenDir1",              mc ? mc -> Dir[1]            : -999;  );
    ADD_VARIABLE("GenDir2",              mc ? mc -> Dir[2]            : -999;  );

}

void Dst::initPointers(){
    beta = NULL;
    betaH = NULL;
    part = NULL;
    tr = NULL;
    clusterHL0 = NULL;
    clusterHL1 = NULL;
    clusterHL2 = NULL;
    clusterHL3 = NULL;
    mc = NULL;

    if(ev == NULL) return;

    if (ev->nBetaH() > 0)     betaH = ev->pBetaH(0);
    if (ev->nBeta() > 0)      beta = ev -> pBeta(0);
    if (ev->nParticle() > 0 ) part = ev->pParticle(0);
    if (part)                 tr = (TrTrackR*) part->pTrTrack();

    if (betaH) clusterHL0 = betaH -> GetClusterHL(0);
    if (betaH) clusterHL1 = betaH -> GetClusterHL(1);
    if (betaH) clusterHL2 = betaH -> GetClusterHL(2);
    if (betaH) clusterHL3 = betaH -> GetClusterHL(3);

    mc = ev->GetPrimaryMC();
}

int main(int argc, char **argv){
    std::string filename = "/afs/cern.ch/work/b/bcoste/protonB800.root";
    if(argc > 1) filename = argv[1];
    Dst t( filename );

    if(argc > 2) t.setOutputFileName(argv[2]);
    t.go();
    return 0;
}

#endif

