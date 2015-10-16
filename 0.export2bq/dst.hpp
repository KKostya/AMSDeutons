#ifndef _DST__HPP_
#define _DST__HPP_

#include <string>
#include <vector>
#include <iostream>

#include "DstAmsBinary.hpp"
#include "rootUtils.hpp"
#include "Stack.hpp"

#include "TrCharge.h"

#include "Geo.h"
#include "Preselect.h"
#include "Golden.h"
#include "MinBias.h"
#include <tuple>
#include "RICH.h"

#define MAXRAM 1e9


class Dst : public DstAmsBinary{
public:
    Dst( std::string _data ) : DstAmsBinary( _data, MAXRAM){
        std::cout << "init with #" << data.size() << std::endl;
    }
  
protected:
    // virtual void init();
    void registerVariables() override; 

    BetaHR* betaH;
    BetaR* beta;
    TofClusterHR *clusterHL0,*clusterHL1,*clusterHL2,*clusterHL3;
    int trackFitId_111,trackFitId_121,trackFitId_131,trackFitId_151;
    MCEventgR* mc;
    Level1R *level;
    RichRingR *rich;
    std::vector<std::pair<std::string, std::function<bool(AMSEventR*)> > > selections;

    virtual void initPointers(){
        beta = NULL;
        betaH = NULL;
        part = NULL;
        tr = NULL;
        level = NULL;
        clusterHL0 = NULL;
        clusterHL1 = NULL;
        clusterHL2 = NULL;
        clusterHL3 = NULL;
        mc = NULL;
        rich = NULL;

        trackFitId_111 = 0;
        trackFitId_121 = 0;
        trackFitId_131 = 0;
        trackFitId_151 = 0;

        if(ev == NULL) return;

        level = ev->pLevel1(0);
        rich = ev->pRichRing(0);

        if (ev->nBetaH() > 0)     betaH = ev->pBetaH(0);
        if (ev->nBeta() > 0)      beta = ev -> pBeta(0);
        if (ev->nParticle() > 0 ) part = ev->pParticle(0);

    
        if (part) tr = (TrTrackR*) part->pTrTrack();

        if(tr){
            trackFitId_111 = tr -> iTrTrackPar(1,1,1);
            trackFitId_121 = tr -> iTrTrackPar(1,2,1);
            trackFitId_131 = tr -> iTrTrackPar(1,3,1);
            trackFitId_151 = tr -> iTrTrackPar(1,5,1);
        }

        if (betaH){
            clusterHL0 = betaH -> GetClusterHL(0);
            clusterHL1 = betaH -> GetClusterHL(1);
            clusterHL2 = betaH -> GetClusterHL(2);
            clusterHL3 = betaH -> GetClusterHL(3);
        }

        mc = ev->GetPrimaryMC();
    }

private:
    void registerSelStatus();
};

#endif


