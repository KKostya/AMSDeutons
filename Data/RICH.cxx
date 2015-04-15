#include "RICH.h"

double BetaRICH(AMSEventR * ev ) { 
    if(!ev->pRichRing(0)) return  -1;
    return ev->pRichRing(0)->getBeta();
}
