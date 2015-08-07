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
#include "Data/Ecal.h"
#include "Data/SelectionStatus.h"
#include "Data/3DVariables.h"
#include "utils/rootUtils.hpp"


extern const char *gitversion;


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

    // Opening input file
    AMSChain  * ch = new AMSChain;
    ch->Add(inFname.c_str());

    // Initializing RTI
    AMSSetupR::RTI rti;rti.UseLatest(6);
    TkDBc::UseFinal();
    TRMCFFKEY_DEF::ReadFromFile = 0;
    TRFITFFKEY_DEF::ReadFromFile = 0;
    TRFITFFKEY.magtemp = 0;

    // Checking if MC
    ch->GetEvent(0);
    bool isMC = AMSEventR::Head()->nMCEventg() > 0;
    ch->Rewind();

    // Creating  output trees
    TFile * File = new TFile(outFname.c_str(), "RECREATE");
    TTree * outTree = new TTree("data","data");

    /////////////////////////////////////////////////////////////////
    // Preparing data writer arrays 
    /////////////////////////////////////////////////////////////////
    ROOTDataList data;
    AddProvenanceVariables(data, outTree);
    AddGeoVariables       (data, outTree);
    AddSelectionVariables (data, outTree);
    AddECALVariable       (data, outTree);
    AddTRDVariables       (data, outTree);
    AddTOFVariables       (data, outTree);
    AddTrackerVariables   (data, outTree);
    
    if(isMC)
    {
        std::cout << "MC detected, adding MC variables \n";
        AddMCVariables	  (data, outTree);
    }

    try {
    /////////////////////////////////////////////////////////////////
    // Event loop
    /////////////////////////////////////////////////////////////////
    if(entries == 0) entries = ch->GetEntries();
    std::cout << "\n Starting processing " << entries << " events.\n" << std::endl;
    for(int ii=0;ii<entries;ii++)
    {
        bool eventPasses = true;
        AMSEventR * ev = ch->GetEvent();
        if(!ev) continue;
    
        //That calculates Francesco's 3D variables
        CalculateDistances(ev);

        // Fill the TTree 
        for(int idat=0; idat<data.size(); idat++) data[idat](ev);
        outTree->Fill();

        if( ii%10000 == 0 ) std::cout << "Entry : " << ii << std::endl;
        if(ii%10000==0) outTree->AutoSave();
    }
    } catch (std::string & ex)
    { std::cout << "Exception; " << ex << "\n";}

    File->mkdir("infos");
    File->cd("infos");

    TObjString selectionBits(GetSelectionNames().c_str());
    selectionBits.Write("selectionBits");

    TObjString gitVersion(gitversion);
    gitVersion.Write("gitVersion");

    TObjString inFileName(inFname.c_str());
    inFileName.Write("inputFileName");

    registerSrcFilesInRootuple(); 
 
    File->Write();
}
