#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "Geo.h"
#include "SAA.h"

////////////////////////////////////////////////
/// Geometry selections
////////////////////////////////////////////////

bool notFirstTwo(AMSEventR * ev){ 
    return (ev->UTime() != ev->fHeader.Run) && (ev->UTime()!=ev->fHeader.Run+1);
}
bool notInSaaCut(AMSEventR * ev){ return saa(ev->fHeader.PhiS, ev->fHeader.ThetaS); }
bool   zenithCut(AMSEventR * ev){ return  ev->fHeader.Zenith() <= 25;  }
bool  runtypeCut(AMSEventR * ev){ return  ev->fHeader.RunType > 61442; }


