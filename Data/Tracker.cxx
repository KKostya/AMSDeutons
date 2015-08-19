#include "Tracker.h"

int NTrackHits(AMSEventR * ev){ return ev->pTrTrack(0)?ev->pTrTrack(0)->NTrRecHit():0; }

///////////////////////////
//  Various fits and chi2
//////////////////////////////

float getRigidity(AMSEventR *ev, int i, int j, int k)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(i,j,k);
    if(!track->ParExists(fitID)) return 0;
    return track->GetRigidity(fitID);
}
float RUp  (AMSEventR * ev) { return getRigidity(ev,1,1,1); }
float RDown(AMSEventR * ev) { return getRigidity(ev,1,2,1); }
float R    (AMSEventR * ev) { return getRigidity(ev,1,3,1); }
float RL1  (AMSEventR * ev) { return getRigidity(ev,1,5,1); }

float getChisquare(AMSEventR * ev, int i, int j, int k)
{ 
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    int fitID = track->iTrTrackPar(i,j,k);
    if(!track->ParExists(fitID)) return 0;
    return track->GetChisq(fitID);
}
float ChiQUp  (AMSEventR * ev) { return getChisquare(ev,1,1,1); }
float ChiQDown(AMSEventR * ev) { return getChisquare(ev,1,2,1); }
float ChiQ    (AMSEventR * ev) { return getChisquare(ev,1,3,1); }
float ChiQL1  (AMSEventR * ev) { return getChisquare(ev,1,5,1); }

//////////////////////////////////////////
// Total energy deposited in each layer //
//////////////////////////////////////////

template<int SIDE>
std::vector<float> edepLayer(AMSEventR * ev)
{
    std::vector<float> ret(9, 0);
    for (int i = 0; i < ev->NTrCluster(); i++) 
    {
        TrClusterR* cluster = ev->pTrCluster(i);
        if (cluster->GetSide() != SIDE) continue;
        int ilay = cluster->GetLayerJ()-1;
        ret[ilay] += cluster->GetEdep();
    }
    return ret;
}

std::vector<float> EDepLayerX(AMSEventR * ev) { return edepLayer<0>(ev); }
std::vector<float> EDepLayerY(AMSEventR * ev) { return edepLayer<1>(ev); }

//////////////////////////////////////////
//  Energy deposited along the track    //
//////////////////////////////////////////

template<int SIDE>
std::vector<float> edepTrack(AMSEventR * ev)
{
    std::vector<float> ret(9, 0);
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

std::vector<float> EDepTrackX(AMSEventR * ev) { return edepTrack<0>(ev); }
std::vector<float> EDepTrackY(AMSEventR * ev) { return edepTrack<1>(ev); }

/////////////////////////
//  Charge estimators  //
/////////////////////////

std::vector<float> LayerJQ(AMSEventR * ev)
{
    std::vector<float> ret(9, 0);
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return ret;
    for (int j = 0; j < 9; j++) 
        ret[j] = track->GetLayerJQ(j+1);
    return ret; 
}

float Q_all(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    return track->GetQ_all().Mean;
}

float InnerQ_all(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    return track->GetInnerQ_all().Mean;
}

///////////////////////////////
//  Hit coordinates 1 and 2  //
///////////////////////////////
template <int J, int N>
float coordHit(AMSEventR * ev)
{
    TrTrackR * track = ev->pTrTrack(0);
    if(!track) return 0;
    return track->GetHitCooLJ(J)[N];
}


float L1_Hit_X(AMSEventR * ev) { return coordHit<1,0>(ev); }
float L1_Hit_Y(AMSEventR * ev) { return coordHit<1,1>(ev); }
float L1_Hit_Z(AMSEventR * ev) { return coordHit<1,2>(ev); }
float L2_Hit_X(AMSEventR * ev) { return coordHit<2,0>(ev); }
float L2_Hit_Y(AMSEventR * ev) { return coordHit<2,1>(ev); }
float L2_Hit_Z(AMSEventR * ev) { return coordHit<2,2>(ev); }

///////////////////
//  Residuals    //
///////////////////

template <int SIDE, int FID>
std::vector<float> Residual(AMSEventR * ev)
{
    std::vector<float> ret(9, -999999);
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

std::vector<float> ResidualX    (AMSEventR * ev) { return Residual<0,3>(ev); }
std::vector<float> ResidualY    (AMSEventR * ev) { return Residual<1,3>(ev); }
std::vector<float> ResidualUpX  (AMSEventR * ev) { return Residual<0,1>(ev); }
std::vector<float> ResidualUpY  (AMSEventR * ev) { return Residual<1,1>(ev); }
std::vector<float> ResidualDownX(AMSEventR * ev) { return Residual<0,2>(ev); }
std::vector<float> ResidualDownY(AMSEventR * ev) { return Residual<1,2>(ev); }
std::vector<float> ResidualL1X(AMSEventR * ev)   { return Residual<0,5>(ev); }
std::vector<float> ResidualL1Y(AMSEventR * ev)   { return Residual<1,5>(ev); }

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

