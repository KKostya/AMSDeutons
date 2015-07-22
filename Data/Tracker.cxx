#include "Tracker.h"

int NTrackHits(AMSEventR * ev){ return ev->pTrTrack(0)?ev->pTrTrack(0)->NTrRecHit():0; }

///////////////////////////
//  Various fits and chi2
//////////////////////////////

double getRigidity(AMSEventR *ev, int i,int j, int k)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(i,j,k);
    return track->GetRigidity(fitID);
}
double Rup  (AMSEventR * ev) { return getRigidity(ev,1,1,1); }
double Rdown(AMSEventR * ev) { return getRigidity(ev,1,2,1); }
double R    (AMSEventR * ev) { return getRigidity(ev,1,3,1); }
double Rfull(AMSEventR * ev) { return getRigidity(ev,1,7,1); }
double Chisquare(AMSEventR * ev)
{ 
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(1,3,1);
    return track->GetChisq(fitID);
}

// Bit patterns for fits
int fit[6] = {
    0x78211,  //  1111000 0010 0001 0001
    0x63211,  //  1100011 0010 0001 0001
    0x0f211,  //  0001111 0010 0001 0001
    0x1c211,  //  0011100 0010 0001 0001
    0x3f211,  //  0111111 0010 0001 0001
    0x7e211,  //  1111110 0010 0001 0001
};

std::vector<double> R_(AMSEventR * ev) 
{ 
    std::vector<double> ret(sizeof(fit)/sizeof(fit[0]), 0);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    for(int i=0; i<sizeof(fit)/sizeof(fit[0]); i++)
    {
        track->FitT(fit[i],-1);
        ret[i] = track->GetRigidity(fit[i]);
    }
    return ret;
}

std::vector<double> chiq(AMSEventR * ev) 
{ 
    std::vector<double> ret(sizeof(fit)/sizeof(fit[0]), 0);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    for(int i=0; i<sizeof(fit)/sizeof(fit[0]); i++)
        ret[i] = track->FitT(fit[i],-1);
    return ret;
}

///////
// Residuals and unused layers
///////

std::vector<double> ResiduiX(AMSEventR * ev)
{
    std::vector<double> ret(9, -999999);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    int fitID = track->iTrTrackPar(1,3,1);
    if(!track->ParExists(fitID)) return ret;
    TrTrackPar parametri = track->gTrTrackPar(fitID);
    for (int layer=2;layer<9;layer++) 
    {
        if(!track->TestHitLayerJ(layer) || !track->TestHitLayerJHasXY(layer)) 
            ret[layer] = -999999;
        else
        {
            AMSPoint Residual_point = track->GetResidualJ(layer,fitID);
            ret[layer] = Residual_point.x();
        }
    }
    return ret;
}

std::vector<double> ResiduiY(AMSEventR * ev)
{
    std::vector<double> ret(9, -999999);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    int fitID = track->iTrTrackPar(1,3,1);
    if(!track->ParExists(fitID)) return ret;
    TrTrackPar parametri = track->gTrTrackPar(fitID);
    for (int layer=2;layer<9;layer++) 
    {
        if(!track->TestHitLayerJ(layer))
            ret[layer] = -999999;
        else
        {
            AMSPoint Residual_point = track->GetResidualJ(layer,fitID);
            ret[layer] = Residual_point.y();
        }
    }
    return ret;
}

int unusedLayers(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return -1;
    int fitID = track->iTrTrackPar(1,3,1);
    if(!track->ParExists(fitID)) return -1;
    TrTrackPar parametri = track->gTrTrackPar(fitID);

    int ret = 0;
    for (int layer=2;layer<9;layer++) 
        if(!parametri.TestHitLayerJ(layer)) ret++;

    return ret;
}

//////////////////////////////
// Deposited energy 
//////////////////////////////

double EdepTrack(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    double ret = 0;   
    if(!track) return ret;
    for(int i=0; i<track->NTrRecHit();i++){
        TrRecHitR * hit=track->pTrRecHit(i);
        ret += hit->Sum();
    }
}

///////////////////////////////
// Charge
///////////////////////////////
std::vector<double> ChargeTracker(ParticleR* part) {
    std::vector<double> ret(sizeof(fit)/sizeof(fit[0]), 0);

    TrTrackR* track = part->pTrTrack(0);
    if(!track) return ret;

    BetaHR* betah = (BetaHR*) part->pBetaH();
    double beta = betah->GetBeta();
    for(int i=0; i<sizeof(fit)/sizeof(fit[0]); i++)
        {
            ret[i] = track->GetQ_all(beta, fit[i]).Mean;
        }
    return ret;
}

