// AMS includes #ifndef _PGTRACK_
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

#include "../Selections/SelectionLists.hpp"

SelectionList selections;

unsigned long long selStatus(AMSEventR * ev)
{
    if(selections.size() == 0)
    {
        AddGeoSelections    (selections);
        AddGoldenSelections (selections);
        AddMinBiasSelections(selections);
        AddPreSelections    (selections);
        AddRICHSelections   (selections);
    }

    unsigned long long ret = 0;
    for(int nsel=0; nsel<selections.size(); nsel++)
        if(selections[nsel].second(ev)) 
            ret += 1 << nsel;
    return ret;
}
