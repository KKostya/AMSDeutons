#include "TOF.h"


int NTofClusters(AMSEventR * ev)    { return ev?ev->NTofCluster():0; }
int NTofClustersUsed(AMSEventR * ev){ return ev?(ev->pBeta(0)?ev->pBeta(0)->NTofCluster():0):0; }

// TOF energy deposit
std::vector<double> EdepTOF(AMSEventR * ev)
{
    std::vector<double> ret(4);
    for(int j=0; j<4; j++) ret[j] = 0;
    for(int j=0; j<ev->NTofCluster(); j++)
        ret[(ev->pTofCluster(j)->Layer)-1] = ev->pTofCluster(j)->Edep;
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