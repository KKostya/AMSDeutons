// AMS includes #ifndef _PGTRACK_
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "MC.h"

double GenMomentum(AMSEventR * ev) { return  ev->GetPrimaryMC()->Momentum; }

int GenParID(AMSEventR * ev) { return ev->GetPrimaryMC()->Particle; }

std::vector<float> GenCoo(AMSEventR * ev) 
{ 
    float * coo = ev->GetPrimaryMC()->Coo; 
    return std::vector<float>(coo, coo+3);
}

std::vector<float> GenDir(AMSEventR * ev) 
{ 
    float * dir = ev->GetPrimaryMC()->Dir; 
    return std::vector<float>(dir, dir+3);
}

