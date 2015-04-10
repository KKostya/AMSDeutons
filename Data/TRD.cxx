#include "TRD.h"

int NTRDclusters(AMSEventR * ev)
{
    if( ev -> pTrdTrack(0) == NULL ) return -1;
    int ret = 0;
    for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
    {
        TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
        for(int i = 0;i < trdSegment->NTrdCluster(); i++) ret++;
    }
    return ret;
}

double ChargeTRD(AMSEventR * ev){
    if( ev -> pTrdTrack(0) == NULL ) return -1;
    return ev->pTrdTrack(0)->Q;
}

double EdepTRD(AMSEventR * ev)
{
    if( ev -> pTrdTrack(0) == NULL ) return -1;
    double ret = 0;
    for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
    {
        TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
        for(int i = 0;i < trdSegment->NTrdCluster(); i++) 
            ret += trdSegment->pTrdCluster(i)->EDep;
    }
    return ret;
}

