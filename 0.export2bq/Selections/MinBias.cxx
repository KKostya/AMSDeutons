#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>
#include "TrTrackSelection.h"

// Local includes
#include "MinBias.h"


////////////////////////////////////////////////
/// MinBias selections
////////////////////////////////////////////////

// Ask for at least one good cluster on every layer
bool minimumbiasTOF(AMSEventR *ev)
{
    if(ev->nParticle()   == 0) return false;
    if(ev->nTofClusterH() == 0) return false;
    bool goodlayer[4]={false,false,false,false};
    
    for(int ic=0;ic<ev->nTofClusterH();ic++)
    {
        TofClusterHR * cluster = ev->pTofClusterH(ic);
        if(!cluster) continue;

	// bit3(4)  -> ambig
	// bit5(16) -> BAD((bit9 | bit10) & !bit12))
	// bit8 is ORed over cluster-members
        if(cluster->Status & 0x1f94) continue; // 0b1111110010100
        goodlayer[cluster->Layer-1]=true;
    }
    
    int nGoodLayers = 0;
    for(int i=0;i<4;i++) if(goodlayer[i]) nGoodLayers++;
    if(nGoodLayers < 4) return false;
    return true;
}

//chiedo un numero di TOF trigger <=4	
bool minimumbiasTRIGG(AMSEventR *ev)
{
    Level1R* level1=ev->pLevel1(0);
    if(!level1) return false;
    return (level1->TofFlag1 >= 0  && level1->TofFlag1 < 5);
}

//chiedo un numero di TRDHSegment=2
bool minimumbiasTRD(AMSEventR* ev)
{
    for(int i=0; /*i<ev->nTrdHTrack()*/i<1;i++){
        TrdHTrackR * traccia = ev-> pTrdHTrack(i);
        if(!traccia) continue;
        if(traccia->nTrdHSegment()==2) return true;
    }
    return false;
}

//chiedo che esista almeno un fit sui layer interni
bool minimumbiasTRACKER(AMSEventR *pev) 
{
    if (pev->nTrTrack()<=0) return false;
    for(int i=0;i<pev->nTrTrack();i++) 
    {
        TrTrackR* track = pev->pTrTrack(i);
        if (!track) continue;
        if(track->IsFake()) continue;
        Int_t fitID = track->iTrTrackPar(1, 3, 1);
        if (fitID < 0 || !track->ParExists(fitID)) continue;
        Double_t rgt = fabs(track->GetRigidity (fitID));
        Double_t csq = track->GetNormChisqY(fitID);
        if (rgt == 0 || csq < 0) continue;
        Int_t span = TrTrackSelection::GetSpanFlags(track) & 0xff;
        if (! (span & TrTrackSelection::kMaxInt)) continue;
        return true;
    }
    return false;
}
