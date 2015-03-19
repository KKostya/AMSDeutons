// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "TRD.h"

int NTRDclusters(AMSEventR * ev)
{
    int ret = 0;
    for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
    {
        TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
        for(int i = 0;i < trdSegment->NTrdCluster(); i++) ret++;
    }
    return ret;
}

double EdepTRD(AMSEventR * ev)
{
    double ret = 0;
    for(int j = 0; j < ev->pTrdTrack(0)->NTrdSegment(); j++) 
    {
        TrdSegmentR * trdSegment = ev->pTrdTrack(0)->pTrdSegment(j);
        for(int i = 0;i < trdSegment->NTrdCluster(); i++) 
            ret += trdSegment->pTrdCluster(i)->EDep;
    }
    return ret;
}

