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
    return ev->pParticle(0)->pBetaH()->GetBeta() > 0;
}

bool betaNotCrazy(AMSEventR *ev) 
{ 
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBetaH()) return false;
    return ev->pParticle(0)->pBetaH()->GetBeta() < 8;
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

// 
bool basicBetaH(AMSEventR *ev)
{
    ParticleR * particle = ev->pParticle(0);
    if(!particle) return false;
    BetaHR* betaH = particle->pBetaH();
    if(!betaH) return false;
    if(betaH->GetBeta()==0) return false;
    return betaH->NTofClusterH() >= 3;
}

bool isolatedBetaH(AMSEventR *ev)
{
    ParticleR * particle = ev->pParticle(0);
    if(!particle) return false;
    BetaHR* betaH = particle->pBetaH();
    if(!betaH) return false;
    if(betaH->GetBeta()==0) return false;
    return (betaH->NTofClusterH() == 4 && ev->NTofClusterH() == 4);
}

bool tofTrackInsideInnerTracker(AMSEventR *ev){
    TofRecon::BuildTofTracks(ev);
    if( TofRecon::TofTracksList.size() == 0) return false;

    // Ask that extrapolation crosses Tracker layers L2 to L8 with a safety margin of 0
    int isInsideBit = TofRecon::TofTracksList[0] -> GetPatternInsideTracker(0);

    if( (isInsideBit&0b011111110) != 0b011111110 ) return false;
    return true;
}

bool tofTrackInsideFullSpan(AMSEventR *ev){
    if( TofRecon::TofTracksList.size() == 0) return false;

    // Ask that extrapolation crosses Tracker layers L2 to L8 with a safety margin of 0
    int isInsideBit = TofRecon::TofTracksList[0] -> GetPatternInsideTracker(0);

    if( (isInsideBit&0b111111111) != 0b111111111 ) return false;

    return true;
}
