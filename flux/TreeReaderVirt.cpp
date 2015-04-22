#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "TKey.h"
#include "TROOT.h"
#include "TChain.h"
#include "TF1.h"

#include "rootUtils.hpp"

#include "TreeReaderVirt.hpp"


TreeReaderVirt::TreeReaderVirt(std::vector<std::string> _data) : maxEntries(0), maxRootFiles(0), data(_data){
}

void TreeReaderVirt::loadChain(){
    std::cout << "TreeReaderVirt::loadChain()" << std::endl;
    ch = new TChain();
    std::cout << "\033[1;31m";
    
    int N = data.size();
    if(maxRootFiles > 0 && maxRootFiles < N) std::cout << "Loading " << maxRootFiles << " on a grand total of  # : " << N << std::endl;
    else std::cout << "Loading all root files, # : " << N << std::endl;

    for(int i = 0;i<N;i++){
	if(maxRootFiles >0 && i >= maxRootFiles) break;
	if(i < 5) std::cout << "root file " << i << " : " << data[i].c_str() << std::endl;
	ch -> Add(data[i].c_str());
    }
    
    std::cout << "\033[0m" << std::endl;

}

void TreeReaderVirt::init(){
    nentriesAfterCuts = 0;
  
    loadChain();

    openOutputFiles();
  
    nentries = ch->GetEntries();
  
    AMSEventR* ev = 0;
    ch->SetBranchAddress("ev.",&ev);

    setBranchStatuses();
  
    std::cout << "End of TreeReaderVirt::init()" << std::endl;
}

void TreeReaderVirt::loopOnEvents(){
    std::cout << "TreeReaderVirt::loopOnEvents()" << std::endl;

    int theCut;

    std::cout << "nentries : " << nentries << std::endl;
    std::cout << "maxEntries : " << maxEntries << std::endl;
    if(maxEntries > 0 && nentries > maxEntries) nentries = maxEntries;

    std::cout << "\033[1;31m" << "Number of entries to read : " << nentries << "\033[0m" << std::endl;
    bool keepEvent;
    for (entry=0 ;entry < nentries;entry++) {
	if( entry%10000 == 0 ) std::cout << "entry   : " << entry   << std::endl;
	
	ch -> GetEntry(entry);

	theCut = cutEvent();
	cut[ theCut ]++;
	if( theCut > 0 ) continue;
	if( process() == false ) continue;
	nentriesAfterCuts++;
    }

    std::cout << "End of TreeReaderVirt::loopOnEvents()" << std::endl;
}

void TreeReaderVirt::openOutputFiles(){
    rootUtils::makeFolder("output");

    TFile* currentFile = gFile;
  
    if( outputFileName == "" ){
	outputFileName = "output/output_";
	outputFileName += rootUtils::dateTime();
	outputFileName += ".root";
    }

    outputFile = new TFile(outputFileName.c_str(),"recreate");

    outputTree = new TTree("tree","tree");
    setOutputBranches();
  
    registerSrcFilesInRootuple();

    if( currentFile ) currentFile -> cd();
}

void TreeReaderVirt::registerSrcFilesInRootuple(){
    std::vector <std::string > files = rootUtils::getFilesInDir(".");
    TDirectory *srcDir = outputFile -> mkdir("src");
    srcDir -> cd();

    for(int i = 0; i < files.size(); i++){
	string extension = rootUtils::getExtension( files[i] );
	if( extension == "cpp" || extension == "hpp" || extension == "h" || extension == "c" || extension == "C" || extension == "cxx" || extension == "hxx"){
	    TMacro m( rootUtils::getFileName(files[i]).c_str() );
	    m.Write( rootUtils::getFileName(files[i]).c_str() );
	}
    }
  
    outputFile -> cd();
    
}

void TreeReaderVirt::writePrivate(){
    outputFile -> cd();

    // for( std::map< std::string, TH1* >::iterator it = h.begin(); it != h.end();  ++it){
    // 	if(it -> second != NULL){
    // 	    it -> second -> Write();
    // 	}
    // }

    // for( std::map< std::string, TH2* >::iterator it = h2.begin(); it != h2.end();  ++it){
    // 	if(it -> second != NULL){
    // 	    it -> second -> Write();
    // 	}
    // }

    // for( std::map< std::string, TGraph* >::iterator it = gr.begin(); it != gr.end();  ++it){
    // 	if(it -> second != NULL){
    // 	    it -> second -> Write(it -> first.c_str());
    // 	}
    // }

    // if( outputTree ) outputTree -> Write();

    // User function write
    write();
}

void TreeReaderVirt::dumpCuts(){
    int nCut = 0;

    for( std::map<int,int>::iterator it = cut.begin(); it != cut.end(); ++it){
	if( it -> first > nCut ) nCut = it -> first;
    }

    std::cout << "Cut number - #entries" << std::endl;
    for(int iCut = 0; iCut <= nCut; iCut++){
	std::cout << iCut << " - " << cut[iCut] << std::endl;
    }
}



