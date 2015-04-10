#include "Geo.h"

double ThetaS   (AMSEventR * ev ){ return  ev->fHeader.ThetaS;       }
double PhiS     (AMSEventR * ev ){ return  ev->fHeader.PhiS;         }
double Livetime (AMSEventR * ev ){ return  ev->LiveTime();           }
double Latitude (AMSEventR * ev ){ return  ev->fHeader.ThetaM; }

double Rcutoff  (AMSEventR * ev )
{
    if(!ev->pParticle(0)) return  -1;
    return ev->pParticle(0)->Cutoff;
}

int PhysBPatt(AMSEventR * ev) 
{
    if(!ev->pLevel1(0)) return -1;
    return ev->pLevel1(0)->PhysBPatt; 
}

int JMembPatt(AMSEventR * ev) 
{
    if(!ev->pLevel1(0)) return -1;
    return ev->pLevel1(0)->JMembPatt;
}

unsigned long long fStatus(AMSEventR * ev) { return ev->fStatus; }

