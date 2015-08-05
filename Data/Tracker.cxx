#include "Tracker.h"

int NTrackHits(AMSEventR * ev){ return ev->pTrTrack(0)?ev->pTrTrack(0)->NTrRecHit():0; }

///////////////////////////
//  Various fits and chi2
//////////////////////////////

double getRigidity(AMSEventR *ev, int i, int j, int k)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(i,j,k);
    if(!track->ParExists(fitID)) return 0;
    return track->GetRigidity(fitID);
}
double RUp  (AMSEventR * ev) { return getRigidity(ev,1,1,1); }
double RDown(AMSEventR * ev) { return getRigidity(ev,1,2,1); }
double R    (AMSEventR * ev) { return getRigidity(ev,1,3,1); }
double RL1  (AMSEventR * ev) { return getRigidity(ev,1,5,1); }

double getChisquare(AMSEventR * ev, int i, int j, int k)
{ 
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(i,j,k);
    if(!track->ParExists(fitID)) return 0;
    return track->GetChisq(fitID);
}
double ChiQUp  (AMSEventR * ev) { return getChisquare(ev,1,1,1); }
double ChiQDown(AMSEventR * ev) { return getChisquare(ev,1,2,1); }
double ChiQ    (AMSEventR * ev) { return getChisquare(ev,1,3,1); }
double ChiQL1  (AMSEventR * ev) { return getChisquare(ev,1,5,1); }

//////////////////////////////////////////
// Total energy deposited in each layer //
//////////////////////////////////////////

template<int SIDE>
std::vector<double> edepLayer(AMSEventR * ev)
{
    std::vector<double> ret(9, 0);
    for (int i = 0; i < ev->NTrCluster(); i++) 
    {
        TrClusterR* cluster = ev->pTrCluster(i);
        if (cluster->GetSide() != SIDE) continue;
        int ilay = cluster->GetLayerJ()-1;
        ret[ilay] += cluster->GetEdep();
    }
    return ret;
}

std::vector<double> EDepLayerX(AMSEventR * ev) { return edepLayer<0>(ev); }
std::vector<double> EDepLayerY(AMSEventR * ev) { return edepLayer<1>(ev); }

//////////////////////////////////////////
//  Energy deposited along the track    //
//////////////////////////////////////////

template<int SIDE>
std::vector<double> edepTrack(AMSEventR * ev)
{
    std::vector<double> ret(9, 0);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    for (int i = 0; i < track->GetNhits(); i++) 
    {
        TrRecHitR* hit = track->GetHit(i);
        int ilay = hit->GetLayerJ()-1;
        TrClusterR* cluster = hit->GetYCluster();   
        if(SIDE == 1) ret[ilay] = cluster->GetEdep();
        if (hit->OnlyY()) continue;
        cluster = hit->GetXCluster();   
        if(SIDE == 0) ret[ilay] = cluster->GetEdep();
    }
    return ret;
}

std::vector<double> EDepTrackX(AMSEventR * ev) { return edepTrack<0>(ev); }
std::vector<double> EDepTrackY(AMSEventR * ev) { return edepTrack<1>(ev); }

///////////////////////////////
//  Hit coordinates 1 and 2  //
///////////////////////////////



///////////////////
//  Residuals    //
///////////////////

template <int SIDE, int FID>
std::vector<double> Residual(AMSEventR * ev)
{
    std::vector<double> ret(9, -999999);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    int fitID = track->iTrTrackPar(1,FID,1);
    if(!track->ParExists(fitID)) return ret;
    for (int layer = 0;layer < 9;layer++) 
    {
        if(!track->TestHitLayerJ(layer+1))
            ret[layer] = -999999;
        else
        {
            AMSPoint Residual_point = track->GetResidualJ(layer+1,fitID);
            if(SIDE == 0) ret[layer] = Residual_point.x();
            if(SIDE == 1) ret[layer] = Residual_point.y();
        }
    }
    return ret;
}

std::vector<double> ResidualX    (AMSEventR * ev) { return Residual<0,3>(ev); }
std::vector<double> ResidualY    (AMSEventR * ev) { return Residual<1,3>(ev); }
std::vector<double> ResidualUpX  (AMSEventR * ev) { return Residual<0,1>(ev); }
std::vector<double> ResidualUpY  (AMSEventR * ev) { return Residual<1,1>(ev); }
std::vector<double> ResidualDownX(AMSEventR * ev) { return Residual<0,2>(ev); }
std::vector<double> ResidualDownY(AMSEventR * ev) { return Residual<1,2>(ev); }
std::vector<double> ResidualL1X(AMSEventR * ev)   { return Residual<0,5>(ev); }
std::vector<double> ResidualL1Y(AMSEventR * ev)   { return Residual<1,5>(ev); }

//////////////////////////////////////////
// unused layers //
//////////////////////////////////////////

int unusedLayers(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return -1;
    int fitID = track->iTrTrackPar(1,3,1);
    if(!track->ParExists(fitID)) return -1;
    TrTrackPar parametri = track->gTrTrackPar(fitID);

    int ret = 0;
    for (int layer = 0; layer < 9; layer++) 
        if(!parametri.TestHitLayerJ(layer+1)) ret++;

    return ret;
}

template <int FIT>
int getLayerBits(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(1,FIT,1);
    if(!track->ParExists(fitID)) return 0;
    TrTrackPar parametri = track->gTrTrackPar(fitID);

    int ret = 0;
    for (int layer = 0; layer < 9; layer++) 
        if(parametri.TestHitLayerJ(layer+1)) 
            ret |= (1 << layer);
    return ret;
}

int LayerBits    (AMSEventR * ev){ return getLayerBits<3>(ev); }
int LayerBitsUp  (AMSEventR * ev){ return getLayerBits<1>(ev); }
int LayerBitsDown(AMSEventR * ev){ return getLayerBits<2>(ev); }
int LayerBitsL1  (AMSEventR * ev){ return getLayerBits<5>(ev); }

