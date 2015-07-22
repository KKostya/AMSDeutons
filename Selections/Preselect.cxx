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
bool oneTRDTrack(AMSEventR *ev) { return ev->NTrdTrack() == 1; }

bool chargeOne(AMSEventR *ev) { 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pCharge()) return false;
    return  ev->pParticle(0)->pCharge()->Charge() == 1;
}

bool downGoing(AMSEventR *ev) 
{ 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBetaH()) return false;
    return ev->pParticle(0)->pBetaH()->Beta > 0;
}

bool betaNotCrazy(AMSEventR *ev) 
{ 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBeta()) return false;
    return ev->pParticle(0)->pBeta()->Beta < 8;
}

// Ensure at least one physics trigger
bool physicsTrigger(AMSEventR *ev)
{
    Level1R* level1 = ev->pLevel1(0);
    if( level1 == NULL ) return false;
    return ((level1->PhysBPatt >> 1)&0b11111);
}

template<int FIT>
bool fitExists(AMSEventR *ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return false;
    int fitID = track->iTrTrackPar(1,FIT,1);
    return track->ParExists(fitID);
}
