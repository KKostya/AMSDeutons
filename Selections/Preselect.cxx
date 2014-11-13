#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "Preselect.h"

////////////////////////////////////////////////
///  Preselections
////////////////////////////////////////////////

bool aParticle(AMSEventR *ev) { return ev->nParticle() >= 1; }
bool aTrack(AMSEventR *ev) { return ev->nTrTrack()  >= 1; }
bool aTRDTrack(AMSEventR *ev) { return ev->NTrdTrack() >= 1; }

bool oneParticle(AMSEventR *ev) { return ev->nParticle() == 1; }
bool oneTrack(AMSEventR *ev) { return ev->nTrTrack()  == 1; }

bool chargeOne(AMSEventR *ev) { 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pCharge()) return false;
    return  ev->pParticle(0)->pCharge()->Charge() == 1;
}

bool downGoing(AMSEventR *ev) 
{ 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBeta()) return false;
    return ev->pParticle(0)->pBeta()->Beta > 0;
}

bool betaNotCrazy(AMSEventR *ev) 
{ 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBeta()) return false;
    return ev->pParticle(0)->pBeta()->Beta < 8;
}

template<int FIT>
bool fitExists(AMSEventR *ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    int fitID = track->iTrTrackPar(1,FIT,1);
    return track->ParExists(fitID);
}

/////////////////////////////////////////////
//////////////// Utils //////////////////////
/////////////////////////////////////////////

std::vector<SubSelection<AMSEventR *> *> preselectionCuts;
std::vector<SubSelection<AMSEventR *> *> GetListOfPreselections()
{
    if(preselectionCuts.size() > 0) return preselectionCuts;
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( aParticle    , "At least one particle"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( aTrack       , "At least one track"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( aTRDTrack    , "At least one TRD track"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( oneParticle  , "Exactly one particle"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( oneTrack     , "Exactly one track"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( chargeOne    , "Charge == 1"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( downGoing    , "Beta > 0"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( betaNotCrazy , "Beta < 8"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( fitExists<1> , "FitID1 exists"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( fitExists<2> , "FitID2 exists"));
    preselectionCuts.push_back(new SubSelection<AMSEventR *>( fitExists<3> , "FitID3 exists"));
    return preselectionCuts;
}

bool Preselection(AMSEventR * event)
{
    bool selection = true;
    std::vector<SubSelection<AMSEventR *> *> cuts =  GetListOfPreselections();

    for (int i=0; i<cuts.size(); i++) 
        selection &= (!cuts[i]->Test(event));
    return selection;
}   

