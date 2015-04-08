#include <amschain.h>
#include "SelectionLists.hpp"

#include "Geo.h"
#include "Preselect.h"
#include "Golden.h"
#include "MinBias.h"
#include "RICH.h"


 
void AddGeoSelections(SelectionList & selections)
{
    selections.push_back( SelectionItem("notFirstTwo", notFirstTwo));
    selections.push_back( SelectionItem("notInSaaCut", notInSaaCut));
    selections.push_back( SelectionItem("zenithCut",   zenithCut));
    selections.push_back( SelectionItem("runtypeCut",  runtypeCut));
}


void AddGoldenSelections(SelectionList & selections)
{
    selections.push_back( SelectionItem("minimumbiasTOF", minimumbiasTOF));
    selections.push_back( SelectionItem("minimumbiasTRIGG", minimumbiasTRIGG));
    selections.push_back( SelectionItem("minimumbiasTRD", minimumbiasTRD));
    selections.push_back( SelectionItem("minimumbiasTRACKER", minimumbiasTRACKER));
}

void AddMinBiasSelections(SelectionList & selections)
{
    selections.push_back( SelectionItem("goldenTOF", goldenTOF<0,3>));
    selections.push_back( SelectionItem("goldenTRD", goldenTRD<0,3>));
    selections.push_back( SelectionItem("goldenTRACKER", goldenTRACKER<0,3>));
}

void AddPreSelections(SelectionList & selections)
{
    selections.push_back( SelectionItem("aParticle", aParticle));
    selections.push_back( SelectionItem("aTrack", aTrack));
    selections.push_back( SelectionItem("aTRDTrack", aTRDTrack));
    selections.push_back( SelectionItem("oneParticle", oneParticle));
    selections.push_back( SelectionItem("oneTrack", oneTrack));
    selections.push_back( SelectionItem("oneTRDTrack", oneTRDTrack));
    selections.push_back( SelectionItem("chargeOne", chargeOne));
    selections.push_back( SelectionItem("downGoing", downGoing));
    selections.push_back( SelectionItem("betaNotCrazy", betaNotCrazy));
}

void AddOldRICHSelections(SelectionList & selections)
{
    selections.push_back( SelectionItem("aRing", aRing));
    selections.push_back( SelectionItem("oneRing", oneRing));
    selections.push_back( SelectionItem("noNaF", noNaF));
    selections.push_back( SelectionItem("photFracG04", photFracG04));
    selections.push_back( SelectionItem("photFracL2", photFracL2));
    // selections.push_back( SelectionItem("atleastFiveHits", atleastFiveHits)); ?? check
    selections.push_back( SelectionItem("betaDisp", betaDisp));
    selections.push_back( SelectionItem("counts5", counts5));
}

void AddRICHSelections(SelectionList & selections)
{
    selections.push_back( SelectionItem("aRing", aRing));
    selections.push_back( SelectionItem("oneRing", oneRing));
    selections.push_back( SelectionItem("noNaF", noNaF));

    selections.push_back( SelectionItem("ringGood",  ringGood  ));
    selections.push_back( SelectionItem("ringClean", ringClean ));
    selections.push_back( SelectionItem("ringProb",  ringProb   ));
    selections.push_back( SelectionItem("ringPMTs",  ringPMTs   ));

    selections.push_back( SelectionItem("ringChargeConsistency", ringChargeConsistency ));
    selections.push_back( SelectionItem("ringPhotoElectrons",    ringPhotoElectrons    ));
    selections.push_back( SelectionItem("ringExpPhe",            ringExpPhe            ));
    selections.push_back( SelectionItem("ringBetaCons",          ringBetaCons          ));
    selections.push_back( SelectionItem("ringNoNaFBorder",         ringNoNaFBorder         ));
}
