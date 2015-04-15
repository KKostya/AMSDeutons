#ifndef GEO_H
#define GEO_H

// AMS includes #ifndef _PGTRACK_
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

double ThetaS   (AMSEventR * ev );
double PhiS     (AMSEventR * ev );
double Livetime (AMSEventR * ev );
double Latitude (AMSEventR * ev );
double Rcutoff  (AMSEventR * ev );
int    PhysBPatt(AMSEventR * ev );
int    JMembPatt(AMSEventR * ev );
unsigned long long fStatus(AMSEventR * ev);

#endif //GEO_H
