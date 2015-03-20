// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "TOF.h"


int NTofClusters(AMSEventR * ev)    { return ev->NTofCluster(); }
int NTofClustersUsed(AMSEventR * ev){ return ev->pBeta(0)->NTofCluster(); }

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
    if(particle->pBetaH()) beta = particle->pBetaH()->GetBeta();
    if(beta>=1) return beta/(2*beta-1); // WTF
    return beta;
}

