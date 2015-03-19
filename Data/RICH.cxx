// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "RICH.h"

double BetaRICH(AMSEventR * ev ) { 
    if(!ev->pRichRing(0)) return  -1;
    return ev->pRichRing(0)->getBeta();
}
