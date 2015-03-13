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

        



