// std includes
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include <amschain.h>

// local includes
#include "Selections/Geo.h"
#include "Selections/Golden.h"
#include "Selections/MinBias.h"
#include "Selections/Preselect.h"
#include "Selections/RICH.h"

typedef bool (*CutFunction)(AMSEventR *);

bool unbiased(AMSEventR * ev)
{
    Level1R * trig = ev->pLevel1(0);
    return trig && ((trig->PhysBPatt&1) == 1);
}



int main(int argc, char * argv[])
{

    //Processing input options
    int c;
    int entries = 0;
    std::string outFname;
    std::string  inFname;
    while((c = getopt(argc, argv, "o:n:")) != -1) {
        if(c == 'o') outFname = std::string(optarg);
        if(c == 'n') entries = atoi(optarg);
    }
    if(outFname.empty()) outFname = std::string("ntuple.root");
    if (optind < argc) inFname = std::string(argv[optind++]); else return 1;

    std::cout << "Input file: " << inFname << std::endl;
    std::cout << "Output file: " << outFname << std::endl;

    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(inFname.c_str());

    // Preparing work data
    double tempozona[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contasecondi[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contaeventi = 0;

    // 

    std::vector<std::pair<std::string, CutFunction> > selections;

    selections.push_back(std::make_pair("unbias", notFirstTwo));

    selections.push_back(std::make_pair("notFirstTwo", notFirstTwo));
    selections.push_back(std::make_pair("notInSaaCut", notInSaaCut));
    selections.push_back(std::make_pair("zenithCut",   zenithCut));
    selections.push_back(std::make_pair("runtypeCut",  runtypeCut));

    selections.push_back(std::make_pair("minimumbiasTOF", minimumbiasTOF));
    selections.push_back(std::make_pair("minimumbiasTRIGG", minimumbiasTRIGG));
    selections.push_back(std::make_pair("minimumbiasTRD", minimumbiasTRD));
    selections.push_back(std::make_pair("minimumbiasTRACKER", minimumbiasTRACKER));

    selections.push_back(std::make_pair("goldenTOF", goldenTOF<0,3>));
    selections.push_back(std::make_pair("goldenTRD", goldenTRD<0,3>));
    selections.push_back(std::make_pair("goldenTRACKER", goldenTRACKER<0,3>));

    selections.push_back(std::make_pair("aParticle", aParticle));
    selections.push_back(std::make_pair("aTrack", aTrack));
    selections.push_back(std::make_pair("aTRDTrack", aTRDTrack));
    selections.push_back(std::make_pair("oneParticle", oneParticle));
    selections.push_back(std::make_pair("oneTrack", oneTrack));
    selections.push_back(std::make_pair("chargeOne", chargeOne));
    selections.push_back(std::make_pair("downGoing", downGoing));
    selections.push_back(std::make_pair("betaNotCrazy", betaNotCrazy));

    selections.push_back(std::make_pair("aRing", aRing));
    selections.push_back(std::make_pair("oneRing", oneRing));
    selections.push_back(std::make_pair("noNaF", noNaF));
    selections.push_back(std::make_pair("photFracG04", photFracG04));
    selections.push_back(std::make_pair("photFracL2", photFracL2));
    selections.push_back(std::make_pair("atleastFiveHits", atleastFiveHits));
    selections.push_back(std::make_pair("betaDisp", betaDisp));
    selections.push_back(std::make_pair("counts5", counts5));
     
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    if(entries == 0) entries = ch->GetEntries();
    std::cout << "\n Strating processing " << entries << " events.\n" << std::endl;
    for(int ii=0;ii<entries;ii++)
    {
        unsigned int RunNumber;
        unsigned int EventNumber;
        AMSEventR * ev = ch->GetEvent();
    }
}

        



