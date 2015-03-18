// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "Geo.h"

double ThetaS   (AMSEventR * ev ){ return  ev->fHeader.ThetaS;       }
double PhiS     (AMSEventR * ev ){ return  ev->fHeader.PhiS;         }
double U_time   (AMSEventR * ev ){ return  ev->UTime();              }
double Livetime (AMSEventR * ev ){ return  ev->LiveTime();           }
double Latitude (AMSEventR * ev ){ return  fabs(ev->fHeader.ThetaM); }

double Rcutoff  (AMSEventR * ev ){
    if(!ev->pParticle(0)) return  -1;
    return ev->pParticle(0)->Cutoff;
}


