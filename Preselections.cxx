#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "PreSelections.h"
#include "SAA.h"

////////////////////////////////////////////////
/// Geometry selections
////////////////////////////////////////////////

bool notInSaaCut(AMSEventR * ev) 
{ return saa(ev->fHeader.ThetaS, ev->fHeader.PhiS); }

bool zenithCut(AMSEventR * ev)  { return  ev->fHeader.Zenith() <= 25; }
bool runtypeCut(AMSEventR * ev) { return  ev->fHeader.RunType > 61442; }

std::vector<SubSelection<AMSEventR *> *> geoCuts;
std::vector<SubSelection<AMSEventR *> *> GetGeoSelectionsList()
{
    if(geoCuts.size() > 0) return geoCuts;
    geoCuts.push_back(new SubSelection<AMSEventR*>(notInSaaCut, "Not in SAA"             ));
    geoCuts.push_back(new SubSelection<AMSEventR*>(zenithCut,   "Zenith in 25 deg"       ));
    geoCuts.push_back(new SubSelection<AMSEventR*>(runtypeCut,  "Proper RunType"         ));
    return geoCuts;
}

bool Quality(Data &data)
{
    bool selection = true;
    std::vector<SubSelection *> cuts =  GetListOfSelections();

    for (int i=0; i<cuts.size(); i++) 
        selection &= (!cuts[i]->Test(data));
    return selection;
}   


////////////////////////////////////////////////
/// MinBias selections
////////////////////////////////////////////////

bool minimumbiasTOF(AMSEventR *ev)
{
    if(ev->nParticle() == 0) return false;
    if(ev->nTofCluster() == 0) return false
    bool goodlayer[4]={false,false,false,false};
    
    for(int ic=0;ic<ev->nTofCluster();ic++)
    {
        TofClusterR * cluster = ev->pTofCluster(ic);
        if(!cluster) continue;

        // 2DO. Rewrite.
        for(int i=7;i<13;i++)
            if((cluster->Status>>i)&1==1) continue;
        if((cluster->Status>>2)&1==1) continue;
        if((cluster->Status>>4)&1==1) continue;

        goodlayer[cluster->Layer-1]=true;
    }
    
    int c=0;
    for(int i=0;i<4;i++) if(goodlayer[i]) c++;
    if(c < 4) return false;
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


std::vector<SubSelection<AMSEventR *> *> minBiasCuts;
std::vector<SubSelection<AMSEventR *> *> GetMinBiasList()
{
    if(minBiasCuts.size() > 0) return minBiasCuts;
    minBiasCuts.push_back(new SubSelection<AMSEventR*>(minimumbiasTOF     , "Minbias TOF"     ));
    minBiasCuts.push_back(new SubSelection<AMSEventR*>(minimumbiasTRIGG   , "Minbias TRIGG"   ));
    minBiasCuts.push_back(new SubSelection<AMSEventR*>(minimumbiasTRD     , "Minbias TRD"     ));
    minBiasCuts.push_back(new SubSelection<AMSEventR*>(minimumbiasTRACKER , "Minbias TRACKER" ));
    return minBiasCuts;
}

////////////////////////////////////////////////
/// Golden selections
////////////////////////////////////////////////


