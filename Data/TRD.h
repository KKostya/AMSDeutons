#ifndef TRD_H
#define TRD_H

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

int NTRDclusters(AMSEventR * ev);
double EdepTRD(AMSEventR * ev);

#endif //TRD_H
