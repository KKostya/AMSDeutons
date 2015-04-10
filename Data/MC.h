#ifndef MC_H
#define MC_H

// AMS includes #ifndef _PGTRACK_
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

double GenMomentum(AMSEventR *);
int GenParID(AMSEventR *);
std::vector<float> GenCoo(AMSEventR * ev);
std::vector<float> GenDir(AMSEventR * ev);

#endif //MC_H
