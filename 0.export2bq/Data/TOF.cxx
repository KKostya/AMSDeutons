#include "TOF.h"

int NTofClusters(AMSEventR * ev)    { return ev?ev->NTofClusterH():0; }
int NTofClustersUsed(AMSEventR * ev){ return ev?(ev->pBetaH(0)?ev->pBetaH(0)->NTofClusterH():0):0; }

// TOF energy deposit
std::vector<double> EdepTOF(AMSEventR * ev)
{
    std::vector<double> ret(4);
    for(int j=0; j<4; j++) ret[j] = 0;
    for(int j=0; j<ev->NTofClusterH(); j++)
        ret[(ev->pTofClusterH(j)->Layer)-1] = ev->pTofClusterH(j)->GetEdep();
    return ret;
}

double BetaTOF(AMSEventR * ev)
{
    double beta = 0;
    ParticleR * particle = ev->pParticle(0);
    if(!particle) return beta;
    if(particle->pBetaH()) beta = particle->pBetaH()->GetBeta();
    return beta;
}

double ChargeTOF(AMSEventR * ev)
{
    ParticleR * particle = ev->pParticle(0);
    if(!particle) return -999;

    BetaHR *betah=ev->pParticle(0)->pBetaH();
    if( betah == NULL ) return -999;

    int nlay; float qrms;
    return betah->GetQ(nlay,qrms); //TOF Trancate Mean Q, see vdev/examples/Tof_BetaH.C for more charges accessors
}

template <int I>
std::vector<double> tofCoords(AMSEventR * ev)
{
    std::vector<double> ret(4);
    for(int j=0; j<4; j++) ret[j] = 0;
    for(int j=0; j<ev->NTofClusterH(); j++)
        ret[(ev->pTofClusterH(j)->Layer)-1] = ev->pTofClusterH(j)->Coo[I];
    return ret;
}

int TrackTof(AMSEventR * ev){
    if( TofRecon::TofTracksList.size() == 0) return 0;

    // Ask that extrapolation crosses Tracker layers L2 to L8 with a safety margin of 0
    return TofRecon::TofTracksList[0] -> GetPatternInsideTracker(0);
}

std::vector<double> TOFCoordsX(AMSEventR * ev) { return tofCoords<0>(ev); }
std::vector<double> TOFCoordsY(AMSEventR * ev) { return tofCoords<1>(ev); }
std::vector<double> TOFCoordsZ(AMSEventR * ev) { return tofCoords<2>(ev); }


