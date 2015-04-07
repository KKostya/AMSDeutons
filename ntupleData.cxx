// std includes
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

// ROOT includes
#include "TObjString.h"
#include "TMacro.h"

// AMS includes
#ifndef _PGTRACK_
#define _PGTRACK_
#include "TrTrack.h"
#endif

#include <amschain.h>

// local includes
#include "Selections/SelectionLists.hpp"
#include "Data/RootWriter.hpp"
#include "Data/TOF.h"
#include "Data/Tracker.h"
#include "Data/SelectionStatus.h"
#include "utils/rootUtils.hpp"

double geomag[12]={0,0,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.3};

extern const char *gitversion;

bool DoSelection( AMSEventR * ev,
    SelectionList & selections,
    std::map<std::string, std::pair<long,long> > & counts,
    bool eventPasses)
{
    for(int nsel=0; nsel<selections.size(); nsel++)
    {
        std::string name = selections[nsel].name;
        bool thisPasses = selections[nsel].cutFunction(ev);
        eventPasses = eventPasses && thisPasses;
        if(thisPasses) counts[name].first++;
        if(eventPasses) counts[name].second++;
    }
    return eventPasses;
}


// Extract run tag from filename
void addRunTag( std::map< std::string, long int > &runTag, std::string inFname ){
    std::string runTagStr = (rootUtils::getFileName(inFname)).substr(0,10);
    runTag[ runTagStr ] = rootUtils::stringTo<long int>(runTagStr);
}


void registerSrcFilesInRootuple(){
    std::vector <std::string > files = rootUtils::getFilesInDir(".");
    std::vector <std::string > dataFiles = rootUtils::getFilesInDir("Data");
    std::vector <std::string > selectionFiles = rootUtils::getFilesInDir("Selection");

    files.insert(files.end(), dataFiles.begin(), dataFiles.end());
    files.insert(files.end(), selectionFiles.begin(), selectionFiles.end());
    
    TDirectory *srcDir = gFile -> mkdir("infos/srcFiles");
    gFile -> cd("infos/srcFiles");

    for(int i = 0; i < files.size(); i++){
	string extension = rootUtils::getExtension( files[i] );
	if( extension == "cpp" || extension == "hpp" || extension == "h" || extension == "c" || extension == "C" || extension == "cxx" || extension == "hxx"){
	    TMacro m( files[i].c_str() );
	    m.Write( rootUtils::getFileName(files[i]).c_str() );
	}
    }
  
    gFile -> cd();
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

    std::map< std::string, long int> runTag;
    
    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(inFname.c_str());

    // Checking if MC
    ch->GetEvent(0);
    bool isMC = AMSEventR::Head()->nMCEventg() > 0;
    ch->Rewind();

    // Adding a tag to output file
    addRunTag(runTag, inFname);

    // Creating  output trees
    TFile * File = new TFile(outFname.c_str(), "RECREATE");
    TTree * effTree = new TTree("selections","selections");
    TTree * outTree = new TTree("data","data");

    /////////////////////////////////////////////////////////////////
    // Preparing data writer arrays 
    /////////////////////////////////////////////////////////////////
    ROOTDataList effdata;
    AddProvenanceVariables(effdata, effTree);
    AddGeoVariables       (effdata, effTree);
    AddSelectionVariables (effdata, effTree);

    ROOTDataList data;
    AddProvenanceVariables(data, outTree);
    AddTrackerVariables(data, outTree);
    AddTRDVariables(data, outTree);
    AddTOFVariables(data, outTree);
    
    double BetaRICH, BetaCorr, Mass; 
    outTree->Branch("BetaRICH", &BetaRICH);
    outTree->Branch("BetaCorr", &BetaCorr);
    outTree->Branch("Mass",     &Mass);

    if(isMC)
    {
        std::cout << "MC detected, adding MC variables \n";
        AddMCVariables	  (effdata, effTree);
        AddMCVariables	  (effdata, outTree);
    }

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
        counts[geoSelections[nsel].name] = std::make_pair(0,0);
    for(int nsel=0; nsel<selections.size(); nsel++)
        counts[selections[nsel].name] = std::make_pair(0,0);
    for(int nsel=0; nsel<richSelections.size(); nsel++)
        counts[richSelections[nsel].name] = std::make_pair(0,0);
    
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    if(entries == 0) entries = ch->GetEntries();
    std::cout << "\n Starting processing " << entries << " events.\n" << std::endl;
    for(int ii=0;ii<entries;ii++)
    {
        if( ii%10000 == 0 ) std::cout << "Entry : " << ii << std::endl;
        bool eventPasses = true;
        AMSEventR * ev = ch->GetEvent();

        // Compute and write selection status table
        for(int idat=0; idat<effdata.size(); idat++) effdata[idat](ev);
        effTree->Fill();

        // Looping over geometric/geomagnetinc selections 
        eventPasses = DoSelection(ev, geoSelections, counts, eventPasses);
        // If doesn't pass Geometry/Geography/SAA e.t.c then skip event
        if (!eventPasses) continue;

        // Looping over selections 
        eventPasses = DoSelection(ev, selections, counts, eventPasses);
        if(!eventPasses) continue;
        // Record most of the data
        for(int idat=0; idat<data.size(); idat++) data[idat](ev);

        // Doing RICH selections / updating beta
        BetaCorr = BetaTOF(ev);
        BetaRICH = -1;
        eventPasses = DoSelection(ev, richSelections, counts, eventPasses);
        if (eventPasses) 
        {
            BetaRICH = ev->pRichRing(0)->getBeta();
            BetaCorr = BetaRICH;
        }
        // Mass
        Mass = pow(fabs(pow(fabs(R(ev))*pow((1-pow(BetaCorr,2)),0.5)/BetaCorr,2)),0.5);

        outTree->Fill();
        if(ii%10000==0) outTree->AutoSave();
    }

    std::string runTagListStr;
    for( std::map<std::string,long int>::iterator it = runTag.begin(); it != runTag.end(); it++){
    	runTagListStr += it -> first;
    	runTagListStr += " ";
    }

    File->mkdir("infos");
    File->cd("infos");
    TObjString runTagList( runTagListStr.c_str() );
    runTagList.Write("runTag");

    TObjString selectionBits(GetSelectionNames().c_str());
    selectionBits.Write("selectionBits");

    TObjString gitVersion(gitversion);
    gitVersion.Write("gitVersion");
    registerSrcFilesInRootuple(); 
 
    File->Write();

    //Printing all the selection counts
    std::cout << "\n\n\n";

    for(int nsel=0; nsel<geoSelections.size(); nsel++)
    {
        std::string name = geoSelections[nsel].name;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
    for(int nsel=0; nsel<selections.size(); nsel++)
    {
        std::string name = selections[nsel].name;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
    for(int nsel=0; nsel<richSelections.size(); nsel++)
    {
        std::string name = richSelections[nsel].name;
        std::cout << name << " : " <<counts[name].first << "," << counts[name].second << "\n";
    }
}
