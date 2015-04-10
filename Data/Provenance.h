#ifndef _PROVENANCE__H__
#define _PROVENANCE__H__

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

unsigned int Run  (AMSEventR * ev);
unsigned int Event(AMSEventR * ev);
unsigned int UTime(AMSEventR * ev);
double JMDCTime(AMSEventR * ev);

#endif

