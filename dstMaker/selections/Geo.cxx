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

// Do not select first two events of any run
bool notFirstTwo(AMSEventR * ev){ 
    return (ev->UTime() != ev->fHeader.Run) && (ev->UTime()!=ev->fHeader.Run+1);
}

// Do not select events in South Atlantic Anomaly
bool notInSaaCut(AMSEventR * ev){ return saa(ev->fHeader.PhiS, ev->fHeader.ThetaS); }

// Do not select events with a zenithal angle above 25 degrees
bool   zenithCut(AMSEventR * ev){ return  ev->fHeader.Zenith() <= 25;  }

// ??
bool  runtypeCut(AMSEventR * ev){ return  ev->fHeader.RunType > 61442; }


