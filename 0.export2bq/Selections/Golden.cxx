#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "Golden.h"


////////////////////////////////////////////////
/// Golden selections
////////////////////////////////////////////////

template <int SEVERITY, int FIT>
bool goldenTRACKER(AMSEventR *ev)
{	//chiedo che il fit sui layer interni sia buono
    
    float quality=5-(SEVERITY*10*20/100);
    TrTrackR * traccia=ev->pTrTrack(0);
    if(!traccia) return false;
    int fitID = traccia->iTrTrackPar(1,FIT,1);
    if (fitID < 0 || !traccia->ParExists(fitID)) return false;
    if(traccia->GetNormChisqY(fitID) > 5) return false;
    if(traccia->GetNormChisqX(fitID) > 10) return false;
    return true;
}  

template <int SEVERITY, int FIT>
bool goldenTOF(AMSEventR *ev)
{	//chiedo che i cluster del TOF abbiano un buon match con la traccia
    int c=0;
    if (ev->nParticle()==0) return false;
    TrTrackR* track=ev->pTrTrack(0);
    if(!track) return false;
    int fitID=track->iTrTrackPar(1,FIT,1);
    float LONGCUT[4][10]={  9. , 8. , 8. , 8. , 8. , 8. , 8. , 9.  , 0. , 0.  , 
                           12. , 8. , 8. , 8. , 8. , 8. , 8. , 12. , 0. , 0.  , 
                           12. , 8. , 8. , 8. , 8. , 8. , 8. , 8.  , 8. , 12. , 
                           10. , 8. , 8. , 8. , 8. , 8. , 8. , 10. , 0. , 0.  , };
    float TRANCUT[4][10]={ 13. , 6. , 6. , 6. , 6. , 6. , 6. , 13. , 0. , 0.  , 
                           14. , 6. , 6. , 6. , 6. , 6. , 6. , 14. , 0. , 0.  , 
                           10. , 6. , 6. , 6. , 6. , 6. , 6. , 6.  , 6. , 10. , 
                           14. , 6. , 6. , 6. , 6. , 6. , 6. , 14. , 0. , 0.  ,};
    TofClusterHR* cluster;
    bool good_match=false;
    double tlen;
    AMSPoint pnt;
    AMSDir dir;
    int longit[4]={0,1,1,0};
    int tranit[4]={1,0,0,1};
    double dlong,dtran;
    bool goodlayer[4]={false,false,false,false};
    for(int i=0; i<ev->nTofClusterH();i++) 
    {
        cluster=ev->pTofClusterH(i);
        if(cluster>0)
        {
            int layer=cluster->Layer-1;
            int bar=cluster->Bar-1;
            tlen=track->Interpolate(cluster->Coo[2],pnt,dir,fitID);
            dlong=cluster->Coo[longit[layer]]-pnt[longit[layer]];
            dtran=cluster->Coo[tranit[layer]]-pnt[tranit[layer]];
            if(fabs(dlong)<(LONGCUT[layer][bar])-(SEVERITY*10*LONGCUT[layer][bar]/100) && fabs(dtran)<TRANCUT[layer][bar]-SEVERITY*10*TRANCUT[layer][bar]/100)
                goodlayer[layer]=true;
        }
    }
    
    for(int i=0; i<4; i++)
        if(goodlayer[i]) c++;
    if(c>=3) good_match=true;
    BetaHR *betah=ev->pParticle(0)->pBetaH();
    //if(!betah) return false;
    //   if(betah->IsTkTofMatch()==false) good_match=false;
    return good_match;
}

template <int SEVERITY, int FIT>
bool goldenTRD(AMSEventR* ev) 
{
    int TRDclustersontrack=0;
    if (!ev->pTrdTrack(0)) return false;
    for(int i=0;i<ev->pTrdTrack(0)->NTrdSegment();i++) {
        for(int j=0; j<ev->pTrdTrack(0)->pTrdSegment(i)->NTrdCluster();j++)
            TRDclustersontrack++;}

    TrTrackR* track=ev->pTrTrack(0);
    if(!track) return false;
    int fitID=track->iTrTrackPar(1,FIT,1);
    bool golden=false;
    TrdHTrackR* trd_track;
    for(int i=0;/* i<ev->nTrdHTrack()*/i<1;i++)
    {
        trd_track=ev->pTrdHTrack(i);
        if(trd_track>0)
        {
            int nHits=ev->nTrdRawHit();
            int nHitsonTrack=trd_track->Nhits;
            if(/*(nHitsonTrack/(float)(nHits))>0*/TRDclustersontrack/(double)ev->NTrdCluster()!=10000000000)
            {
                if(trd_track->status>0)
                {
                    AMSPoint pnt;
                    AMSDir dir;
                    TrTrackR* track=ev->pTrTrack(0);
                    track->Interpolate(trd_track->Coo[2],pnt,dir,fitID);

                    Double_t dtx=pnt.x()-trd_track->Coo[0];
                    Double_t dty=pnt.y()-trd_track->Coo[1];
                    if(dtx*dtx+dty*dty<(1.5-(SEVERITY*10*1.5/100))*(1.5-(SEVERITY*10*1.5/100))) golden=true;
                }
            }
        }
    }
    return golden;
}


/////////////////////////////////////////
/////////// Instantiation ///////////////
/////////////////////////////////////////

template bool goldenTRACKER<0,3>(AMSEventR *data);
template bool goldenTOF<0,3>(AMSEventR *data);
template bool goldenTRD<0,3>(AMSEventR *data);
 


