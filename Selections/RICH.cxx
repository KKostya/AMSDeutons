#include <math.h>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif
#include <amschain.h>

// Local includes
#include "RICH.h"

bool    aRing(AMSEventR * ev) { return ev->NRichRing() >= 1; }
bool  oneRing(AMSEventR * ev) { return ev->NRichRing() == 1; }
bool    noNaF(AMSEventR * ev) { 
    if(!ev->pRichRing(0)) return false;
    return !ev->pRichRing(0)->IsNaF(); 
}

bool photFracG04(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    return anello->getExpectedPhotoelectrons()/anello->getPhotoElectrons()>0.4; 
}

bool photFracL2(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    return anello->getExpectedPhotoelectrons()/anello->getPhotoElectrons()<2; 
}

bool atleastFiveHits(AMSEventR * ev) { 
    if(!ev->pRichRing(0)) return false;
    return ev->pRichRing(0)->getHits() >= 5; 
}

bool betaDisp(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    if(!ev->pParticle(0)) return false;
    if(!ev->pParticle(0)->pBeta()) return false;
    double beta = ev->pParticle(0)->pBeta()->Beta;
    return (beta - anello->getBeta()) / beta < 0.1;
}

bool counts5(AMSEventR * ev) { 
    RichRingR * anello= ev->pRichRing(0);
    if(!anello) return false;
    if(anello->getHits() < 5) return false;

    int totali = ev->NRichHit();
    int  usate = ev->pRichRing(0)->Used;
    int hotspots = 0;
    int usatebis = 0;
    for(int i=0; i<ev->NRichHit(); i++)
    {
        RichHitR * Hit = ev->pRichHit(i);
        if(Hit->UsedInRingNumber(0)) usatebis++;
        if(Hit->IsCrossed()) hotspots++;
    }
    return totali-usate-hotspots < 5;
}

/////////////////////////////////////////////
//////////////// Utils //////////////////////
/////////////////////////////////////////////

std::vector<SubSelection<AMSEventR *> *> richCuts;
std::vector<SubSelection<AMSEventR *> *> GetRICHSelectionsList()
{
    if(richCuts.size() > 0) return richCuts;
    richCuts.push_back(new SubSelection<AMSEventR*>(aRing,       "Not in SAA"       ));
    richCuts.push_back(new SubSelection<AMSEventR*>(oneRing,     "Zenith in 25 deg" ));
    richCuts.push_back(new SubSelection<AMSEventR*>(noNaF,       "Proper RunType"   ));
    richCuts.push_back(new SubSelection<AMSEventR*>(photFracG04, "Proper RunType"   ));
    richCuts.push_back(new SubSelection<AMSEventR*>(photFracL2,  "Proper RunType"   ));
    richCuts.push_back(new SubSelection<AMSEventR*>(atleastFiveHits,  "Proper RunType" ));
    richCuts.push_back(new SubSelection<AMSEventR*>(betaDisp,    "Proper RunType"   ));
    richCuts.push_back(new SubSelection<AMSEventR*>(counts5,     "Proper RunType"   ));
    return richCuts;
}

bool RICHSelection(AMSEventR * event)
{
    bool selection = true;
    std::vector<SubSelection<AMSEventR *> *> cuts =  GetRICHSelectionsList();

    for (int i=0; i<cuts.size(); i++) 
        selection &= cuts[i]->Test(event);
    return selection;
}   

