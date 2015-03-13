#include "Geo.h"
#include "Golden.h"
#include "MinBias.h"
#include "RICH.h"

void AddGeoSelections(SelectionList & selections)
{
    selections.push_back(std::make_pair("notFirstTwo", notFirstTwo));
    selections.push_back(std::make_pair("notInSaaCut", notInSaaCut));
    selections.push_back(std::make_pair("zenithCut",   zenithCut));
    selections.push_back(std::make_pair("runtypeCut",  runtypeCut));
}


void AddGoldenSelections(SelectionList & selections)
{
    selections.push_back(std::make_pair("minimumbiasTOF", minimumbiasTOF));
    selections.push_back(std::make_pair("minimumbiasTRIGG", minimumbiasTRIGG));
    selections.push_back(std::make_pair("minimumbiasTRD", minimumbiasTRD));
    selections.push_back(std::make_pair("minimumbiasTRACKER", minimumbiasTRACKER));
}

void AddMinBiasSelections(SelectionList & selections)
{
    selections.push_back(std::make_pair("goldenTOF", goldenTOF<0,3>));
    selections.push_back(std::make_pair("goldenTRD", goldenTRD<0,3>));
    selections.push_back(std::make_pair("goldenTRACKER", goldenTRACKER<0,3>));
}

void AddPreSelections(SelectionList & selections)
{
    selections.push_back(std::make_pair("aParticle", aParticle));
    selections.push_back(std::make_pair("aTrack", aTrack));
    selections.push_back(std::make_pair("aTRDTrack", aTRDTrack));
    selections.push_back(std::make_pair("oneParticle", oneParticle));
    selections.push_back(std::make_pair("oneTrack", oneTrack));
    selections.push_back(std::make_pair("chargeOne", chargeOne));
    selections.push_back(std::make_pair("downGoing", downGoing));
    selections.push_back(std::make_pair("betaNotCrazy", betaNotCrazy));
}

void AddOldRICHSelections(SelectionList & selections)
{
    selections.push_back(std::make_pair("aRing", aRing));
    selections.push_back(std::make_pair("oneRing", oneRing));
    selections.push_back(std::make_pair("noNaF", noNaF));
    selections.push_back(std::make_pair("photFracG04", photFracG04));
    selections.push_back(std::make_pair("photFracL2", photFracL2));
    selections.push_back(std::make_pair("atleastFiveHits", atleastFiveHits));
    selections.push_back(std::make_pair("betaDisp", betaDisp));
    selections.push_back(std::make_pair("counts5", counts5));
}

void AddRICHSelections(SelectionList & selections)
{
    selections.push_back(std::make_pair("aRing", aRing));
    selections.push_back(std::make_pair("oneRing", oneRing));
    selections.push_back(std::make_pair("noNaF", noNaF));

    selections.push_back(std::make_pair("ringGood",  ringGood  );
    selections.push_back(std::make_pair("ringClean", ringClean );
    selections.push_back(std::make_pair("ringProb",  ringProb   );
    selections.push_back(std::make_pair("ringPMTs",  ringPMTs   );

    selections.push_back(std::make_pair("ringChargeConsistency", ringChargeConsistency );
    selections.push_back(std::make_pair("ringPhotoElectrons",    ringPhotoElectrons    );
    selections.push_back(std::make_pair("ringExpPhe",            ringExpPhe            );
    selections.push_back(std::make_pair("ringBetaCons",          ringBetaCons          );
    selections.push_back(std::make_pair("ringNaFBorder",         ringNaFBorder         );
}
