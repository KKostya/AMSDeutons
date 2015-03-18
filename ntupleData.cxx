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
#include "Selections/SelectionLists.hpp"
#include "Data/RootWriter.hpp"

double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

bool DoSelection( AMSEventR * ev,
    SelectionList & selections,
    std::map<std::string, std::pair<long,long> > counts,
    bool eventPasses)
{
    for(int nsel=0; nsel<selections.size(); nsel++)
    {
        std::string name = selections[nsel].first;
        bool thisPasses = selections[nsel].second(ev);
        eventPasses = eventPasses && thisPasses;
        if(thisPasses) counts[name].first++;
        if(eventPasses) counts[name].second++;
    }
    return eventPasses;
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

    // Creating an output
    TFile * File = new TFile(outFname.c_str(), "RECREATE");
    TTree * outTree = new TTree("data","data");
    TTree * geoTree = new TTree("dataigeo","datageo");

    /////////////////////////////////////////////////////////////////
    // Preparing data writer arrays 
    /////////////////////////////////////////////////////////////////
    ROOTDataList data;
    AddProvenanceVariables(data, outTree);
    AddGeoVariables(data, outTree);
    AddTrackerVariables(data, outTree);
     
    // Preparing work data
    double tempozona[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contasecondi[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int contaeventi = 0;

    /////////////////////////////////////////////////////////////////
    // Creating selections arrays
    /////////////////////////////////////////////////////////////////
    SelectionList geoSelections;
    AddGeoSelections    (geoSelections);

    SelectionList selections;
    AddGoldenSelections (selections);
    AddMinBiasSelections(selections);
    AddPreSelections    (selections);

    SelectionList richSelections;
    AddRICHSelections   (richSelections);

    std::map<std::string, std::pair<long,long> > counts;
    for(int nsel=0; nsel<geoSelections.size(); nsel++)
        counts[geoSelections[nsel].first] = std::make_pair(0,0);
    for(int nsel=0; nsel<selections.size(); nsel++)
        counts[selections[nsel].first] = std::make_pair(0,0);
    for(int nsel=0; nsel<richSelections.size(); nsel++)
        counts[richSelections[nsel].first] = std::make_pair(0,0);
    
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    if(entries == 0) entries = ch->GetEntries();
    std::cout << "\n Starting processing " << entries << " events.\n" << std::endl;
    for(int ii=0;ii<entries;ii++)
    { 
        bool eventPasses = true;
        AMSEventR * ev = ch->GetEvent();

        // Trigger part
        //Level1R * trig = ev->pLevel1(0);
        //if(trig && ((trig->PhysBPatt&1) == 1)) data.Unbias=1; else data.Unbias=0;
       
        // Looping over geometric/geomagnetinc selections 
        eventPasses = DoSelection(ev, geoSelections, counts, eventPasses);
        // If doesn't pass Geometry/Geography/SAA e.t.c then skip event
        if (!eventPasses) continue;

        //for(int i=0;i<12;i++){
        //    double geo= geomag[i]  ;
        //    double geo2=/*(i+1)/(double)10*/geomag[i+1];
        //    if(fabs(ev->fHeader.ThetaM)>geo && fabs(ev->fHeader.ThetaM)<geo2) 
        //        datageo.zonageo = i;
        //    else 
        //        tempozona[i]=ev->UTime();
        //}
        //geoTree->Fill();

        // Looping over selections 
        eventPasses = DoSelection(ev, selections, counts, eventPasses);
        if(!eventPasses) continue;

        // That records the data
        for(int idat=0; idat<data.size(); idat++) data[idat](ev);

//        // Looping over rich selections 
//        eventPasses = DoSelection(ev, richSelections, counts, eventPasses);
//        if (eventPasses) 
//        {
//            data.BetaRICH = ev->pRichRing(0)->getBeta();
//            data.Betacorr = data.BetaRICH;
//        }
//
//        // Mass
//        data.Massa = pow(fabs(pow(fabs(data.R)*pow((1-pow(data.Betacorr,2)),0.5)/data.Betacorr,2)),0.5);

        outTree->Fill();
        if(ii%10000==0) outTree->AutoSave();
    }
    File->Write();

    //Printing all the selection counts
    for(int nsel=0; nsel<geoSelections.size(); nsel++)
    {
        std::string name = geoSelections[nsel].first;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
    for(int nsel=0; nsel<selections.size(); nsel++)
    {
        std::string name = selections[nsel].first;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
    for(int nsel=0; nsel<richSelections.size(); nsel++)
    {
        std::string name = richSelections[nsel].first;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
}

