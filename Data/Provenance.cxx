// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "Provenance.h"

unsigned int Run  (AMSEventR * ev){ return ev->Run();   }
unsigned int Event(AMSEventR * ev){ return ev->Event(); }
time_t       UTime(AMSEventR * ev){ return ev->UTime(); }

