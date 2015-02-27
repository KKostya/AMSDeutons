// std includes
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

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

std::vector<std::pair<std::string, CutFunction> > GetSelections()
{
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
    return selections;
}

typedef void (*DataLogger)(AMSEventR *, std::ostream & output);

void Run   (AMSEventR * ev, std::ostream & output){ output <<  ev->fHeader.Run;   }
void Event (AMSEventR * ev, std::ostream & output){ output <<  ev->fHeader.Event; }
void UTime (AMSEventR * ev, std::ostream & output){ output <<  ev->UTime();       }
void ThetaM(AMSEventR * ev, std::ostream & output){ output <<  ev->fHeader.ThetaM;}

void R(AMSEventR * ev, std::ostream & output)
{
    TrTrackR  * track    = ev->pTrTrack(0);
    if(track) output << track->GetRigidity( track->iTrTrackPar(1,3,1)); else output << 0;
}

void Beta(AMSEventR * ev, std::ostream & output)
{
    ParticleR * particle = ev->pParticle(0);
    if(particle && particle->pBetaH()) output << particle->pBetaH()->GetBeta(); else output << 0;
}

void BetaRICH(AMSEventR * ev, std::ostream & output)
{
    if(ev->pRichRing(0)) output << ev->pRichRing(0)->getBeta(); else output << 0;
}

void LiveTime(AMSEventR * ev, std::ostream & output){output << ev->LiveTime();}
void fStatus(AMSEventR * ev, std::ostream & output){output << ev->fStatus;}

std::vector<std::pair<std::string, DataLogger> > GetDataLoggers()
{
    std::vector<std::pair<std::string, DataLogger> > datalog;

    datalog.push_back(std::make_pair("Run",      Run      ));
    datalog.push_back(std::make_pair("Event",    Event    ));
    datalog.push_back(std::make_pair("UTime",    UTime    ));
    datalog.push_back(std::make_pair("LiveTime", LiveTime ));
    datalog.push_back(std::make_pair("ThetaM",   ThetaM   ));
    datalog.push_back(std::make_pair("fStatus",  fStatus  ));
    datalog.push_back(std::make_pair("R",        R        ));
    datalog.push_back(std::make_pair("Beta",     Beta     ));
    datalog.push_back(std::make_pair("BetaRICH", BetaRICH ));

    return datalog;
}

int main(int argc, char * argv[])
{
    //Processing input options
    int c;
    int entries = 0;
    std::string  inFname;
    std::streambuf * buf = std::cout.rdbuf();
    std::ofstream of;
    while((c = getopt(argc, argv, "o:n:")) != -1) {
        if(c == 'o') { of.open(optarg); buf = of.rdbuf(); }
        if(c == 'n') entries = atoi(optarg);
    }
    if (optind < argc) inFname = std::string(argv[optind++]); else return 1;

    std::ostream output(buf);

    std::cout << "Input file: " << inFname << std::endl;

    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(inFname.c_str());

    //Populating the lists
    std::vector<std::pair<std::string, DataLogger> >  datas      = GetDataLoggers(); 
    std::vector<std::pair<std::string, CutFunction> > selections = GetSelections(); 

    // Printing the header
    std::vector<std::pair<std::string, DataLogger> >::iterator data;
    for (data = datas.begin(); data != datas.end(); ++data)
        output << (*data).first << ',';

    std::vector<std::pair<std::string, CutFunction> >::iterator selection;
    for (selection = selections.begin(); selection != selections.end()-1; ++selection)
        output << (*selection).first << ',';
    output << (*selection).first;

    output << '\n';

     
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    if(entries == 0) entries = ch->GetEntries();
    std::cout << "\n Strating processing " << entries << " events.\n" << std::endl;
    
    for(int ii=0;ii<entries;ii++)
    {
        AMSEventR * ev = ch->GetEvent();


        for (data = datas.begin(); data != datas.end(); ++data) 
        { (*data).second(ev,output); output << ','; }

        for (selection = selections.begin(); selection != selections.end()-1; ++selection)
            output << (*selection).second(ev) << ',';
        output << (*selection).second(ev) << '\n';

        if (ii % 10000 == 0) output.flush(); 
    }
}

        



