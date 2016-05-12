#ifndef PRESELECT_H
#define PRESELECT_H
#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

#include "TofRecon.h"

bool aParticle   (AMSEventR * ); 
bool aTrack      (AMSEventR * ); 
bool aTRDTrack   (AMSEventR * ); 
bool oneParticle (AMSEventR * ); 
bool oneTrack    (AMSEventR * );
bool oneTRDTrack    (AMSEventR * ); 
bool chargeOne   (AMSEventR * ); 
bool downGoing   (AMSEventR * ); 
bool betaNotCrazy(AMSEventR * );
bool physicsTrigger(AMSEventR *);
bool basicBetaH(AMSEventR *);
bool isolatedBetaH(AMSEventR *);
bool tofTrackInsideFullSpan(AMSEventR *);
bool tofTrackInsideInnerTracker(AMSEventR *);

template <int N>
bool fitExists(AMSEventR * ); 

#endif //PRESELECT_H
