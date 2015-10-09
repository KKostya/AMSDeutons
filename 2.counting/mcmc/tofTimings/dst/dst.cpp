#ifndef _DST__CPP_
#define _DST__CPP_

#include "dst.hpp"

using namespace rootUtils;

#define ADD_VARIABLE(name, lambda) fill[name] =  [this](){ var[name][chunkStepNumber] = lambda }


void Dst::registerVariables(){
    maxEntries = 100;

    ADD_VARIABLE("beta",               beta ? beta  -> Beta           : -1; );
    ADD_VARIABLE("betaH",             betaH ? betaH -> GetBeta()      : -1; );
    ADD_VARIABLE("NTofClusterH",      betaH ? betaH -> NTofClusterH() : -1; );
    ADD_VARIABLE("time_L0",      clusterHL0 ? clusterHL0 -> Time      : -1; );
    ADD_VARIABLE("time_L1",      clusterHL1 ? clusterHL1 -> Time      : -1; );
    ADD_VARIABLE("time_L2",      clusterHL2 ? clusterHL2 -> Time      : -1; );
    ADD_VARIABLE("time_L3",      clusterHL3 ? clusterHL3 -> Time      : -1; );
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

    if(ev == NULL) return;

    if (ev->nBetaH() > 0)     betaH = ev->pBetaH(0);
    if (ev->nBeta() > 0)      beta = ev -> pBeta(0);
    if (ev->nParticle() > 0 ) part = ev->pParticle(0);
    if (part)                 tr = (TrTrackR*) part->pTrTrack();

    if (betaH) clusterHL0 = betaH -> GetClusterHL(0);
    if (betaH) clusterHL1 = betaH -> GetClusterHL(1);
    if (betaH) clusterHL2 = betaH -> GetClusterHL(2);
    if (betaH) clusterHL3 = betaH -> GetClusterHL(3);
}

int main(int argc, char **argv){
    TApplication app("app",&argc,argv);

    Dst t( "/afs/cern.ch/work/b/bcoste/protonB800.root" );
    t.go();

    app.Run();
    return 0;
}

#endif

