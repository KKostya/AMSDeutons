#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "Geo.h"
#include "SAA.h"

////////////////////////////////////////////////
/// Geometry selections
////////////////////////////////////////////////

bool notInSaaCut(AMSEventR * ev){ return saa(ev->fHeader.ThetaS, ev->fHeader.PhiS); }
bool   zenithCut(AMSEventR * ev){ return  ev->fHeader.Zenith() <= 25;  }
bool  runtypeCut(AMSEventR * ev){ return  ev->fHeader.RunType > 61442; }

/////////////////////////////////////////////
//////////////// Utils //////////////////////
/////////////////////////////////////////////

std::vector<SubSelection<AMSEventR *> *> geoCuts;
std::vector<SubSelection<AMSEventR *> *> GetGeoSelectionsList()
{
    if(geoCuts.size() > 0) return geoCuts;
    geoCuts.push_back(new SubSelection<AMSEventR*>(notInSaaCut, "Not in SAA"       ));
    geoCuts.push_back(new SubSelection<AMSEventR*>(zenithCut,   "Zenith in 25 deg" ));
    geoCuts.push_back(new SubSelection<AMSEventR*>(runtypeCut,  "Proper RunType"   ));
    return geoCuts;
}

bool GeoSelection(AMSEventR * event)
{
    bool selection = true;
    std::vector<SubSelection<AMSEventR *> *> cuts =  GetGeoSelectionsList();

    for (int i=0; i<cuts.size(); i++) 
        selection &= cuts[i]->Test(event);
    return selection;
}   

